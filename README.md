# c-debug

Simple log-to-file library for debugging C/C++ programs.


## Why Use This?

Regardless of the fact that logging to a file with precise timestamps can generally be more practical and useful than printing to the screen...

There are times when you need to debug issues:
- that only manifest during runtime.
- when access to a debugger isn't available.
- when halting the process isn't feasible.
- when the stdout/stderr isn't visible.
- when dealing with a plug-in or a child process.

In such scenarios, logging to a file can be invaluable.

This repository offers a straightforward logger, complete with detailed timestamps, enabling quick setup for file logging.

This library can also be used for simple terminal printing.  
It adds the following features:
- a global switch to disable all debug_log() calls.
- timestamp to the output (can be easily disabled).

<div style="text-align: right;">
    <a href="#c-debug">Back to top</a>
</div>


## Usage

1. Copy `debug.c` and `debug.h` into your project.
2. Insert `#include "debug.h"` in the `.c` file where you want to use the logging functions.
3. Call `debug_enable(PATH, FLAGS);` at the start of your `main()`.  
    - `PATH` can be a path to any file or folder where you want the log file to be written.  
    - **Trick**: Use `debug_enable(argv[0], FLAGS);` to write the log file in the same folder as the executable.
    - `FLAGS` allows to turn options on or off. See "FLAGS options" below.
4. Every time you need to log something, call `debug_log(SOMETHING);` just like you would call `printf(SOMETHING);`.
5. When you have finished debugging, comment or delete `// debug_enable(PATH, FLAGS);` to disable logging.
    - No need to comment or delete any `debug_log();` line. Without `debug_enable();`, they will do nothing.

<div style="text-align: right;">
    <a href="#c-debug">Back to top</a>
</div>


## FLAGS options

There are some flags you can use to customize how debug_log() works.


### FLAGS.terminal_output_enable

Why forgo terminal output while logging to file?  
Set this to 1 in order to see everything you log to file also on the process stdout.
Do you want to disable this at some point?  
Simply set it back to 0 before calling debug_enable().


### FLAGS.terminal_timestamp_enable

If you don't want timestamps for every line in your terminal, set this to 0.


### FLAGS.file_output_enable

Need to disable logging to file?  
Use this switch to enable (1) or disable (0) file logging.


### FLAGS.file_timestamp_enable

If you don't want timestamps for every line in your file, set this to 0.


### FLAGS.file_history_enable

**FLAGS.file_history_enable = 0**: only one file is written and it is overwritten over and over everytime the executable executes.
```
root
├── executable.exe
└── debug
    └── executable.exe.log
```

**FLAGS.file_history_enable = 1**: it generates a new timestamped file each time the executable is executed. 
```
root
├── executable.exe
└── debug
    ├── 20240531_1234_000_executable.exe.log
    ├── 20240531_1234_123_executable.exe.log
    ├── 20240531_1256_012_executable.exe.log
    └── 20240531_1345_987_executable.exe.log
```

<div style="text-align: right;">
    <a href="#c-debug">Back to top</a>
</div>


## Testing and compiling the example.

- Check `example.c`.
- Compile it with command `gcc example.c debug.c -o example`.
- Execute it with command `./example`.
- Check the log file that has been written in `debug/` folder.
- Experiment with the `example.c` file (disable debugging, change FLAGS, log other types of data, etc.).

<div style="text-align: right;">
    <a href="#c-debug">Back to top</a>
</div>


## Links.

- [Debug logger for Python.](https://github.com/RobertoPorpora/python-debug)
- [Debug logger for C/C++.](https://github.com/RobertoPorpora/c-debug)
- [Debug logger for Node.js.](https://github.com/RobertoPorpora/node-debug)
- [Debug logger for Rust.](https://github.com/RobertoPorpora/rust-debug)


<div style="text-align: right;">
    <a href="#c-debug">Back to top</a>
</div>
