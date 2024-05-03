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

  check(argc > 1, "No parameters were provided. \nUsage: ./ex26 [-o] KEYWORDS");

  int set_or_flag = 0;
  if (strcmp(argv[1], "-o") == 0) set_or_flag = 1;

  int words_to_search_len = argc - 1 - set_or_flag;
  check(words_to_search_len > 0, "No keywords were provided.");

  int number_of_lines = 0;
  int *ptr_number_of_lines = &number_of_lines;

  // TODO: Update cleanup function to free the words_to_search array.
  char **words_to_search = malloc(sizeof(char *) * words_to_search_len);
  memcpy(words_to_search, &argv[1 + set_or_flag], sizeof(char *) * words_to_search_len);
  check(words_to_search != NULL, "Failed to copy argv to words_to_search.");

  char **file_list = read_logfind_dot_file(logfind_dot_file, ptr_number_of_lines);
  check(file_list != NULL, "Failed to read content of dot file.");

  #ifndef NDEBUG
  print_file_list(file_list, number_of_lines);
  #endif

  finder_cb finder_func = NULL;
  if (set_or_flag){
    finder_func = finder_or;
  } else {
    finder_func = finder_and;
  }
  
  finder(file_list, number_of_lines, words_to_search, words_to_search_len, finder_func);

  cleanup(logfind_dot_file, file_list);
  return 0;
error:
  cleanup(logfind_dot_file, file_list);
  return -1;
}
