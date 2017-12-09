#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include <wx/image.h>
#include "PersistentManager.h"

#ifdef __WXMSW__
typedef BOOL WINAPI (*SetProcessDPIAwareFunc)();
#endif

// Define the MainApp
class MainApp : public wxApp
{
    PersistentManager m_persistentManager;

private:
    void MSWEnableHiDPI()
    {
#ifdef __WXMSW__

        HMODULE m_user32Dll = LoadLibrary(L"User32.dll");
        if(m_user32Dll) {
            SetProcessDPIAwareFunc pFunc = (SetProcessDPIAwareFunc)GetProcAddress(m_user32Dll, "SetProcessDPIAware");
            if(pFunc) {
                pFunc();
            }
            FreeLibrary(m_user32Dll);
            m_user32Dll = NULL;
        }
#endif
    }

public:
    MainApp() { GitLiteRepo::Initialize(); }
    virtual ~MainApp() { GitLiteRepo::Shutdown(); }

    virtual bool OnInit()
    {
        MSWEnableHiDPI(); // Enable HiDPI on Windows
        wxPersistenceManager::Get().Set(m_persistentManager);

        // Add the common image handlers
        wxImage::AddHandler(new wxPNGHandler);
        wxImage::AddHandler(new wxJPEGHandler);

        MainFrame* mainFrame = new MainFrame(NULL);
        SetTopWindow(mainFrame);
        return GetTopWindow()->Show();
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
