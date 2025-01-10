#include <stdio.h> 
#include <unistd.h>
#include <string.h> 
#include <errno.h>
#include <fcntl.h>

int main()
{ 
    int fd1 = open("file.txt",O_CREAT | O_RDWR | O_APPEND,0777);
    int fd2 = dup2(fd1,15); // dup en küçük fd'ye kopyalarken dup2 istenilen fd'ye kopyalar 
    // istenilen fd dolu ise onu close yapıp fd'yi kopyalar
    char* path = "file.txt"; 
    // access bir dosyanın izinlerini kontrol eder 
    if (access(path,R_OK | X_OK) == 0) 
        printf("Okuma ve çaliştirma izni var \n"); 
    else 
        printf("%s\n",strerror(errno)); 
    // Ya da perror ile istenilen hata çıktısı 
    close(fd2); close(fd1); 


    printf ("execve'den önce");     
    char *args[] = {"/bin/cmatrix", NULL};
    char *env[] = {"TERM=xterm",NULL};

    if (execve("/bin/cmatrix",args,env) == -1)
        perror("execve hatasi");
}