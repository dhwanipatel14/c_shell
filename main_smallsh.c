#include "smallsh.h"
//Asking user to enter the command
char *prompt = "Command> ";

int userin(char *p);
void procline(void);

int main()
{
    //If command are succesfully read than procline is executed to check commands.
	while (userin(prompt) != EOF)
		procline();
}

