#include "GitEvents.h"

//====================================
// GitLiteEvent event
//====================================
GitLiteEvent::GitLiteEvent(wxEventType commandType, int winid)
    : wxCommandEvent(commandType, winid)
{
}

GitLiteEvent& GitLiteEvent::operator=(const GitLiteEvent& src)
{
    // Copy wxCommandEvent members here
    m_eventType = src.m_eventType;
    m_id = src.m_id;
    m_cmdString = src.m_cmdString;
    m_commandInt = src.m_commandInt;
    m_extraLong = src.m_extraLong;
    return *this;
}

GitLiteEvent::GitLiteEvent(const GitLiteEvent& src) { *this = src; }

GitLiteEvent::~GitLiteEvent() {}

//====================================
// Progress event
//====================================
wxDEFINE_EVENT(wxEVT_GIT_PROGRESS, GitLiteProgressEvent);
wxDEFINE_EVENT(wxEVT_GIT_PROGRESS_COMPLETED, GitLiteProgressEvent);

GitLiteProgressEvent::GitLiteProgressEvent(wxEventType commandType, int winid)
    : GitLiteEvent(commandType, winid)
    , m_total(100)
    , m_current(0)
    , m_cancelled(false)
{
}

GitLiteProgressEvent& GitLiteProgressEvent::operator=(const GitLiteProgressEvent& src)
{
    GitLiteEvent::operator=(src);
    m_total = src.m_total;
    m_cancelled = src.m_cancelled;
    m_current = src.m_current;
    return *this;
}

GitLiteProgressEvent::GitLiteProgressEvent(const GitLiteProgressEvent& src) { *this = src; }

GitLiteProgressEvent::~GitLiteProgressEvent() {}
