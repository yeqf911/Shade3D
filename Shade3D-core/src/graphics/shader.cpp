#include "shader.h"

namespace Shade
{
namespace Graphics
{
	Shader::Shader(const char *vertShaderSrcFile, const char *fragShaderSrcFile)
	{
		m_vertPath = vertShaderSrcFile;
		m_fragPath = fragShaderSrcFile;
		m_shaderID = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderID);
	}

	void Shader::enable() const
	{
		glUseProgram(m_shaderID);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	void Shader::setUniform1f(const GLchar* uniform, const GLfloat value) const
	{
		glUniform1f(getUniformLocation(uniform), value);
	}

	void Shader::setUniform1i(const GLchar* uniform, const GLint value) const
	{
		glUniform1i(getUniformLocation(uniform), value);
	}

	void Shader::setUniform2f(const GLchar* uniform, const Maths::vec2& vector) const
	{
		glUniform2f(getUniformLocation(uniform), vector.x, vector.y);
	}

	void Shader::setUniform3f(const GLchar* uniform, const Maths::vec3& vector) const
	{
		glUniform3f(getUniformLocation(uniform), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* uniform, const Maths::vec4& vector) const
	{
		glUniform4f(getUniformLocation(uniform), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMatrix4fv(const GLchar* uniform, GLboolean isTranspose, const Maths::matrix4f& mat4f) const
	{
		GLuint location = getUniformLocation(uniform);
		glUniformMatrix4fv(location, 1, isTranspose, mat4f._element);
	}

	GLuint Shader::load()
	{
		GLuint vertShader = createVertShader();
		GLuint fragShader = createFragShader();
		GLuint program = glCreateProgram();
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);
		/* 检查Link是否成功 */
		GLint success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLint length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			std::vector<GLchar> logInfo(length);
			glGetProgramInfoLog(program, length, &length, &logInfo[0]);
			LOG("ERROR::SHADER::LINK_FAILED\n", &logInfo[0]);
			program = 0;
		}
		/* Link结束，再不需要着色器对象了，要删除资源 */
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		return program;
	}

	GLuint Shader::createVertShader()
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		std::string vertSrc = read_file(m_vertPath.c_str());
		const char *vertSource = vertSrc.c_str();
		glShaderSource(vertexShader, 1, &vertSource, nullptr);
		glCompileShader(vertexShader);

		GLint success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[MAX_INFO_SIZE];
			glGetShaderInfoLog(vertexShader, MAX_INFO_SIZE, nullptr, infoLog);
			LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", infoLog);
		//	return vertexShader;
		}
		return vertexShader;
	}

	GLuint Shader::createFragShader()
	{
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragSrc = read_file(m_fragPath.c_str());
		const char *fragSource = fragSrc.c_str();
		glShaderSource(fragmentShader, 1, &fragSource, nullptr);
		glCompileShader(fragmentShader);

		GLint success;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[MAX_INFO_SIZE];
			glGetShaderInfoLog(fragmentShader, MAX_INFO_SIZE, nullptr, infoLog);
			LOG("ERROR::SHADER::FGRAGMENT::COMPILATION_FAILED\n", infoLog);
			//	return vertexShader;
		}
		return fragmentShader;
	}

	GLuint Shader::getUniformLocation(const GLchar* uniform) const
	{
		return glGetUniformLocation(m_shaderID, uniform);
	}
} // namespace Graphics
} // namespace Shade hekki
