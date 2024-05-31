#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#include "debug.h"

//-----------------------------------------------------------------------------

#if defined(_WIN32)

#include <direct.h>
#define create_folder(dir) _mkdir(dir)
#define SYSTEM_FOLDER_SEPARATOR '\\'

#include <windows.h>
uint64_t get_milliseconds()
{
    SYSTEMTIME st;
    GetSystemTime(&st);
    return (uint64_t)st.wHour * 3600000ULL + (uint64_t)st.wMinute * 60000ULL + (uint64_t)st.wSecond * 1000ULL + (uint64_t)st.wMilliseconds;
}

#else

#include <sys/stat.h>
#define create_folder(dir) mkdir(dir, 0700)
#define SYSTEM_FOLDER_SEPARATOR '/'

#include <sys/time.h>
uint64_t get_milliseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000ULL + (uint64_t)tv.tv_usec / 1000ULL;
}

#endif

//-----------------------------------------------------------------------------

FILE *debug_file = NULL;
debug_flags_t debug_flags = {0};

#define DEFAULT_BUFFER_SIZE 256

//-----------------------------------------------------------------------------

static const char *get_file_name(const char *path)
{
    const char *last = NULL;
    while (path != NULL)
    {
        if (path[0] == SYSTEM_FOLDER_SEPARATOR)
        {
            path = &path[1];
        }
        last = path;
        path = strchr(path, SYSTEM_FOLDER_SEPARATOR);
    }
    return last;
}

static char *current_timestamp()
{
    static char timestamp[DEFAULT_BUFFER_SIZE] = {'\0'};
    time_t now = time(NULL);
    struct tm *tmvar = localtime(&now);
    strftime(timestamp, DEFAULT_BUFFER_SIZE, "%Y%m%d_%H%M%S_", tmvar);
    sprintf(timestamp + strlen(timestamp), "%03ld", get_milliseconds() % 1000);
    return timestamp;
}

//-----------------------------------------------------------------------------

void debug_enable(const char *path, debug_flags_t flags)
{
    debug_flags = flags;

    if (!debug_flags.file_output_enable)
    {
        return;
    }
    create_folder("debug");
    char debug_file_path[DEFAULT_BUFFER_SIZE] = {'\0'};
    const char *file_name = get_file_name(path);
    if (file_name == NULL)
    {
        return;
    }
    strncat(debug_file_path, "debug/", DEFAULT_BUFFER_SIZE - 1);
    if (debug_flags.file_history_enable)
    {
        strncat(debug_file_path, current_timestamp(), DEFAULT_BUFFER_SIZE - 1);
        strncat(debug_file_path, "_", DEFAULT_BUFFER_SIZE - 1);
    }
    strncat(debug_file_path, file_name, DEFAULT_BUFFER_SIZE - 1);
    strncat(debug_file_path, ".log", DEFAULT_BUFFER_SIZE - 1);

    debug_file = fopen(debug_file_path, "w");
}

void debug_log(const char *format, ...)
{
    if (debug_flags.file_output_enable && debug_file != NULL)
    {
        if (debug_flags.file_timestamp_enable)
        {
            fprintf(debug_file, "%s ", current_timestamp());
        }
        va_list args;
        va_start(args, format);
        vfprintf(debug_file, format, args);
        va_end(args);
        fputs("\n", debug_file);
        fflush(debug_file);
    }
    if (debug_flags.terminal_output_enable)
    {
        if (debug_flags.terminal_timestamp_enable)
        {
            fprintf(stdout, "%s ", current_timestamp());
        }
        va_list args;
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
        fputs("\n", stdout);
        fflush(stdout);
    }
}

//-----------------------------------------------------------------------------