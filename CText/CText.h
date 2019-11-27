#pragma once

// tchar support
#if !defined(UNICODE) && !defined(_UNICODE)
#include "CTextA.h"
typedef CTextA CText;
#else // UNICODE
#include "CTextU.h"
typedef CTextU CText;
#endif // UNICODE

