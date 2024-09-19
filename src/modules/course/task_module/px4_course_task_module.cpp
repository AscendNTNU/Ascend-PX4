#include <cstdio>

#include "px4_course_task_module.h"
#define MIN(X,Y)	((X) < (Y) ? (X) : (Y))

using namespace time_literals;

int TaskModule::print_usage(const char *reason)
{
	printf("usage: task_module {start|stop|status}\n");
	return 0;
}

int TaskModule::task_spawn(int argc, char *argv[])
{
	_task_id = px4_task_spawn_cmd("module",
				      SCHED_DEFAULT,
				      SCHED_PRIORITY_DEFAULT,
				      1024,
				      (px4_main_t)&run_trampoline,
				      (char *const *)argv);

	if (_task_id < 0) {
		_task_id = -1;
		return -errno;
	}

	return 0;
}

/*
* We can use this function to implement custom commands for our module.
* I.e. things other than the standard start/stop/status/print_usage.
*/
int TaskModule::custom_command(int argc, char *argv[])
{
	printf("User ran command \"%s\" with arguments \"", argv[0]);

	for (int i = 1; i < argc; ++i) {
		printf("%s ", argv[i]);
	}

	printf("\"\n");
	return 1;
}

/*
* This function is called from the new thread that is created for the module.
* It should create an instance of the module and return it.
* It can also parse the arguments passed to the module, and use them to configure the module.
* You don't need to modify this function.
*/
TaskModule *TaskModule::instantiate(int argc, char *argv[])
{
	TaskModule *instance = new TaskModule();

	if (instance == nullptr) {
		PX4_ERR("alloc failed");
	}

	return instance;
}

/*
* Constructor for the TaskModule class.
*/
TaskModule::TaskModule()
	: ModuleParams(nullptr)
{
}

void TaskModule::greet(uint32_t num_greetings, bool long_greeting)
{
	constexpr const char *short_greeting_str = "Hi!";
	constexpr const char *long_greeting_str = "Hello, PX4 course!";

	for (uint32_t i = 0; i < num_greetings; i++) {
		printf("%s\n", long_greeting ? long_greeting_str : short_greeting_str);
	}
}

void TaskModule::sound_alert()
{
	tune_control_s tune{};
	tune.tune_override = true;
	tune.timestamp = hrt_absolute_time();
	tune.tune_id = 0;
	tune.frequency = 2000;
	tune.volume = 20;
	tune.duration = 150_ms;

	_tune_control_pub.publish(tune);

}

/*
* The run function is called when the module is started.
* This is where the main logic of the module should be.
* Notice that the function should return when should_exit() returns true.
*/
void TaskModule::run()
{
	// NB! Most time related functions in PX4 are in microseconds, not milliseconds!
	// By using time_literals we can convert to microseconds easily, like below.
	uint64_t greet_interval = 10_s;
	hrt_abstime last_greet{0};

	while (!should_exit()) {
		// Check for parameter updates. Maybe the greet interval has changed.
		if (_parameter_update_sub.updated()) {
			// clear update so that updated() returns false next time
			parameter_update_s update;
			_parameter_update_sub.copy(&update);

			// Update parameters from storage
			// This is provided by the ModuleParams class we inherit from
			updateParams();
		}

		auto time_since_last_greet = hrt_elapsed_time(&last_greet);

		if (time_since_last_greet >= greet_interval) {
			greet(_param_course_hi_num.get(), _param_course_hi_long.get());
			last_greet = hrt_absolute_time();
		}

		// TODO: Check for acceleration updates and sound alarm if
		// the acceleration is above a certain value

		// Sleep for 0.1 second or until the next greet time
		px4_usleep(MIN(100_ms, greet_interval - time_since_last_greet));
	}

}

/*
 * You don't need to change this function, it just calls main in the class.
*/
extern "C" __EXPORT int task_module_main(int argc, char *argv[])
{
	return TaskModule::main(argc, argv);
}
