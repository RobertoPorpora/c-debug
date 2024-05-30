#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32)
#include <direct.h>
#define DEBUG_CREATE_FOLDER(dir) _mkdir(dir)
#define DEBUG_FOLDER_SEPARATOR '\\'
#else
#include <sys/stat.h>
#define DEBUG_CREATE_FOLDER(dir) mkdir(dir, 0700)
#define DEBUG_FOLDER_SEPARATOR '/'
#endif

FILE *debug_file = NULL;

#define DEBUG_DEFAULT_BUFSIZE 256

static char *get_file_name(char *path)
{
    char *last = NULL;
    while (path != NULL)
    {
        if (path[0] == DEBUG_FOLDER_SEPARATOR)
        {
            path = &path[1];
        }
        last = path;
        path = strchr(path, DEBUG_FOLDER_SEPARATOR);
    }
    return last;
}

void debug_enable(char *path)
{
    DEBUG_CREATE_FOLDER("debug");
    char debug_file_path[DEBUG_DEFAULT_BUFSIZE] = {'\0'};
    char *file_name = get_file_name(path);
    if (file_name == NULL)
    {
        return;
    }
    strncat(debug_file_path, "debug/", DEBUG_DEFAULT_BUFSIZE - 1);
    strncat(debug_file_path, file_name, DEBUG_DEFAULT_BUFSIZE - 1);
    strncat(debug_file_path, ".debug.log", DEBUG_DEFAULT_BUFSIZE - 1);

    debug_file = fopen(debug_file_path, "w");
}

char *current_timestamp()
{
    static char timestamp[DEBUG_DEFAULT_BUFSIZE] = {'\0'};
    time_t now = time(NULL);
    struct tm *tmvar = localtime(&now);
    strftime(timestamp, DEBUG_DEFAULT_BUFSIZE, "%Y-%m-%d %H:%M:%S", tmvar);
    return timestamp;
}

void debug_log(const char *description, const char *format, ...)
{
    if (debug_file == NULL)
    {
        return;
    }
    fprintf(debug_file, "%s - %s - ", current_timestamp(), description);
    va_list args;
    va_start(args, format);
    vfprintf(debug_file, format, args);
    va_end(args);
    fputs("\n", debug_file);
    fflush(debug_file);
}
