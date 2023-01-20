#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iterator>
#include <string_view>

class IApplication {
	public:
		IApplication();
		~IApplication();
	
		bool Create(int32_t resX, int32_t resY, const std::string &title);
		void Run();

		/* 'inline' keyword is optimization method with old compilers -> copies function to everywhere instead of calling it */
		/* Modern compilers do that automatically. -> Used as documentation at this context pretty much. */
		inline int32_t GetWidth() const { return m_iWidth; }
		inline int32_t GetHeight() const { return m_iHeight; }
		inline HWND GetWindow() { return m_Window; }
	protected:
	private:
		static HWND MakeWindow(int32_t width, int32_t height, const std::string &title);

		HWND			m_Window;
		int32_t			m_iWidth;
		int32_t			m_iHeight;


};