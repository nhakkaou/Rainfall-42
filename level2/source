
int p(){
    fflush(sdtout);
    char *ptr;
    gets(ptr);
    if((return_addr & 0xb0000000 ) != 0xb0000000){
        puts(ptr);
        return strdup(ptr);
       
    }   
        printf("(%p)\n", return_addr);
        exit(1);
}


int main(){
    return p()
}