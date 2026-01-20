#pragma once

#include "Flux/Core.h"

#include <iostream>

namespace Flux {

	template <typename T>
	struct AssetHandle
	{
		AssetHandle() = default;
		AssetHandle(uint32_t index, uint32_t generation)
			: Index(index), Generation(generation) { }

		uint32_t Index;
		uint32_t Generation;

		bool IsValid() const { return Index != InvalidIndex; }

		static constexpr uint32_t InvalidIndex = 0xFFFFFFFF;
	};

}
