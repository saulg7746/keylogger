#ifndef TIMER_H
#define TIMER_H
#include <thread>
#include <chrono>


class Timer
{
public:
	Timer();
	Timer(const std::function<void(void)>& func, const unsigned long &i);

	// Queries
	bool is_active();
	const std::function <void(void)> &call_thread_function() const;

	// Modifiers
	void set_function(const std::function<void(void)>& f); 
	void set_duration(const unsigned long &i);
	void start(bool sync);
	void stop();

private:
	//Timer will be a thread that is executed while timer is alive
	std::thread Thread;
	std::function<void(void)> func = nullptr;
	long repeat = -1L;
	bool active = false;
	std::chrono::milliseconds duration = std::chrono::milliseconds(0);

	void run(){
		std::this_thread::sleep_for(duration);
		if (active)
			call_thread_function()();
	}

	void thread_function(){
		while (active)
			run();
	}
 
};

Timer::Timer() {}
Timer::Timer(const std::function<void(void)>& func, const unsigned long &i)
	: func(func), duration(i) {}

bool Timer::is_active()	{	return active;	}
const std::function <void(void)> &Timer::call_thread_function() const {
	return func;
}


void Timer::set_function(const std::function<void(void)>& f) {
	func = f;
}
void Timer::set_duration(const unsigned long &i) {
	duration = std::chrono::milliseconds(i);
}
void Timer::start(bool sync)
{
	if (active)
		return;
	active = true;
	if (sync)
		Thread = std::thread(&Timer::thread_function, this);
	else
		this->thread_function();
}
void Timer::stop()
{
	active = false;
	Thread.join();
}


#endif
