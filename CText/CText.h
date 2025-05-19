#pragma once
#include "CTextA.h"
// tchar support
#if !defined(UNICODE) && !defined(_UNICODE)
typedef CTextA CText;
#else // UNICODE
#include "CTextU.h"
typedef CTextU CText;
#endif // UNICODE

