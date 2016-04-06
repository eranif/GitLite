#include "GitEvents.h"

wxDEFINE_EVENT(wxEVT_GIT_CRED_REQUIRED, GitLiteCredEvent);
wxDEFINE_EVENT(wxEVT_GIT_CRED_SSH_KEYS_REQUIRED, GitLiteCredEvent);
wxDEFINE_EVENT(wxEVT_GIT_CLONE_STARTED, GitLiteCloneEvent);
wxDEFINE_EVENT(wxEVT_GIT_CLONE_PROGRESS, GitLiteCloneEvent);
wxDEFINE_EVENT(wxEVT_GIT_CLONE_COMPLETED, GitLiteCloneEvent);
wxDEFINE_EVENT(wxEVT_GIT_CLONE_ERROR, GitLiteEvent);
wxDEFINE_EVENT(wxEVT_GIT_CHECKOUT_ERROR, GitLiteEvent);
wxDEFINE_EVENT(wxEVT_GIT_CHECKOUT_COMPLETED, GitLiteEvent);

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
    m_message = src.m_message;
    m_clientData = src.m_clientData;
    m_clientObject = src.m_clientObject;
    return *this;
}

GitLiteEvent::GitLiteEvent(const GitLiteEvent& src) { *this = src; }

GitLiteEvent::~GitLiteEvent() {}

GitLiteCloneEvent::GitLiteCloneEvent(wxEventType commandType, int winid)
    : GitLiteEvent(commandType, winid)
    , m_total(100)
    , m_current(0)
    , m_cancelled(false)
    , m_error(false)
{
}

GitLiteCloneEvent& GitLiteCloneEvent::operator=(const GitLiteCloneEvent& src)
{
    GitLiteEvent::operator=(src);
    m_total = src.m_total;
    m_cancelled = src.m_cancelled;
    m_current = src.m_current;
    m_error = src.m_error;
    m_path = src.m_path;
    m_url = src.m_url;
    return *this;
}

GitLiteCloneEvent::GitLiteCloneEvent(const GitLiteCloneEvent& src) { *this = src; }

GitLiteCloneEvent::~GitLiteCloneEvent() {}

//====================================
// Request for credentials event
//====================================
GitLiteCredEvent::GitLiteCredEvent(wxEventType commandType, int winid)
    : GitLiteEvent(commandType, winid)
    , m_cancelled(false)
{
}

GitLiteCredEvent::GitLiteCredEvent(const GitLiteCredEvent& src) { *this = src; }

GitLiteCredEvent::~GitLiteCredEvent() {}

GitLiteCredEvent& GitLiteCredEvent::operator=(const GitLiteCredEvent& src)
{
    GitLiteEvent::operator=(src);
    m_cancelled = src.m_cancelled;
    m_user = src.m_user;
    m_pass = src.m_pass;
    m_privateKey = src.m_privateKey;
    m_publicKey = src.m_publicKey;
    return *this;
}