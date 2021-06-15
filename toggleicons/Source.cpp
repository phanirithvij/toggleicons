#include "Header.h"

// Query an interface from the desktop shell view.
void FindDesktopFolderView(REFIID riid, void** ppv, std::string const& interfaceName)
{
	CComPtr<IShellWindows> spShellWindows;
	ThrowIfFailed(
		spShellWindows.CoCreateInstance(CLSID_ShellWindows),
		"Failed to create IShellWindows instance");

	CComVariant vtLoc(CSIDL_DESKTOP);
	CComVariant vtEmpty;
	long lhwnd;
	CComPtr<IDispatch> spdisp;
	ThrowIfFailed(
		spShellWindows->FindWindowSW(
			&vtLoc, &vtEmpty, SWC_DESKTOP, &lhwnd, SWFO_NEEDDISPATCH, &spdisp),
		"Failed to find desktop window");

	CComQIPtr<IServiceProvider> spProv(spdisp);
	if (!spProv)
		ThrowIfFailed(E_NOINTERFACE, "Failed to get IServiceProvider interface for desktop");

	CComPtr<IShellBrowser> spBrowser;
	ThrowIfFailed(
		spProv->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&spBrowser)),
		"Failed to get IShellBrowser for desktop");

	CComPtr<IShellView> spView;
	ThrowIfFailed(
		spBrowser->QueryActiveShellView(&spView),
		"Failed to query IShellView for desktop");

	ThrowIfFailed(
		spView->QueryInterface(riid, ppv),
		"Could not query desktop IShellView for interface " + interfaceName);
}

void ToggleDesktopIcons()
{
	CComPtr<IFolderView2> spView;
	FindDesktopFolderView(IID_PPV_ARGS(&spView), "IFolderView2");

	DWORD flags = 0;
	ThrowIfFailed(
		spView->GetCurrentFolderFlags(&flags),
		"GetCurrentFolderFlags failed");
	ThrowIfFailed(
		spView->SetCurrentFolderFlags(FWF_NOICONS, flags ^ FWF_NOICONS),
		"SetCurrentFolderFlags failed");
}
