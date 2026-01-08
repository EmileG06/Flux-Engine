#include "FXPch.h"
#include "Renderer2D.h"

#include "Flux/Renderer/RenderCommand.h"
#include "Flux/Renderer/VertexArray.h"
#include "Flux/Renderer/Shader.h"

namespace Flux {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Storage;

	void Renderer2D::Init()
	{
		s_Storage = new Renderer2DStorage();
		FX_CORE_ASSERT(s_Storage, "Storage was nullptr!");

		s_Storage->QuadVertexArray = VertexArray::Create();

		float vertices[] = {
		   -0.5f, -0.5f,  0.0f,
			0.5f, -0.5f,  0.0f,
			0.5f,  0.5f,  0.0f,
		   -0.5f,  0.5f,  0.0f
		};

		Ref<VertexBuffer> quadVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" }
		};
		quadVertexBuffer->SetLayout(layout);
		s_Storage->QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

		uint32_t indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_Storage->QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

		s_Storage->FlatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		FX_CORE_ASSERT(s_Storage, "Storage was nullptr!");
		delete s_Storage;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Storage->FlatColorShader->Bind();
		s_Storage->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		DrawQuad(transform, color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		s_Storage->FlatColorShader->Bind();
		s_Storage->FlatColorShader->SetFloat4("u_Color", color);
		s_Storage->FlatColorShader->SetMat4("u_Transform", transform);

		s_Storage->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Storage->QuadVertexArray);
	}

}
