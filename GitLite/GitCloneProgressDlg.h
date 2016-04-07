#ifndef GITCLONEPROGRESSDLG_H
#define GITCLONEPROGRESSDLG_H
#include "wxcrafter.h"
#include "GitEvents.h"
#include "GitLiteRepo.h"

class GitCloneProgressDlg : public GitCloneProgressBaseDlg
{
    GitLiteRepo* m_repo;

public:
    GitCloneProgressDlg(wxWindow* parent, GitLiteRepo* repo);
    virtual ~GitCloneProgressDlg();
    void Update(const GitLiteCloneEvent& event);

protected:
    virtual void OnCancel(wxCommandEvent& event);
};
#endif // GITCLONEPROGRESSDLG_H
