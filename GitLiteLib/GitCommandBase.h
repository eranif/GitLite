#ifndef GITCOMMANDBASE_H
#define GITCOMMANDBASE_H

#include <wx/event.h>
#include "GitLiteExports.h"

class WXDLLIMPEXP_LIBGIT GitCommandBase
{
    wxEvtHandler* m_sink;

public:
    GitCommandBase(wxEvtHandler* sink);
    virtual ~GitCommandBase();
    wxEvtHandler* GetSink() { return m_sink; }
};

#endif // GITCOMMANDBASE_H
