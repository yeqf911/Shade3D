#include "window.h"
#include "../utils/logger.h"

namespace Shade
{
namespace Graphics
{
	//typedef void(*GLFWframebuffersizefun)(GLFWwindow*, int, int);

	Window::Window(char* title, int width, int height)
	{
		m_title = title;
		m_width = width;
		m_height = height;
		m_clased = true;
		if (!init())
			glfwTerminate();
		
		for (int i = 0; i < MAX_KEYS; ++i)
		{
			m_keys[i] = false;
		}

		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
		{
			m_mouseButtons[i] = false;
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

		setCallBack();
		/* Make Sure that GLEW initialize after upon*/
		if (glewInit() != GLEW_OK)
		{
			std::cout << "GLEW Initialize Failed!" << std::endl;
			return false;
		}
		m_clased = false;
		return true;
	}

	void Window::setCallBack()
	{
		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, OnWindowResize);
		glfwSetWindowCloseCallback(m_window, OnWindowClose);
		glfwSetMouseButtonCallback(m_window, OnMouseButtonPressed);
		glfwSetKeyCallback(m_window, OnKeyPressed);
		glfwSetCursorPosCallback(m_window, OnCursorMove);
	}

	void Window::clear(const Maths::vec4& rgba) const
	{
		glClearColor(rgba.x, rgba.y, rgba.z, rgba.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::render() const
	{
		// TODO: render
	}

	void Window::update() const
	{
		GLenum error;
		error = glGetError();
		if (error != GLEW_NO_ERROR)
		{
			LOG("OpenGL Error: ", error);
		}
		/* Render here */
		/* Poll for and process events */
		glfwPollEvents();
		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);
	}

	
	bool Window::closed() const
	{
		return m_clased;
	}

	// 下面是 CallBack function
	void OnErrorOccur(int error, const char* description)
	{
		//TODO: Error handler
		LOG("Error: ", description);
	}

	void OnWindowResize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Window *wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));
		wnd->m_width = width;
		wnd->m_height = height;
	}

	void OnWindowClose(GLFWwindow* window)
	{
		LOG("[OpenGL]: ", "Window Closed");
		Window *wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));
		wnd->m_clased = true;
		//glfwSetWindowShouldClose(this->m_window, );
	}

	void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window *wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));
		wnd->m_keys[key] = (action != GLFW_RELEASE);
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(wnd->m_window, GL_TRUE);
			wnd->m_clased = true;
		}
	}

	void OnCursorMove(GLFWwindow* window, double xpos, double ypos)
	{
		Window *wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));
		wnd->m_corsorX = xpos;
		wnd->m_cursorY = ypos;
	}

	void OnMouseButtonPressed(GLFWwindow* window, int button, int action, int mods)
	{
		Window *wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));
		wnd->m_mouseButtons[button] = (action != GLFW_RELEASE);
	}
} // end of namespace graphics
} // end of namespace shade