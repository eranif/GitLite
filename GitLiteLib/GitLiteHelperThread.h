#ifndef GITLITEHELPERTHREAD_H
#define GITLITEHELPERTHREAD_H

#include "wx/thread.h" // Base class: wxThread
#include "GitLiteExports.h"
#include <wx/msgqueue.h>

struct WXDLLIMPEXP_LIBGIT GitLiteHelperThreadRequest {
};
class WXDLLIMPEXP_LIBGIT GitLiteHelperThread : public wxThread
{
    wxMessageQueue<GitLiteHelperThreadRequest*> m_queue;

public:
    GitLiteHelperThread();
    ~GitLiteHelperThread();

public:
    virtual void* Entry();
    /**
     * Add a request to the worker thread
     * @param request request to execute.
     */
    void Add(GitLiteHelperThreadRequest* request);

    /**
     * Stops the thread
     * This function returns only when the thread is terminated.
     * @note This call must be called from the context of other thread (e.g. main thread)
     */
    void Stop();

    /**
     * Start the thread as joinable thread.
     * @note This call must be called from the context of other thread (e.g. main thread)
     */
    void Start(int priority = WXTHREAD_DEFAULT_PRIORITY);
};

#endif // GITLITEHELPERTHREAD_H
