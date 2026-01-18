#pragma once

#include <string>
#include <print>
#include <chrono>
#include <source_location>
#include <glm/glm.hpp>

namespace Flux {

	enum class LogLevel
	{
		Trace = 0,
		Debug,
		Info,
		Warning,
		Error,
		Fatal
	};

	constexpr std::string_view LogLevelToColor(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::Trace:    return "\033[37m";
		case LogLevel::Debug:    return "\033[36m";
		case LogLevel::Info:     return "\033[32m";
		case LogLevel::Warning:  return "\033[33m";
		case LogLevel::Error:    return "\033[31m";
		case LogLevel::Fatal:	 return "\033[35m";
		default:                 return "\033[0m";
		}
	}

	constexpr std::string_view ResetColor = "\033[0m";

	enum class LoggerType
	{
		Core = 0,
		App
	};

	constexpr std::string_view LoggerTypeToString(LoggerType logger)
	{
		switch (logger)
		{
		case LoggerType::Core:  return "CORE";
		case LoggerType::App:	return "APP";
		default:				return "??";
		}
	}

	class Logger
	{
	public:
		template <typename... A>
		static void Log(
			LoggerType logger,
			LogLevel level,
			std::format_string<A...> format,
			std::source_location location,
			A&&... args)
		{
			auto now = std::chrono::floor<std::chrono::seconds>(
				std::chrono::system_clock::now());

			auto message = std::format(format, std::forward<A>(args)...);

			std::println("{}[{:%H:%M:%S}] [{}] {}:{}{} - {}",
				LogLevelToColor(level),
				now,
				LoggerTypeToString(logger),
				location.file_name(),
				location.line(),
				ResetColor,
				message);
		}
	};

}

template <>
struct std::formatter<glm::vec2> : std::formatter<std::string> {
	auto format(const glm::vec2& v, std::format_context& ctx) const {
		return std::formatter<std::string>::format(
			std::format("({}, {})", v.x, v.y), ctx);
	}
};

template <>
struct std::formatter<glm::vec3> : std::formatter<std::string> {
	auto format(const glm::vec3& v, std::format_context& ctx) const {
		return std::formatter<std::string>::format(
			std::format("({}, {}, {})", v.x, v.y, v.z), ctx);
	}
};

template <>
struct std::formatter<glm::vec4> : std::formatter<std::string> {
	auto format(const glm::vec4& v, std::format_context& ctx) const {
		return std::formatter<std::string>::format(
			std::format("({}, {}, {}, {})", v.x, v.y, v.z, v.w), ctx);
	}
};
