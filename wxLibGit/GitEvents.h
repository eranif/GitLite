#ifndef GIT_EVENTS_H
#define GIT_EVENTS_H

/// a wxCommandEvent that takes ownership of the clientData
#include <wx/event.h>
#include "GitLiteExports.h"

/**
 * @class GitLiteEvent
 * @brief base GitLite event
 */
class WXDLLIMPEXP_LIBGIT GitLiteEvent : public wxCommandEvent
{
public:
    GitLiteEvent(wxEventType commandType = wxEVT_NULL, int winid = 0);
    GitLiteEvent(const GitLiteEvent& src);
    GitLiteEvent& operator=(const GitLiteEvent& src);
    virtual ~GitLiteEvent();
    virtual wxEvent* Clone() const { return new GitLiteEvent(*this); }
};

typedef void (wxEvtHandler::*GitLiteEventFunction)(GitLiteEvent&);
#define GitLiteEventHandler(func) wxEVENT_HANDLER_CAST(GitLiteEventFunction, func)

/**
 * @class GitLiteProgressEvent
 * @brief GitLite progress event
 */
class WXDLLIMPEXP_LIBGIT GitLiteProgressEvent : public GitLiteEvent
{
protected:
    int m_total;
    int m_current;
    bool m_cancelled;

public:
    GitLiteProgressEvent(wxEventType commandType = wxEVT_NULL, int winid = 0);
    GitLiteProgressEvent(const GitLiteProgressEvent& src);
    GitLiteProgressEvent& operator=(const GitLiteProgressEvent& src);
    virtual ~GitLiteProgressEvent();
    virtual wxEvent* Clone() const { return new GitLiteProgressEvent(*this); }
    void SetCancelled(bool cancelled) { this->m_cancelled = cancelled; }
    void SetCurrent(int current) { this->m_current = current; }
    void SetTotal(int total) { this->m_total = total; }
    bool IsCancelled() const { return m_cancelled; }
    int GetCurrent() const { return m_current; }
    int GetTotal() const { return m_total; }
    bool IsDone() const { return m_total == m_current; }
};

typedef void (wxEvtHandler::*GitLiteProgressEventFunction)(GitLiteProgressEvent&);
#define GitLiteProgressEventHandler(func) wxEVENT_HANDLER_CAST(GitLiteProgressEventFunction, func)

//========================================
// Define the GIT events
//========================================

wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_PROGRESS, GitLiteProgressEvent);
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_PROGRESS_COMPLETED, GitLiteProgressEvent);

#endif // GIT_EVENTS_H
