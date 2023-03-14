int run()
{
    fwrite("Good... Wait what?\n",1, 0x13,"stdout");
    return system("/bin/sh");
}

int main(int ac, char **av)
{
    char *tmp;
    gets(tmp);
    return 0;

}