#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define DOT_FILE ".logfind"

char *read_logfind_dot_file(FILE logfind_dot_file) {
  char *files_to_search;


  return files_to_search; 
}

int main(int argc, char *argv[])
{
  FILE *logfind_dot_file = fopen(DOT_FILE, "r");
  check(logfind_dot_file != NULL, "Failed to load file.");

  char *files_to_search = load_files_to_search(logfind_dot_file);




  if (logfind_dot_file) free(logfind_dot_file);
  return 0;
error:
  if (logfind_dot_file) free(logfind_dot_file);
  return -1;
}
