#include "src/graphics/window.h"
#include "src/maths/maths.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffer/buffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL/SOIL.h>

using namespace Shade;
using namespace Graphics;
using namespace Maths;
using namespace std;

int main()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	Window window = Window("Shade3D", 500, 500);

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	LOG("Maximum nr of vertex attributes supported: ", nrAttributes);

	Shader shader = Shader("src/shaders/rectangle.vert", "src/shaders/rectangle.frag");

#if 0
	int width, height;
	unsigned char* image = SOIL_load_image("awesomeface.png", &width, &height, nullptr, SOIL_LOAD_RGB);	
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
#endif

	const GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Top Right
		//0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
		//-0.5f,  0.5f, 0.0f ,0.0f, 1.0f, 1.0f, // Top Left 
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f ,0.0f, 1.0f, 1.0f // Top Left 
	};

	GLfloat tvertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		//-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // 左上

		//0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
	};

	const GLushort indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	//VertexBuffer vbo = VertexBuffer(vertices, sizeof(vertices), 6, GL_STATIC_DRAW);
	VertexBuffer vbo = VertexBuffer(tvertices, sizeof(tvertices), 8, GL_STATIC_DRAW);
	IndexBuffer ibo = IndexBuffer(indices, sizeof(indices), GL_STATIC_DRAW);
	VertexArray vao = VertexArray();
	vao.addVBO(vbo, 0, 3, 0);
	vao.addVBO(vbo, 1, 3, 3);
	vao.addVBO(vbo, 2, 2, 6);
	

	int width, height;
	unsigned char* image = SOIL_load_image("res/container.jpg", &width, &height, nullptr, SOIL_LOAD_RGB);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	image = SOIL_load_image("res/awesomeface.png", &width, &height, nullptr, SOIL_LOAD_RGB);
	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	while (!window.closed())
	{
		window.clear();
		shader.enable();
		vao.bind();
		//vao.addIBO(ibo);
		ibo.bind();
		//glBindTexture(GL_TEXTURE_2D, texture);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		ibo.unbind();
		vao.unbind();
		window.update();
	}
	return 0;
}
