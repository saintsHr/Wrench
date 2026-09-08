#include "wrench/utils/log.hpp"

#include <chrono>
#include <cstdint>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <iostream>

namespace Wrench {

Logger::Logger() {
	start_time_ = Clock::now();
}

std::string Logger::get_timestamp_() const {
	uint64_t ms = static_cast<uint64_t>(
		std::chrono::duration_cast<std::chrono::milliseconds>(
			Clock::now() - start_time_
		).count()
	);

	uint64_t sec = ms / 1000;
	uint64_t min = sec / 60;
	uint64_t hrs = min / 60;

	ms %= 1000;
	sec %= 60;
	min %= 60;

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

void Logger::Log(
	LogLevel level,
	LogCategory category,
	std::string_view message
) {
	std::cout
		<< "["
		<< get_timestamp_()
		<< "]["
		<< level_to_string_(level)
		<< "]["
		<< category_to_string_(category)
		<< "] "
		<< message
		<< '\n'
	;
}

}