//Anne Marie Bogar                                                                                                                                                                                          
//Lab 2                                                                                                                                                                                                     
//March 1, 2016                                                                                                                                                                                             

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_LINE_LEN=1024; //each command line is at most 1023 character long                                                                                                                             
const int WORD_LEN=51; //each word in command line is at most 50 char long                                                                                                                                  
const int MAX_WORD_NUM=20; //each command has at most 20 words in it...                                                                                                                                     
void execute(char cmdline[]); //breaks the shell script from the terminal or a file into multiple worrds and then executes the commands                                                                     

int main(int argc, char *argv[])
{
   char *pwd, *host, *usr;
   char cmdline[MAX_LINE_LEN];
   ifstream scriptFile;

   //Calling getenv to find the current values of environment variables                                                                                                                                     
   pwd = getenv("PWD");
   host = getenv("HOSTNAME");
   usr = getenv("USER");

   //error if there are more than two arguments                                                                                                                                                             
   if(argc > 2)
   {
      cout << "ERROR: too many arguments\n";
      exit(1);
   }
   //read from file if there are two arguments                                                                                                                                                              
   if(argc == 2)
   {
      scriptFile.open(argv[1]);
      if(!scriptFile.is_open())
         _exit(1);
      while(scriptFile.good())
      {
         scriptFile.getline(cmdline, 256);
         while(cmdline[0] == '#') //ignores the comments                                                                                                                                                    
            scriptFile.getline(cmdline, 256);
         if(scriptFile.good())
            execute(cmdline);
      }
      scriptFile.close();
   }
   //read from terminal if there is only 1 argument                                                                                                                                                         
   if(argc == 1)
   {
      while(1)
      {
         cout << "[" << usr << "@" << host << " " << pwd << "]$";
         cin.getline(cmdline, 256);
         execute(cmdline);
      }
   }
}
void execute(char cmdline[])
{
   pid_t pid;
   bool background = false;
   char *Word[MAX_WORD_NUM]; //an array of pointer to char...                                                                                                                                               

   /*TODO: break cmd lines into an array of words,                                                                                                                                                          
        ignoring anything statring crom character # (if any)                                                                                                                                                
        You can assume different words (command line arguments) are always separated by spaces                                                                                                              
        (you can use function strlen (cmdline) to get the length of a C string...)                                                                                                                          
        You need to split the cmdline into multiple words, each word is an argument                                                                                                                         
        1) replace space by \0 (terminating character)                                                                                                                                                      
        2) use Word[0] to point to the first char of the first word                                                                                                                                         
           use Word[1] to point to the cirst char of the second word                                                                                                                                        
           use NULL to indicate the end of Word array */

   Word[0] = &(cmdline[0]);
   int length = strlen(cmdline);
   int i = 1;
   for(int k=0; k<length; k++)
   {
      if(cmdline[k] != '#') //ignores comments                                                                                                                                                              
      {
         if(cmdline[k] == ' ')
         {
            cmdline[k] = '\0';
            if(cmdline[k+1] != '#') //ignores comments                                                                                                                                                      
               Word[i] = &(cmdline[k+1]);
            i++;
         }
      }
   }
   //prepares for if the command is done in the background or not                                                                                                                                           
   if(*Word[i-1] == '&')
   {
      Word[i-1] = NULL;
      background = true;
   }
   else
      Word[i] = NULL;

   if(!strcmp (cmdline, "exit"))
      exit(0);
   /*create a child process*/
   pid = fork();
   if(pid < 0)
   {
      fprintf(stderr, "Fork Failed");
      exit(-1);
   }
   else if(pid == 0)
   {
      //Todo: checking return value of execvp...                                                                                                                                                            
      execvp(Word[0], Word);

      //If we are here, that menas execvp fails...
      cout << "Command not found\n";
      exit(1);
   }
   else
   {
      if(!background)
      {
         //parent will wait for the child to complete                                                                                                                                                       
         wait(NULL);
      }
   }
}
