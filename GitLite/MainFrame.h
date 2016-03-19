#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include "wxLibGit.h"

class MainFrame : public MainFrameBaseClass
{
    GitLiteRepo m_repo;
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
    virtual void OnClone(wxCommandEvent& event);
};
#endif // MAINFRAME_H
