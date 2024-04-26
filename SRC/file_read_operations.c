#include <stdio.h>
#include <stdlib.h>
#include "logfind.h"
#include "dbg.h"

char **read_logfind_dot_file(FILE *logfind_dot_file, int *number_of_lines)
{

  char *rc = NULL;
  int true = 1;
  // I tried to initialize an array with a single poinnter. This
  // did not work. Only the first element was initialized properly, but
  // I did not malloc enough memory for additional items.
  char **files_to_search = malloc(sizeof(char *) * MAX_FILES_TO_SEARCH);
  char **orig_address = files_to_search;

  rewind(logfind_dot_file);

  while (true)
  {
    *files_to_search = malloc(MAX_DATA);
    rc = fgets(*files_to_search, MAX_DATA, logfind_dot_file);

    if (rc == NULL)
    {
      break;
    }

    files_to_search++;
    (*number_of_lines)++;
  }

  return orig_address;
error:
  cleanup(logfind_dot_file, files_to_search);
}
