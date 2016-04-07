#ifndef GIT_EVENTS_H
#define GIT_EVENTS_H

/// a wxCommandEvent that takes ownership of the clientData
#include <wx/event.h>
#include "GitLiteExports.h"
#include <wx/filename.h>

/**
 * @class GitLiteEvent
 * @brief base GitLite event
 */
class WXDLLIMPEXP_LIBGIT GitLiteEvent : public wxCommandEvent
{
    wxString m_message;

public:
    GitLiteEvent(wxEventType commandType = wxEVT_NULL, int winid = 0);
    GitLiteEvent(const GitLiteEvent& src);
    GitLiteEvent& operator=(const GitLiteEvent& src);
    virtual ~GitLiteEvent();
    virtual wxEvent* Clone() const { return new GitLiteEvent(*this); }
    void SetMessage(const wxString& message) { this->m_message = message; }
    const wxString& GetMessage() const { return m_message; }
};

typedef void (wxEvtHandler::*GitLiteEventFunction)(GitLiteEvent&);
#define GitLiteEventHandler(func) wxEVENT_HANDLER_CAST(GitLiteEventFunction, func)

/**
 * @class GitLiteCloneEvent
 * @brief GitLite progress event
 */
class WXDLLIMPEXP_LIBGIT GitLiteCloneEvent : public GitLiteEvent
{
protected:
    int m_totalObjects;
    int m_totalDeltas;
    int m_receivedObjects;
    int m_indexedObjects;
    int m_indexedDeltas;
    wxString m_url;
    wxString m_path;

public:
    GitLiteCloneEvent(wxEventType commandType = wxEVT_NULL, int winid = 0);
    GitLiteCloneEvent(const GitLiteCloneEvent& src);
    GitLiteCloneEvent& operator=(const GitLiteCloneEvent& src);
    virtual ~GitLiteCloneEvent();
    virtual wxEvent* Clone() const { return new GitLiteCloneEvent(*this); }
    void SetIndexedDeltas(int indexedDeltas) { this->m_indexedDeltas = indexedDeltas; }
    void SetIndexedObjects(int indexedObjects) { this->m_indexedObjects = indexedObjects; }
    void SetPath(const wxString& path) { this->m_path = path; }
    void SetReceivedObjects(int receivedObjects) { this->m_receivedObjects = receivedObjects; }
    void SetTotalDeltas(int totalDeltas) { this->m_totalDeltas = totalDeltas; }
    void SetTotalObjects(int totalObjects) { this->m_totalObjects = totalObjects; }
    void SetUrl(const wxString& url) { this->m_url = url; }
    int GetIndexedDeltas() const { return m_indexedDeltas; }
    int GetIndexedObjects() const { return m_indexedObjects; }
    const wxString& GetPath() const { return m_path; }
    int GetReceivedObjects() const { return m_receivedObjects; }
    int GetTotalDeltas() const { return m_totalDeltas; }
    int GetTotalObjects() const { return m_totalObjects; }
    const wxString& GetUrl() const { return m_url; }
};

typedef void (wxEvtHandler::*GitLiteCloneEventFunction)(GitLiteCloneEvent&);
#define GitLiteCloneEventHandler(func) wxEVENT_HANDLER_CAST(GitLiteCloneEventFunction, func)

/**
 * @class GitLiteCredEvent
 * @brief request for credentials
 */
class WXDLLIMPEXP_LIBGIT GitLiteCredEvent : public GitLiteEvent
{
protected:
    wxString m_user;
    wxString m_pass; // password or passphrase
    wxString m_privateKey;
    wxString m_publicKey;
    bool m_cancelled;

public:
    GitLiteCredEvent(wxEventType commandType = wxEVT_NULL, int winid = 0);
    GitLiteCredEvent(const GitLiteCredEvent& src);
    GitLiteCredEvent& operator=(const GitLiteCredEvent& src);
    virtual ~GitLiteCredEvent();
    virtual wxEvent* Clone() const { return new GitLiteCredEvent(*this); }
    void SetCancelled(bool cancelled) { this->m_cancelled = cancelled; }
    void SetPass(const wxString& pass) { this->m_pass = pass; }
    void SetUser(const wxString& user) { this->m_user = user; }
    bool IsCancelled() const { return m_cancelled; }
    const wxString& GetPass() const { return m_pass; }
    const wxString& GetUser() const { return m_user; }
    void SetPrivateKey(const wxString& privateKey) { this->m_privateKey = privateKey; }
    void SetPublicKey(const wxString& publicKey) { this->m_publicKey = publicKey; }
    const wxString& GetPrivateKey() const { return m_privateKey; }
    const wxString& GetPublicKey() const { return m_publicKey; }
};
typedef void (wxEvtHandler::*GitLiteCredEventFunction)(GitLiteCredEvent&);
#define GitLiteCredEventHandler(func) wxEVENT_HANDLER_CAST(GitLiteCredEventFunction, func)

//========================================
// Define the GIT events
//========================================

// Clone specific events
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_CLONE_STARTED, GitLiteCloneEvent);
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_CLONE_PROGRESS, GitLiteCloneEvent);
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_CLONE_COMPLETED, GitLiteCloneEvent);
// Credential specific events
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_CRED_REQUIRED, GitLiteCredEvent);
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_CRED_SSH_KEYS_REQUIRED, GitLiteCredEvent);
// Error events
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_CLONE_ERROR, GitLiteEvent);
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_CHECKOUT_ERROR, GitLiteEvent);
// Success events
wxDECLARE_EXPORTED_EVENT(WXDLLIMPEXP_LIBGIT, wxEVT_GIT_CHECKOUT_COMPLETED, GitLiteEvent);

#endif // GIT_EVENTS_H
