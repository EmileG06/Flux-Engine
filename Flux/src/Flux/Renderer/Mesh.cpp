#include "FXPch.h"
#include "Mesh.h"

namespace Flux {

	Mesh::Mesh(const std::string& filePath)
	{
		FX_CORE_ASSERT(false, "This way of creating meshes isn't supported!");
	}

	Mesh::Mesh(std::vector<Vertex3D>& vertices, std::vector<uint32_t>& indices)
	{
		FX_CORE_ASSERT(!vertices.empty() && !indices.empty(), "Mesh was created with no vertices/indices!");
		CreateBuffers(vertices, indices);
	}

	void Mesh::CreateBuffers(std::vector<Vertex3D>& vertices, std::vector<uint32_t>& indices)
	{
		m_VertexArray = VertexArray::Create();

		Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices.size() * sizeof(Vertex3D));
		vertexBuffer->SetData(vertices.data(), vertices.size() * sizeof(Vertex3D));
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), indices.size());
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}

}
