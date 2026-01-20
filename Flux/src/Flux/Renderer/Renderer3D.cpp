#include "FXPch.h"
#include "Renderer3D.h"

#include "Flux/Renderer/RenderCommand.h"
#include "Flux/Renderer/VertexArray.h"
#include "Flux/Renderer/Shader.h"

namespace Flux {

	struct Renderer3DData
	{
		Ref<VertexArray> CubeVertexArray;
		Ref<Shader> CubeShader;
	};

	static Renderer3DData s_Data;

	void Renderer3D::Init()
	{
		s_Data.CubeVertexArray = VertexArray::Create();

		float vertices[] = {
			// Front face
			-0.5f, -0.5f,  0.5f,  // 0: bottom-left-front
			 0.5f, -0.5f,  0.5f,  // 1: bottom-right-front
			 0.5f,  0.5f,  0.5f,  // 2: top-right-front
			-0.5f,  0.5f,  0.5f,  // 3: top-left-front

			// Back face
			-0.5f, -0.5f, -0.5f,  // 4: bottom-left-back
			 0.5f, -0.5f, -0.5f,  // 5: bottom-right-back
			 0.5f,  0.5f, -0.5f,  // 6: top-right-back
			-0.5f,  0.5f, -0.5f   // 7: top-left-back
		};

		Ref<VertexBuffer> cubeVertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		cubeVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		s_Data.CubeVertexArray->AddVertexBuffer(cubeVertexBuffer);

		uint32_t indices[] = {
			// Front face
			0, 1, 2,
			2, 3, 0,

			// Right face
			1, 5, 6,
			6, 2, 1,

			// Back face
			5, 4, 7,
			7, 6, 5,

			// Left face
			4, 0, 3,
			3, 7, 4,

			// Top face
			3, 2, 6,
			6, 7, 3,

			// Bottom face
			4, 5, 1,
			1, 0, 4
		};

		Ref<IndexBuffer> cubeIndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_Data.CubeVertexArray->SetIndexBuffer(cubeIndexBuffer);

		s_Data.CubeShader = Shader::Create("assets/shaders/Cube.glsl");
	}

	void Renderer3D::Shutdown()
	{
	}

	void Renderer3D::BeginScene(const PerspectiveCamera& camera)
	{
		s_Data.CubeShader->Bind();
		s_Data.CubeShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer3D::EndScene()
	{
	}

	void Renderer3D::DrawCube(const glm::mat4& transform, const glm::vec4& color)
	{
		s_Data.CubeShader->Bind();
		s_Data.CubeShader->SetMat4("u_Transform", transform);
		s_Data.CubeShader->SetFloat4("u_Color", color);

		s_Data.CubeVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.CubeVertexArray);
	}

	void Renderer3D::DrawMesh(const Mesh& mesh, const glm::mat4& transform, const glm::vec4& color)
	{
		s_Data.CubeShader->Bind();
		s_Data.CubeShader->SetMat4("u_Transform", transform);
		s_Data.CubeShader->SetFloat4("u_Color", color);

		mesh.GetVertexArray()->Bind();
		RenderCommand::DrawIndexed(mesh.GetVertexArray());
	}

}
