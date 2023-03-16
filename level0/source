int main(int ac, char **av)
{

    if (atoi(av[1]) == 0x107) // 423
        char *ptr = strdup("/bin/sh");

        int resutlt1 = getegid(); // => esp+0x1c
        int resutlt2 = geteuid(); // => esp+0x18
        setresgid(result1, result1, result1);
        setresuid(resutlt2, resutlt2, resutlt2);
        execv("/bin/sh", &ptr);
    else
        fwrite("No !\n",1,5,stderr);
    return 0;
}