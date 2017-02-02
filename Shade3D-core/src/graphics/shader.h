#ifndef _SHADER_H_
#define _SHADER_H_
#include <GL/glew.h>
#include <string>
#include <vector>
#include "../utils/fileutils.h"
#include "../utils/logger.h"
#include "../maths/maths.h"


namespace Shade
{
namespace Graphics 
{
	
#define MAX_INFO_SIZE	512
	class Shader
	{
	private:
		GLuint m_shaderID;
		//std::string m_vertShader;
		//std::string m_fragShader;
		std::string m_vertPath;
		std::string m_fragPath;

	public:
		Shader(const char *vertShaderSrcFile, const char *fragShaderSrcFile);
		~Shader();
		void enable() const;
		void disable() const;
		void setUniform1f(const GLchar *uniform, const GLfloat value) const;
		void setUniform1i(const GLchar *uniform, const GLint value) const;
		void setUniform2f(const GLchar *uniform, const Maths::vec2& vector) const;
		void setUniform3f(const GLchar *uniform, const Maths::vec3& vector) const;
		void setUniform4f(const GLchar *uniform, const Maths::vec4& vector) const;
		void setUniformMatrix4fv(const GLchar* uniform, GLboolean isTranspose, const Maths::matrix4f& mat4f) const;


	private:
		GLuint load();
		GLuint createVertShader();
		GLuint createFragShader();
		GLuint getUniformLocation(const GLchar *uniform) const;
	};

} // namespace Graphics
} // namespace Shade

#endif // _SHADER_H_