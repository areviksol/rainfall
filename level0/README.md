
# 1.
``` gdb
    (gdb) disass main (the whole disasembled code in main.asm file)
```
#Explaination

###### **1. Function Prologue**

```asm
0x08048ec0 <+0>:     push   %ebp
0x08048ec1 <+1>:     mov    %esp,%ebp
0x08048ec3 <+3>:     and    $0xfffffff0,%esp
0x08048ec6 <+6>:     sub    $0x20,%esp
```

- **`push %ebp`**: Saves the old base pointer on the stack.
- **`mov %esp, %ebp`**: Sets the current stack pointer as the base pointer for the function.
- **`and $0xfffffff0, %esp`**: Aligns the stack pointer to a 16-byte boundary (important for performance on some architectures).
- **`sub $0x20, %esp`**: Reserves 32 bytes of space on the stack for local variables.

---

###### **2. Process Input Arguments**
```asm
0x08048ec9 <+9>:     mov    0xc(%ebp),%eax
0x08048ecc <+12>:    add    $0x4,%eax
0x08048ecf <+15>:    mov    (%eax),%eax
0x08048ed1 <+17>:    mov    %eax,(%esp)
0x08048ed4 <+20>:    call   0x8049710 <atoi>
```

- This part processes the input arguments to the program:
  1. **`mov 0xc(%ebp), %eax`**: Loads the second function argument (address of `argv`) into `eax`.
  2. **`add $0x4, %eax`**: Moves to the first command-line argument (`argv[1]`).
  3. **`mov (%eax), %eax`**: Dereferences `argv[1]` to get its value (a string pointer).
  4. **`mov %eax, (%esp)`**: Prepares the argument for the `atoi` function.
  5. **`call <atoi>`**: Converts the string from `argv[1]` to an integer.

---

###### **3. Compare Input Value**
```asm
0x08048ed9 <+25>:    cmp    $0x1a7,%eax
0x08048ede <+30>:    jne    0x8048f58 <main+152>
```

- **`cmp $0x1a7, %eax`**: Compares the converted input value with `0x1a7` (decimal 423).
- **`jne 0x8048f58`**: If the value is not `0x1a7`, jump to an error-handling part of the code.

---

###### **4. Execute Program Logic**
```asm
0x08048ee0 <+32>:    movl   $0x80c5348,(%esp)
0x08048ee7 <+39>:    call   0x8050bf0 <strdup>
```

- If the input value is correct (`0x1a7`):
  - **`movl $0x80c5348, (%esp)`**: Passes a hardcoded string (likely a command or filename) to `strdup`.
  - **`call <strdup>`**: Duplicates the string.

---

###### **5. Change Process Privileges**
```asm
0x08048f21 <+97>:    call   0x8054700 <setresgid>
0x08048f3d <+125>:   call   0x8054690 <setresuid>
```

- These calls set the real, effective, and saved group/user IDs:
  - **`setresgid`**: Changes the group ID of the process.
  - **`setresuid`**: Changes the user ID of the process.

This is typically done to escalate privileges (e.g., to root) if the binary is running as a privileged user.

---

###### **6. Execute a Command**
```asm
0x08048f4a <+138>:   movl   $0x80c5348,(%esp)
0x08048f51 <+145>:   call   0x8054640 <execv>


```

- **`movl $0x80c5348, (%esp)`**: Prepares the hardcoded command.
``` bash
(gdb) x/s 0x80c5348
0x80c5348:       "/bin/sh"
```
- **`call <execv>`**: Executes the command, replacing the current process image.

---

###### **7. Error Handling**
```asm
0x08048f58 <+152>:   mov    0x80ee170,%eax
0x08048f5d <+157>:   mov    %eax,%edx
0x08048f78 <+184>:   call   0x804a230 <fwrite>
```

- If the input is incorrect, this branch executes:
  - Loads and prints an error message using `fwrite`.

---

###### **8. Function Epilogue**
```asm
0x08048f80 <+192>:   mov    $0x0,%eax
0x08048f85 <+197>:   leave  
0x08048f86 <+198>:   ret
```

- **`mov $0x0, %eax`**: Sets the return value of the function to `0`.
- **`leave`**: Restores the base pointer and stack pointer.
- **`ret`**: Returns control to the caller.

---

###### **Summary**
This program:
1. Takes an integer as input (`argv[1]`).
2. Compares it to `0x1a7` (423).
3. If the input matches:
   - Prepares and executes a command.
   - Changes user/group IDs to escalate privileges.
4. If the input doesn't match, it prints an error and exits.


# 2. By passing 423 as the firt argument, the program calls setuid, getuid and use execv to start a new /bin/sh process.

``` bash
level0@RainFall:~$ ./level0 423
$ 
```
# 3. 
``` bash

$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
# 4. 
``` bash
$ su level1
Password: 
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level1/level1

```