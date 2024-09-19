# Hello, world!

This is one of the smallest possible programs for PX4.

Notice how we have four different files in this module :
- `Kconfig`
	- `CMakeLists.txt`
	- `hello_world.cpp`
	- `hello_world.h`


## Kconfig
The `Kconfig` file is the configuration file for the module. It tells the build system that this module exists. We can also add configuration options here.
For this simple module, the only configuration option is whether the module is enabled or not.
The options we define in the `Kconfig` file are available in the `make <build target> boardconfig` menu.

## CMakeLists
The `CMakeLists.txt` file is the build script for the module. It tells the build system how to build the module.
See the comments in the file for more information.

## hello_world.cpp
This is the main source file for the module. Right now, it contains only a main function.

## hello_world.h
This is the header file for the module. It contains the function prototype for the `hello_world` function.
