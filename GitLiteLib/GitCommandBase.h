#ifndef GITCOMMANDBASE_H
#define GITCOMMANDBASE_H

#include <wx/event.h>
#include "GitLiteExports.h"
#include <wx/sharedptr.h>

class WXDLLIMPEXP_LIBGIT GitCommandBase
{
    wxEvtHandler* m_sink;

public:
    typedef wxSharedPtr<GitCommandBase> Ptr_t;

public:
    GitCommandBase(wxEvtHandler* sink);
    virtual ~GitCommandBase();
    wxEvtHandler* GetSink() { return m_sink; }
    
    /**
     * @brief cast the base to its concrete type
     */
    template <typename T> T* Cast() { return dynamic_cast<T*>(const_cast<GitCommandBase*>(this)); }
    
    /**
     * @brief execute the command
     */
    virtual void Process() = 0;
};

#endif // GITCOMMANDBASE_H
