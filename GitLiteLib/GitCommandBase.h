#ifndef GITCOMMANDBASE_H
#define GITCOMMANDBASE_H

#include <wx/event.h>
#include "GitLiteExports.h"
#include <wx/sharedptr.h>

class wxThread;
class GitLiteRepo;
class WXDLLIMPEXP_LIBGIT GitCommandBase
{
    GitLiteRepo* m_repo;
    
public:
    typedef wxSharedPtr<GitCommandBase> Ptr_t;

public:
    GitCommandBase(GitLiteRepo* sink);
    virtual ~GitCommandBase();
    GitLiteRepo* GetRepo() { return m_repo; }
    
    /**
     * @brief cast the base to its concrete type
     */
    template <typename T> T* Cast() { return dynamic_cast<T*>(const_cast<GitCommandBase*>(this)); }
    
    /**
     * @brief execute the command
     */
    virtual void Process(wxThread* thread = nullptr) = 0;
};

#endif // GITCOMMANDBASE_H
