/*
** CTable. Version 1.0.
*/
/*NOTE: Minor Changes have been made to enable this program to run under TClite
Credit goes to David van Leerdam
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define NAMELEN 11
#define MAX		10
#define MIN		1

char name[NAMELEN];
short int number,wrong;
int table,answer,ch;
int checktable(int table);

int checktable(int table);
void cap(char *ptr2name);


int main(void)
{
	printf("\nCTable by David van Leerdam\n");
	printf("Please enter your name (max. %d): ",NAMELEN-1);
	gets(name);
	cap(name);
	printf("\nDo you want to practise some tables? (Y/N) ",name);
	ch = toupper((int)getch());

	if (ch == 'N') {
		printf("\nOkidoki %s, but you'll have to do extra tomorrow!\n",name);
		exit(EXIT_SUCCESS); }

	else

	 do {
		wrong=0;
		printf("\nWhich table? ");
		scanf("%d",&table);
		checktable(table);
 		number = MIN;

		// hier worden de tafelsommen gemaakt
		// en gecontroleerd.

		do {
			printf("%d x %d = ",number,table);
			scanf("%d",&answer);
			if (answer != (number*table))
			{
			printf("WRONG! %d x %d = %d!\n",number,table,number*table);
				wrong++;
			}

		// beoordeling.

		} while (number++ != (MAX));
				switch(wrong) {
				case 0: printf("\n%s: I'm proud of you! No wrong answer found practising table of %d!",name,table); break;
				case 1:
				case 2: printf("\n%s: Good work! You gave only %d wrong answers doing table of %d.",name,wrong,table); break;
				case 3:
				case 4: printf("\n%s: Can't you do a lot better? %d wrong anwers found doing table of %d.",name,wrong,table); break;
				default : printf("\n%s: Practise a little more. You gave %d wrong answers doing table %d.",name,wrong,table); }
			printf("\nDo you want to practice again? (Y/N) ");
		ch = toupper((int)getch());
		printf("\n");
		} while (ch != 'N');
		printf("\nCTable version 1.0. Copyright by David van Leerdam.\n");
}

// hier wordt gecontroleerd of het tafelnr. een heel getal is.
int checktable(int table)
{
	if ((table < 0) || (table == '\n')) {
		fprintf(stderr,"\nERROR: Input has to be a valid positive integer.\n");
		exit(EXIT_FAILURE); }
   return 1;
      }

// verander de eerste letter van de naam in een hoofdletter.

void cap(char *ptr2name)
{
	if(ptr2name[0])
		*ptr2name = toupper((int)*ptr2name);
}
