/**
 * @file CText.h
 * @brief Advanced Text Proccessing Library
 * @author Anton Milev, baj.mile@abv.bg
 * @version 1.0
 * @date November, 2019
 */
#pragma once 
#include <wchar.h>
#include "CTextT.h"

template<> inline_t const wchar_t CTextT<wchar_t>::CC = L'\\';
template<> inline_t const wchar_t* CTextT<wchar_t>::Slash = L"\\/";
template<> inline_t const wchar_t* CTextT<wchar_t>::Separators  = L" \t\r\n";
template<> inline_t const wchar_t* CTextT<wchar_t>::SeparatorsWord = L" \t\r\n,;..!-?\"({[)}]";
template<> inline_t const wchar_t* CTextT<wchar_t>::SeparatorsLine  = L"\r\n";
template<> inline_t const wchar_t* CTextT<wchar_t>::SeparatorsSentence = L".?!";
template<> inline_t const wchar_t* CTextT<wchar_t>::EOL =L"\n";
template<> inline_t const wchar_t* CTextT<wchar_t>::TAB =L"\t";
template<> inline_t const wchar_t* CTextT<wchar_t>::SPACE = L" ";
template<> inline_t const wchar_t* CTextT<wchar_t>::CR = L"\r";
template<> inline_t const wchar_t* CTextT<wchar_t>::SeparatorsRow = L" \t";
template<> inline_t const wchar_t  CTextT<wchar_t>::HexDigits[16] ={L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9',L'A',L'B',L'C',L'D',L'E',L'F'};
template<> inline_t const wchar_t  CTextT<wchar_t>::Literal = L'\"';
template<> inline_t const wchar_t* CTextT<wchar_t>::Literals = L"\"\'";

typedef CTextT<wchar_t> CTextU;

//-----------------------------------------------------------------------------------------------------------
template<>
inline size_t CTextU::Vsnprintf(wchar_t * str, size_t n, const wchar_t * fmt, va_list args)
{
#ifdef _WIN32
    return _vsnwprintf(str, n, fmt, args);
#else
    return vswprintf(str, n, fmt, args);
#endif
}

//-----------------------------------------------------------------------------------------------------------
template<>
inline CTextU CTextU::FromSingle(const char* s)
{  
    CTextU res;
    if(CTextT<char>::EmptyOrNull(s))
        return res;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
    res.m_str = myconv.from_bytes(s);

    // with mbstowcs
    //std::string curLocale = setlocale(loc, "");
    //size_t len = mbstowcs(NULL, s, 0) + 1;
    //res.resize(len);
    //res.resize(std::mbstowcs(res.str(), s, len));
    return res;
}

//-----------------------------------------------------------------------------------------------------------
template<>
inline CTextT<char> CTextU::ToSingle(const wchar_t* s)
{
    CTextT<char> res;    
    if(!s || !*s)
        return res;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
    res = myconv.to_bytes(s);
    return res;
}

//-----------------------------------------------------------------------------------------------------------
template<>
inline CTextU CTextU::FromWide(const wchar_t* s)
{
    return CTextU(s);
}

//-----------------------------------------------------------------------------------------------------------
template<>
inline CTextT<wchar_t> CTextU::ToWide(const wchar_t* s)
{
    return CTextU(s);
}

//-----------------------------------------------------------------------------------------------------------
template<>
template <typename CharT>
inline bool CTextU::ReadFile(const CharT* filePath, CTextU& res)
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
        res = FromSingle(ss.str().c_str());
    }
#ifdef _WIN32
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
#endif
    return true;
}
template<>
template <typename CharT>
inline bool CTextU::WriteFile(const CharT* filePath, const wchar_t* s, EncodingType encoding)
{
    std::ofstream file(filePath);

    if(!file.is_open())// unable to read file
        return false;

    if(encoding == ENCODING_UTF8)
    {
        unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        file.write((char*)bom, sizeof(bom));

        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
        std::string u8str = myconv.to_bytes(s);
        file << u8str;
    }
#ifdef _WIN32
    else if(encoding == ENCODING_UTF16LE)
    {
        unsigned char bom[] = {0xFF, 0xFE};
        file.write((char*)bom, sizeof(bom));

        std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> conv2;
        std::string u16str = conv2.to_bytes(s);
        file << u16str;
    }

    else if(encoding == ENCODING_UTF16BE)
    {
        unsigned char bom[] = {0xFE, 0xFF};
        file.write((char*)bom, sizeof(bom));
        std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> conv2;
        std::string src = conv2.to_bytes(s);
        std::string dst;
        dst.resize(src.size() + 1);
        CTextT<char>::Swab(&src[0u], &dst[0u], src.size());
        file << dst;
    }
#endif
    else  //write UTF8 without BOM
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
        std::string u8str = myconv.to_bytes(s);
        file << u8str;
    }

    file.close();

    return true;
}


