#include <stdio.h>
#include <unistd.h>

#define PROGRAM_NAME "mayflowerTextEngine"
#define COPYRIGHT_DATE "2022"
#define CREATOR_NAME "www.crontab.pw"

void initializeEngine();
void mainLoop();
void terminateEngine();

int main (void)
{
	initializeEngine();
	mainLoop();
	terminateEngine();
	return 0;
}

void initializeEngine()
{
	printf("\e[1;1H\e[2J");	/* clears the screen */
	printf("initializing %s...\n", PROGRAM_NAME);
	printf("Copyright %s %s\n", COPYRIGHT_DATE, CREATOR_NAME);
	sleep(1);
};

void mainLoop()
{

}

void terminateEngine()
{
        printf("\e[1;1H\e[2J"); /* clears the screen */
}

