#define PROGRAM_NAME "mayflowerTextEngine"
#define COMMAND_PROMPT "<> "
#define COPYRIGHT_DATE "2022"
#define CREATOR_NAME "www.crontab.pw"
#define MAXIMUM_SIZE 200
#define MAXIMUM_TOKENS 2 /* Represents elements in array. 0 = first element */
#define OFF 0
#define ON 1

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

