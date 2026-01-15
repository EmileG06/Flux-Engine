#pragma once

#include "Flux/Core.h"
#include "Flux/Renderer/Shader.h"

namespace Flux {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int32_t value) override;
		void SetIntArray(const std::string& name, int32_t* values, uint32_t count) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		void SetMat4(const std::string& name, const glm::mat4& matrix) override;

		const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int32_t value);
		void UploadUniformIntArray(const std::string& name, int32_t* values, uint32_t count);

		void UploadUniformFloat1(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<uint32_t, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<uint32_t, std::string>& shaderSources);

	private:
		uint32_t m_RendererID = 0;
		std::string m_Name;
	};

}
