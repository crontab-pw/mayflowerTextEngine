int call_function(const char *name);
void commandAbout();
void commandHelp();

/* Global array of commands and their functions */
        const char validCommands[][2][MAXIMUM_SIZE] =
        {
                {"about", "commandAbout"},
                {"help", "commandHelp"},
                {"/quit", "\0"}
        };

/* Determine  number of rows in validCommands[][][] */
int numberOfValidComands = sizeof(validCommands) / sizeof(validCommands[0]);

const static struct {
  const char *name;
  void (*func)(void);
} function_map [] = {
  { "commandAbout", commandAbout },
  { "commandHelp", commandHelp },
};

int call_function(const char *name)
{
  int i;

  for (i = 0; i < (sizeof(function_map) / sizeof(function_map[0])); i++) {
    if (!strcmp(function_map[i].name, name) && function_map[i].func) {
      function_map[i].func();
      return 0;
    }
  }

  return -1;
}

void commandAbout()
{
        printf("%s %s %s\n\n", PROGRAM_NAME, COPYRIGHT_DATE, CREATOR_NAME);
}

void commandHelp()
{
        printf("Help with %s - List of commands available:\n\n", PROGRAM_NAME);
}

