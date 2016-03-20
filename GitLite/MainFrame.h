#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include "GitLiteRepo.h"
#include "GitEvents.h"
#include <wx/progdlg.h>

class MainFrame : public MainFrameBaseClass
{
    GitLiteRepo m_repo;
    wxProgressDialog* m_cloneProgress;

public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

protected:
    virtual void OnClone(wxCommandEvent& event);

    // Git clone event handlers
    void OnCloneError(GitLiteCloneEvent& event);
    void OnCloneStart(GitLiteCloneEvent& event);
    void OnCloneCompleted(GitLiteCloneEvent& event);
    void OnCloneProgress(GitLiteCloneEvent& event);
};
#endif // MAINFRAME_H
