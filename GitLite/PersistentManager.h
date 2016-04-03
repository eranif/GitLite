#ifndef PERSISTENTMANAGER_H
#define PERSISTENTMANAGER_H

#include <wx/persist.h>
#include <wx/fileconf.h>

class PersistentManager : public wxPersistenceManager
{
    wxFileConfig* m_config;

public:
    PersistentManager();
    ~PersistentManager();

    wxConfigBase* GetConfig() const { return m_config; }
};

#endif // PERSISTENTMANAGER_H
