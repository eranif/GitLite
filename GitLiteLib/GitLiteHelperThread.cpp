#include "GitLiteHelperThread.h"

GitLiteHelperThread::GitLiteHelperThread()
    : wxThread(wxTHREAD_JOINABLE)
{
}

GitLiteHelperThread::~GitLiteHelperThread() {}

void* GitLiteHelperThread::Entry()
{
    while(true) {
        // Did we get a request to terminate?
        if(TestDestroy()) break;
        GitLiteHelperThreadRequest* request = NULL;
        if(m_queue.ReceiveTimeout(50, request) == wxMSGQUEUE_NO_ERROR) {
            wxDELETE(request);
        }
    }
    return NULL;
}

void GitLiteHelperThread::Add(GitLiteHelperThreadRequest* request) { m_queue.Post(request); }

void GitLiteHelperThread::Stop()
{
    // Notify the thread to exit and
    // wait for it
    if(IsAlive()) {
        Delete(NULL, wxTHREAD_WAIT_BLOCK);

    } else {
        Wait(wxTHREAD_WAIT_BLOCK);
    }
}

void GitLiteHelperThread::Start(int priority)
{
    Create();
    SetPriority(priority);
    Run();
}
