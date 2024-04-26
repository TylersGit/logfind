#ifndef __logfind_h__
#define __logfind_h__

#define DOT_FILE ".logfind"
#define MAX_DATA 512 
#define MAX_FILES_TO_SEARCH 10

char **read_logfind_dot_file(FILE *logfind_dot_file, int *number_of_lines);

void cleanup(FILE *logfind_dot_file, char **file_list);

#endif