# pragma once

// The main function must be declared as extern "C" to prevent name mangling.
// Basically, this is so that a C program can call this function, even though it is written in C++.
extern "C" __EXPORT int hello_world_main(int argc, char *argv[]);
