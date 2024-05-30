#include "debug.h"

int main(int argc, char **argv)
{
    // starting the logger.
    // argv[0] should contain the name of the executable
    // that is obtained by compiling this file.
    debug_enable(argv[0]);

    // logging arguments
    for (int i = 0; i < argc; i++)
    {
        debug_log("received argument", "%d => %s", i, argv[i]);
    }

    // some random data
    typedef struct
    {
        char name[20];
        int age;
        float height;
    } Person;
    Person alice = {"Alice", 25, 1.65};
    Person bob = {"Bob", 30, 1.80};

    // logging structs
    debug_log("Person 1", "Name: %s, Age: %d, Height: %.2f", alice.name, alice.age, alice.height);
    debug_log("Person 2", "Name: %s, Age: %d, Height: %.2f", bob.name, bob.age, bob.height);

    // it's ok for the process to terminate here without closing the debug file.
    // every line is written to disk as soon as it is produced.
    return 0;
}
