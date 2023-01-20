#include "../include/IApplication.h"

IApplication::IApplication() :
	m_Window(nullptr),
	m_iWidth(0),
	m_iHeight(0) {}

IApplication::~IApplication() {

}

bool IApplication::Create(int32_t resX, int32_t resY, const std::string& title) {
	m_Window = MakeWindow(resX, resY, title);

	if (!m_Window) {
		return false;
	}

	m_iWidth = resX;
	m_iHeight = resY;
	
	return true;
}

void IApplication::Run() {
	// TODO : main loop
	MSG msg;
	BOOL gotMsg = false;

	::PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE);

	while (msg.message != WM_QUIT) {
		gotMsg = ::GetMessage(&msg, nullptr, 0, 0);

		if (gotMsg) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (msg.message != WM_QUIT) {
			// TODO : run our actual main loop
		}
	}

}

HWND IApplication::MakeWindow(int32_t width, int32_t height, const std::string& title) {
	HINSTANCE hInst = ::GetModuleHandle(nullptr);
	DWORD windowStyle = 0;

	windowStyle =
		WS_OVERLAPPED |
		WS_CAPTION |
		WS_SYSMENU |
		WS_THICKFRAME |
		WS_MINIMIZEBOX |
		WS_MAXIMIZE;

	WNDCLASS wc;
	std::memset(&wc, 0, sizeof(WNDCLASS));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = nullptr; // TODO : add a window procedure.
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