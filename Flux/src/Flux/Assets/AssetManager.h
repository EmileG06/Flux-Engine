#pragma once

#include "Flux/Core.h"
#include "Flux/Assets/AssetHandle.h"
#include "Flux/Renderer/Mesh.h"

namespace Flux {

	template <typename T>
	class AssetPool
	{
	public:
		template <typename... A>
		AssetHandle<T> Create(A&&... args)
		{
			uint32_t index;

			if (!m_FreeList.empty())
			{
				index = m_FreeList.back();
				m_FreeList.pop_back();
				m_Entries[index].Generation++;
			}
			else
			{
				index = (uint32_t)m_Entries.size();
				m_Entries.push_back({ T(), 0, false});
			}

			m_Entries[index].Asset = T(std::forward<A>(args)...);
			m_Entries[index].Active = true;

			return AssetHandle<T>(index, m_Entries[index].Generation);
		}

		Mesh* Get(AssetHandle<T> handle)
		{
			if (handle.Index >= m_Entries.size())
				return nullptr;

			Entry& entry = m_Entries[handle.Index];

			if (!entry.Active || entry.Generation != handle.Generation)
				return nullptr;

			return &entry.Asset;
		}

		void Destroy(AssetHandle<T> handle)
		{
			if (handle.Index >= m_Entries.size())
				return;

			Entry& entry = m_Entries[handle.Index];

			if (!entry.Active || entry.Generation != handle.Generation)
				return;

			entry.Active = false;
			entry.Asset.reset();
			m_FreeList.push_back(handle.Index);
		}
		
	private:
		struct Entry
		{
			T Asset;
			uint32_t Generation;
			bool Active;
		};

		std::vector<Entry> m_Entries;
		std::vector<uint32_t> m_FreeList;
	};

	class AssetManager
	{
	public:
		static void Init();

		static MeshHandle GetCube();

		static MeshHandle CreateMesh(const std::string& filePath);
		static MeshHandle CreateMesh(std::vector<Vertex3D>& vertices, std::vector<uint32_t>& indices);
		static Mesh* GetMesh(MeshHandle handle);

	private:
		static AssetPool<Mesh> s_MeshPool;
	};

}
