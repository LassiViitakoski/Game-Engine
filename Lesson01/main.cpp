#include "../core/include/IApplication.h"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdLine, int cmdShow) {
	auto app = std::make_unique<IApplication>();

	if (!app->Create(1280, 720, "SUPERGAMGE")) {
		// Something went wrong.
		return 0;
	}

	app->Run();
	return 0;
}