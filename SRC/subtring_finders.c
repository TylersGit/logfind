#include <stdio.h>
#include "dbg.h"
#include "logfind.h"

void finder(glob_t **globs_to_search, int globs_to_search_len, char **words_to_search, int words_to_search_len, finder_cb finder_func)
{
    // Verify finder func is provided.
    // We do not need to check for the rest of the arguments, as they are already
    // verified earlier in the program.
    check(finder_func != NULL, "finder_func not provided.");

    for (int i = 0; i < globs_to_search_len; i++)
    {

        for (int file_index = 0; file_index < globs_to_search[i]->gl_pathc; file_index++)
        {
            // TODO: Add cur_file to cleanup in case of error.
            FILE *cur_file = fopen(globs_to_search[i]->gl_pathv[file_index], "r");
            check(cur_file != NULL, "Failed to open file %s.\n", globs_to_search[i]->gl_pathv[file_index]);

            char line[MAX_DATA];
            while (fgets(line, sizeof(line), cur_file))
            {
                int rc = finder_func(line, words_to_search, words_to_search_len);

                if (rc == 1)
                {
                    printf("%s: %s", globs_to_search[i]->gl_pathv[file_index], line);
                }
            }

            fclose(cur_file);
        }
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
        if (!strstr(line, words_to_search[i]))
        {
            return 0;
        }
    }

    return 1;
}

int finder_or(char *line, char **words_to_search, int words_to_search_len)
{
    for (int i = 0; i < words_to_search_len; i++)
    {
        if (strstr(line, words_to_search[i]))
        {
            return 1;
        }
    }

    return 0;
}
