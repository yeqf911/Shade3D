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
	const float s = 0;

	if (s >= -FLT_EPSILON && s <= FLT_EPSILON)
	{
		cout << "true" << endl;
	}


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	Window window = Window("Shade3D", 640, 360);

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
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Top Right
		//0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
		//-0.5f,  0.5f, 0.0f ,0.0f, 1.0f, 1.0f, // Top Left 
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom Left
		-0.5f, 0.5f, 0.0f ,0.0f, 1.0f, 1.0f // Top Left 
	};

	GLfloat tvertices[] = {
		//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
		//-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // 左上

		//0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // 左上
	};

	GLfloat sprit1[] = {
		0, 0, 0,
		0, 9, 0,
		16, 9, 0,
		16, 0, 0
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		//1.0f, 1.0f, 0.0f,
		//0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
	};

	GLfloat color1[] = {
		0.2f, 0.3f, 0.8f, 1.0,
		0.2f, 0.3f, 0.8f, 1.0,
		0.2f, 0.3f, 0.8f, 1.0,
		0.2f, 0.3f, 0.8f, 1.0
	};

	GLfloat color2[] = {
		0.2f, 0.8f, 0.8f, 1.0,
		0.2f, 0.8f, 0.8f, 1.0,
		0.2f, 0.8f, 0.8f, 1.0,
		0.2f, 0.8f, 0.8f, 1.0
	};


	const GLuint indices[] = {	// Note that we start from 0!
		0, 1, 3,	// First Triangle
		1, 2, 3		// Second Triangle
	};

	Shader shader = Shader("./res/shaders/rectangle.vs", "./res/shaders/rectangle.fs");
	shader.enable();

	matrix4f ortho = matrix4f::orthographic(0.0f, 16.0f, 0.0f, 9.0f, 1.0f, -1.0f);
	shader.setUniformMatrix4fv("pr_matrix", GL_FALSE, ortho);
	//shader.setUniformMatrix4fv("ml_matrix", GL_FALSE, matrix4f::translation(vec3(0, 0, 0)));
	//shader.setUniform2f("light_pos", vec2(4.0f, 3.0f));
	//shader.setUniform2f("light_pos", vec2(window.getCursorX(), window.getCursorY()));
	//shader.setUniform4f("colour", vec4(0.2f, 0.2f, 0.4f, 1.0f));


	VertexBuffer vbo = VertexBuffer(sprit1, sizeof(sprit1), 3);


	VertexBuffer colorA = VertexBuffer(color1, sizeof(color1), 4);
	VertexBuffer colorB = VertexBuffer(color2, sizeof(color2), 4);

	IndexBuffer ibo = IndexBuffer(indices, sizeof(indices));

	VertexArray spritA = VertexArray();
	VertexArray spritB = VertexArray();

	spritA.addVBO(vbo, 0);
	spritA.addVBO(colorA, 1);
	spritA.addIBO(ibo);
	
	spritB.addVBO(vbo, 0);
	spritB.addVBO(colorB, 1);
	spritB.addIBO(ibo);

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
		double x, y;
		window.getCursorPosition(x, y);
		double wy = window.getHeight();
		double wx = window.getWidth();

		shader.setUniform2f("light_pos", vec2(static_cast<float>(x * 16.0f / wx), static_cast<float>(y * 9.0f / wy)));
		std::cout << "(" << x << ", " << y << ")" << std::endl;

		spritA.bind();
		shader.setUniformMatrix4fv("ml_matrix", GL_FALSE, matrix4f::translation(vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		spritA.unbind();
		/*
		spritB.bind();
		shader.setUniformMatrix4fv("ml_matrix", GL_FALSE, matrix4f::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		spritB.unbind();
		*/
		window.update();
	}
	return 0;
}
