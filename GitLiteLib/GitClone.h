#ifndef GITCLONE_H
#define GITCLONE_H

#include "GitLiteHelperThread.h"
#include <wx/string.h>

typedef struct git_transfer_progress git_transfer_progress;
typedef struct git_repository git_repository;

class GitClone : public GitLiteThreadRequest
{
    wxString m_url;
    wxString m_folder;
    GitLiteHelperThread* m_thread;

protected:
    static int FetchProgress(const git_transfer_progress* stats, void* payload);
    static void CheckoutProgress(const char* path, size_t completed_steps, size_t total_steps, void* payload);

public:
    virtual void Process(GitLiteHelperThread* thread);

    GitClone(wxEvtHandler* sink, const wxString& url, const wxString& targetFolder);
    ~GitClone();
};

#endif // GITCLONE_H
