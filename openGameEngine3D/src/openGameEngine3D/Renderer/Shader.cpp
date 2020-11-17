#include "ogepch.h"
#include "openGameEngine3D/Renderer/Shader.h"

#include "openGameEngine3D/Renderer/Renderer.h"
#include "Platforms/OpenGL/OpenGLShader.h"

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	Ref<Shader> Shader::Create (const std::string& filepath)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    std::cout << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader> (filepath);
		}

		std::cout << "Unknown RendererAPI!";
		return nullptr;
	}

	Ref<Shader> Shader::Create (const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    std::cout << "false, RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader> (name, vertexSrc, fragmentSrc);
		}

		std::cout << "false, Unknown RendererAPI!";
		return nullptr;
	}

	Ref<Shader> Shader::Create (const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI ())
		{
			case RendererAPI::API::None:    std::cout << "false, RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader> (vertexSrc, fragmentSrc);
		}

		std::cout << "false, Unknown RendererAPI!";
		return nullptr;
	}

	void ShaderLibrary::Add (const std::string& name, const Ref<Shader>& shader)
	{
		std::cout << "Shader already exists!";
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add (const Ref<Shader>& shader)
	{
		auto& name = shader->GetName ();
		Add (name, shader);
	}

	Ref<Shader> ShaderLibrary::Load (const std::string& filepath)
	{
		auto shader = Shader::Create (filepath);
		Add (shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load (const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create (filepath);
		Add (name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get (const std::string& name)
	{
		if(!Exists(name))
		{
			std::cout << "Shader not found!";
		}
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists (const std::string& name) const
	{
		return m_Shaders.find (name) != m_Shaders.end ();
	}
}