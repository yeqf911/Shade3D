#include "src/graphics/window.h"
using namespace shade;
using namespace graphics;

int main()
{
	Window window = Window("Shade3D", 600, 400);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	while (!window.closed())
	{
		window.clear();
	
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f,  0.5f);
		glVertex2f( 0.5f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
		window.update();
	}
	//system("PAUSE");
	return 0;
}