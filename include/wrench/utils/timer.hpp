#pragma once

#include <chrono>

namespace Wrench {

class Timer {
public:
	using Clock = std::chrono::steady_clock;

	Timer();

	void Reset();

	float Tick();

	float ElapsedSeconds() const;
	float ElapsedMilliseconds() const;
	float ElapsedMicroseconds() const;

protected:

private:
	Clock::time_point start_time_;
};

}
