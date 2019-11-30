/**
 * @file CText.h
 * @brief Advanced Text Proccessing Library
 * @author Anton Milev, baj.mile@abv.bg
 * @version 1.0
 * @date November, 2019
 */

#include <wchar.h>
#include "CTextT.h"

template<> const wchar_t CTextT<wchar_t>::CC = L'\\'; 
template<> const wchar_t* CTextT<wchar_t>::Slash = L"\\/";
template<> const wchar_t* CTextT<wchar_t>::Separators  = L" \t\r\n";
template<> const wchar_t* CTextT<wchar_t>::SeparatorsWord = L" \t\r\n,;..!-?\"({[)}]";
template<> const wchar_t* CTextT<wchar_t>::SeparatorsLine  = L"\r\n";
template<> const wchar_t* CTextT<wchar_t>::SeparatorsSentence = L".?!"; 
template<> const wchar_t* CTextT<wchar_t>::EOL =L"\n";
template<> const wchar_t  CTextT<wchar_t>::TAB =L'\t';
template<> const wchar_t* CTextT<wchar_t>::SPACE = L" ";
template<> const wchar_t* CTextT<wchar_t>::SeparatorsRow = L" \t";
template<> const wchar_t  CTextT<wchar_t>::HexDigits[16] ={L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9',L'A',L'B',L'C',L'D',L'E',L'F'};
template<> const wchar_t  CTextT<wchar_t>::Literal = L'\"';
template<> const wchar_t* CTextT<wchar_t>::Literals = L"\"\'";

typedef CTextT<wchar_t> CTextU;

template<>
size_t CTextU::Vsnprintf(wchar_t * str, size_t n, const wchar_t * fmt, va_list args)
{
#ifdef _WIN32
    return _vsnwprintf(str, n, fmt, args);
#else
    return vsnwprintf(str, n, fmt, args);
#endif
};

template<>
bool CTextU::FromChars(const char* s, CTextU& res)
{  
    if(!s || !*s)
        return false;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
    res.m_str = myconv.from_bytes(s);

    // with mbstowcs
    //std::string curLocale = setlocale(loc, "");
    //size_t len = mbstowcs(NULL, s, 0) + 1;
    //res.resize(len);
    //res.resize(std::mbstowcs(res.str(), s, len));
    return true;
}

template<>
bool CTextU::ToChars(const wchar_t* s, std::basic_string<char>& res)
{
    if(!s || !*s)
        return false;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
    res = myconv.to_bytes(s);
    return true;
}

template<>
bool CTextU::FromWChars(const wchar_t* s, CTextU& res)
{
    res = s;
    return true;
}

template<>
bool CTextU::ToWChars(const wchar_t* s, std::basic_string<wchar_t>& res)
{
    res = s;
    return true;
}

template<>
static bool CTextU::ReadFile(const wchar_t* filePath, CTextU& res)
{
    std::ifstream ifs(filePath, std::ios::binary);
    EncodingType encoding = ENCODING_ASCII;
    if(!ifs.is_open() || ifs.eof())// Unable to read file
        return false;

    int ch1 = ifs.get();
    int ch2 = ifs.get();

    if(ch1 == 0xFF && ch2 == 0xFE)
        encoding = ENCODING_UTF16LE;// The file contains UTF-16LE BOM
    else if(ch1 == 0xFE && ch2 == 0xFF)
        encoding = ENCODING_UTF16BE; // The file contains UTF-16BE BOM
    else
    {
        int ch3 = ifs.get();
        if(ch1 == 0xEF && ch2 == 0xBB && ch3 == 0xBF) // The file contains UTF-8 BOM
            encoding = ENCODING_UTF8;
    }

    if(encoding == ENCODING_ASCII)  // The file does not have BOM
        ifs.seekg(0);

    //ifs.imbue(std::locale(std::locale(""), new std::codecvt_utf8<wchar_t>));

    std::stringstream ss;
    ss << ifs.rdbuf() << '\0';

    if(encoding == ENCODING_UTF8 || encoding == ENCODING_ASCII)
    {
        FromChars(ss.str().c_str(), res);
    }

    if(encoding == ENCODING_UTF16LE || encoding == ENCODING_UTF16BE)
    {
        std::wifstream wif(filePath, std::ios::binary);
        if(wif.is_open())
        {
            // apply BOM-sensitive UTF-16 facet
            wif.imbue(std::locale(wif.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
            std::wstringstream wss;
            wss << wif.rdbuf();
            res = wss.str();
            wif.close();
        }
    }

    return true;
}

template<>
static bool CTextU::WriteFile(const wchar_t* filePath, CTextU& s, EncodingType encoding)
{
    std::ofstream file(filePath);

    if(!file.is_open())// unable to read file
        return false;

    if(encoding == ENCODING_UTF8)
    {
        unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        file.write((char*)bom, sizeof(bom));

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
        std::string u8str = myconv.to_bytes(s.str());
        file << u8str;
    }

    else if(encoding == ENCODING_UTF16LE)
    {
        unsigned char bom[] = {0xFF, 0xFE};
        file.write((char*)bom, sizeof(bom));

        std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> conv2;
        std::string u16str = conv2.to_bytes(s.str());
        file << u16str;
    }

    else if(encoding == ENCODING_UTF16BE)
    {
        unsigned char bom[] = {0xFE, 0xFF};
        file.write((char*)bom, sizeof(bom));
        std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> conv2;
        std::string src = conv2.to_bytes(s.str());
        std::string dst;
        dst.resize(src.size() + 1);
        CTextT<char>::Swab(&src[0u], &dst[0u], src.size());
        file << dst;
    }

    else  //write UTF8 without BOM
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
        std::string u8str = myconv.to_bytes(s.str());
        file << u8str;
    }

    file.close();

    return true;
}



template<>
bool CTextU::ReadLinesFromFile(const wchar_t* path, CTextU& res, size_t lineStart, size_t lineEnd)
{
    //#error Not implemented for unicode!
    return 0;
}

