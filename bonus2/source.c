int Language = 0;

int greetuser(char *tmp)
{
    char *h = "Hello ";
    if (Language == 1)
        h = "Hyvää päivää ";
    if (Language == 2)
        h = "Goedemiddag! ";

    concat(tmp, h);
    puts(tmp);
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 3)
    {
        char *tmp;
        int a;
        bzero(tmp, 0x13); // 19
        strncpy(tmp, av[1], 40);
        strncpy(tmp + 0x28, av[2], 32);
        char *env = getenv('LANG');
        if (!env)
        {
        }
        else
        {
            if (memcmp(env, "fi", 2) == 0)

                Language = 1;

            if (memcmp(env, "nl", 2) == 0)

                Language = 2;

            for (int i = 19; i > 0; i--)
            {
                // replace this buufer in the tmp by 1 <---
                // 0xbffff630:	0x41414141	0x41414141	0x00000041	0x00000000
                // 0xbffff640:	0x00000000	0x00000000	0x00000000	0x00000000
                // 0xbffff650:	0x00000000	0x00000000	0x42424242	0x42424242
                // 0xbffff660:	0x00000000	0x00000000	0x00000000	0x00000000
                // 0xbffff670:	0x00000000	0x00000000	0x00000000	0xb7e5ec73
                // 0xbffff680:	0x41414141	0x41414141	0x00000041	0x00000000
                // 0xbffff690:	0x00000000	0x00000000	0x00000000	0x00000000
                // 0xbffff6a0:	0x00000000	0x00000000	0x42424242	0x42424242
                // 0xbffff6b0:	0x00000000	0x00000000	0x00000000	0x00000000
                // 0xbffff6c0:	0x00000000	0x00000000	0x00000000
            }
            return (greetuser(tmp));
        }
    }
    return (1);
}
