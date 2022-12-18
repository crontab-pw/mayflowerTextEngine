#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define PROGRAM_NAME "mayflowerTextEngine"
#define COPYRIGHT_DATE "2022"
#define CREATOR_NAME "www.crontab.pw"

int* determineTerminalSize();
void initializeEngine();
void mainLoop();
void terminateEngine();

int main (void)
{
	int *totalRowsColumns = determineTerminalSize();
	initializeEngine();
	mainLoop();
	terminateEngine();
	return 0;
}

int* determineTerminalSize()
{
	static int totalRowsColumns[2];	/* [0] = rows [1] = columns */
        struct winsize max;
        ioctl(0, TIOCGWINSZ , &max);
	totalRowsColumns[0] = max.ws_row;
	totalRowsColumns[1] = max.ws_col;
	return totalRowsColumns;
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

