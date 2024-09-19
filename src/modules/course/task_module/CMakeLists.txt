px4_add_module (
	MODULE modules__course__task_module
	MAIN task_module
	SRCS
		px4_course_task_module.cpp
	MODULE_CONFIG
		module.yaml
	)
