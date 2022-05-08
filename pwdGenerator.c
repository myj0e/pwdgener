//
//@Copyright:Copyright 2022 HOWV
//@License:
//@Birth:created by Howv on 2022-05-01
//@Content:log information console
//@Version:1.0.0
//@Revision:last revised by Howv on 2022-05-01
//


/*****************************************************************************************************/
/*                                                 INCLUDE                                           */
/*****************************************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pwdGenerator.h"
#include "debug.h"
/*****************************************************************************************************/
/*                                                 DEFINE                                            */
/*****************************************************************************************************/

/*****************************************************************************************************/
/*                                                   TYPE                                            */
/*****************************************************************************************************/

/*****************************************************************************************************/
/*                                                 VARIABLE                                          */
/*****************************************************************************************************/

static char *symbal = "`~!@#$%^&*()_+-=[]{};:<>,.?/|\"'";

static char *digit = "0123456789";

static char *captital = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static char *lower = "abcdefghijklmnopqrstuvwxyz";
/*****************************************************************************************************/
/*                                                 FUNCTION                                          */
/*****************************************************************************************************/


int passwordGenerator(IN int len, IN unsigned char mode, IN char *symbalList, INOUT char *password)
{
	int total = 0;
	int pwdlen = len;
	int index = 0;
	char table[128] = {0};
	char *tmpptr = table;
	
	if(len <= 0 || mode <= 0 || password == NULL)
	{
		ERROR("Input error");
		return -1;
	}

	if(NULL == symbalList)
	{
		symbalList = symbal;
	}

	if(mode & PWDGENER_LITTER_LOWER)
	{
		memcpy(tmpptr, lower, strlen(lower));
		total += strlen(lower);
		tmpptr += strlen(lower);
	}

	if(mode & PWDGENER_LITTER_CAPITAL)
	{
		memcpy(tmpptr, captital, strlen(captital));
		total += strlen(captital);
		tmpptr += strlen(captital);
	}

	if(mode & PWDGENER_DIGIT)
	{
		memcpy(tmpptr, digit, strlen(digit));
		total += strlen(digit);
		tmpptr += strlen(digit);
	}


	if(mode & PWDGENER_SYMBOL)
	{
		memcpy(tmpptr, symbalList, strlen(symbalList));
		total += strlen(symbalList);
	}

	DEBUG("current table:\nlen: %d\n%s", (int)strlen(table), table);
	if(!total)
	{
		ERROR("no character to use");
		return -1;
	}
	srand((unsigned)time(NULL));

	while(pwdlen > 0)
	{
		pwdlen --;
		
		index = rand()%total;
		INFO("rand index: %2d -- %c", index, table[index]);
		password[pwdlen] = table[index];
	}

	return 0;	
}
