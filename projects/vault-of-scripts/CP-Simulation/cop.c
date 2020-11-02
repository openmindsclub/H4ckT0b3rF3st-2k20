#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    int fSource,fDest;
    char* buf;
    struct stat StatusBuffer;
    if(argc != 3){
        printf("Usage: %s <File name#>\n",argv[0]);
        exit(1);
    }
    else
    {
        fSource = open(argv[1],O_RDONLY);
        if(fSource==-1)
            printf("le fichier source %s n'existe pas !\n",argv[1]);
        else
        {
            if(stat(argv[1],&StatusBuffer)==-1){
                perror(argv[1]);
                exit(1);
            }
            fDest = (int)open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,StatusBuffer.st_mode);
            if(fDest==-1)
                printf("le fichier Destination %s n'existe pas !\n",argv[1]);
            else
            {
                read(fSource,&buf,StatusBuffer.st_size);
                write(fDest,&buf,StatusBuffer.st_size);
                close(fDest);
            }   
            close(fSource);
        }

    }
    return EXIT_SUCCESS;
}