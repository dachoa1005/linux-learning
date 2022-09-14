#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
// #include <iostream>
#include <dirent.h>
// #include <conio.h>


int main(int argc, char const *argv[])
{
    DIR* dir = opendir("/home/dachoa1005/Desktop/linux/");
    if (dir == NULL){
        return 1;
    }

    struct dirent* entity;
    entity = readdir(dir);
    while (entity != NULL){
        printf("%hhd %s\n",entity->d_type, entity->d_name);
        entity = readdir(dir);
        // if (entity->d_type == DT_)
    }

    closedir(dir);
    return 0;
}
