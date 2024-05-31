#pragma once

typedef struct
{
    unsigned int terminal_output_enable : 1;
    unsigned int terminal_timestamp_enable : 1;
    unsigned int file_output_enable : 1;
    unsigned int file_timestamp_enable : 1;
    unsigned int file_history_enable : 1;
} debug_flags_t;

void debug_enable(const char *path, debug_flags_t flags);
void debug_log(const char *format, ...);