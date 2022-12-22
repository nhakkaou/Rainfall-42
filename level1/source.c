int run()
{
    write(1, "Good... Wait what?\n", 0x13);
    return system("/bin/sh");
}

int main(int ac, char **av)
{
    char tmp[76];
    gets(tmp);
    return 0;
}