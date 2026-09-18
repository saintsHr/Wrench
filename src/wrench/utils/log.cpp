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

#include <cstdlib>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <iostream>
#include <cmath>

#include "wrench/utils/log.hpp"

namespace Wrench {

Logger* gLogger = nullptr;

std::string Logger::get_timestamp_() const {
    float total_ms = timer_.ElapsedMilliseconds();

    int hrs = static_cast<int>(total_ms / 3600000);
    total_ms = std::fmod(total_ms, 3600000.0f);

    int min = static_cast<int>(total_ms / 60000);
    total_ms = std::fmod(total_ms, 60000.0f);

    int sec = static_cast<int>(total_ms / 1000);
    int ms = static_cast<int>(std::fmod(total_ms, 1000.0f));

    std::ostringstream stream;

    stream
        << std::setfill('0')
        << std::setw(2) << hrs << ":"
        << std::setw(2) << min << ":"
        << std::setw(2) << sec << "."
        << std::setw(3) << ms;

    return stream.str();
}

const char* Logger::level_to_string_(LogLevel level) const {
	switch (level) {
		case LogLevel::Trace: return "Trace";
		case LogLevel::Debug: return "Debug";
		case LogLevel::Info: return "Info";
		case LogLevel::Warning: return "Warning";
		case LogLevel::Error: return "Error";
		case LogLevel::Fatal: return "Fatal";

		default: return "Unknown";
	}
}


const char* Logger::category_to_string_(LogCategory category) const {
	switch (category) {
		case LogCategory::Core: return "Core";
		case LogCategory::Window: return "Window";
		case LogCategory::Renderer: return "Renderer";

		default: return "Unknown";
	}
}

void Logger::write_(
	LogLevel level,
	LogCategory category,
	std::string_view message
) {
	std::cout
		<< "["
		<< get_timestamp_()
		<< "]["
		<< category_to_string_(category)
		<< "]["
		<< level_to_string_(level)
		<< "] "
		<< message
		<< '\n'
	;

	std::cout.flush();

	if (level == LogLevel::Fatal) std::exit(EXIT_FAILURE);
}

}
