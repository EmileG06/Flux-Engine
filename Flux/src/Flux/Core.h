#pragma once

#include "Flux/Core/Log.h"
#include "Flux/Events/Event.h"

#include <memory>

#define FX_ENABLE_ASSERTS 1

#ifndef FX_PLATFORM_WINDOWS
#error Flux only supports windows!
#endif

#ifdef FX_CFG_DEBUG
#define FX_CORE_TRACE(x, ...) Flux::Logger::Log(Flux::LoggerType::Core, Flux::LogLevel::Trace, x, std::source_location::current(), __VA_ARGS__);
#define FX_CORE_DEBUG(x, ...) Flux::Logger::Log(Flux::LoggerType::Core, Flux::LogLevel::Debug, x, std::source_location::current(), __VA_ARGS__);
#define FX_CORE_INFO(x, ...) Flux::Logger::Log(Flux::LoggerType::Core, Flux::LogLevel::Info, x, std::source_location::current(), __VA_ARGS__);
#define FX_CORE_WARN(x, ...) Flux::Logger::Log(Flux::LoggerType::Core, Flux::LogLevel::Warning, x, std::source_location::current(), __VA_ARGS__);
#define FX_CORE_ERROR(x, ...) Flux::Logger::Log(Flux::LoggerType::Core, Flux::LogLevel::Error, x, std::source_location::current(), __VA_ARGS__);
#define FX_CORE_FATAL(x, ...) Flux::Logger::Log(Flux::LoggerType::Core, Flux::LogLevel::Fatal, x, std::source_location::current(), __VA_ARGS__);

#define FX_TRACE(x, ...) Flux::Logger::Log(Flux::LoggerType::App, Flux::LogLevel::Trace, x, std::source_location::current(), __VA_ARGS__);
#define FX_DEBUG(x, ...) Flux::Logger::Log(Flux::LoggerType::App, Flux::LogLevel::Debug, x, std::source_location::current(), __VA_ARGS__);
#define FX_INFO(x, ...) Flux::Logger::Log(Flux::LoggerType::App, Flux::LogLevel::Info, x, std::source_location::current(), __VA_ARGS__);
#define FX_WARN(x, ...) Flux::Logger::Log(Flux::LoggerType::App, Flux::LogLevel::Warning, x, std::source_location::current(), __VA_ARGS__);
#define FX_ERROR(x, ...) Flux::Logger::Log(Flux::LoggerType::App, Flux::LogLevel::Error, x, std::source_location::current(), __VA_ARGS__);
#define FX_FATAL(x, ...) Flux::Logger::Log(Flux::LoggerType::App, Flux::LogLevel::Fatal, x, std::source_location::current(), __VA_ARGS__);
#else
#define FX_CORE_TRACE(x, ...)
#define FX_CORE_DEBUG(x, ...)
#define FX_CORE_INFO(x, ...)
#define FX_CORE_WARN(x, ...)
#define FX_CORE_ERROR(x, ...)
#define FX_CORE_FATAL(x, ...)

#define FX_TRACE(x, ...)
#define FX_DEBUG(x, ...)
#define FX_INFO(x, ...)
#define FX_WARN(x, ...)
#define FX_ERROR(x, ...)
#define FX_FATAL(x, ...)
#endif

#ifdef FX_ENABLE_ASSERTS
#ifdef FX_CFG_DEBUG
#define FX_CORE_ASSERT(cond, fmt, ...) { if (!(cond)) { FX_CORE_FATAL(fmt, __VA_ARGS__); __debugbreak(); } }
#define FX_ASSERT(cond, fmt, ...) { if (!(cond)) { FX_FATAL(fmt, __VA_ARGS__); __debugbreak(); } }
#else
#define FX_CORE_ASSERT(cond, fmt, ...)
#define FX_ASSERT(cond, fmt, ...)
#endif
#endif

#define FX_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Flux {

	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T, typename... A>
	constexpr Scope<T> CreateScope(A&&... args)
	{
		return std::make_unique<T>(std::forward<A>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T, typename... A>
	constexpr Ref<T> CreateRef(A&&... args)
	{
		return std::make_shared<T>(std::forward<A>(args)...);
	}

}
