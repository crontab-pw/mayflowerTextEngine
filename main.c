#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define PROGRAM_NAME "mayflowerTextEngine"
#define COMMAND_PROMPT "<> "
#define COPYRIGHT_DATE "2022"
#define CREATOR_NAME "www.crontab.pw"

int* determineTerminalSize();
void displayCommandLine();
void displayTitleBar();
void initializeEngine();
void mainLoop();
void terminateEngine();

int main (void)
{
	/* Determines if we loop through mainLoop() */
	int isEngineOn = 1;

	/* Initialize text engine and loop through mainLoop() */
	initializeEngine();
	while(isEngineOn)
		mainLoop();
	
	/* Terminate text engine */
	terminateEngine();

	return 0;
}

void displayCommandLine() {

	/* Pointer to determine Row & Columns in terminal */
	/* Element[0] determines the rows, [1] the columns */
	int *totalRowsColumns = determineTerminalSize();

	/* Reset colours to terminal default */
	printf("\x1b[39;49m");

	/* Move cursor to last row of the terminal */
        printf("\e[%d;0H", totalRowsColumns[0]);

	/* Display command prompt */
	printf("%s", COMMAND_PROMPT);

	getchar();	/* Temportary place holder for user input */
}

void displayTitleBar()
{
	/* Pointer to determine Row & Columns in terminal */
        /* Element[0] determines the rows, [1] the columns */
	int *totalRowsColumns = determineTerminalSize();

	/* Move cursor to point 0,0 on screen */
	printf("\e[0;0H");
	
	/* Draw the title bar across the top of the terminal */
	for (int i = 0; i < totalRowsColumns[1]; i++)
		printf("\x1b[2;44;44m ");
	
	/* Move cursor to centre position and display PROGRAM_NAME */
	printf("\e[1;%luH%s", ((totalRowsColumns[1] - (sizeof(PROGRAM_NAME) - 1)) / 2), PROGRAM_NAME );

//sizeof(PROGRAM_NAME)
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
	printf("\e[0;0H\e[2J");	/* clears the screen */
	printf("initializing %s...\n", PROGRAM_NAME);
	printf("Copyright %s %s\n", COPYRIGHT_DATE, CREATOR_NAME);
	sleep(1);
	printf("\e[0;0H\e[2J"); /* clears the screen */
};

void mainLoop()
{
	displayTitleBar();
	displayCommandLine();
}

void terminateEngine()
{
	/* Reset colours to terminal default */
        printf("\x1b[39;49m");

	/* Clear the screen and reset cursor position */
        printf("\e[1;1H\e[2J"); /* clears the screen */
}
