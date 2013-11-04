#ifndef JTIMER_H
#define JTIMER_H

class JTimer
{
private:
	int startTicks;
	int pausedTicks;

	bool paused;
	bool started;

public:
	JTimer(void);

	void start();
	void stop();
	void pause();
	void unpause();

	int getTicks();

	~JTimer(void);
};

#endif