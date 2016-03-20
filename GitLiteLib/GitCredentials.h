#ifndef GITCREDENTIALS_H
#define GITCREDENTIALS_H

typedef struct git_cred git_cred;

class GitCredentials
{
public:
    GitCredentials();
    ~GitCredentials();

    static int CloneCredentials(
        git_cred** out, const char* url, const char* username_from_url, unsigned int allowed_types, void* payload);
};

#endif // GITCREDENTIALS_H
