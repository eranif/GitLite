#include "GitCommandBase.h"

GitCommandBase::GitCommandBase(wxEvtHandler* sink)
    : m_sink(sink)
{
}

GitCommandBase::~GitCommandBase()
{
}

