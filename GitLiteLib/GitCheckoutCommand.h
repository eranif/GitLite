#ifndef GITCHECKOUTCOMMAND_H
#define GITCHECKOUTCOMMAND_H

#include "GitCommandBase.h" // Base class: GitCommandBase
#include "GitLiteExports.h"

class GitLiteRepo;
class WXDLLIMPEXP_LIBGIT GitCheckoutCommand : public GitCommandBase
{
public:
    enum eCheckoutCommandType {};

protected:
    size_t m_flags;
    wxString m_branchName;

public:
    GitCheckoutCommand(GitLiteRepo* repo, const wxString& branch);
    ~GitCheckoutCommand();

public:
    virtual void Process();
    
};

#endif // GITCHECKOUTCOMMAND_H
