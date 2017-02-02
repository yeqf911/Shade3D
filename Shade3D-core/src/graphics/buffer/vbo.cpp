#include "vbo.h"

namespace Shade
{
namespace Graphics
{
	VertexBuffer::VertexBuffer(const GLfloat *data, const GLsizei size, const GLuint vertDataCount, GLenum usage)
	{
		m_size = size;
		m_vertDataCount = vertDataCount;
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_size, data, usage);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
} // namespace Graphics
} // namespacc Shade