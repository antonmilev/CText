/**
 * @file CText.h
 * @brief Advanced Text Proccessing Library
 * @author Anton Milev, baj.mile@abv.bg
 * @version 1.0
 * @date November, 2019
 */

#include "CTextT.h"

template<> const char CTextT<char>::CC = '\\';
template<> const char* CTextT<char>::Slash  = "\\/";
template<> const char* CTextT<char>::Separators  = " \t\r\n\v\f";
template<> const char* CTextT<char>::SeparatorsWord = " \t\r\n,;..-!?({[)}]\"";
template<> const char* CTextT<char>::SeparatorsLine  = "\r\n";  
template<> const char* CTextT<char>::SeparatorsSentence = ".?!";  
template<> const char* CTextT<char>::EOL ="\n";
template<> const char CTextT<char>::TAB ='\t';
template<> const char* CTextT<char>::SPACE = " ";
template<> const char* CTextT<char>::SeparatorsRow = " \t";
template<> const char CTextT<char>::HexDigits[16] ={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
template<> const char  CTextT<char>::Literal = '\"';
template<> const char* CTextT<char>::Literals = "\"\'";

typedef CTextT<char> CTextA;

template<>
size_t  CTextA::Vsnprintf(char* str, size_t n, const char * fmt, va_list args)
{
#ifdef _WIN32
    return _vsnprintf(str, n, fmt, args);
#else
    return vsnprintf(str, n, fmt, args);
#endif
};


template<>
bool CTextA::FromChars(const char* s, CTextA& res)
{
    res = s;
    return true;
}


template<>
bool CTextA::ToChars(const char* s, std::basic_string<char>& res)
{
    res = s;
    return true;
}

template<>
bool CTextA::FromWChars(const wchar_t* s, CTextA& res)
{
    if(!s || !*s)
        return false;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
    res.m_str = myconv.to_bytes(s);
    return true;
}

template<>
bool CTextA::ToWChars(const char* s, std::basic_string<wchar_t>& res)
{
    if(!s || !*s)
        return false;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
    res = myconv.from_bytes(s);
    return true;
}

template<>
bool CTextA::ReadFile(const char* filePath, CTextA& res)
{
    std::ifstream ifs(filePath, std::ios::binary);   
    if(!ifs.is_open() || ifs.eof())// Unable to read file
        return false;

    EncodingType encoding = ENCODING_ASCII;
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

    if(encoding == ENCODING_UTF8 || encoding == ENCODING_ASCII)
    {
        std::stringstream ss;
        ss << ifs.rdbuf();
        res = ss.str();
    }

    ifs.close();

    if(encoding == ENCODING_UTF16LE || encoding == ENCODING_UTF16BE)
    {
        std::wstring ws;
        std::wifstream wif(filePath, std::ios::binary);
        if(wif.is_open())
        {
            // apply BOM-sensitive UTF-16 facet
            wif.imbue(std::locale(wif.getloc(), new std::codecvt_utf16<wchar_t, 0x10ffff, std::consume_header>));
            std::wstringstream wss;
            wss << wif.rdbuf();
            ws = wss.str();
            wif.close();
            res.fromWChars(ws.c_str());
        }
    }

    return true;
}

template<>
bool CTextA::ReadLinesFromFile(const char* path, CTextA& res, size_t lineStart, size_t lineEnd)
{
    res.clear();
    size_t num = 0;
    std::string tmpString;
    std::ifstream txtFile(path);
    if(txtFile.is_open())
    {
        while(txtFile.good() && num < lineStart)
        {
            num++;
            std::getline(txtFile, tmpString);
        }

        while(txtFile.good() && num < lineEnd)
        {
            num++;
            std::getline(txtFile, tmpString);
            res += tmpString;
            res += EOL;
        }
        txtFile.close();
    }

    return num;
}

template<>
bool CTextA::WriteFile(const char* filePath, CTextA& s, EncodingType encoding)
{
    std::ofstream file(filePath);

    if(!file.is_open())// unable to read file
        return false;

    if(encoding == ENCODING_ASCII)
    {
        file << s;  //just write to the file without BOM
    }

    else if(encoding == ENCODING_UTF8)
    {
        unsigned char bom[] = {0xEF, 0xBB, 0xBF};
        file.write((char*)bom, sizeof(bom));
        file << s;
    }
    else if(encoding == ENCODING_UTF16LE)
    {
        unsigned char bom[] = {0xFF, 0xFE};
        file.write((char*)bom, sizeof(bom));
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
        std::wstring res = myconv.from_bytes(s.str());
        std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> conv2;
        std::string u16str = conv2.to_bytes(res);
        file << u16str;
    }

    else if(encoding == ENCODING_UTF16BE)
    {
        unsigned char bom[] = {0xFE, 0xFF};
        file.write((char*)bom, sizeof(bom));
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> myconv;
        std::wstring res = myconv.from_bytes(s.str());
        std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>> conv2;
        std::string src = conv2.to_bytes(res);
        std::string dst ;
        dst.resize(src.size() + 1);
        Swab(&src[0u], &dst[0u], src.size());
        file << dst;
    }

    file.close();

    return true;
}

