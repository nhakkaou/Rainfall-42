#include <stdio.h>

int main(int ac, char **av)
{
    FILE *fd = fopen("/home/user/end/.pass", 'r');
    char *tmp;
    for (int i = 33; i > 0; i--)
        tmp[i] = '\0';

    if (fd || ac != 2)
        return (1);
    else
    {
        int a = fread(tmp, 0x1, 0x42, fd);
        int b = atoi(av[1]);
        tmp[b * 1 + 0x18] = '\0';
        fread(tmp, 0x1, 0x42, fd);
        if (strcmp(av[1], tmp) == 0)
            exec("/bin/bash");
    }
    return (0);
}