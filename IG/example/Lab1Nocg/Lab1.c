#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

char text[1024], dest_loc[128];
int dest, source, r, w;

int main(int argc, char *argv[])
{
   if(argc > 3)
   {
      printf("ERROR: Usage %s <file name>\n", argv[0]);
      _exit(1);
   }

   source = 0;
   dest = 0;

   if(argc == 3)
   {
      printf("I will copy content of ");
      printf("%s", argv[1]);
      printf(" to ");
      printf("%s\n", argv[2]);
      source = open(argv[1], O_RDONLY);
      if(source == -1)
      {
         printf("ERROR: %s does not exist\n", argv[1]);
         _exit(1);
      }
      strcpy(dest_loc, argv[2]);
   }

   if(argc == 2)
   {
      printf("I will save whatever you type into %s. Enter CTRL+D when done\n", argv[1]);
      strcpy(dest_loc, argv[1]);
   }

   if(argc == 1)
      printf("I will echo standard input to standard output! Enter CTRL+D when done\n");

   if(argc == 3 | argc == 2)
   {
      dest = open(dest_loc, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
      if(dest == -1)
      {
         printf("ERROR: %s could not open\n", argv[2]);
         _exit(1);
      }
   }

   do
   {
      r = read(source, text, 1024);
      if(r == -1)
      {
         printf("ERROR: system could not read from terminal\n");
         _exit(1);
      }
      w = write(dest, &text, r);
      if(w == -1)
      {
         printf("ERROR: %s could not be written into\n", argv[1]);
         _exit(1);
      }
   } while(r > 0);

   if(close(source) == -1)
   {
      printf("ERROR: system could not close terminal\n");
      _exit(1);
   }
   if(argc == 2 | argc == 3)
   {
      if(close(dest) == -1)
      {
         printf("ERROR: %s could not close\n", argv[1]);
         _exit(1);
      }
   }

   printf("done!\n");

   return 0;
}
