#ifndef GITBRANCH_H
#define GITBRANCH_H

#include "GitCommandBase.h"
#include "GitLiteExports.h"
#include "GitLiteRepo.h"

class WXDLLIMPEXP_LIBGIT GitBranch : public GitCommandBase
{
public:
    enum eBranchCommandType {
        kListBranches = (1 << 0),
    };

protected:
    GitLiteRepo* m_gitRepo;
    size_t m_command;
    wxArrayString m_localBranches;
    wxArrayString m_remoteBranches;

public:
    GitBranch(GitLiteRepo* repo, size_t command);
    ~GitBranch();

    virtual void Process();
    
    const wxArrayString& GetLocalBranches() const { return m_localBranches; }
    const wxArrayString& GetRemoteBranches() const { return m_remoteBranches; }
};

#endif // GITBRANCH_H
