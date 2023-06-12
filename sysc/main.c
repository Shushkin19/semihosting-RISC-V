#include <stdio.h>
#include <malloc.h>
#include "syscalls.h"

int main()
{

    char data[100] = {0};
    /*
       FILE *file;
      if ((file = fopen("//home//shusha//Code//RISC-V//Learn//semihosting-RISC-V//sysc//for_read.txt", "r")) == NULL)
      {
          printf("Error with file r\n");
      }
      else
      {

          fseek(file, 0, SEEK_END);
          int size_file = ftell(file);
          fseek(file, 0, SEEK_SET);
          fgets(data, size_file, file);

          fclose(file);
          printf("%s\n", data);
     */

    FILE *wrt = NULL;
    if ((wrt = fopen("//home//shusha//Code//RISC-V//Learn//semihosting-RISC-V//sysc//for_write.txt", "w")) == NULL)
    {
        printf("Error with file w\n");
    }
    else
    {

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
        fprintf(wrt, "%s", "\nThis is just an example :)");
    }
    fclose(wrt);
    // }

    int a = 10;
    printf("%d\n ", a);

    return 0;
}