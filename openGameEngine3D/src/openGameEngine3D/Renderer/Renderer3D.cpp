#include "ogepch.h"
#include "openGameEngine3D/Renderer/Renderer3D.h"

#include "openGameEngine3D/Renderer/VertexArray.h"
#include "openGameEngine3D/Renderer/Shader.h"
#include "openGameEngine3D/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>
#include <glad/glad.h>

/*
	David Milot
	License : MIT
*/

namespace openGameEngine3D
{
	unsigned int VBO,cubeVAO;
	unsigned int lightCubeVAO;

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer3DData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		//Ref<VertexArray> QuadVertexArray;
		Ref<VertexArray> CubeVertexArray;
		Ref<VertexBuffer> CubeVertexBufferArray;
		//Ref<VertexBuffer> QuadVertexBuffer;
		Ref<VertexArray> LightCubeVertexArray;
		Ref<VertexBuffer> LightCubeBufferArray;
		//Ref<Shader> TextureShader;
		Ref<Shader> LightingShader;
		Ref<Shader> BasicCubeShader;
		//Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];

		Renderer3D::Statistics Stats;
	};

	static Renderer3DData s_Data;

	void Renderer3D::Init ()
	{
		OGE_PROFILE_FUNCTION ();

		/*s_Data.LightingShader = Shader::Create ("LightingCube",
			"assets/shaders/LightCube3DVertex.glsl",
			"assets/shaders/LightCube3DFragment.glsl");*/

		s_Data.BasicCubeShader = Shader::Create ("assets/shaders/LightCube3D.glsl");

		//s_Data.BasicCubeShader = Shader::Create ("BasicCube",
		//	"assets/shaders/BasicLighting3DVertex.glsl",
		//	"assets/shaders/BasicLighting3DFragment.glsl");

		s_Data.LightingShader = Shader::Create ("assets/shaders/BasicLighting3D.glsl");
		// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};
		
		/*s_Data.QuadVertexArray = VertexArray::Create ();

		s_Data.QuadVertexBuffer = VertexBuffer::Create (s_Data.MaxVertices * sizeof (QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout ({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
			});
		s_Data.QuadVertexArray->AddVertexBuffer (s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create (quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer (quadIB);
		delete[] quadIndices;*/

		/*s_Data.WhiteTexture = Texture2D::Create (1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData (&whiteTextureData, sizeof (uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;*/

		//s_Data.TextureShader = Shader::Create ("assets/shaders/Texture.glsl");

		//s_Data.LightingShader->Bind ();

		s_Data.CubeVertexArray = VertexArray::Create ();		//glCreateVertexArrays (1, &m_RendererID);

		s_Data.CubeVertexBufferArray = VertexBuffer::Create (vertices, sizeof (vertices));

		/*
		* glCreateBuffers (1, &m_RendererID);
		* glBindBuffer (GL_ARRAY_BUFFER, m_RendererID);
		* glBufferData (GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		*/
		s_Data.CubeVertexArray->Bind ();		//glBindVertexArray (m_RendererID);
		s_Data.CubeVertexArray->AddCustomVertexBuffer (0, 3, ShaderDataType::Float, false, 6, 0); 
		/*									^^^
		* glVertexAttribPointer (index, 3, ShaderDataTypeToOpenGLBaseType(type), normalized, stride * sizeof (float), (void*)offset);
		* glEnableVertexAttribArray (index);
		*/

		s_Data.CubeVertexArray->AddCustomVertexBuffer (1, 3, ShaderDataType::Float, false, 6, 3);
		
		//LightCubeBufferArray

		s_Data.LightCubeVertexArray = VertexArray::Create ();	//glGenVertexArrays(1, &lightCubeVAO);
		s_Data.LightCubeBufferArray = VertexBuffer::Create ();
		s_Data.LightCubeBufferArray->BindVertexArray ();		//glBindVertexArray(lightCubeVAO)
		s_Data.LightCubeBufferArray->Bind ();					//glBindBuffer (GL_ARRAY_BUFFER, VBO);
		s_Data.LightCubeBufferArray->AddCustomVertexBuffer (0, 3, ShaderDataType::Float, false, 6, 0);	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
																										//glEnableVertexAttribArray (0);

		// note that we update the lamp's position attribute's stride to reflect the updated buffer data

		//s_Data.TextureShader->SetIntArray ("u_Textures", samplers, s_Data.MaxTextureSlots);

		// Set first texture slot to 0
		//s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		//s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		//s_Data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		//s_Data.QuadVertexPositions[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		//s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };


		glGenVertexArrays (1, &cubeVAO);
		glGenBuffers (1, &VBO);

		glBindBuffer (GL_ARRAY_BUFFER, VBO);
		glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray (cubeVAO);

		// position attribute
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)0);
		glEnableVertexAttribArray (0);
		// normal attribute
		glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)(3 * sizeof (float)));
		glEnableVertexAttribArray (1);

		// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
		glGenVertexArrays (1, &lightCubeVAO);
		glBindVertexArray (lightCubeVAO);

		glBindBuffer (GL_ARRAY_BUFFER, VBO);
		// note that we update the lamp's position attribute's stride to reflect the updated buffer data
		glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)0);
		glEnableVertexAttribArray (0);
	}

	void Renderer3D::Shutdown ()
	{
		OGE_PROFILE_FUNCTION ();

		//delete[] s_Data.QuadVertexBufferBase;

		/*glDeleteVertexArrays (1, &cubeVAO);
		glDeleteVertexArrays (1, &lightCubeVAO);
		glDeleteBuffers (1, &VBO);*/
	}

	/*
	void Renderer3D::BeginScene (const PerspectiveCamera& camera)
	{
		OGE_PROFILE_FUNCTION ();

		s_Data.TextureShader->Bind ();
		s_Data.TextureShader->SetMat4 ("u_ViewProjection", camera.GetViewProjectionMatrix ());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}*/

	void Renderer3D::BeginScene (const Camera3D& camera3D, const glm::mat4& transform)
	{
		OGE_PROFILE_FUNCTION ();
		//glm::mat4 viewProj = camera3D.GetProjection () * glm::inverse (transform);

		// view/projection transformations
		glm::mat4 projectionCamera = camera3D.GetProjection ();
		//glm::mat4 projection = glm::perspective (glm::radians (camera3D.Zoom), 1.5f, 0.1f, 100.0f);
		glm::vec3 pos (transform[3][0], transform[3][1], transform[3][2]);
		glm::vec3 front (0.0f, 0.0f, -1.0f);		//direction of camera
		glm::vec3 up = glm::vec3 (0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize (glm::cross (up, front));
		glm::vec3 cameraUp = glm::cross (front, cameraRight);
		glm::mat4 viewMatrix = glm::lookAt (pos, pos + front, cameraUp);
		//glm::mat4 viewMatrix = glm::lookAt (camera3D.Position, camera3D.Position + camera3D.Front, camera3D.Up);
		//glm::mat4 viewMatrix = glm::lookAt (glm::vec3 (0.0f, 0.0f, 5.0f), camera3D.Position + glm::vec3 (0.0f, 0.0f, -1.0f), glm::vec3 (0.0f, 1.0f, 0.0f));

		// lighting
		glm::vec3 lightPos (1.2f, 1.0f, 2.0f);

		/*s_Data.LightingShader->Bind ();		//glUseProgram (m_RendererID);
		s_Data.LightingShader->SetFloat3("objectColor", glm::vec3 (1.0f, 0.5f, 0.31f));
		s_Data.LightingShader->SetFloat3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		s_Data.LightingShader->SetFloat3("lightPos", lightPos);*/

		s_Data.LightingShader->Bind ();		//glUseProgram (m_RendererID);
		s_Data.LightingShader->SetFloat3 ("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		s_Data.LightingShader->SetFloat3 ("lightColor", glm::vec3 (1.0f, 1.0f, 1.0f));
		s_Data.LightingShader->SetFloat3 ("lightPos", lightPos);
		s_Data.LightingShader->SetFloat3 ("viewPos", pos);
		s_Data.LightingShader->SetMat4 ("projection", projectionCamera);
		s_Data.LightingShader->SetMat4 ("view", viewMatrix);

		// world transformation
		glm::mat4 model = glm::mat4 (1.0f);
		s_Data.LightingShader->SetMat4 ("model", model);

		// render the cube
		//s_Data.CubeVertexArray->RenderCube (36);
		glBindVertexArray (cubeVAO);
		glDrawArrays (GL_TRIANGLES, 0, 36);

		//also draw the lamp object
		s_Data.BasicCubeShader->Bind ();	//glUseProgram (m_RendererID);
		s_Data.BasicCubeShader->SetMat4 ("projection", projectionCamera);
		s_Data.BasicCubeShader->SetMat4 ("view", viewMatrix);

		model = glm::mat4 (1.0f);
		model = glm::translate (model, lightPos);
		model = glm::scale (model, glm::vec3 (0.2f)); // a smaller cube
		s_Data.BasicCubeShader->SetMat4 ("model", model);

		//s_Data.LightCubeVertexArray->RenderCube (lightCubeVAO, 36);
		glBindVertexArray (lightCubeVAO);
		glDrawArrays (GL_TRIANGLES, 0, 36);

		//s_Data.TextureShader->SetMat4 ("u_ViewProjection", viewProj);
		//s_Data.QuadIndexCount = 0;
		//s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		/*
		std::cout << "Renderer3D::BeginScene() Projection Camera = " << glm::to_string (camera3D.GetProjection ()) << std::endl;
		std::cout << "Renderer3D::BeginScene() Camera Zoom = " << camera3D.Zoom << std::endl;
		std::cout << "Renderer3D::BeginScene() Camera Up = " << glm::to_string (camera3D.Up) << std::endl;
		std::cout << "Renderer3D::BeginScene() Camera World Up = " << glm::to_string (camera3D.WorldUp) << std::endl;
		std::cout << "Renderer3D::BeginScene() Camera Position = " << glm::to_string (camera3D.Position) << std::endl;
		std::cout << "Renderer3D::BeginScene() Transform Position = " << glm::to_string (pos) << std::endl;
		std::cout << "Renderer3D::BeginScene() transform Position = " << (transform[3][0]) << ":" << (transform[3][1]) << ":" << (transform[3][2]) << std::endl;
		*/

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer3D::EndScene ()
	{
		OGE_PROFILE_FUNCTION ();

		//uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		//s_Data.QuadVertexBuffer->SetData (s_Data.QuadVertexBufferBase, dataSize);
		//s_Data.LightCubeVertextArray->SetData (s_Data.QuadVertexBufferBase, dataSize);

		//Flush ();
	}

	void Renderer3D::Flush ()
	{
		//if (s_Data.QuadIndexCount == 0)
		//	return; // Nothing to draw

		//// Bind textures
		//for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		//	s_Data.TextureSlots[i]->Bind (i);

		//RenderCommand::DrawIndexed (s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer3D::FlushAndReset ()
	{
		EndScene ();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer3D::DrawQuad (const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad ({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer3D::DrawQuad (const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		OGE_PROFILE_FUNCTION ();

		glm::mat4 transform = glm::translate (glm::mat4 (1.0f), position)
			* glm::scale (glm::mat4 (1.0f), { size.x, size.y, 1.0f });

		DrawQuad (transform, color);
	}

	void Renderer3D::DrawQuad (const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad ({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer3D::DrawQuad (const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		OGE_PROFILE_FUNCTION ();

		glm::mat4 transform = glm::translate (glm::mat4 (1.0f), position)
			* glm::scale (glm::mat4 (1.0f), { size.x, size.y, 1.0f });

		DrawQuad (transform, texture, tilingFactor, tintColor);
	}

	void Renderer3D::DrawQuad (const glm::mat4& transform, const glm::vec4& color)
	{
		OGE_PROFILE_FUNCTION ();
		constexpr size_t quadVertexCount = 4;
		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (s_Data.QuadIndexCount >= Renderer3DData::MaxIndices)
			FlushAndReset ();

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer3D::DrawQuad (const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		OGE_PROFILE_FUNCTION ();

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (s_Data.QuadIndexCount >= Renderer3DData::MaxIndices)
			FlushAndReset ();

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (s_Data.TextureSlotIndex >= Renderer3DData::MaxTextureSlots)
				FlushAndReset ();

			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		for (size_t i = 0; i < quadVertexCount; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer3D::DrawRotatedQuad (const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad ({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer3D::DrawRotatedQuad (const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		OGE_PROFILE_FUNCTION ();

		glm::mat4 transform = glm::translate (glm::mat4 (1.0f), position)
			* glm::rotate (glm::mat4 (1.0f), glm::radians (rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale (glm::mat4 (1.0f), { size.x, size.y, 1.0f });
		DrawQuad (transform, color);
	}

	void Renderer3D::DrawRotatedQuad (const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad ({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer3D::DrawRotatedQuad (const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		OGE_PROFILE_FUNCTION ();

		glm::mat4 transform = glm::translate (glm::mat4 (1.0f), position)
			* glm::rotate (glm::mat4 (1.0f), glm::radians (rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale (glm::mat4 (1.0f), { size.x, size.y, 1.0f });
		DrawQuad (transform, texture, tilingFactor, tintColor);
	}

	void Renderer3D::ResetStats ()
	{
		memset (&s_Data.Stats, 0, sizeof (Statistics));
	}

	Renderer3D::Statistics Renderer3D::GetStats ()
	{
		return s_Data.Stats;
	}
}