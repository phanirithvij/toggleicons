#include "Header.h"

// To view the exact commands run by visual sudio go to Tools > Options > Project and Solutions > Build and Run > two verbosity settings
// Set to Detailed
// https://stackoverflow.com/a/20910024/8608146

// https://stackoverflow.com/a/2752645/8608146
// Need to use /SUBSYSTEM:WINDOWS in the linker options
// to avoid executable opening a cmd prompt after every run

// https://stackoverflow.com/a/53081427/8608146
// Can be added in Project properties -> Config Properties -> Linker -> Command Line

// And need to also use WinMain instead of wmain or main for gui apps (which we are setting by /subsystem:windows)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	try
	{
		CComInit init;

		ToggleDesktopIcons();

		std::cout << "Desktop icons have been toggled.\n";
	}
	catch (std::system_error const& e)
	{
		std::cout << "ERROR: " << e.what() << ", error code: " << e.code() << "\n";
		return 1;
	}

}

