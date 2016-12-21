#include "window.h"

namespace shade
{
namespace graphics
{
	//typedef void(*GLFWframebuffersizefun)(GLFWwindow*, int, int);

	/**
	* \brief 错误发生回调函数
	* \param error
	* \param description
	*/
	void OnErrorOccur(int error, const char* description);

	/**
	* \brief 窗口大小改变回调函数
	* \param window
	* \param width
	* \param height
	*/
	void OnWindowResize(GLFWwindow* window, int width, int height);

	/**
	* \brief 试图关闭窗口时回调函数
	* \param window
	*/
	void OnWindowClose(GLFWwindow* window);


	Window::Window(char* title, int width, int height)
	{
		m_title = title;
		m_width = width;
		m_height = height;
		m_clased = false;
		if (!init())
		{
			glfwTerminate();
		}

		std::cout << "[OpenGL VERSION]: " << glGetString(GL_VERSION) << std::endl;
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	

	bool Window::init()
	{
		/* 设置错误发生回调函数 */
		glfwSetErrorCallback(OnErrorOccur);

		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}

		m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			std::cout << "Failed to create GLFW Window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_window);
		/* 设置窗口大小改变回调函数 */
		glfwSetFramebufferSizeCallback(m_window, OnWindowResize);
		glfwSetWindowCloseCallback(m_window, OnWindowClose);
		return true;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::render() const
	{
		//glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::update() const
	{
		/* Render here */
		render();

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	
	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_window);
	}

	// 下面是 CallBack function
	void OnErrorOccur(int error, const char* description)
	{
		//TODO: Error handler
		std::cout << "error<" << error << "> " << description << std::endl;
	}

	void OnWindowResize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void OnWindowClose(GLFWwindow* window)
	{
		std::cout << "Closed" << std::endl;
		//glfwSetWindowShouldClose(this->m_window, );
	}

} // end of namespace graphics
} // end of namespace shade