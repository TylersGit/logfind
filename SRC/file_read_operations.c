#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include "logfind.h"
#include "dbg.h"

glob_t **read_logfind_dot_file(FILE *logfind_dot_file, int *number_of_lines)
{

  char *rc = NULL;
  int true = 1;
  // I tried to initialize an array with a single poinnter. This
  // did not work. Only the first element was initialized properly, but
  // I did not malloc enough memory for additional items.
  glob_t **files_to_search = malloc(sizeof(char *) * MAX_FILES_TO_SEARCH);
  glob_t **orig_address = files_to_search;

  rewind(logfind_dot_file);

  while (true)
  {
    *files_to_search = malloc(sizeof(glob_t));
    char *temp = malloc(MAX_DATA);
    rc = fgets(temp, MAX_DATA, logfind_dot_file);

    if (rc == NULL)
    {
      break;
    }

    // strcspn gets the length of the string until the charset (second string - "\n") is met.
    // We use it to get the index of the \n char and replace it with a terminator byte.
    rc[strcspn(rc, "\n")] = 0;

    glob(rc, 0, NULL, *files_to_search);
    free(temp);

    files_to_search++;
    (*number_of_lines)++;
  }

  return orig_address;
error:
  cleanup(logfind_dot_file, files_to_search);
}

void print_file_list(char **file_list, int number_of_lines)
{
  int i = 0;
  for (i = 0; i < number_of_lines; i++)
  {
    if (strcmp(file_list[i], "") == 0 || file_list[i] == NULL)
      break;
    printf("String: %s \n", file_list[i]);
  }
}