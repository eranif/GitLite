#include "PersistentManager.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>

PersistentManager::PersistentManager()
{
    wxFileName persistentStorage(wxStandardPaths::Get().GetUserDataDir(), "PersistentUI.conf");
    persistentStorage.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    m_config = new wxFileConfig("", "", persistentStorage.GetFullPath());
}

PersistentManager::~PersistentManager() 
{
    m_config->Flush();
    wxDELETE(m_config);
}
