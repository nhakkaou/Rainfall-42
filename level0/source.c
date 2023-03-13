int main(int ac, char **av)
{
    int iVar1;
    iVar1 = atoi(av[1]);
    if (iVar1 == 0x1a7) // 423
        execv("/bin/sh", *av);
    else
        write(1, "No !\n", 5);
    return 0;
}