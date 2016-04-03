#include "GitConfig.h"
#include <wx/stdpaths.h>

GitConfig::GitConfig() {}

GitConfig::~GitConfig() {}

void GitConfig::Load()
{
    wxFileName fn(wxStandardPaths::Get().GetUserDataDir(), "GitLite.conf");
    fn.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    m_json = wxSimpleJSON::Create(fn);
    if(m_json->IsNull()) {
        m_json = wxSimpleJSON::Create(wxString("{}"));
    }
}

void GitConfig::Save()
{
    wxFileName fn(wxStandardPaths::Get().GetUserDataDir(), "GitLite.conf");
    fn.Mkdir(wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
    m_json->Save(fn);
}

void GitConfig::AddSshKeys(
    const wxString& publicKey, const wxString& privateKey, const wxString& remoteUser, const wxString& passphrase)
{
    // Delete any previous settings if exists
    m_json->DeleteProperty("SSHCredentials");
    // Add new node
    m_json->Add("SSHCredentials", wxSimpleJSON::Create(wxSimpleJSON::kObject));
    wxSimpleJSON::Ptr_t p = m_json->GetProperty("SSHCredentials");

    p->Add("publicKey", publicKey)
        .Add("privateKey", privateKey)
        .Add("remoteUser", remoteUser)
        .Add("passphrase", passphrase);
}

bool GitConfig::GetSshKeys(wxString& publicKey, wxString& privateKey, wxString& remoteUser, wxString& passphrase)
{
    wxSimpleJSON::Ptr_t p = m_json->GetProperty("SSHCredentials");
    if(p->IsNull()) return false;

    publicKey = p->GetProperty("publicKey")->GetValueString();
    privateKey = p->GetProperty("privateKey")->GetValueString();
    remoteUser = p->GetProperty("remoteUser")->GetValueString();
    passphrase = p->GetProperty("passphrase")->GetValueString();
    return true;
}

void GitConfig::AddLastCloneInfo(const wxString& cloneURL, const wxString& path)
{
    // Delete any previous settings if exists
    m_json->DeleteProperty("LastClone");
    // Add new node
    m_json->Add("LastClone", wxSimpleJSON::Create(wxSimpleJSON::kObject));
    wxSimpleJSON::Ptr_t p = m_json->GetProperty("LastClone");

    p->Add("cloneURL", cloneURL).Add("path", path);
}

bool GitConfig::GetLastCloneInfo(wxString& cloneURL, wxString& path)
{
    wxSimpleJSON::Ptr_t p = m_json->GetProperty("LastClone");
    if(p->IsNull()) return false;
    cloneURL = p->GetProperty("cloneURL")->GetValueString();
    path = p->GetProperty("path")->GetValueString();
    return true;
}
