#ifdef _WIN32
#include <tchar.h>
#else
#ifdef  _UNICODE
typedef wchar_t TCHAR;
#define _T(x)      L ## x
#else
typedef char TCHAR;
#define _T(x)      x
#endif
#endif

#ifdef _WIN32
#include <direct.h>
#if !defined(UNICODE) && !defined(_UNICODE)
#define getcwd _getcwd 
#else
#define getcwd _wgetcwd
#endif
#else
#include <unistd.h>
#endif
