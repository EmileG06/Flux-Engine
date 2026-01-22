#pragma once

#include <Flux.h>

namespace Flux {

	class Widgets
	{
	public:
		static void DrawVec3(const std::string& label, glm::vec3& value, float resetValue = 0.0f, float columnWidth = 100.0f);
	};

}
