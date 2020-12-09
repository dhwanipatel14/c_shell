#include "smallsh.h"

static char inpbuf[MAXBUF], tokbuf[2 * MAXBUF],
*ptr = inpbuf, *tok = tokbuf;
//Function to check if user enters special characters
int inarg(char c);

int userin(char *p)
{
	int c, count;
	ptr = inpbuf;
	tok = tokbuf;

	printf("%s", p);
	count = 0;
	while (1)
	{
		if ((c = getchar()) == EOF)
			return(EOF);
		if (count < MAXBUF)
			inpbuf[count++] = c;
		if (c == '\n' && count < MAXBUF)
		{
			inpbuf[count] = '\0';
			return count;
		}
		if (c == '\n')
		{
			printf("smallsh: input line too long\n");
			count = 0;
			printf("%s ", p);
		}
	}
}
//Checking the type of tokens enetred by user
int gettok(char **outptr)
{
	int type;

	*outptr = tok;
	//ignoring space and tab
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;

	*tok++ = *ptr;

	switch (*ptr++) {
	case '\n':
		type = EOL;
		break;
	case '&':
		type = AMPERSAND;
		break;
	case ';':
		type = SEMICOLON;
		break;
	default:
		type = ARG;
		//Calling inarg to check special character
		while (inarg(*ptr))
			*tok++ = *ptr++;
	}
	*tok++ = '\0';
	return type;
}

//****************************************************************************************
static char special[] = { ' ', '\t', '&', ';', '\n', '\0' };
int inarg(char c)
{
	char *wrk;
	for (wrk = special; *wrk; wrk++)
	{
		if (c == *wrk)
			return (0);
	}
	return (1);
}


