#ifndef _VAO_H_
#define _VAO_H_
#include <GL/glew.h>
#include <vector>
#include "vbo.h"
#include "ibo.h"

namespace Shade
{
namespace Graphics
{

	class VertexArray
	{
	private:
		GLuint m_vao;
		//std::vector<VertexBuffer&> m_vbos;

	public:
		VertexArray();
		~VertexArray();

		void addVBO(const VertexBuffer& vbo, GLuint location);
		void addIBO(const IndexBuffer& ibo);
		void bind() const;
		void unbind() const;

	};

} // namespace Graphics
} // namespace Maths

#endif // _VAO_H_
