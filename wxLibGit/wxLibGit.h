#ifndef WXLIBGIT_H
#define WXLIBGIT_H

#include <wx/event.h>
#include <wx/string.h>
#include "GitLiteExports.h"

typedef struct git_transfer_progress git_transfer_progress;
typedef struct git_repository git_repository;

class WXDLLIMPEXP_LIBGIT GitLiteException
{
    wxString m_what;

public:
    GitLiteException(const wxString& what)
        : m_what(what)
    {
    }
    virtual ~GitLiteException() {}
    const wxString& What() const { return m_what; }
};

class WXDLLIMPEXP_LIBGIT GitLiteRepo : public wxEvtHandler
{
    git_repository* m_repo;
    wxString m_repoURL;
    wxString m_repoPath;

protected:
    static int FetchProgress(const git_transfer_progress* stats, void* payload);
    static void CheckoutProgress(const char* path, size_t completed_steps, size_t total_steps, void* payload);

public:
    GitLiteRepo();
    ~GitLiteRepo();

    const wxString& GetRepoPath() const { return m_repoPath; }
    const wxString& GetRepoURL() const { return m_repoURL; }

    /**
     * @brief initialize the library
     */
    static void Initialize();
    /**
     * @brief shutdown the library
     */
    static void Shutdown();
    /**
     * @brief clone a repository into a target folder
     */
    void Clone(const wxString& url, const wxString& targetFolder) throw(GitLiteException);
};

#endif // WXLIBGIT_H
