#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "logfind.h"


void cleanup(FILE *logfind_dot_file, char **file_list)
{
  int i = 0;
  if (logfind_dot_file)
  {
    fclose(logfind_dot_file);
  }
  
  
  if (file_list)
  {
    for (i = 0; i < MAX_FILES_TO_SEARCH; i++)
    {
      if (file_list[i])
      {
        free(file_list[i]);
      }
    }
    free(file_list);
  }
}

int main(int argc, char *argv[])
{
  FILE *logfind_dot_file = fopen(DOT_FILE, "r");
  check(logfind_dot_file != NULL, "Failed to load dot file.");
  int number_of_lines = 0;
  int *ptr_number_of_lines = &number_of_lines;

  char **file_list = read_logfind_dot_file(logfind_dot_file, ptr_number_of_lines);
  check(file_list != NULL, "Failed to read content of dot file.");

  int i = 0;
  for (i = 0; i < number_of_lines; i++)
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
