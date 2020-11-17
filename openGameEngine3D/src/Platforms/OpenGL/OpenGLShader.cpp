#include "ogepch.h"
#include "Platforms/OpenGL/OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

/*
	Hazel Engine
	License : Apache 2.0
*/

namespace openGameEngine3D
{
	static GLenum ShaderTypeFromString (const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}

		if (type == "fragment" || type == "pixel")
		{ 
			return GL_FRAGMENT_SHADER;
		}

		OGE_CORE_ASSERT (false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader (const std::string& filepath)
	{
		OGE_PROFILE_FUNCTION ();
		std::string source = ReadFile (filepath);

		auto shaderSources = PreProcess (source);

		Compile (shaderSources);

		// Extract name from filepath
		auto lastSlash = filepath.find_last_of ("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind ('.');
		auto count = lastDot == std::string::npos ? filepath.size () - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr (lastSlash, count);
	}

	OpenGLShader::OpenGLShader (const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name (name)
	{
		OGE_PROFILE_FUNCTION ();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;

		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile (sources);
	}

	OpenGLShader::OpenGLShader (const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		OGE_PROFILE_FUNCTION ();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;

		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile (sources);
	}

	OpenGLShader::~OpenGLShader ()
	{
		glDeleteProgram (m_RendererID);
	}

	std::string OpenGLShader::ReadFile (const std::string& filepath)
	{
		OGE_PROFILE_FUNCTION ();
		std::string result;
		std::ifstream in (filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII

		if (in)
		{
			in.seekg (0, std::ios::end);
			size_t size = in.tellg ();
			if (size != -1)
			{
				result.resize (size);
				in.seekg (0, std::ios::beg);
				in.read (&result[0], size);
			}
			else
			{
				OGE_CORE_ERROR ("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			OGE_CORE_ERROR ("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess (const std::string& source)
	{
		OGE_PROFILE_FUNCTION ();
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen (typeToken);
		size_t pos = source.find (typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of ("\r\n", pos); //End of shader type declaration line
			OGE_CORE_ASSERT (eol != std::string::npos, "Syntax error");
			//std::cout << "EOL Syntax error?????? - OpenGLShader.cpp";
			size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
			std::string type = source.substr (begin, eol - begin);

			ShaderTypeFromString (type); // "Invalid shader type specified");
			OGE_CORE_ASSERT (ShaderTypeFromString (type), "Invalid shader type specified");
			//std::cout << ShaderTypeFromString (type) << "Invalid shader type specified";

			size_t nextLinePos = source.find_first_not_of ("\r\n", eol); //Start of shader code after shader type declaration line
			OGE_CORE_ASSERT (nextLinePos != std::string::npos, "Syntax error");
			pos = source.find (typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[ShaderTypeFromString (type)] = (pos == std::string::npos) ? source.substr (nextLinePos) : source.substr (nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}
	void OpenGLShader::checkCompileErrors (unsigned int object, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv (object, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog (object, 1024, NULL, infoLog);
				std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
					<< infoLog << "\n -- --------------------------------------------------- -- "
					<< std::endl;
			}
		}
		else
		{
			glGetProgramiv (object, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog (object, 1024, NULL, infoLog);
				std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
					<< infoLog << "\n -- --------------------------------------------------- -- "
					<< std::endl;
			}
		}
	}
	void OpenGLShader::Compile (const char* vertexSource, const char* fragmentSource, const char* geometrySource)
	{
		unsigned int ID;
		unsigned int sVertex, sFragment, gShader;
		// vertex Shader
		sVertex = glCreateShader (GL_VERTEX_SHADER);
		glShaderSource (sVertex, 1, &vertexSource, NULL);
		glCompileShader (sVertex);
		checkCompileErrors (sVertex, "VERTEX");
		// fragment Shader
		sFragment = glCreateShader (GL_FRAGMENT_SHADER);
		glShaderSource (sFragment, 1, &fragmentSource, NULL);
		glCompileShader (sFragment);
		checkCompileErrors (sFragment, "FRAGMENT");
		// if geometry shader source code is given, also compile geometry shader
		if (geometrySource != nullptr)
		{
			gShader = glCreateShader (GL_GEOMETRY_SHADER);
			glShaderSource (gShader, 1, &geometrySource, NULL);
			glCompileShader (gShader);
			checkCompileErrors (gShader, "GEOMETRY");
		}
		// shader program
		ID = glCreateProgram ();
		glAttachShader (ID, sVertex);
		glAttachShader (ID, sFragment);
		if (geometrySource != nullptr)
			glAttachShader (ID, gShader);
		glLinkProgram (ID);
		checkCompileErrors (ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader (sVertex);
		glDeleteShader (sFragment);
		if (geometrySource != nullptr)
			glDeleteShader (gShader);
	}

	void OpenGLShader::Compile (const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		OGE_PROFILE_FUNCTION ();
		GLuint program = glCreateProgram ();
		//std::cout << shaderSources.size () << "We only support 2 shaders for now";
		OGE_CORE_ASSERT (shaderSources.size () <= 2, "We only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;		
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader (type);

			const GLchar* sourceCStr = source.c_str ();
			glShaderSource (shader, 1, &sourceCStr, 0);

			glCompileShader (shader);

			GLint isCompiled = 0;
			glGetShaderiv (shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog (maxLength);
				glGetShaderInfoLog (shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader (shader);

				OGE_CORE_ASSERT ("{0}", infoLog.data ());
				OGE_CORE_ASSERT (false, "Shader compilation failure!");
				break;
			}

			glAttachShader (program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;

		// Link our program
		glLinkProgram (program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv (program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv (program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog (maxLength);
			glGetProgramInfoLog (program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram (program);

			for (auto id : glShaderIDs)
				glDeleteShader (id);

			OGE_CORE_ERROR ("{0}", infoLog.data ());
			OGE_CORE_ASSERT (false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader (program, id);
			glDeleteShader (id);
		}
	}

	void OpenGLShader::SetIntArray (const std::string& name, int* values, uint32_t count)
	{
		UploadUniformIntArray (name, values, count);
	}

	void OpenGLShader::SetFloat (const std::string& name, float value)
	{
		OGE_PROFILE_FUNCTION ();

		UploadUniformFloat (name, value);
	}

	void OpenGLShader::Bind () const
	{
		OGE_PROFILE_FUNCTION ();
		glUseProgram (m_RendererID);
	}

	void OpenGLShader::Unbind () const
	{
		OGE_PROFILE_FUNCTION ();
		glUseProgram (0);
	}

	void OpenGLShader::SetInt (const std::string& name, int value)
	{
		OGE_PROFILE_FUNCTION ();
		UploadUniformInt (name, value);
	}

	void OpenGLShader::SetFloat3 (const std::string& name, const glm::vec3& value)
	{
		OGE_PROFILE_FUNCTION ();
		UploadUniformFloat3 (name, value);
	}

	void OpenGLShader::SetFloat4 (const std::string& name, const glm::vec4& value)
	{
		OGE_PROFILE_FUNCTION ();
		UploadUniformFloat4 (name, value);
	}

	void OpenGLShader::SetMat4 (const std::string& name, const glm::mat4& value)
	{
		OGE_PROFILE_FUNCTION ();
		UploadUniformMat4 (name, value);
	}

	void OpenGLShader::UploadUniformInt (const std::string& name, int value)
	{
		GLint location = glGetUniformLocation (m_RendererID, name.c_str ());
		glUniform1i (location, value);
	}

	void OpenGLShader::UploadUniformIntArray (const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation (m_RendererID, name.c_str ());
		glUniform1iv (location, count, values);
	}

	void OpenGLShader::UploadUniformFloat (const std::string& name, float value)
	{
		GLint location = glGetUniformLocation (m_RendererID, name.c_str ());
		glUniform1f (location, value);
	}

	void OpenGLShader::UploadUniformFloat2 (const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation (m_RendererID, name.c_str ());
		glUniform2f (location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3 (const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation (m_RendererID, name.c_str ());
		glUniform3f (location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4 (const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation (m_RendererID, name.c_str ());
		glUniform4f (location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3 (const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation (m_RendererID, name.c_str ());
		glUniformMatrix3fv (location, 1, GL_FALSE, glm::value_ptr (matrix));
	}

	void OpenGLShader::UploadUniformMat4 (const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation (m_RendererID, name.c_str ());
		glUniformMatrix4fv (location, 1, GL_FALSE, glm::value_ptr (matrix));
	}
}