#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<pwd.h>
#include<stdlib.h>
#include<time.h>
#include <grp.h>

int main(int argc,char *argv[]){
    struct stat StatusBuffer;
    
    if(stat(argv[1],&StatusBuffer)==-1){
        perror(argv[1]);
        exit(1);
    }
    switch (StatusBuffer.st_mode & S_IFMT) {
        case S_IFBLK:  printf("b");     break;
        case S_IFCHR:  printf("c");     break;
        case S_IFDIR:  printf("d");     break;
        case S_IFIFO:  printf("p");     break;
        case S_IFLNK:  printf("l");     break;
        case S_IFREG:  printf("-");     break;
        case S_IFSOCK: printf("s");     break;
    }

    //printf("%c",StatusBuffer.st_mode & __S_IFDIR ? 'd' : '-');
    printf("%c",StatusBuffer.st_mode & S_IRUSR ? 'r' : '-');
    printf("%c",StatusBuffer.st_mode & S_IWUSR ? 'w' : '-');
    printf("%c",StatusBuffer.st_mode & S_IXUSR ? 'x' : '-');
    printf("%c",StatusBuffer.st_mode & S_IRGRP ? 'r' : '-');
    printf("%c",StatusBuffer.st_mode & S_IWGRP ? 'w' : '-');
    printf("%c",StatusBuffer.st_mode & S_IXGRP ? 'x' : '-');
    printf("%c",StatusBuffer.st_mode & S_IROTH ? 'r' : '-');
    printf("%c",StatusBuffer.st_mode & S_IWOTH ? 'w' : '-');
    printf("%c ",StatusBuffer.st_mode & S_IXOTH ? 'x' : '-');
    printf("%ld ",StatusBuffer.st_nlink);
    printf("%s ",getpwuid(StatusBuffer.st_uid)->pw_name);
    printf("%s ",getgrgid(StatusBuffer.st_uid)->gr_name);
    printf("%ld ",StatusBuffer.st_size);
    for (int i = 4; i < 16; i++)
    {
        printf("%c",ctime(&StatusBuffer.st_ctime)[i]);
    }
    printf(" %s\n",argv[1]);
    return EXIT_SUCCESS;
}