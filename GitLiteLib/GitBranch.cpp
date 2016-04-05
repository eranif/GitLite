#include "GitBranch.h"
#include <git2/buffer.h>
#include <git2/branch.h>

GitBranch::GitBranch(GitLiteRepo* repo, size_t commandType)
    : GitCommandBase(repo)
    , m_gitRepo(repo)
    , m_command(commandType)
{
}

GitBranch::~GitBranch() {}

void GitBranch::Process()
{
    if(m_command & kListBranches) {
        git_branch_iterator* iter = NULL;
        git_branch_iterator_new(&iter, m_gitRepo->GetRepoHandler(), GIT_BRANCH_ALL);
        if(iter) {
            git_reference* ref = NULL;
            git_branch_t branchType;
            int rc = git_branch_next(&ref, &branchType, iter);
            while(rc == 0) {
                const char* name = NULL;
                git_branch_name(&name, ref);
                if(branchType == GIT_BRANCH_LOCAL) {
                    m_localBranches.Add(name);
                } else {
                    m_remoteBranches.Add(name);
                }
                rc = git_branch_next(&ref, &branchType, iter);
            }
        }
        git_branch_iterator_free(iter);
    }
}
