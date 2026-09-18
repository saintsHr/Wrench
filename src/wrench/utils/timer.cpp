/*
MIT License

Copyright (c) 2026 saintsHr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
