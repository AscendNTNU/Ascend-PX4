#include "px4_course.h"

int PX4Course::print_usage(const char *reason){
	printf("Use the PX4 course module however you like!\n");
	return 0;
}

int PX4Course::task_spawn(int argc, char*argv[]){
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

int PX4Course::custom_command(int argc, char *argv[]){
	printf("User ran command %s with arguments \"", argv[0]);
	for (int i = 0; i < argc; ++i){
		printf("%s ", argv[i]);
	}
	printf("\"\n");
	return 1;
}

PX4Course *PX4Course::instantiate(int argc, char *argv[])
{
	PX4Course *instance = new PX4Course();
	if (instance == nullptr) {
		PX4_ERR("alloc failed");
	}

	return instance;
}

PX4Course::PX4Course()
	: ModuleParams(nullptr)
{
}

void PX4Course::run()
{
	bool first_iteration{true};
	while (!should_exit()) {

		sleep(20);
		PX4_INFO("PX4 course is%srunning!", first_iteration ? " " : " still ");

		// Add code to beep here!

		parameters_update(false);
	}

}

void PX4Course::parameters_update(bool force)
{
	// check for parameter updates
	if (_parameter_update_sub.updated() || force) {
		// clear update
		parameter_update_s update;
		_parameter_update_sub.copy(&update);

		// update parameters from storage
		updateParams();
	}
}

int PX4Course::print_status(){
	auto num_hellos = _param_px4cs_num_greet.get();
	for (int i = 0; i < num_hellos; ++i){
		printf("Hello! ");
	}
	printf("\n");
	return 0;
}

/**
 * You don't need to change this function, it just calls main in the class.
*/
extern "C" __EXPORT int px4_course_main(int argc, char *argv[])
{
	return PX4Course::main(argc, argv);
}
