### main

``` bash
(gdb) disass main
Dump of assembler code for function main:
   0x0804847c <+0>:     push   %ebp
   0x0804847d <+1>:     mov    %esp,%ebp
   0x0804847f <+3>:     and    $0xfffffff0,%esp
   0x08048482 <+6>:     sub    $0x20,%esp
   0x08048485 <+9>:     movl   $0x40,(%esp)
   0x0804848c <+16>:    call   0x8048350 <malloc@plt>
   0x08048491 <+21>:    mov    %eax,0x1c(%esp)
   0x08048495 <+25>:    movl   $0x4,(%esp)
   0x0804849c <+32>:    call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:    mov    %eax,0x18(%esp)
   0x080484a5 <+41>:    mov    $0x8048468,%edx
   0x080484aa <+46>:    mov    0x18(%esp),%eax
   0x080484ae <+50>:    mov    %edx,(%eax)
   0x080484b0 <+52>:    mov    0xc(%ebp),%eax
   0x080484b3 <+55>:    add    $0x4,%eax
   0x080484b6 <+58>:    mov    (%eax),%eax
   0x080484b8 <+60>:    mov    %eax,%edx
   0x080484ba <+62>:    mov    0x1c(%esp),%eax
   0x080484be <+66>:    mov    %edx,0x4(%esp)
   0x080484c2 <+70>:    mov    %eax,(%esp)
   0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:    mov    0x18(%esp),%eax
   0x080484ce <+82>:    mov    (%eax),%eax
   0x080484d0 <+84>:    call   *%eax
   0x080484d2 <+86>:    leave
   0x080484d3 <+87>:    ret
End of assembler dump.
```

### Key Points:
1. **Function Prologue (Setup Stack Frame)**:
   ```assembly
   0x0804847c <+0>:     push   %ebp
   0x0804847d <+1>:     mov    %esp,%ebp
   0x0804847f <+3>:     and    $0xfffffff0,%esp
   0x08048482 <+6>:     sub    $0x20,%esp
   ```
   - **push %ebp**: Push the base pointer to save the previous stack frame.
   - **mov %esp, %ebp**: Set up the base pointer to the current stack pointer, creating a new stack frame.
   - **and $0xfffffff0, %esp**: Align the stack pointer to a multiple of 16, a common practice to maintain stack alignment.
   - **sub $0x20, %esp**: Allocate space on the stack (32 bytes) for local variables.

2. **Calling `malloc` for Memory Allocation**:
   ```assembly
   0x08048485 <+9>:     movl   $0x40,(%esp)
   0x0804848c <+16>:    call   0x8048350 <malloc@plt>
   0x08048491 <+21>:    mov    %eax,0x1c(%esp)
   ```
   - **movl $0x40, (%esp)**: Push the argument `0x40` (64 bytes) to the stack, which will be passed to `malloc`.
   - **call 0x8048350 <malloc@plt>**: Call `malloc` to allocate 64 bytes of memory. The return address of the function is stored in the `PLT` (Procedure Linkage Table).
   - **mov %eax, 0x1c(%esp)**: Store the return value (pointer to the allocated memory) in a local variable on the stack.

3. **Calling `malloc` Again for a Smaller Allocation**:
   ```assembly
   0x08048495 <+25>:    movl   $0x4,(%esp)
   0x0804849c <+32>:    call   0x8048350 <malloc@plt>
   0x080484a1 <+37>:    mov    %eax,0x18(%esp)
   ```
   - Similar to the previous call, but this time allocating only 4 bytes of memory (`0x4`).
   - The pointer to this memory is stored in a local variable.

4. **Writing Data to Allocated Memory**:
   ```assembly
   0x080484a5 <+41>:    mov    $0x8048468,%edx
   0x080484aa <+46>:    mov    0x18(%esp),%eax
   0x080484ae <+50>:    mov    %edx,(%eax)
   ```
   - **mov $0x8048468, %edx**: Load the address `0x8048468` into `edx` (this could be a string or data to be written).
   - **mov 0x18(%esp), %eax**: Load the pointer from the previous `malloc` allocation (4 bytes) into `eax`.
   - **mov %edx, (%eax)**: Write the value `0x8048468` (perhaps an address or data) to the allocated memory at the address in `eax`.

5. **Calling `strcpy`**:
   ```assembly
   0x080484b0 <+52>:    mov    0xc(%ebp),%eax
   0x080484b3 <+55>:    add    $0x4,%eax
   0x080484b6 <+58>:    mov    (%eax),%eax
   0x080484b8 <+60>:    mov    %eax,%edx
   0x080484ba <+62>:    mov    0x1c(%esp),%eax
   0x080484be <+66>:    mov    %edx,0x4(%esp)
   0x080484c2 <+70>:    mov    %eax,(%esp)
   0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
   ```
   - **mov 0xc(%ebp), %eax**: Load the address of the first command-line argument (passed to the program) into `eax`.
   - **add $0x4, %eax**: Move to the second argument (in the stack frame).
   - **mov (%eax), %eax**: Dereference the pointer to get the actual value.
   - **mov %eax, %edx**: Move the value into `edx` to pass as an argument.
   - **mov 0x1c(%esp), %eax**: Load the pointer from the first `malloc` into `eax`.
   - **call 0x8048340 <strcpy@plt>**: Call `strcpy`, copying the string from the first argument into the memory allocated earlier.

6. **Calling the Function Pointer**:
   ```assembly
   0x080484ca <+78>:    mov    0x18(%esp),%eax
   0x080484ce <+82>:    mov    (%eax),%eax
   0x080484d0 <+84>:    call   *%eax
   ```
   - **mov 0x18(%esp), %eax**: Load the pointer to the function (perhaps `exit()`) into `eax`.
   - **mov (%eax), %eax**: Dereference the pointer to get the function address.
   - **call *%eax**: Call the function at the address in `eax`.

7. **Function Epilogue**:
   ```assembly
   0x080484d2 <+86>:    leave
   0x080484d3 <+87>:    ret
   ```
   - **leave**: Clean up the stack frame (restore `%esp` and `%ebp`).
   - **ret**: Return from the `main` function.

- The program first allocates memory, stores values in that memory, and then calls `strcpy` to copy a string to that memory.
- The last part calls a function pointer (which could be `exit()` or another function), and this function is determined by the memory content at the address passed to `strcpy`.

### m

``` bash
(gdb) disass m
Dump of assembler code for function m:
   0x08048468 <+0>:     push   %ebp
   0x08048469 <+1>:     mov    %esp,%ebp
   0x0804846b <+3>:     sub    $0x18,%esp
   0x0804846e <+6>:     movl   $0x80485d1,(%esp)
   0x08048475 <+13>:    call   0x8048360 <puts@plt>
   0x0804847a <+18>:    leave
   0x0804847b <+19>:    ret
End of assembler dump.
```


### Disassembly Breakdown:

```assembly
0x08048468 <+0>:     push   %ebp
0x08048469 <+1>:     mov    %esp,%ebp
0x0804846b <+3>:     sub    $0x18,%esp
```
- **push %ebp**: Save the base pointer of the previous stack frame.
- **mov %esp, %ebp**: Set up a new stack frame by moving the stack pointer to the base pointer.
- **sub $0x18, %esp**: Allocate space on the stack for local variables. In this case, it reserves 24 bytes.

```assembly
0x0804846e <+6>:     movl   $0x80485d1,(%esp)
0x08048475 <+13>:    call   0x8048360 <puts@plt>
```
- **movl $0x80485d1, (%esp)**: Place the address `0x80485d1` on the stack. This is likely a string literal or memory address.
- **call 0x8048360 <puts@plt>**: Call the `puts()` function, which is used to print a string. The address placed on the stack is the argument passed to `puts()`, so it will print the string at `0x80485d1`.

```assembly
0x0804847a <+18>:    leave
0x0804847b <+19>:    ret
```
- **leave**: Clean up the stack by restoring the previous stack pointer and base pointer.
- **ret**: Return from the function.

### Explanation:
- The function `m` prints a string by calling `puts()` with the address `0x80485d1`. The value `0x80485d1` refers to a string, and `puts()` will print the contents of that string.
- After printing, the function finishes by cleaning up the stack and returning.

- The function `m` doesn't do much other than printing a string located at `0x80485d1`.
- You can find the exact string by looking at the memory address `0x80485d1`, likely located in the `.data` section of the binary.

### n

``` bash
(gdb) disass n
Dump of assembler code for function n:
   0x08048454 <+0>:     push   %ebp
   0x08048455 <+1>:     mov    %esp,%ebp
   0x08048457 <+3>:     sub    $0x18,%esp
   0x0804845a <+6>:     movl   $0x80485b0,(%esp)
   0x08048461 <+13>:    call   0x8048370 <system@plt>
   0x08048466 <+18>:    leave
   0x08048467 <+19>:    ret
End of assembler dump.
```

```assembly
0x08048454 <+0>:     push   %ebp
0x08048455 <+1>:     mov    %esp,%ebp
0x08048457 <+3>:     sub    $0x18,%esp
```
- **push %ebp**: Save the previous base pointer (of the calling function) onto the stack.
- **mov %esp, %ebp**: Set up a new stack frame, so the base pointer points to the current stack pointer.
- **sub $0x18, %esp**: Allocate space on the stack for local variables. It reserves 24 bytes.

```assembly
0x0804845a <+6>:     movl   $0x80485b0,(%esp)
0x08048461 <+13>:    call   0x8048370 <system@plt>
```
- **movl $0x80485b0, (%esp)**: The address `0x80485b0` is placed on the stack, which most likely points to a string (probably a shell command or system call).
- **call 0x8048370 <system@plt>**: The `system()` function is called. It executes the command pointed to by the address `0x80485b0`. This will run the string as a shell command.

```assembly
0x08048466 <+18>:    leave
0x08048467 <+19>:    ret
```
- **leave**: Cleans up the stack by restoring the previous stack pointer and base pointer.
- **ret**: Returns control to the calling function.

### Explanation:
- The function `n` calls the `system()` function with a command that is located at the address `0x80485b0`. This address likely points to a string in memory (possibly a shell command).
- The `system()` function will execute that command as if it were run in the shell.
- After executing the system command, the function cleans up and returns.
    