#include <stdio.h>
#include "dbg.h"
#include "logfind.h"

int finder(char **files_to_search, int files_to_search_len, char **words_to_search, int words_to_search_len, finder_cb finder_func)
{
    // If the match is found according to search function, return 1.
    // Otherwise, return 0.
    int rc = 0;
    
    check(finder_func != NULL, "finder_func not provided.");

    for (int i = 0; i < files_to_search_len; i++)
    {
        // TODO: Add cur_file to cleanup in case of error.

        FILE *cur_file = fopen(files_to_search[i], "r");
        check(cur_file != NULL, "Failed to open file %s.\n", files_to_search[i]);

        printf("String: %s", files_to_search[i]);

        fclose(cur_file);
    }

    return rc;
error:
    // TODO: Add cleanup. see above.
    return -1;
}

int finder_and(char *line, char **words_to_search, int words_to_search_len)
{
    return 0;
}

int finder_or(char *line, char **words_to_search, int words_to_search_len)
{
    return 0;
}
