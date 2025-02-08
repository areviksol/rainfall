The program allocates **64 bytes** on the heap using `malloc(64)`, then copies the contents of `argv[1]` into this allocated memory using `strcpy`. Additionally, another heap allocation (`malloc(4)`) is made to store a function pointer, which points to a function `m()`. This function, however, only calls `puts()` and does nothing useful.  

The program **calls the function stored in the second malloc'd buffer** (which initially points to `m()`), but this can be exploited.  

### Breakdown of the Call:
1. **Heap Allocation:**  
   - `malloc(64)`, storing its pointer at `0x1c(%esp)`.  
   - `malloc(4)`, storing its pointer at `0x18(%esp)`.  

2. **Function Pointer Setup:**  
   - `0x8048468` (which is `m()`) is stored inside the second allocated buffer (`0x18(%esp)`).  

3. **Copying User Input:**  
   - `strcpy(argv[1], malloc(64))` → This allows a buffer overflow if `argv[1]` is larger than 64 bytes.  

4. **Function Call via Indirect Pointer:**  
   - The program **loads the function pointer from the heap** (`mov (%eax), %eax`).  
   - It **calls the function stored there** (`call *%eax`).  

### Exploit Opportunity:  

If we **overwrite the function pointer stored in `0x18(%esp)`** with the address of `n()`, we can execute it instead of `m()`. Since `n()` contains a call to `system()`, this can be leveraged for command execution.
However, there is another function, `n()`, which contains a call to `system()`, but it is **never directly called** in the program.  

Our goal is to **exploit the heap allocation** and modify the function pointer so that when `m()` is supposed to execute, it instead **calls `n()`**, giving us control over execution.

strcpy does not check for the destination buffer size, meaning if the source string is larger than the destination buffer, it overwrites adjacent memory.

The offset is 72 

``` bash
Starting program: /home/user/level6/level6 $(python -c "print('A'*72)")

Program received signal SIGSEGV, Segmentation fault.
0x08004141 in ?? ()

level6@RainFall:~$ ./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
bash