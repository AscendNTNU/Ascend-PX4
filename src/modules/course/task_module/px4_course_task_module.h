#pragma once

#include <px4_platform_common/module.h>
#include <px4_platform_common/module_params.h>
#include <uORB/SubscriptionInterval.hpp>
#include <uORB/Publication.hpp>
#include <uORB/topics/parameter_update.h>
#include <uORB/topics/vehicle_acceleration.h>
#include <uORB/topics/tune_control.h>

using namespace time_literals;
extern "C" __EXPORT int task_module_main(int argc, char *argv[]);

// Note that the TaskModule inherits from the ModuleBase, which gives us some useful features

class TaskModule : public ModuleBase<TaskModule>, public ModuleParams
{
public:
	TaskModule();

	virtual ~TaskModule() = default;

	// All classes that inherit from ModuleBase and run in their own thread
	// must implement the funtions below.
	static int task_spawn(int argc, char *argv[]);
	static TaskModule *instantiate(int argc, char *argv[]);
	static int custom_command(int argc, char *argv[]);
	static int print_usage(const char *reason = nullptr);
	void run() override;

private:
	void greet(uint32_t num_greetings, bool long_greeting);
	void sound_alert();

	DEFINE_PARAMETERS(
		(ParamInt<px4::params::COURSE_HI_NUM>) _param_course_hi_num,
		(ParamBool<px4::params::COURSE_HI_LONG>) _param_course_hi_long
	)

	// Subscriptions
	uORB::SubscriptionInterval _parameter_update_sub{ORB_ID(parameter_update), 1_s};
	uORB::SubscriptionInterval _vehicle_acceleration_sub{ORB_ID(vehicle_acceleration), 100_ms};
	uORB::Publication<tune_control_s> _tune_control_pub{ORB_ID(tune_control)};
};
