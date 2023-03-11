int main(int ac, char **av)
{
    int tmp = atoi(av[1]);
    char *t;
    if (tmp <= 9)
    {
        int size = tmp << 2;
        memcpy(t, av[2], size);
        if (tmp == 0x574f4c46)
            exec("/bin/sh");
        return (0);
    }
    else
        return (1);
}