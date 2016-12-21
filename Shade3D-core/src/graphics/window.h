#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GLFW/glfw3.h>
#include <iostream>


namespace shade
{
namespace graphics
{
	class Window
	{
	private:
		const char* m_title;
		int m_width;
		int m_height;
		GLFWwindow* m_window;
		bool m_clased;
	
	public:
		Window(char * title, int width, int height);
		~Window();
		void clear() const;
		void render() const;
		void update() const;
		bool closed() const;

	private:
		bool init();

	};
} //end of namespace graphics
} // end of namespace shade


#endif //_WINDOW_H_
