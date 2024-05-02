#include <stdio.h>
#include "dbg.h"
#include "logfind.h"

void finder(char **files_to_search, int files_to_search_len, char **words_to_search, int words_to_search_len, finder_cb finder_func)
{
    // Verify finder func is provided.
    // We do not need to check for the rest of the arguments, as they are already 
    // verified earlier in the program.
    check(finder_func != NULL, "finder_func not provided.");

    for (int i = 0; i < files_to_search_len; i++)
    {
        // TODO: Add cur_file to cleanup in case of error.

        FILE *cur_file = fopen(files_to_search[i], "r");
        check(cur_file != NULL, "Failed to open file %s.\n", files_to_search[i]);

        char line[MAX_DATA];
        while (fgets(line, sizeof(line), cur_file))
        {
            int rc = finder_func(line, words_to_search, words_to_search_len);
            
            if (rc == 1) {
                printf("%s: %s", files_to_search[i], line);
            }
        }

        fclose(cur_file);
    }

    return; 
error:
    // TODO: Add cleanup. see above.
    printf("Error handling still needs to be added\n");
}

int finder_and(char *line, char **words_to_search, int words_to_search_len)
{
    for (int i = 0; i < words_to_search_len; i++)
    {
        if (!strstr(line, words_to_search[i])){
            return 0;
        }
    }

    return 1;
}

int finder_or(char *line, char **words_to_search, int words_to_search_len)
{
    for (int i = 0; i < words_to_search_len; i++)
    {
        if (strstr(line, words_to_search[i])){
            return 1;
        }
    }
    
    return 0;
}
