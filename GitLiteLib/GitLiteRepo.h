#ifndef WXLIBGIT_H
#define WXLIBGIT_H

#include <wx/event.h>
#include <wx/string.h>
#include "GitLiteExports.h"
#include "GitLiteHelperThread.h"

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
    GitLiteHelperThread m_thread;

protected:
    static int FetchProgress(const git_transfer_progress* stats, void* payload);
    static void CheckoutProgress(const char* path, size_t completed_steps, size_t total_steps, void* payload);

public:
    GitLiteRepo();
    ~GitLiteRepo();

    const wxString& GetRepoPath() const { return m_repoPath; }
    const wxString& GetRepoURL() const { return m_repoURL; }

    void SetRepo(git_repository* repo) {this->m_repo = repo;}
    
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
     * This operation is done async via a helper thread. The Clone object fires the following events:
     * wxEVT_GIT_PROGRESS, wxEVT_GIT_PROGRESS_COMPLETED, wxEVT_GIT_PROGRESS_ERROR
     * In case of success, a handler to the git repository is sent back in the event
     */
    void Clone(const wxString& url, const wxString& targetFolder);
};

#endif // WXLIBGIT_H
