#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "logfind.h"

char **read_logfind_dot_file(FILE *logfind_dot_file)
{

  char *rc = NULL;
  int true = 1;
  char **files_to_search = malloc(sizeof(char *));
  char **orig_address = files_to_search;

  rewind(logfind_dot_file);

  while (true)
  {
    *files_to_search = malloc(sizeof(char) * MAX_DATA);
    rc = fgets(*files_to_search, MAX_DATA, logfind_dot_file);

    if (rc == NULL)
    {
      break;
    }

    files_to_search++;
  }

  return orig_address;
error:
  if (*files_to_search)
    free(*files_to_search);
}

void cleanup(FILE *logfind_dot_file, char **file_list)
{
  int i = 0;
  if (logfind_dot_file)
    free(logfind_dot_file);
  for (i = 0; file_list[i]; i++)
  {
    if (strcmp(file_list[i], "") == 0 || file_list[i] == NULL)
    {
      break;
    }

    if (file_list[i]) free(file_list[i]);
  }
}

int main(int argc, char *argv[])
{
  FILE *logfind_dot_file = fopen(DOT_FILE, "r");
  check(logfind_dot_file != NULL, "Failed to load file.");

  char **file_list = read_logfind_dot_file(logfind_dot_file);

  int i = 0;
  for (i = 0; file_list[i]; i++)
  {
    if (strcmp(file_list[i], "") == 0 || file_list[i] == NULL)
      break;
    printf("String: %s \n", file_list[i]);
  }

  cleanup(logfind_dot_file, file_list);
  return 0;
error:
  cleanup(logfind_dot_file, file_list);
  return -1;
}
