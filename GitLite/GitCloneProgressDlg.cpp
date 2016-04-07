#include "GitCloneProgressDlg.h"
#include <wx/wupdlock.h>

GitCloneProgressDlg::GitCloneProgressDlg(wxWindow* parent, GitLiteRepo* repo)
    : GitCloneProgressBaseDlg(parent)
    , m_repo(repo)
{
}

GitCloneProgressDlg::~GitCloneProgressDlg() {}

void GitCloneProgressDlg::Update(const GitLiteCloneEvent& event)
{
    double total_objects = event.GetTotalObjects();
    double indexed_objects = event.GetIndexedObjects();
    double total_deltas = event.GetTotalDeltas();
    double indexed_deltas = event.GetIndexedDeltas();
    double recv_objects = event.GetReceivedObjects();

    // Objects received progress
    double prog1 = ((recv_objects / total_objects) * 100.0);
    // Indexed objects
    double prog2 = ((indexed_objects / total_objects) * 100.0);
    // Indexed deltas
    double prog3 = ((indexed_deltas / total_deltas) * 100.0);

    wxWindowUpdateLocker locker(this);
    m_gaugeObjRecv->SetValue(prog1);
    m_gaugeObjIndexed->SetValue(prog2);
    m_gaugeDeltasIndexed->SetValue(prog3);

    m_staticTextIndexedDeltas->SetLabel(wxString() << indexed_deltas << "/" << total_deltas);
    m_staticTextRecvObjects->SetLabel(wxString() << recv_objects << "/" << total_objects);
    m_staticTextIndexedObjects->SetLabel(wxString() << indexed_objects << "/" << total_objects);
}

void GitCloneProgressDlg::OnCancel(wxCommandEvent& event) { m_repo->GetHelperThread().SetCancel(true); }
