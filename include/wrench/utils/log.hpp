#pragma once

#include <chrono>
#include <string>
#include "wrench/utils/timer.hpp"

namespace Wrench {

enum class LogLevel {
	Trace,
	Debug,
	Info,
	Warning,
	Error,
	Fatal,
};

enum class LogCategory {
	Core,
	Window,
	Renderer,
};

class Logger {
public:
	template<typename... Args>
	void Log(
		LogLevel level,
		LogCategory category,
		std::format_string<Args...> format,
		Args&&... args
	) {
		Log(
			level, category,
			std::format(
				format,
				std::forward<Args>(args)...
			)
		);
	}
private:
	using Clock = std::chrono::steady_clock;

	std::string get_timestamp_() const;
	const char* level_to_string_(LogLevel level) const;
	const char* category_to_string_(LogCategory category) const;

	void Log(
		LogLevel level,
		LogCategory category,
		std::string_view message
	);

	Timer timer_;
};

}