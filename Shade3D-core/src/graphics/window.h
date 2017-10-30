#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../maths/vec4.h"
#include <list>

namespace Shade
{
namespace Graphics
{
#define MAX_KEYS			1024
#define MAX_MOUSE_BUTTONS	32

	/**
	* \brief 错误发生回调函数
	*/
	static void OnErrorOccur(int error, const char* description);

	/**
	* \brief 窗口大小改变回调函数
	*/
	static void OnWindowResize(GLFWwindow* window, int width, int height);

	/**
	* \brief 试图关闭窗口时回调函数
	*/
	static void OnWindowClose(GLFWwindow* window);

	/**
	* \brief 按键回调函数
	*/
	static void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);


	/**
	 * \brief 光标移动回调函数
	 */
	static void OnCursorMove(GLFWwindow* window, double xpos, double ypos);


	/**
	 * \brief 鼠标按键回调函数
	 */
	static void OnMouseButtonPressed(GLFWwindow* window, int button, int action, int mods);

	
	class Window
	{
	private:
		const char* m_title;
		int m_width;
		int m_height;
		GLFWwindow* m_window;
		bool m_clased;
		bool m_keys[MAX_KEYS];
		bool m_mouseButtons[MAX_MOUSE_BUTTONS];
		double m_corsorX;	//鼠标位置 x 坐标
		double m_cursorY;	//鼠标位置 y 坐标;
	
	public:
		Window(char * title, int width, int height);
		~Window();
		void clear(const Maths::vec4& rgba = Maths::vec4(0.2f, 0.3f, 0.3f, 1.0f)) const;
		void render() const;
		void update() const;
		bool closed() const;

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
		inline double getCursorX() const { return m_corsorX; }
		inline double getCursorY() const { return m_cursorY; }

		inline void getCursorPosition(double& xpos, double &ypos) const
		{
			xpos = m_corsorX;
			ypos = m_cursorY;
		}

		inline bool isKeyPressed(unsigned int keyCode)
		{
			
			if (keyCode >= MAX_KEYS)
			{
				//TODO: Log somethong
				return false;
			}
			return m_keys[keyCode];
		}

		inline bool isMouseButtonPressed(unsigned int mouseBtnCode)
		{
			if (mouseBtnCode >= MAX_MOUSE_BUTTONS)
			{
				//TODO: Log somethong
				return false;
			}
			std::list<int> s;
			return m_mouseButtons[mouseBtnCode];
		}
		
	private:
		bool init();
		void setCallBack();

		// friend function
		friend static void OnWindowResize(GLFWwindow* window, int width, int height);
		friend static void OnMouseButtonPressed(GLFWwindow* window, int button, int action, int mods);
		friend static void OnWindowClose(GLFWwindow* window);
		friend static void OnKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void OnCursorMove(GLFWwindow* window, double xpos, double ypos);

	};
} // end of namespace Graphics
} // end of namespace Shade

#endif //_WINDOW_H_
