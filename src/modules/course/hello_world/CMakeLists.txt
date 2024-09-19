# This tells PX4 that this directory contains a module.
# It is also possible to add a library or a test. (But we will not cover that in this course.)
px4_add_module(
# This is the name of the module. It is common to use the following format:
# (It is possible to have one extra level of submodules, like we have here.)
# MODULE <namespace>__<module_name>
	MODULE modules__course__hello_world

# This is the name of the main function of the module.
# This means that there must be a function with this name, postfixed with "_main" somewhere in the source code.
# E.g. if this is "hello_world", there must be a function called "hello_world_main".
	MAIN hello_world

# This is a list of source code files that are part of the module and should be built.
# The source files are relative to the directory of this CMakeLists.txt file.
	SRCS
	hello_world.cpp
)

# To see the full list of options, see the file `cmake/px4_add_module.cmake`
