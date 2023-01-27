#include "../include/IApplication.h"

IApplication* IApplication::m_pApp = nullptr;

IApplication::IApplication() :m_Window{ nullptr }, m_iWidth{ 0 }, m_iHeight{ 0 }, m_bActive{ false } {
	this->m_pApp = this;
}

IApplication::~IApplication() {

}

void IApplication::SetActive(bool set) {
	this->m_bActive = set;
}

bool IApplication::Create(int32_t resX, int32_t resY, const std::string& title) {
	this->m_Window = MakeWindow(resX, resY, title);

	if (!this->m_Window) {
		return false;
	}

	this->m_iWidth = resX;
	this->m_iHeight = resY;
	this->SetActive(true);
	
	return true;
}

void IApplication::Run() {
	// TODO : main loop
	MSG msg;
	BOOL gotMsg = false;

	::PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE);


	while (msg.message != WM_QUIT) {
		gotMsg = this->IsActive()
			? ::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)
			: ::GetMessage(&msg, nullptr, 0, 0);

		if (gotMsg) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (msg.message != WM_QUIT) {
			::OutputDebugString(L"RUNNING!\n");
			// TODO : run our actual main loop
		}
	}
}

bool IApplication::OnEvent(UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_SIZE:
			switch (wParam) {
				case SIZE_MINIMIZED:
					this->SetActive(false);
					break;
				case SIZE_MAXIMIZED:
				case SIZE_RESTORED:
					this->SetActive(true);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return false;
}

// STATIC
HWND IApplication::MakeWindow(int32_t width, int32_t height, const std::string& title) {
	HINSTANCE hInst = ::GetModuleHandle(nullptr);
	DWORD windowStyle = 0;

	windowStyle =
		WS_OVERLAPPED |
		WS_CAPTION |
		WS_SYSMENU |
		WS_THICKFRAME |
		WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX;

	WNDCLASS wc;
	std::memset(&wc, 0, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.hInstance = hInst;
	wc.hIcon = ::LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) ::GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = L"GRAPHICSENGINE_WNDCLASS";

	if (!::RegisterClass(&wc)) {
		return nullptr;
	}

	// Create the window.
	std::wstring widestr = std::wstring(title.begin(), title.end());
	HWND window = ::CreateWindow(
		wc.lpszClassName,
		widestr.c_str(),
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		hInst,
		nullptr
	);

	if (!window) {
		return nullptr;
	}

	RECT clientArea = { 0, 0, width, height };

	::SetWindowLong(window, GWL_STYLE, windowStyle);
	::AdjustWindowRectEx(&clientArea, windowStyle, FALSE, 0);
	::SetWindowPos(
		window,
		nullptr,
		0,
		0,
		clientArea.right - clientArea.left,
		clientArea.bottom - clientArea.top,
		SWP_NOZORDER | SWP_NOMOVE | SWP_SHOWWINDOW
	);
	::UpdateWindow(window);
	::ShowWindow(window, SW_SHOWNORMAL);

	return window;
}

// STATIC
long WINAPI IApplication::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
		case WM_CREATE:
			::SetForegroundWindow(hwnd);
			break;
		case WM_CLOSE:
			::DestroyWindow(hwnd);
			return 0;
		default:
			break;
	}

	auto app = IApplication::GetApp();

	if (app && app->OnEvent(message, wParam, lParam)) {
		return 0;
	}

	return (long) ::DefWindowProc(hwnd, message, wParam, lParam);
}