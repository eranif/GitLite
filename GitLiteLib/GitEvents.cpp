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
    , m_totalObjects(0)
    , m_totalDeltas(0)
    , m_receivedObjects(0)
    , m_indexedObjects(0)
    , m_indexedDeltas(0)
{
}

GitLiteCloneEvent& GitLiteCloneEvent::operator=(const GitLiteCloneEvent& src)
{
    GitLiteEvent::operator=(src);
    m_totalObjects = src.m_totalObjects;
    m_totalDeltas = src.m_totalDeltas;
    m_receivedObjects = src.m_receivedObjects;
    m_indexedObjects = src.m_indexedObjects;
    m_indexedDeltas = src.m_indexedDeltas;
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