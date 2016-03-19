#ifndef GITLITE_EXPORTS_H
#define GITLITE_EXPORTS_H

#ifdef __WXMSW__
#ifdef WXDLLIMPEXP_LIBGIT
#undef WXDLLIMPEXP_LIBGIT
#endif
#ifdef WXMAKINGDLL_LIBGIT
#define WXDLLIMPEXP_LIBGIT __declspec(dllexport)
#elif defined(WXUSINGDLL_LIBGIT)
#define WXDLLIMPEXP_LIBGIT __declspec(dllimport)
#else // not making nor using DLL
#define WXDLLIMPEXP_LIBGIT
#endif
#else
#define WXDLLIMPEXP_LIBGIT
#endif

#endif // GITLITE_EXPORTS_H
