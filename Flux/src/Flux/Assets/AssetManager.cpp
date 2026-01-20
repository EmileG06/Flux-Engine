#include "FXPch.h"
#include "AssetManager.h"

namespace Flux {

	AssetPool<Mesh> AssetManager::s_MeshPool;

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
