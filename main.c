#include <stdio.h>
#include <unistd.h>

#define PROGRAM_NAME "mayflowerTextEngine"

void initializeEngine();
void terminateEngine();

int main (void)
{
	initializeEngine();
	terminateEngine();
	return 0;
}

void initializeEngine()
{
	printf("\e[1;1H\e[2J");	/* clears the screen */
	printf("initializing %s...\n", PROGRAM_NAME);
	printf("Copyright (c) 2022 www.crontab.pw\n");
	sleep(1);
}

void terminateEngine()
{
        printf("\e[1;1H\e[2J"); /* clears the screen */
}

