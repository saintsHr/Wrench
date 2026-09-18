#include "wrench/utils/timer.hpp"
#include <chrono>

namespace Wrench {

Timer::Timer() {
	Reset();
}

void Timer::Reset() {
	start_time_ = Clock::now();
}

float Timer::Tick() {
    auto now = Clock::now();

    float elapsed = std::chrono::duration<float>(
        now - start_time_
    ).count();

    start_time_ = now;

    return elapsed;
}

float Timer::ElapsedSeconds() const {
	return static_cast<float>(
		std::chrono::duration_cast<std::chrono::seconds>(
			Clock::now() - start_time_
		).count()
	);
}

float Timer::ElapsedMilliseconds() const {
	return static_cast<float>(
		std::chrono::duration_cast<std::chrono::milliseconds>(
			Clock::now() - start_time_
		).count()
	);
}

float Timer::ElapsedMicroseconds() const {
	return static_cast<float>(
		std::chrono::duration_cast<std::chrono::microseconds>(
			Clock::now() - start_time_
		).count()
	);
}

}
