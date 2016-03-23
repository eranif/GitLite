#ifndef GITCLONEDIALOG_H
#define GITCLONEDIALOG_H
#include "wxcrafter.h"

class GitCloneDialog : public GitCloneDialogBase
{
public:
    GitCloneDialog(wxWindow* parent);
    virtual ~GitCloneDialog();
};
#endif // GITCLONEDIALOG_H
