#include <stdio.h>
#include <stdlib.h>

char *p(char *s, char *str)
{
    char buffer[4096];

    puts(str);
    read(0, buffer, 4096);
    strchr(buffer, '\n') = 0;
    return (strncpy(s, buffer, 20));
}

char *pp(char *buffer)
{
    char b[20];
    char a[20];
    unsigned int len;

    p(a, " - ");
    p(b, " - ");
    strcpy(buffer, a);
    /*
        repnz  scas al,BYTE PTR es:[edi]
        mov    eax,ecx
        not    eax
        sub    eax,0x1
    */
    len = strlen(buffer);
    /*
        add	   eax,DWORD PTR [ebp+0x8]
        movzx  edx,WORD PTR [ebx]
        mov    WORD PTR [eax],dx
    */
    buffer[len] = ' ';
    buffer[len + 1] = 0;
    return (strcat(buffer, b));
}
int main(int ac, char **av)
{
    char tmp[42]; // 0x40 - 0x16
    pp(tmp);
    puts(tmp);
    return (0);
}