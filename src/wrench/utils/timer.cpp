#include "wrench/utils/timer.hpp"

namespace Wrench {

Timer::Timer() {
	Reset();
}

void Timer::Reset() {
	start_time_ = Clock::now();
}

uint64_t Timer::ElapsedSeconds() const {
	return static_cast<uint64_t>(
		std::chrono::duration_cast<std::chrono::seconds>(
			Clock::now() - start_time_
		).count()
	);
}

uint64_t Timer::ElapsedMilliseconds() const {
	return static_cast<uint64_t>(
		std::chrono::duration_cast<std::chrono::milliseconds>(
			Clock::now() - start_time_
		).count()
	);
}

}