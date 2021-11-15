#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

void readdir_print(const char* path){
    DIR * dir;
    struct dirent * ptr;
    dir = opendir(path);
    while((ptr = readdir(dir)) != NULL)
    {
        printf("d_name : %s\n", ptr->d_name);
    }
    closedir(dir);
}


int main()
{
    readdir_print("/proc");
    return 0;
}
