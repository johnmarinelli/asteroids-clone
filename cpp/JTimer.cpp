#include "JTimer.h"


JTimer::JTimer(void)
{
	startTicks = 0;
	pausedTicks = 0;
	started = false;
	paused = false;
}

void JTimer::start()
{
	started = true;
}


JTimer::~JTimer(void)
{
}
