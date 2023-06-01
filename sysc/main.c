#include <stdio.h>
#include <malloc.h>
#include "syscalls.h"

int main()
{

/*
    FILE *file;
    if ((file = fopen("//home//ubuntu//code//risc-v//one//sysc//for_read.txt", "r")) == NULL)
    {
        printf("Error with file r\n");
        return 0;
    }

    char data[30];

    fseek(file, 0, SEEK_END);
    int size_file = ftell(file);
    fgets(data, 29, file);

    fclose(file);

    printf("\n%s\n\n", data);

    FILE *wrt;
    if ((wrt = fopen("//home//ubuntu//code//risc-v//one//sysc//for_write.txt", "w")) == NULL)
    {
        printf("Error with file w\n");
        return 0;
    }

    int i = 0;

    while (data[i] != "\n")
    {
        if (data[i] == " ")
        {
            fprintf(wrt, "%s", "\n");
        }
        else
        {
            fprintf(wrt, "%c", data[i]);
        }
        i++;
    }

    fprintf(file, "%s", "\nThis is just an example :)");

    fclose(wrt);

*/
    int a = 10;
    printf("%d\n", a);

    return 0;
}