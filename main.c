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
#include <stdio.h>
#include <unistd.h>
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
/* debug level */
unsigned char debuglevel = LV_ERROR;// | LV_DEBUG | LV_INFO ;

/*****************************************************************************************************/
/*                                                 FUNCTION                                          */
/*****************************************************************************************************/
static void helpHandler()
{
	printf(
"	Usage: pwdgener [args]\n"
"\n"
"	-m mode, default(-m D)\n"
"	-l length, default(-l 6-12)\n"
"	-o filename, output to filename, will not print on screen\n"
"	-s set symbal list, some characters need to transcoding by '\\'\n"
	);
}

int main(int argc, char *argv[])
{
	int i = 0;
	int rv = 0;
	char opt = 0;
	int len = 0;
	int len_min = LEN_MIN_DEFAULT;
	int len_max = LEN_MAX_DEFAULT;
	int len_size = 0;
	int mode = PWDGENER_DIGIT;
	char *tmp = NULL;
	char *modeendp = NULL;
	char *filename = NULL;
	char *password = NULL;
	char *symbalList = NULL;
	char *optstring = "l:m:s:o:h";
	FILE *fp = NULL;

	INFO("argc: %d\n", argc);
	for(i = 0; i < argc; i++)
	{
		INFO("arg-%d: %s", i, argv[i]);
	}
	while((opt = getopt(argc, argv, optstring)) != -1)
	{
		INFO("opt:%c", opt);
		switch(opt)
		{
		case 'l':
			tmp = strchr(optarg, '-');
			if(tmp != NULL)
			{
				*tmp = '\0';
				len_min = atoi(optarg);
				len_max = atoi(tmp+1);

			}
			else
			{
				len_min = atoi(optarg);
				len_max = len_min;
			}
			
			break;
		case 'm':
			modeendp = optarg + strlen(optarg);
			tmp = optarg;
			while(tmp < modeendp)
			{
				INFO("mode :  %c(%d)", *tmp, *tmp);
				switch(*tmp)
				{
				case 'D':
					mode |= PWDGENER_DIGIT;
					break;
				case 'L':
					mode |= PWDGENER_LITTER_LOWER;
					break;
				case 'C':
					mode |= PWDGENER_LITTER_CAPITAL;
					break;
				case 'S':
					mode |= PWDGENER_SYMBOL;
					break;
				default:
					ERROR("invalid mode %c(%d)", *tmp, *tmp);
					return -1;
				}
				tmp++;
			}
			break;
		case 's':
			symbalList = optarg;
			break;
		case 'o':
			filename = optarg;
			break;
		case 'h':
			helpHandler();
			return 0;
			break;
		default:
			ERROR("Unknown option!(%d)", opt);
			break;
		}
	}

	/* rand len */
	len_size = len_max - len_min + 1;
	INFO("len_size: %d  len_min: %d  len_max: %d ", len_size, len_min, len_max);
	if(len_size < 0 || len_min <= 0)
	{
		ERROR("invalid length range");
		return -1;
	}
	else if(len_size == 0)
	{
		len = len_min;
	}
	else
	{
		srand((unsigned)time(NULL));
		len = len_min + (rand()%len_size);
	}
	
	DEBUG("len: %d  mode:%d", len, mode);

	password = (char *)malloc(len + 1);
	memset(password, 0, len+1);
	if(password == NULL)
	{
		ERROR("memery alloc fail!");
		return -1;
	}
	
	rv = passwordGenerator(len, mode, symbalList, password);
	if(!rv)
	{
		if(NULL != filename)
		{
			fp = fopen(filename, "w+");
			fprintf(fp, "#password len: %d\n", len);
			fprintf(fp, "%s\n", password);
			fclose(fp);
			printf("OK, save to %s\n", filename);
		}
		else
		{
			printf("#password len: %d\n", len);
			printf("%s\n", password);
		}

	}
	else
	{
		ERROR("unexpected error");
	}

	free((void *)password);
	return 0;
}

