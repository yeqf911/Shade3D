#include "vao.h"

namespace Shade
{
namespace Graphics
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_vao);
	}

	VertexArray::~VertexArray()
	{
	}

	void VertexArray::addVBO(const VertexBuffer& vbo, GLuint location)
	{
		bind();
		vbo.bind();
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(
			location, 
			vbo.getVertDataCount(),
			GL_FLOAT, 
			GL_FALSE,
			0,
			0
		);
		unbind();
		//m_vbos.push_back(vbo);
	}

	void VertexArray::addIBO(const IndexBuffer& ibo)
	{
		bind();
		ibo.bind();
		unbind();
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_vao);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
} // namespace Graphics
} // namespace Shade