#ifndef __logfind_h__
#define __logfind_h__

#define DOT_FILE ".logfind"
#define MAX_DATA 512 
#define MAX_FILES_TO_SEARCH 10

typedef int (*finder_cb)(char *line, char **words_to_search, int words_to_search_len);


char **read_logfind_dot_file(FILE *logfind_dot_file, int *number_of_lines);

void print_file_list(char **file_list, int number_of_lines);

void cleanup(FILE *logfind_dot_file, char **file_list);

int finder(char **files_to_search, int files_to_search_len, char **words_to_search, int words_to_search_len, finder_cb finder_func);

int finder_and(char *line, char **words_to_search, int words_to_search_len);

int finder_or(char *line, char **words_to_search, int words_to_search_len);

#endif