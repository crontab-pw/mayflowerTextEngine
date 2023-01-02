#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "programdefinitions.h"
#include "ansidefinitions.h"
#include "commands.h"

int* determineTerminalSize();
void displayCommandLine();
void displayTitleBar();
char* getUserInput();
int parseUserInput(char*);
void initializeEngine();
void mainLoop();
void terminateEngine();
void tokenizeString(char*, char *tokens[MAXIMUM_TOKENS][MAXIMUM_SIZE]);
int validateTokens(char *tokens[MAXIMUM_TOKENS][MAXIMUM_SIZE], char *commandToExecute);

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
	/* Create userInput variable and get input from user */
	static char userInput[MAXIMUM_SIZE] ;
	gets_s(userInput, MAXIMUM_SIZE);

	/* Force all user input to be lower case */
	for(int i = 0; userInput[i]; i++)
		userInput[i] = tolower(userInput[i]);

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

int parseUserInput(char* userInput)
{
	/* Tokenize user input */
	char *tokens[MAXIMUM_TOKENS][MAXIMUM_SIZE];
	tokenizeString(userInput, tokens);

	char *commandToExecute[MAXIMUM_SIZE];

	if (tokens[0][0] == NULL)
		return ON;
	else if ((strcmp(tokens[0][0], "/quit") == 0))
		return OFF;
	else
	{
		int validToken = validateTokens(tokens, commandToExecute);
		if (validToken)
			call_function(commandToExecute);
		else
			printf("Syntax error. Type 'help' for a list of commands.\n\n");

		return ON;
	}
}

void terminateEngine()
{
	/* Reset colors to terminal default */
	printf(DEFAULT_COLORS);

	/* Clear the screen and reset cursor position */
	printf(CLEAR_SCREEN CURSOR_HOME);
}

void tokenizeString(char *userInput, char *tokens[MAXIMUM_TOKENS][MAXIMUM_SIZE])
{
        /* Tokenize string by spaces */
        char *tokenizedPointer;

        for (int i = 0; i <= MAXIMUM_TOKENS; i++)
                if (i == 0)
                        tokens[i][0] = strtok_r(userInput, " ", &tokenizedPointer);
                else
                        tokens[i][0] = strtok_r(NULL, " ", &tokenizedPointer);
}

int validateTokens(char *tokens[MAXIMUM_TOKENS][MAXIMUM_SIZE], char *commandToExecute)
{
	/* Variable see if first token is valid */
	int validToken = OFF;

	/* Loop through valid commands to see if first token is valid */
	for (int i = 0; i < numberOfValidComands; i++)
		if (strcmp(tokens[0][0], &validCommands[i][0]) == 0)
		{
			validToken = ON;
			strcpy(commandToExecute, &validCommands[i][1]);
		}

	return validToken;
}
