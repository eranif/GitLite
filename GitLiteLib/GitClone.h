#ifndef GITCLONE_H
#define GITCLONE_H

#include "GitLiteHelperThread.h"
#include <wx/string.h>
#include "GitCommandBase.h"
#include "GitLiteExports.h"

typedef struct git_transfer_progress git_transfer_progress;
typedef struct git_repository git_repository;

class WXDLLIMPEXP_LIBGIT GitCloneCommand : public GitCommandBase
{
    wxString m_url;
    wxString m_folder;
    bool m_startEventSent;

protected:
    static int FetchProgress(const git_transfer_progress* stats, void* payload);
    static void CheckoutProgress(const char* path, size_t completed_steps, size_t total_steps, void* payload);

public:
    virtual void Process();
    GitCloneCommand(GitLiteRepo* repo, const wxString& url, const wxString& targetFolder);
    ~GitCloneCommand();
};

#endif // GITCLONE_H
