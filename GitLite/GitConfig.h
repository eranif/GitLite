#ifndef GITCONFIG_H
#define GITCONFIG_H

#include "wxSimpleJSON.h"

class GitConfig
{
    wxSimpleJSON::Ptr_t m_json;

public:
    GitConfig();
    ~GitConfig();

    /**
     * @brief load the configuration file
     */
    void Load();

    /**
     * @brief save the configuration file
     */
    void Save();

    /**
     * @brief store ssh keys in the configuration file
     */
    void AddSshKeys(
        const wxString& publicKey, const wxString& privateKey, const wxString& remoteUser, const wxString& passphrase);
    /**
     * @brief read ssh keys from settings
     */
    bool GetSshKeys(wxString& publicKey, wxString& privateKey, wxString& remoteUser, wxString& passphrase);
    
    /**
     * @brief return the last clone URL
     */
    bool GetLastCloneInfo(wxString& cloneURL, wxString& path);
    void AddLastCloneInfo(const wxString& cloneURL, const wxString& path);
    
    /**
     * @brief return JSON configuraton
     */
    wxSimpleJSON::Ptr_t GetData() const { return m_json; }
};

#endif // GITCONFIG_H
