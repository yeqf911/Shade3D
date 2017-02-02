#ifndef _VBO_H_
#define _VBO_H_
#include <GL/glew.h>

namespace Shade
{
namespace Graphics
{
	
	class VertexBuffer
	{
	private:
		GLuint m_vbo;
		//GLfloat *m_data;
		GLsizei m_size;
		GLuint m_vertDataCount;

	public:
		VertexBuffer(const GLfloat *data, const GLsizei size, const GLuint vertDataCount, GLenum usage);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

		inline GLint getSize() const { return m_size; }
		inline GLuint getVertDataCount() const { return m_vertDataCount; }

	};

} // namespace Graphics
} // namespace Maths

#endif // _VBO_H_
