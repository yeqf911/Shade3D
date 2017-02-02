#ifndef _IBO_H_
#define _IBO_H_
#include <GL/glew.h>

namespace Shade
{
namespace Graphics
{

	class IndexBuffer
	{
	private:
		GLuint m_ibo;
		//GLushort *m_data;
		GLuint m_size;

	public:
		IndexBuffer(const GLushort* data, const GLsizei size, GLenum usage);
		~IndexBuffer();
		void bind() const;
		void unbind() const;

	};

} // namespace Graphics
} // namespace Maths

#endif // _IBO_H_
