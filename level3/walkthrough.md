# Level 3

like the previous level we have a benary file `level3` when we excute it wait for input and print it.

```c
level3@RainFall:~$ ./level3
can hack me
can hack me
level3@RainFall:~$

```

let check the binary file withh gdb and see what is going on

```c
Dump of assembler code for function main:
   0x0804851a <+0>:	push   ebp
   0x0804851b <+1>:	mov    ebp,esp
   0x0804851d <+3>:	and    esp,0xfffffff0
   0x08048520 <+6>:	call   0x80484a4 <v>
   0x08048525 <+11>:	leave
   0x08048526 <+12>:	ret
End of assembler dump.

```

we can see that the main function call the function `v` so let check it

```c
(gdb) disassemble v
Dump of assembler code for function v:
   0x080484a4 <+0>:	push   ebp
   0x080484a5 <+1>:	mov    ebp,esp
   0x080484a7 <+3>:	sub    esp,0x218
   0x080484ad <+9>:	mov    eax,ds:0x8049860
   0x080484b2 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x080484b6 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x080484be <+26>:	lea    eax,[ebp-0x208]
   0x080484c4 <+32>:	mov    DWORD PTR [esp],eax
   0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484cc <+40>:	lea    eax,[ebp-0x208]
   0x080484d2 <+46>:	mov    DWORD PTR [esp],eax
   0x080484d5 <+49>:	call   0x8048390 <printf@plt>
   0x080484da <+54>:	mov    eax,ds:0x804988c
   0x080484df <+59>:	cmp    eax,0x40
   0x080484e2 <+62>:	jne    0x8048518 <v+116>
   0x080484e4 <+64>:	mov    eax,ds:0x8049880
   0x080484e9 <+69>:	mov    edx,eax
   0x080484eb <+71>:	mov    eax,0x8048600
   0x080484f0 <+76>:	mov    DWORD PTR [esp+0xc],edx
   0x080484f4 <+80>:	mov    DWORD PTR [esp+0x8],0xc
   0x080484fc <+88>:	mov    DWORD PTR [esp+0x4],0x1
   0x08048504 <+96>:	mov    DWORD PTR [esp],eax
   0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
   0x0804850c <+104>:	mov    DWORD PTR [esp],0x804860d
   0x08048513 <+111>:	call   0x80483c0 <system@plt>
   0x08048518 <+116>:	leave
   0x08048519 <+117>:	ret
End of assembler dump.

```

```c
(gdb) x/s 0x8048600
0x8048600:	 "Wait what?!\n"
(gdb) x/s 0x804860d
0x804860d:	 "/bin/sh"
```

as you see they read input with `fgets` and print it with `printf` and then they check if the input is 0x40 = 64 bytes, if equal they print with `fwrite` **Wait what?!** and then call `system` with the string `/bin/sh` else they leave the function.

so in this level we need to assign 64bit to the address `0x8049880` to get the shell.

we cant use `fgets` to do a buffer overflow because it check the input size and if it is bigger than 0x200 it will stop reading and return so we need to use `printf` to do the buffer overflow : **_format string attack_**.

[man 3 printf](https://man7.org/linux/man-pages/man3/printf.3.html) in Bug section :

**Code such as `printf(foo);` often indicates a bug, since foo may
contain a % character. If foo comes from untrusted user input,
it may contain %n, causing the printf() call to write to memory
and creating a security hole.**

in printf we had a `%n` that will write to memory, `%x` that print the value in hex , let check if we can use it.

```c
level3@RainFall:~$ ./level3
AAAABBBBCCCC %x %x %x %x %x %x
AAAABBBBCCCC 200 b7fd1ac0 b7ff37d0 41414141 42424242 43434343
```

let go in gdb and see what is going on
