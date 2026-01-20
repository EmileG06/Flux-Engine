#pragma once

#include "Flux/Core.h"
#include "Flux/Assets/AssetHandle.h"
#include "Flux/Renderer/Vertex3D.h"
#include "Flux/Renderer/VertexArray.h"
#include "Flux/Renderer/Shader.h"

namespace Flux {

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(const std::string& filePath);
		Mesh(std::vector<Vertex3D>& vertices, std::vector<uint32_t>& indices);

		const Ref<VertexArray>& GetVertexArray() const { return m_VertexArray; }

	private:
		void CreateBuffers(std::vector<Vertex3D>& vertices, std::vector<uint32_t>& indices);

	private:
		Ref<VertexArray> m_VertexArray;
	};

	using MeshHandle = AssetHandle<Mesh>;

}
