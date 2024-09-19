#include <px4_platform_common/log.h>
#include <stdio.h>

#include <uORB/topics/tune_control.h>

#include "hello_world.h"

using namespace time_literals;

void play_note(int frequency = 440, int duration = 250_ms, int volume = 20)
{
	// The tune_control topic is used to play tunes or individual notes on the buzzer
	tune_control_s tune{};

	tune.timestamp = hrt_absolute_time(); // Must be set to the current time
	tune.tune_id = 0; // Indicates a custom note
	tune.frequency = frequency;
	tune.volume = volume;
	tune.duration = duration;

	// Publish the tune_control message
	orb_advertise(ORB_ID(tune_control), &tune);
}

int hello_world_main(int argc, char *argv[])
{
	PX4_INFO("Hello, World!");
	// TODO: Play a note
	return 0;
}
