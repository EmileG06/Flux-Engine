#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/Texture.h"

namespace Flux {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filePath);
		virtual ~OpenGLTexture2D();

		void Bind(uint32_t slot = 0) const override;

		uint32_t GetWidth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }
		uint32_t GetRendererID() const override { return m_RendererID; }

	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID = 0;
	};

}
