#pragma once

#include <chrono>

namespace Wrench {

class Timer {
public:
	using Clock = std::chrono::steady_clock;

	Timer();

	void Reset();
	uint64_t ElapsedSeconds() const;
	uint64_t ElapsedMilliseconds() const;
private:
	Clock::time_point start_time_;
};

}