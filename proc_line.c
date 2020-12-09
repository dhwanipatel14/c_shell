#include "smallsh.h"
#include <string.h>
#include <stdlib.h>

int gettok(char **outptr);
int runcommand(char **cline, int where);


void procline(void)
{
	char *arg[MAXARG + 1];
	int toktype;
	int narg;
	int type;

	narg = 0;

	for (;;)
	{
	//checking tokentype ofcommand entered by user 
	   switch (toktype = gettok(&arg[narg])) {
		//If command is valid agrgument increment the counter.
		case ARG:
			if (narg < MAXARG){
                //printf("arg[narg=%d] = %s\n",narg,arg[narg]);
                narg++;
			}
            break;
		case EOL:
		case SEMICOLON:
		case AMPERSAND:
			if (toktype == AMPERSAND)
				type = BACKGROUND;
			else
				type = FOREGROUND;
			 //Condition to append null character at the end.
			if (narg != 0)
			{
				arg[narg] = NULL;
				//Passing arguments and its type to runcommand to execute it.
				runcommand(arg, type);
			}
			if (toktype == EOL)
				return;
			narg = 0;
			break;
	  }
	}
}
