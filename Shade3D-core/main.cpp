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

	Window window = Window("Shade3D", 640, 500);

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	LOG("Maximum nr of vertex attributes supported: ", nrAttributes);

	

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

	GLfloat positions[] = {
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
	};

	const GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,  // First Triangle
		1, 2, 3   // Second Triangle
	};

	Shader shader = Shader("src/shaders/rectangle.vs", "src/shaders/rectangle.fs");
	shader.enable();

	matrix4f ortho = matrix4f::orthographic(0.0f, 16.0f, 0.0f, 9.0f, 1.0f, -1.0f);
	shader.setUniformMatrix4fv("pr_matrix", GL_FALSE, ortho);
	shader.setUniformMatrix4fv("ml_matrix", GL_FALSE, matrix4f::translation(vec3(4, 3, 0)));

	//shader.setUniform2f("light_pos", vec2(window.getCursorX(), window.getCursorY()));
	shader.setUniform4f("colour", vec4(0.0f, 0.1f, 0.0f, 1.0f));

	
	VertexBuffer position = VertexBuffer(positions, sizeof(tvertices), 3);
	VertexBuffer color = VertexBuffer(colors, sizeof(colors), 3);
	IndexBuffer ibo = IndexBuffer(indices, sizeof(indices));
	VertexArray vao = VertexArray();
	vao.addVBO(position, 0);
	//vao.addVBO(color, 1);
	vao.addIBO(ibo);
	
#if 0
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
#endif

	while (!window.closed())
	{
		window.clear(vec4(0.0f, 0.0f, 0.0f, 1.0f));
		vao.bind();
		double x, y;
		window.getCursorPosition(x, y);
		shader.setUniform2f("light_pos", vec2(float(x * 16.0f / 960.0f), float(9.0f - y * 9.0f / 540.0f)));
		//shader.setUniform2f("light_pos", vec2(x, y));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		vao.unbind();
		window.update();
	}
	return 0;
}
