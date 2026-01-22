#include "FXPch.h"
#include "AssetManager.h"

namespace Flux {

	AssetPool<Mesh> AssetManager::s_MeshPool;

	static MeshHandle s_CubeMesh;

	void AssetManager::Init()
	{
		std::vector<Vertex3D> vertices = {
			{ { -0.5f, -0.5f,  0.5f } },
			{ {  0.5f, -0.5f,  0.5f } },
			{ {  0.5f,  0.5f,  0.5f } },
			{ { -0.5f,  0.5f,  0.5f } },
			{ { -0.5f, -0.5f, -0.5f } },
			{ {  0.5f, -0.5f, -0.5f } },
			{ {  0.5f,  0.5f, -0.5f } },
			{ { -0.5f,  0.5f, -0.5f } }
		};

		std::vector<uint32_t> indices = {
			0, 1, 2,
			2, 3, 0,
			1, 5, 6,
			6, 2, 1,
			5, 4, 7,
			7, 6, 5,
			4, 0, 3,
			3, 7, 4,
			3, 2, 6,
			6, 7, 3,
			4, 5, 1,
			1, 0, 4
		};

		s_CubeMesh = CreateMesh(vertices, indices);
	}

	Flux::MeshHandle AssetManager::GetCube()
	{
		return s_CubeMesh;
	}

	MeshHandle AssetManager::CreateMesh(const std::string& filePath)
	{
		return s_MeshPool.Create(filePath);
	}

	MeshHandle AssetManager::CreateMesh(std::vector<Vertex3D>& vertices, std::vector<uint32_t>& indices)
	{
		return s_MeshPool.Create(vertices, indices);
	}

	Mesh* AssetManager::GetMesh(MeshHandle handle)
	{
		return s_MeshPool.Get(handle);
	}

}
