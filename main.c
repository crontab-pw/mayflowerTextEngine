#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "ansidefinitions.h"

#define PROGRAM_NAME "mayflowerTextEngine"
#define COMMAND_PROMPT "<> "
#define COPYRIGHT_DATE "2022"
#define CREATOR_NAME "www.crontab.pw"
#define MAXIMUM_SIZE 200
#define OFF 0
#define ON 1

int* determineTerminalSize();
void displayCommandLine();
void displayTitleBar();
char* getUserInput();
int parseUserInput(const char*);
void initializeEngine();
void mainLoop();
void terminateEngine();

int main (void)
{
	/* Initialize text engine */
	initializeEngine();

	/* Enter main loop */
	mainLoop();
	
	/* Terminate text engine */
	terminateEngine();

	return 0;
}

void displayCommandLine() {
	/* Pointer to determine Row & Columns in terminal */
	/* Element[0] determines the rows, [1] the columns */
	int *totalRowsColumns = determineTerminalSize();

	/* Reset colors to terminal default */
	printf(DEFAULT_COLORS);

	/* Move cursor to last row of the terminal */
	printf(CURSOR_LAST, totalRowsColumns[0]);

	/* Display command prompt */
	printf(COMMAND_PROMPT);
}

void displayTitleBar()
{
	/* Pointer to determine Row & Columns in terminal */
        /* Element[0] determines the rows, [1] the columns */
	int *totalRowsColumns = determineTerminalSize();

	/* Move cursor to point 1,1 on screen */
	printf(CURSOR_HOME);
	
	/* Draw the title bar across the top of the terminal */
	for (int i = 0; i < totalRowsColumns[1]; i++)
		printf(DRAW_TITLEBAR);
	
	/* Move cursor to centre position and display PROGRAM_NAME */
	printf(DISPLAY_TITLE, ((totalRowsColumns[1] - (sizeof(PROGRAM_NAME) - 1)) / 2), PROGRAM_NAME );
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

char* getUserInput()
{
	static char userInput[MAXIMUM_SIZE] ;
     	fgets(userInput, MAXIMUM_SIZE, stdin) ;
	return userInput;
}

void initializeEngine()
{
	/* Clear the screen and reset cursor position */
        printf(CLEAR_SCREEN CURSOR_HOME);
	printf("initializing %s...\n", PROGRAM_NAME);
	printf("Copyright %s %s\n", COPYRIGHT_DATE, CREATOR_NAME);
	sleep(1);

	/* Clear the screen and reset cursor position */
	printf(CLEAR_SCREEN CURSOR_HOME);
}

void mainLoop()
{
	/* Determines if we loop through mainLoop() */
        int engineRunning = ON;

	while(engineRunning == ON)
	{
		displayTitleBar();
		displayCommandLine();

		/* Get user input  */
		char *userInput;
		userInput = getUserInput();

		/* Parse user input */
		engineRunning = parseUserInput(userInput);
	}
}

int parseUserInput(const char* userInput)
{
	/* If the user types in `/quit` into the engine, shut the engine down */
	if (strcmp(userInput, "/quit\n"))
		return ON;
	else
		return OFF;
}

void terminateEngine()
{
	/* Reset colors to terminal default */
	printf(DEFAULT_COLORS);

	/* Clear the screen and reset cursor position */
	printf(CLEAR_SCREEN CURSOR_HOME);
}
