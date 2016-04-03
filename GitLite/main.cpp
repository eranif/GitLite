#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include <wx/image.h>
#include "PersistentManager.h"

// Define the MainApp
class MainApp : public wxApp
{
    PersistentManager m_persistentManager;
public:
    MainApp() { GitLiteRepo::Initialize(); }
    virtual ~MainApp() { GitLiteRepo::Shutdown(); }

    virtual bool OnInit()
    {
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
