#include "CTextT.h"
//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT()
{}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(const std::basic_string<T>& s) : m_str(s)
{}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(std::basic_string<T>&& s) noexcept : m_str(std::move(s))
{}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(T c, size_t len) : m_str(len, c)
{}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(const CTextT& str) : m_str(str.m_str)
{}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(CTextT&& str) noexcept : m_str(std::move(str.m_str))
{}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(const T* s)
{
    if(!EmptyOrNull(s))
        m_str = s;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(const T* s, size_t len) : m_str(s, len)
{}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(std::initializer_list<const T*> list)
{
    for(auto s : list)
    {
        if(!EmptyOrNull(s))
            m_str.append(s);
    }
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::CTextT(std::initializer_list<T> list) : m_str(list)
{}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>::~CTextT()
{
    clear();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator=(const CTextT<T>& s)
{
    if(&s == this)
        return *this;
    equal(s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator=(CTextT&& s) noexcept
{
    if(&s == this)
        return *this;

    m_str = std::move(s.m_str);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator=(std::basic_string<T>&& s) noexcept
{
    if(&s == &m_str)
        return *this;

    m_str = std::move(s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator=(const std::basic_string<T>& s)
{
    if(&s == &m_str)
        return *this;
    equal(s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator=(const T* s)
{
    equal(s);
    return *this;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
const CTextT<T>& CTextT<T>::operator+=(const T* str)
{
    append(str);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const CTextT<T>& CTextT<T>::operator+=(const CTextT<T>& string)
{
    if(string.isEmpty())
        return *this;
    append(string);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const CTextT<T>& CTextT<T>::operator+=(T ch)
{
    append(ch);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator<<(const T* s)
{
    append(s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator<<(const T c)
{
    append(c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator<<(const std::basic_string<T>& s)
{
    append(s.c_str());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator<<(const CTextT& s)
{
    append(s.str());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
CTextT<T>& CTextT<T>::operator<<(Num i)
{
    fromInteger(i, true);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator << (double f)
{
    fromDouble(f, 6, true, true, true);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::clear(bool bRelease)
{
    if(isEmpty())
        return;

    m_str.clear();

    if(bRelease)
        m_str.shrink_to_fit();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T CTextT<T>::at(size_t pos) const
{
    return m_str.at(pos);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T& CTextT<T>::at(size_t pos)
{
    return m_str.at(pos);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T CTextT<T>::operator[](size_t pos) const
{
    return m_str[pos];
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T& CTextT<T>::operator[](size_t pos)
{
    return m_str[pos];
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::length() const
{
    return m_str.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::equal(T c, size_t len)
{
    m_str.assign(len, c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::equal(const CTextT<T>& s)
{
    m_str.assign(s.m_str);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::equal(const T* s)
{
    if(EmptyOrNull(s))
        clear();
    else
        m_str.assign(s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::equal(const T* s, size_t len, size_t offset)
{
    if(EmptyOrNull(s))
        clear();
    else
        m_str.assign(s + offset, len);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::copyTo(T* s)
{
    if(length())
    {
        memcpy(s, str(), length() * sizeof(T));
        str[length()] = 0;
    }
    else
        *str = 0;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::copyTo(T* s, size_t max_len)
{
    size_t nToCopy = std::min(max_len, length());
    if(nToCopy)
    {
        memcpy(s, str(), nToCopy * sizeof(T));
        s[nToCopy] = 0;
    }
    else
        *s = 0;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::str(size_t from) const
{
    if(from >= length())
        return nullptr;
    return m_str.c_str() + from;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T* CTextT<T>::str()
{
    return &m_str[0];
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t  CTextT<T>::capacity() const
{
    return m_str.capacity();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::alloc(size_t len)
{
    m_str.reserve(len);
    return m_str.capacity() == len;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isEmpty() const
{
    return (m_str.size() == 0);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::Add(const CTextT& str1, const CTextT& str2)
{
    CTextT<T> res;
    res.m_str = str1.m_str + str2.m_str;
    return res;
}
//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::Add(const CTextT<T>& str1, const T* str2)
{
    CTextT<T> res;
    res.m_str = str1.m_str + str2;
    return res;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::Add(const T* str1, const CTextT<T>& str2)
{
    CTextT<T> res(str1);
    res += str2;
    return res;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::Add(const CTextT<T>& str, T c)
{
    CTextT<T> res;
    res.m_str = str.m_str + c;
    return res;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::Add(T c, const CTextT<T>& str)
{
    CTextT<T> res(c);
    res += str;
    return res;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::append(const CTextT<T>& str)
{
    m_str.append(str.m_str);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::append(T c, size_t count)
{
    m_str.append(count, c);
    return *this;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::append(const T* s)
{
    if(!EmptyOrNull(s))
        m_str.append(s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::append(const T* s, size_t len)
{
    if(!EmptyOrNull(s))
        m_str.append(s, len);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::append(std::initializer_list<T> list)
{
    for(T c : list)
        append(c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::append(std::initializer_list<const T*> list)
{
    for(const T* c : list)
        append(c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::append(const C& container)
{
    for(auto& v : container)
        append(v);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::appendRange(T cBegin, T cEnd)
{
    for(T c = cBegin; c <= cEnd; c++)
        append(c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::Strlen(const T* str)
{
    if(!str)
        return 0;

    int n = 0;

    while(*str++)
        n++;

    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T* CTextT<T>::Strcpy(T* dst, const T* src)
{
    if(!dst)
        return 0;

    T* d = dst;

    *d = 0;

    if(!src)
        return d;

    while((*d++ = *src++) != 0);

    return (dst);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T* CTextT<T>::Strncpy(T *dst, const T *src, size_t n)
{
    if(!dst || !src || !n)
        return dst;

    T* d = dst;

    while(*src && n--)
        *d++ = *src++;

    // force ending zero 
    *d = 0;
    return dst;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T* CTextT<T>::Strcat(T* dst, const T *src)
{
    if(!dst || !src)
        return dst;

    T* d = dst;

    while(*d)
        d++;

    while(*src)
        *d++ = *src++;

    *d = 0;
    return dst;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T* CTextT<T>::Strncat(T *dst, const T *src, size_t n)
{
    if(!dst || !src)
        return dst;

    T* d = dst;

    while(*d)
        d++;

    while(*src && n--)
        *d++ = *src++;

    *d = 0;
    return dst;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T CTextT<T>::lower(T c)
{
    return ::tolower(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T CTextT<T>::upper(T c)
{
    return (T)(::toupper(c));
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsDigit(T c)
{
    return isdigit(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsAlpha(T c)
{
    return isalpha(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsAlphanumeric(T c)
{
    return isalnum(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsLower(T c)
{
    return islower(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsHex(T c)
{
    return isxdigit(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsUpper(T c)
{
    return isupper(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsSpace(T c)
{
    return isspace(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsFormating(T c)
{
    return c == *SPACE || c == *TAB || c == *EOL || c == *CR;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T CTextT<T>::first() const
{
    if(isEmpty())
        return 0;
    return m_str.front();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T CTextT<T>::last() const
{
    if(isEmpty())
        return 0;

    return m_str.back();
}
//-----------------------------------------------------------------------------------------------------------
//Return Value
//Returns an integral value indicating the relationship between the strings:
//return value  indicates
//<0    the first character that does not match has a lower value in ptr1 than in ptr2
//        OR first string is empty while second is not
//0     the contents of both strings are equal
//        OR both strings are empty
//>0    the first character that does not match has a greater value in ptr1 than in ptr2
//        OR second string is empty while first is not
template <typename T>
int CTextT<T>::Strcmp(const T* p1, const T* p2, bool bCase)
{
    if(!p1 || !*p1)
    {
        if(!p2 || !*p2)
            return 0; //both strings are empty
        else
            return -1;  // second bigger then first
    }

    if(!p2 || !*p2)
    {
        if(!p1 || !*p1)
            return 0; //both strings are empty
        else
            return 1; // second less then first
    }

    T x1 = *p1, x2 = *p2;
    while(x1 != 0 && x2 != 0)
    {
        if(!bCase)
        {
            x1 = upper(x1);
            x2 = upper(x2);
        }

        if(x1 < x2)       // first less than second 
            return -1;

        else if(x1 > x2)  // first bigger than second 
            return 1;

        x1 = *++p1;
        x2 = *++p2;
    }

    if(x2 > x1)
        return -1;

    if(x1 > x2)
        return 1;

    return 0;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::StartsWith(const T* text, const T* str, bool bCase, size_t max_len, size_t* count)
{
    if(EmptyOrNull(text) || EmptyOrNull(str))
        return false;

    const T* start = text;
    const T* start_s = str;

    while(*text != 0 && *str != 0)
    {
        if(0 != *str && (bCase ? (*text != *str) : (upper(*text) != upper(*str))))
            return false;
        text++;
        str++;

        // check if the maximal number of characters is reached
        if(max_len > 0 && (size_t)(text - start) >= max_len)
            break; 
    }

    if(*str != 0)
        return false;

    if(count)
        *count = (size_t)(str - start_s);

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::startsWith(T c, size_t from, bool bCase, size_t* count) const
{
    if(isEmpty() || from >= length())
        return false;

    if(count) *count = 1;
    T first = *(str(from));
    return bCase ? (first == c) : (upper(first) == upper(c));
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename S, typename X>
bool CTextT<T>::startsWith(const S& s, size_t from, bool bCase, size_t* count) const
{
    if(isEmpty() || EmptyOrNull(ToStr(s)) || from >= length())
        return false;

    return StartsWith(str(from), ToStr(s), bCase, 0, count);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::startsWith(std::initializer_list<T> list)
{
    for(T c : list)
    {
        if(startsWith(c))
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CharTrie CTextT<T>::BuildTrie(C& list, bool bCase, bool reverse)
{
    CharTrie trie;
    size_t pos = 0;
    if(bCase == true)
    {
        for(auto& str : list)
        {
            trie.add((const CharTrie::byte*)(ToStr(str)), Strlen(str) * sizeof(T), pos, reverse);
            pos++;
        }
    }
    else
    {
        CTextT<T> sTemp;
        for(auto& str : list)
        {
            sTemp = str;
            sTemp.toLower();
            trie.add((const CharTrie::byte*)(sTemp.str()), sTemp.length()*sizeof(T), pos, reverse);
            pos++;
        }
    }
    return trie;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
bool CTextT<T>::startsWithAny(const C& list, size_t from, bool bCase, bool useTrie, size_t* idx, size_t* count) const
{
    if(isEmpty() || from >= length())
        return false;

    size_t pos = 0, len ;
    if(useTrie)
    {
        CharTrie t = BuildTrie(list, bCase);
        bool res = t.beginsWith((const CharTrie::byte*)(str(from)), (length()-from) * sizeof(T), pos, len );
        if(idx) *idx = pos;
        if(count) *count = (len/ sizeof(T));
        t.clear();
        return res;
    }
    else
    {
        // iterate through all strings in the list
        for(auto& s : list)
        {
            if(startsWith(s, from, bCase, count))
            {
                if(idx) *idx = pos;
                return true;
            }
            pos++;
        }
    }

    return false;
}




//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsOneOf(T c, const T* list, bool bCase, size_t* idx)
{
    if(EmptyOrNull(list))
        return false;

    const T* s = list;

    if(!bCase) c = upper(c);

    T c2 = bCase ? *s : upper(*s);

    while(c2)
    {
        if(c == c2)
        {
            if(idx) *idx = (s - list);
            return true;
        }
        c2 = bCase ? *++s : upper(*++s);
    }
    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename S, typename X>
bool CTextT<T>::startsWithAny(const S& cList, size_t from, bool bCase, size_t* idx, size_t* count) const
{
    if(from >= length() || EmptyOrNull((const T*)cList))
        return false;
    bool bRes = IsOneOf(m_str[from], (const T*)cList, bCase);
    if(bRes)
        if(idx) *idx = from;
    if(count) *count = 1;
    return bRes;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::endsWith(T c, size_t from, bool bCase) const
{
    if(isEmpty() || from >= length())
        return false;

    T last = *str(length() - from - 1);

    if(bCase)
        return last == c;
    else
        return upper(last) == upper(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename S, typename X>
bool CTextT<T>::endsWith(const S& s, size_t from, bool bCase) const
{
    if(isEmpty() || EmptyOrNull(ToStr(s)) || from >= length())
        return false;

    from = length() - from;  //from is calculated from the back

    return EndsWith(str(), ToStr(s), bCase, from);
}



//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::endsWith(std::initializer_list<T> cList)
{
    for(T c : cList)
    {
        if(endsWith(c))
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::EndsWith(const T* text, const T* str, bool bCase, size_t len)
{
    size_t str_len = Strlen(str);
    if(str_len == 0)
        return false;

    if(len == std::string::npos)
        len = Strlen(text);

    if(str_len > len)
        return false;

    const T* s = text + len - 1;
    const T* sBegin = str;
    const T* strEnd = str + str_len - 1;

    if(bCase)
    {
        while(strEnd >= sBegin)
        {
            if(*strEnd != *s)
                return false;
            strEnd--;
            s--;
        }
    }
    else // case insensitive
    {
        while(strEnd >= sBegin)
        {
            if(upper(*strEnd) != upper(*s))
                return false;
            strEnd--;
            s--;
        }
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::endsWithAny(const T* cList, bool bCase) const
{
    if(isEmpty() || EmptyOrNull(cList))
        return false;

    return IsOneOf(m_str[length() - 1], cList, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
bool CTextT<T>::endsWithAny(const C& list, size_t from, bool bCase, bool useTrie, size_t* idx) const
{
    size_t pos = 0, len;
    if(useTrie)
    {
        CharTrie t = BuildTrie(list, bCase, true);
        bool res = t.endWith((const CharTrie::byte*)(str(from)), (length() - from) * sizeof(T), pos, len);
        if(idx) *idx = pos;
        t.clear();
        return res;
    }
    else
    {
        for(auto v : list)
        {
            if(endsWith(v, from, bCase))
            {
                if(idx) *idx = pos;
                return true;
            }
            pos++;
        }
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::contain(T c, bool bCase) const
{
    if(bCase)
        return m_str.find(c) != std::string::npos;

    return StrFindCh(str(), c, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::contain(const T* s, bool bCase) const
{
    if(isEmpty() || EmptyOrNull(s))
        return false;

    if(bCase)
        return m_str.find(s) != std::string::npos;

    return StrFind(str(), s, bCase) != nullptr;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::contain(const T c, size_t from, size_t to) const
{
    if(isEmpty() || from >= length() || to < from)
        return false;

    if(to > length() - 1)
        to = length() - 1;

    auto start = m_str.begin() + from;
    auto end = m_str.begin() + to + 1;
    while(start != end)
    {
        if(*start++ == c)
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isEqual(const T* s, bool bCase) const
{
    return compare(s, bCase) == 0;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::StrFind(const T* str, const T* text, bool bCase)
{
    if(!str || !*str || !text || !*text)
        return 0;

    T cht = *str;

    while(cht)
    {
        if(StartsWith(str, text, bCase))
            return str;

        cht = *++str;
    }

    return nullptr;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::Contain(const T* text, const T* str, bool bCase) 
{
    if(EmptyOrNull(text) || EmptyOrNull(str))
        return false;

    return StrFind(text, str, bCase) != nullptr;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::StrFindCh(const T* s, T c, bool bCase)
{
    if(!bCase) c = upper(c);

    T cs = bCase ? *s : upper(*s);

    while(cs)
    {
        if(cs == c)
            return s;

        cs = bCase ? *++s : upper(*++s);
    }

    return nullptr;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::find(const T *s, bool bCase) const
{
    return StrFind(str(), s, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::find(const T c, bool bCase) const
{
    return StrFindCh(str(), c, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::reverseFind(const T* s, bool bCase) const
{
    size_t idx = lastIndexOf(s, 0, bCase);

    if(idx == std::string::npos)
        return nullptr;

    return str(idx);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::lastIndexOf(T c, size_t from, bool bCase) const
{
    if(isEmpty() || from > length()-1)
        return std::string::npos;

    return LastIndexOf(str(from), length()-from, c, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::lastIndexOf(const T* s, size_t from, bool bCase) const
{
    if(EmptyOrNull(s) || from > length()-1)
        return std::string::npos;

    return LastIndexOf(str(from), length()-from, s, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::LastIndexOf(const T* str, size_t len, T c, bool bCase)
{
    if(EmptyOrNull(str) || !len)
        return std::string::npos;

    // find the last single character
    const T* p = str + len - 1;

    if(!bCase) c = upper(c);

    while(p >= str)
    {
        if(bCase ? *p == c : upper(*p) == c)
            return ((size_t)(p - str));
        p--;
    }

    // return -1 if not found, distance from beginning otherwise
    return std::string::npos;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::LastIndexOf(const T* str, size_t len, const T* s, bool bCase)
{
    if(EmptyOrNull(str) || EmptyOrNull(s))
        return std::string::npos;

    // find the last single character
    const T* p = str + len - 1;

    while(p >= str)
    {
        if(StartsWith(p, s, bCase))
            return static_cast<size_t>(p - str);
        p--;
    }

    // return -1 if not found, distance from beginning otherwise
    return std::string::npos;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::indexOfAny(const C& list, size_t from, bool bCase, bool useTrie, size_t* idxList) const
{
    if(isEmpty() || from >= length())
        return std::string::npos;

    size_t pos,len;
    size_t idx = from;
    if(useTrie)
    {
        CharTrie t = BuildTrie(list, bCase);
        while(idx < length())
        {
            if(t.beginsWith((const CharTrie::byte*)(str(idx)), (length() - idx) * sizeof(T), pos, len))
            {
                if(idxList) *idxList = pos;
                t.clear();
                return idx;
            }

            idx++;
        }
        t.clear();
    }
    else
    {
        while(idx < length())
        {
            if(startsWithAny(list, idx, bCase, false, &pos))
            {
                if(idxList)
                    *idxList = pos;
                return idx;
            }
            idx++;
        }
    }

    return std::string::npos;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::indexOfAny(const T* cList, size_t from, bool bCase) const
{
    if(isEmpty()  || from >= length() || EmptyOrNull(cList))
        return std::string::npos;

    const T* s = StrFindChAny(str(from), cList, bCase);
    return (s == 0) ? std::string::npos : (size_t)(s - str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::indexOf(T c, size_t from, bool bCase) const
{
    if(isEmpty() || from >= length())
        return std::string::npos;

    return (from + IndexOf(str(from), c, bCase));
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::indexOf(const T* s, size_t from, bool bCase) const
{
    if(EmptyOrNull(s) || from >= length())
        return std::string::npos;

    if(s[1] == 0)
        return indexOf(s[0], from, bCase);

    if(bCase && !from)
        return m_str.find(s);

    // find first matching substring
    const T* first = StrFind(str(from), s, bCase);

    // return -1 if not found, distance from beginning otherwise
    return (first == 0) ? std::string::npos : (size_t)(first - str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::IndexOf(const T* str, T c, bool bCase)
{
    if(EmptyOrNull(str))
        return std::string::npos;

    // find first single character
    const T* s = StrFindCh(str, c, bCase);

    // return -1 if not found and index otherwise
    return (s == 0) ? -1 : (size_t)(s - str);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::indexOfNot(T c, size_t from, bool bCase) const
{
    if(isEmpty() || from >= length() )
        return std::string::npos;

    // find first single character
    const T* s = str(from);

    if(!bCase) c = upper(c);

    while(*s)
    {
        if(bCase ? *s != c : upper(*s) != c)
            return ((size_t)(s - str()));
        s++;
    }

    // return -1 if contain only c, distance from beginning otherwise
    return std::string::npos;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::indexOfNotAny(const T* cList, size_t from, bool bCase) const
{
    if(isEmpty() || from >= length())
        return std::string::npos;

    // find first single character
    const T* s = str(from);
    while(*s)
    {
        if(!IsOneOf(*s, cList, bCase))
            return ((size_t)(s - str()));
        s++;
    }
    // return -1 if nothing but charList found, distance from beginning otherwise
    return std::string::npos;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::lastIndexOfAny(const T* cList, size_t from, bool bCase) const
{
    if(isEmpty() || from >= length())
        return std::string::npos;

    // find last single character
    const T* s = str(length() - 1 - from);
    while(s >= str())
    {
        if(IsOneOf(*s, cList, bCase))
            return ((size_t)(s - str()));
        s--;
    }
    // return -1 if not found, distance from beginning otherwise
    return std::string::npos;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::lastIndexOfNot(T c, bool bCase) const
{
    if(isEmpty())
        return std::string::npos;

    // find last single character
    const T* s = str() + length() - 1;

    if(!bCase) c = upper(c);

    while(s >= str())
    {
        if(bCase ? *s != c : upper(*s) != c)
            return ((size_t)(s - str()));
        s--;
    }

    // return -1 if contain only c, distance from beginning otherwise
    return std::string::npos;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::containAny(std::initializer_list<T> cList)
{
    for(T c : cList)
    {
        if(contain(c))
            return true;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
bool CTextT<T>::containAny(const C& container, bool bCase, bool useTrie) const
{
    return (indexOfAny(container, 0, bCase, useTrie) != std::string::npos);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::containAny(const T* cList, bool bCase) const
{
    return (indexOfAny(cList, 0, bCase) != std::string::npos);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::StrFindChAny(const T* s, const T* cList, bool bCase)
{
    T c = *s;
    while(c)
    {
        if(IsOneOf(c, cList, bCase))
            return s;

        c = *++s;
    }
    return nullptr;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::containOnly(const T* cList, bool bCase) const
{
    return StrFindChNot(str(), cList, bCase) == nullptr;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::StrFindChNot(const T* s, const T* cList, bool bCase)
{
    if(EmptyOrNull(cList))
        return s;

    T c = *s;
    while(c)
    {
        if(!IsOneOf(c, cList, bCase))
            return s;

        c = *++s;
    }
    return nullptr;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::findPositions(RangeVector& pos, size_t skip, bool appendSeparators, const T* sep) const
{
    if(isEmpty())
        return 0;
    if(skip == 0)
        skip = 1;
    pos.clear();
    size_t posNext = 0, start, count;
    size_t n = 0;
    while(nextExcluding(posNext, start, count, appendSeparators, sep))
    {
        if(n++ % skip == 0)
            pos.push_back(std::make_pair(start, start + count - 1));
    }
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::findWordPositions(const C& list, RangeVector& pos, bool bCase, const T* sep, std::vector<size_t>* indexes) const
{
    if(isEmpty())
        return 0;

    pos.clear();
    size_t posNext = 0, start, count;
    CharTrie t = BuildTrie(list, bCase);
    size_t idxList;

    while(nextExcluding(posNext, start, count, false, sep))
    {
        if(t.contain((const CharTrie::byte*)(str(start)), count * sizeof(T), idxList))
        {
            pos.push_back(std::make_pair(start, start + count - 1));

            if(indexes)
                indexes->push_back(idxList);
        }
    }

    t.clear();
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::findPositions(const C& list, RangeVector& pos, bool bCase, bool useTrie, std::vector<size_t>* indexes) const
{
    if(isEmpty())
        return 0;

    pos.clear();

    size_t idx = 0;
    size_t idxList;
    size_t len;

    if(useTrie)
    {
        CharTrie t = BuildTrie(list, bCase);
        while(idx < length()) 
        {
            if(t.beginsWith((const CharTrie::byte*)(str(idx)), (length() - idx) * sizeof(T), idxList, len))
            {
                pos.push_back(std::make_pair(idx, idx + len / sizeof(T) - 1));
                if(indexes)
                    indexes->push_back(idxList);
                idx += (len / sizeof(T)); // will not overlap
                continue;
            }
            idx++;
        }
        t.clear();
    }
    else
    {
        while(idx < length())
        {
            if(startsWithAny(list, idx, bCase, false, &idxList, &len))
            {
                pos.push_back(std::make_pair(idx, idx + len - 1));
                if(indexes)
                    indexes->push_back(idxList);
                idx += len; // will not overlap
                continue;
            }
            idx++;
        }
    }
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::remove(T c, size_t from)
{
    if(isEmpty())
        return 0;

    size_t old_len = length();

    if(from > length() - 1)
        return 0;

    m_str.erase(std::remove(m_str.begin() + from, m_str.end(), c), m_str.end());

    return old_len - length();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::remove(const T* what, bool bCase)
{
    if(isEmpty())
        return 0;
    size_t len = length();
    size_t lenWhat = Strlen(what);
    if(lenWhat == std::string::npos || len < lenWhat)
        return 0;

    size_t nRemoved = 0;
    const T* from = str();
    auto to = m_str.begin();

    while(*from)
    {
        if(StartsWith(from, what, bCase))
        {
            nRemoved++;
            from += lenWhat;
            continue;
        }

        if(nRemoved)
            *to = *from;
        to++;
        from++;
    }

    if(to != m_str.end())
        m_str.erase(to, m_str.end());

    return nRemoved;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::remove(std::initializer_list<T> list)
{
    size_t n = 0;
    for(T c : list)
        n += remove(c);

    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::removeAny(const T* cList, bool bCase)
{
    if(isEmpty() || EmptyOrNull(cList))
        return 0;

    auto from = m_str.begin();
    auto to = m_str.begin();

    size_t n = 0;
    while(from != m_str.end())
    {
        T ch = *from;
        if(!IsOneOf(ch, cList, bCase))
        {
            *to = ch;
            if(to != from)
                *to = ch;
            to++;
        }
        else
            n++;

        from++;
    }

    if(to != m_str.end())
        m_str.erase(to, m_str.end());

    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::removeAny(const C& list, bool bCase, bool useTrie)
{
    RangeVector pos;
    if(findPositions(list, pos, bCase, useTrie))
        removeAt(pos);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::removeAny(std::initializer_list<const T*> list, bool bCase)
{
    std::vector<const T*> c;
    for(const T* v : list)
        c.push_back(v);
    return removeAny(c, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::removeBlocks(const T* sepBegin, const T* sepEnd)
{
    size_t nFound, nTotFound = 0;
    RangeVector pos;
    if((nFound = findBlockPositions(sepBegin, sepEnd, pos)) > 0)
    {
        removeAt(pos);
        nTotFound += nFound;
    }

    return nTotFound;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::spanIncluding(const T* cList) const
{
    return left(Strspn(str(), cList));
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::spanExcluding(const T* cList) const
{
    return left(Strcspn(str(), cList));
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::trim(const T* cList)
{
    trimRight(cList);
    trimLeft(cList);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::trimLeft(const T c)
{
    size_t n = indexOfNot(c);
    if(n != std::string::npos)
        cutLeft(n);

    return *this;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::trimLeft(const T* cList)
{
    size_t n = Strspn(str(), cList);
    if(n)
        cutLeft(n);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::trimRight(const T c)
{
    size_t n = lastIndexOfNot(c);
    if(n != std::string::npos)
        keepLeft(n + 1);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::trimRight(const T* cList)
{
    size_t n = Strrspn(str(), cList);
    if(n)
        cutRight(n);

    return *this;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::Strspn(const T* s1, const T* s2)
{
    if(EmptyOrNull(s1) || EmptyOrNull(s2))
        return 0;

    const T* p = s1;
    while(*p)
    {
        const T* s = s2;
        while(*s)
        {
            if(*s == *p)
                break;

            s++;
        }

        if(!*s)
            break;

        p++;
    }
    return p - s1;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::Strrspn(const T* s1, const T* s2)
{
    if(EmptyOrNull(s1) || EmptyOrNull(s2))
        return 0;

    size_t len = Strlen(s1);

    const T* p = s1 + len - 1;
    int n = 0;
    while(p >= s1)
    {
        const T* s = s2;
        while(*s)
        {
            if(*s == *p)
                break;

            s++;
        }

        if(!*s)
            break;
        n++;
        p--;
    }
    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::Strcspn(const T* s1, const T* s2)
{
    if(EmptyOrNull(s1) || EmptyOrNull(s2))
        return 0;

    const T* p = s1;
    while(*p)
    {
        const T* s = s2;
        while(*s)
        {
            if(*s == *p)
                break;

            s++;
        }

        if(*s)
            break;

        p++;
    }
    return p - s1;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::Strrev(T* begin, T* end)
{
    T tmp;
    while(end > begin)
        tmp = *end, *end-- = *begin, *begin++ = tmp;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T* CTextT<T>::Strrev(T *str)
{
    size_t n = Strlen((const T *)str);
    if(n < 2)
        return str;

    Strrev(str, str + n - 1);
    return str;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>&  CTextT<T>::limit(size_t maxLen)
{
    if(length() > maxLen)
        m_str.erase(m_str.begin() + maxLen, m_str.end());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>&  CTextT<T>::removeAt(const RangeVector& pos)
{
    if(isEmpty() || !pos.size() || pos[0].first >= length())
        return *this;

    size_t start = pos[0].first;

    auto psrc = m_str.begin() + start;
    auto pdst = m_str.begin() + start;
    size_t idxBlock = 0;
    size_t nBlockSize;
    size_t idx = start;

    while(idx < length())
    {
        if(idxBlock < pos.size() && idx >= pos[idxBlock].first && idx <= pos[idxBlock].second)
        {
            nBlockSize = pos[idxBlock].second - pos[idxBlock].first + 1;

            idxBlock++;
            psrc += nBlockSize;  //move source only
            idx += nBlockSize;
        }
        else
        {
            if(pdst != psrc)
                *pdst = *psrc;

            psrc++;
            pdst++;
            idx++;
        }
    }

    if(pdst != m_str.end())
        m_str.erase(pdst, m_str.end());

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::removeLast()
{
    size_t old_len = length();
    m_str.erase(length() - 1);
    return old_len > length();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::erase(size_t from, size_t count)
{
    // out-of-bounds requests return sensible things
    if(from < 0)
        from = 0;
    if(count < 0)
        count = 0;

    if(from + count > length())
        count = length() - from;

    // case of returning entire string
    if(from < 0 || from + count > length())
        return 0;
    if(from == 0 && from + count >= length())
        return 0;

    size_t old_len = length();
    m_str.erase(m_str.begin() + from, m_str.begin() + from + count);

    return old_len - length();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::keep(size_t from, size_t count)
{
    if(from > 0)
        cutLeft(from);
    limit(count);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::keepEnds(size_t count)
{
    return erase(count, length() - 2 * count);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::keepLeft(size_t count)
{
    return keep(0, count);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::keepRight(size_t count)
{
    if(isEmpty() || count > length())
        return 0;

    return erase(0, length() - count);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::between(T cLeft, T cRight, bool include)
{
    if(isEmpty())
        return false;

    size_t idxLeft = indexOf(cLeft);

    if(idxLeft == std::string::npos) //not found
        return false;

    if(!include) idxLeft++;

    size_t idxRight = lastIndexOf(cRight);

    if(idxRight == std::string::npos)
        return false;  //not found

    if(include) idxRight++;

    keep(idxLeft, idxRight - idxLeft);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::between(const T* sLeft, const T* sRight, bool include)
{
    if(isEmpty() || EmptyOrNull(sLeft) || EmptyOrNull(sRight))
        return false;

    size_t idxLeft = indexOf(sLeft);

    if(idxLeft == std::string::npos) //not found
        return false;

    if(!include) idxLeft += Strlen(sLeft);

    size_t idxRight = lastIndexOf(sRight);

    if(idxRight == std::string::npos)
        return false;  //not found

    if(include) idxRight += Strlen(sRight);

    keep(idxLeft, idxRight - idxLeft);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::left(size_t nCount) const
{
    if(nCount < 0)
        nCount = 0;
    if(nCount >= length())
        return *this;

    CTextT<T> dest;
    dest.equal(str(), nCount, 0);
    return dest;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::right(size_t nCount) const
{
    if(nCount < 0)
        nCount = 0;
    if(nCount >= length())
        return *this;

    CTextT<T> dest;
    dest.equal(str(), nCount, length() - nCount);
    return dest;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutLeft(size_t count)
{
    erase(0, count);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutRight(size_t count)
{
    if(count >= length())
    {
        clear();
        return *this;
    }

    limit(length() - count);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutEnds(size_t fromLeft, size_t fromRight)
{
    return keep(fromLeft, length() - fromLeft - fromRight);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutEnds(size_t count)
{
    return keep(count, length() - 2 * count);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutAfterFirst(T c, bool include, bool bCase)
{
    size_t idx = indexOf(c,0,bCase);

    if(idx == std::string::npos) //not found
        return *this;

    if(include)
        idx++;

    keepLeft(idx);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutAfterLast(T c, bool include, bool bCase)
{
    size_t idx = lastIndexOf(c, 0, bCase);

    if(idx == std::string::npos)
        return *this;

    if(include)
        idx++;

    keepLeft(idx);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutAfterLastOfAny(const T* cList, bool include, bool bCase)
{
    size_t idx = lastIndexOfAny(cList, 0, bCase);

    if(idx == std::string::npos)
        return *this;

    if(include)
        idx++;

    keepLeft(idx);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutAfterLast(const T* s, bool include, bool bCase)
{
    if(EmptyOrNull(s) || isEmpty())
        return *this;

    if(!s[1])
        return cutAfterLast(s[0], bCase);

    size_t idx = lastIndexOf(s,0,bCase);

    if(idx == std::string::npos)
        return *this;

    if(include)
        idx += Strlen(s);

    keepLeft(idx);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutAfterFirst(const T* s, bool include, bool bCase)
{
    if(EmptyOrNull(s) || isEmpty())
        return *this;

    if(!s[1])
        return cutAfterFirst(s[0], include, bCase);

    size_t idx = indexOf(s,0, bCase);

    if(idx == std::string::npos) //not found
        return *this;

    if(include)
        idx += Strlen(s);

    keepLeft(idx);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutAfterFirstOfAny(const T* chList, bool include, bool bCase)
{
    size_t idx = indexOfAny(chList, 0, bCase);

    if(idx == std::string::npos) //not found
        return *this;

    if(include)
        idx++;

    keepLeft(idx);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutBeforeFirst(T c, bool include, bool bCase)
{
    size_t idx = indexOf(c, 0, bCase);

    if(idx == std::string::npos) //not found
        return *this;

    if(include)
        idx++;

    if(length() > idx)
        cutLeft(idx);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutBeforeFirst(const T* s, bool include, bool bCase)
{
    if(EmptyOrNull(s) || isEmpty())
        return *this;

    if(!s[1])
        return cutBeforeFirst(s[0], include);  //TODO - add bCase

    size_t idx = indexOf(s, 0, bCase);

    if(idx == std::string::npos) //not found
        return *this;

    if(include)
        idx += Strlen(s);

    if(length() > idx)
        cutLeft(idx);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutBeforeFirstOfAny(const T* cList, bool include, bool bCase)
{
    size_t idx = indexOfAny(cList, 0, bCase);

    if(idx == std::string::npos) //not found
        return *this;

    if(include)
        idx++;

    if(length() > idx)
        cutLeft(idx);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::reverseAt(const RangeVector& pos)
{
    for(size_t k = 0; k < pos.size(); k++)
        std::reverse(m_str.begin() + pos[k].first, m_str.begin() + pos[k].second + 1);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
int CTextT<T>::compare(const T* s, bool bCase) const
{
    // do not use m_str.compare(s)
    return Strcmp(str(), s, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::reduceChain(T c)
{
    if(isEmpty() || !c || length() < 2)
        return 0;

    auto from = m_str.begin() + 1;
    auto to = m_str.begin();

    size_t old_len = length();
    T chFrom;

    while(from != m_str.end())
    {
        chFrom = *from++;

        if(chFrom != c || *to != c)
            *++to = chFrom;
    }

    if(to != m_str.end())
        m_str.erase(++to, m_str.end());

    return old_len - length();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::reduceChainAny(const T* cList)
{
    while(*cList)
    {
        reduceChain(*cList);

        cList++;
    }

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::reduceChain(const T* cList, T cNew)
{
    if(isEmpty())
        return *this;

    if(!cNew)
        return reduceChainAny(cList);

    auto from = m_str.begin();
    auto to = m_str.begin();
    T cFrom = *from++;

    if(IsOneOf(cFrom, cList))
        *to = cNew;

    while(from != m_str.end())
    {
        cFrom = *from++;
        if(!IsOneOf(cFrom, cList))
            *++to = cFrom;
        else if(*to != cNew)
            *++to = cNew;
    }

    if(to != m_str.end())
        m_str.erase(++to, m_str.end());

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::reduceToNumber()
{
    auto from = m_str.begin();
    auto to = m_str.begin();

    while(from != m_str.end())
    {
        if(IsDigit(*from))
        {
            if(to != from)
                *to = *from;
            to++;
        }

        from++;
    }

    if(to != m_str.end())
        m_str.erase(to, m_str.end());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::makeUnique(T c)
{
    size_t old_len = length();

    size_t idx = indexOf(c);

    if(idx != std::string::npos)
        remove(c, idx + 1);

    return old_len - length();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::countUnique(const T* cList, size_t from, size_t to)
{
    if(to == std::string::npos)
        to = length();

    size_t n = 0;
    while(*cList)
    {
        if(contain(*cList, from, to))
            n++;
        cList++;
    }

    return n;
}

//-----------------------------------------------------------------------------------------------------------
// TODO - optimize!
template <typename T>
CTextT<T>& CTextT<T>::makeUniqueAny(const T* chList)
{
    while(*chList)
    {
        makeUnique(*chList);

        chList++;
    }
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::mid(size_t count)
{
    return substring(count, length() - 2 * count);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::makeUnique()
{
    if(isEmpty())
        return 0;

    size_t old_len = length();

    auto from = m_str.begin();
    auto to = m_str.begin();
    size_t n = 0;
    T ch;
    while(from != m_str.end())
    {
        ch = *from++;
        if(!n || !contain(ch, 0, n - 1)) //always include first
        {
            *to++ = ch;
            n++;
        }
    }

    if(to != m_str.end())
        m_str.erase(to, m_str.end());
    return old_len - length();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::reverse()
{
    if(isEmpty())
        return *this;
    std::reverse(m_str.begin(), m_str.end());
    return *this;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::shuffle()
{
    if(isEmpty())
        return *this;

    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());

    std::shuffle(m_str.begin(), m_str.end(), std::default_random_engine(seed));
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::rotateLeft(size_t n)
{
    if(isEmpty() || !n)
        return *this;

    n = n % length();
    std::rotate(m_str.begin(), m_str.begin() + n, m_str.end());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::rotateRight(size_t n)
{
    if(isEmpty() || !n)
        return *this;

    n = n % length();
    std::rotate(m_str.begin(), m_str.begin() + m_str.size() - n, m_str.end());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::toUpper()
{
    if(isEmpty())
        return *this;

    std::transform(m_str.begin(), m_str.end(), m_str.begin(), toupper);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::toLower()
{
    if(isEmpty())
        return *this;

    std::transform(m_str.begin(), m_str.end(), m_str.begin(), tolower);
    return *this;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::reverseAny(const C& list, bool bCase)
{
    RangeVector v;
    while(findPositions(list, v, bCase))
        reverseAt(v);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isAlpha() const
{
    return IsAlpha(str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isBinary() const
{
    return IsBinary(str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isHexNumber() const
{
    return IsHexNumber(str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsBinary(const T* s)
{
    if(EmptyOrNull(s))
        return false;

    T c = *s;
    while(c)
    {
        if(c != T('0') && c != T('1'))
            return false;
        c = *++s;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsHexNumber(const T* s)
{
    if(EmptyOrNull(s))
        return false;

    T ch = *s;

    while(ch)
    {
        if(!IsHex(ch))
            return false;
        ch = *++s;
    }

    return true;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsAlpha(const T* s)
{
    if(EmptyOrNull(s))
        return false;

    T c = *s;
    while(c)
    {
        if(!IsAlpha(c))
            return false;
        c = *++s;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsUpper(const T* s, bool strict)
{
    if(EmptyOrNull(s))
        return false;

    T c = *s;
    while(c)
    {
        if(!IsUpper(c))
        {
            if(strict || IsAlpha(c))
                return false;
        }
        c = *++s;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsLower(const T* s, bool strict)
{
    if(EmptyOrNull(s))   return false;

    T c = *s;
    while(c)
    {
        if(!IsLower(c))
        {
            if(strict || IsAlpha(c))
                return false;
        }
        c = *++s;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isLower(bool strict) const
{
    return IsLower(str(), strict);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isUpper(bool strict) const
{
    return IsUpper(str(), strict);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isNumber(bool allowSign) const
{
    return IsNumber(str(), allowSign);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsPalindrome(const T* s, bool bCase, size_t len)
{
    if(EmptyOrNull(s))
        return false;

    if(len == std::string::npos)
        len = Strlen(s);

    size_t i = 0;
    size_t j = len - 1;
    while(i < j)
    {
        if(bCase)
        {
            if(s[i] != s[j])
                return false;
        }
        else
        {
            if(upper(s[i]) != upper(s[j]))
                return false;
        }
        i++;
        j--;
    }
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::hash() const
{
    return std::hash<tstring>{}(m_str);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::isPalindrome() const
{
    return IsPalindrome(str(), length());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::substring(size_t from, size_t nCount) const
{
    CTextT<T> dest;
    // out-of-bounds requests return sensible things
    if(from < 0)
        from = 0;
    if(nCount <= 0)
        return dest;

    if(from + nCount > length())
        nCount = length() - from;
    if(from > length())
        nCount = 0;

    // optimize case of returning entire string
    if(from <= 0 && from + nCount >= length())
        return *this;

    dest.equal(str(), nCount, from);
    return dest;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::substringRight(size_t from) const
{
    return substring(from, length() - from);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::substringLeft(size_t count) const
{
    return substring(0, count);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::substringBeforeFirst(T c, bool include) const
{
    size_t idx = indexOf(c);

    if(include)
        idx++;

    return substringLeft(idx);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::substringBeforeFirst(const T* s) const
{
    if(EmptyOrNull(s) || isEmpty())
        return CTextT();

    if(!s[1])
        return substringBeforeFirst(s[0]);

    size_t idx = indexOf(s);

    if(idx == std::string::npos) //not found
        return CTextT();

    return left(idx);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::substringBetween(T cLeft, T cRight, bool include)
{
    if(isEmpty())
        return CTextT();

    size_t idxLeft = indexOf(cLeft);

    if(idxLeft == std::string::npos) //not found
        return CTextT();

    if(!include) idxLeft++;

    size_t idxRight = lastIndexOf(cRight);

    if(idxRight == std::string::npos)
        return CTextT();  //not found

    if(include) idxRight++;

    return substring(idxLeft, idxRight - idxLeft);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::substringBetween(const T* sLeft, const T* sRight, bool include)
{
    if(isEmpty() || EmptyOrNull(sLeft) || EmptyOrNull(sRight))
        return CTextT();

    size_t idxLeft = indexOf(sLeft);

    if(idxLeft == std::string::npos) //not found
        return CTextT();

    if(!include) idxLeft += Strlen(sLeft);

    size_t idxRight = lastIndexOf(sRight);

    if(idxRight == std::string::npos)
        return CTextT(); //not found

    if(include) idxRight += Strlen(sRight);

    return substring(idxLeft, idxRight - idxLeft);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::sort()
{
    if(isEmpty())
        return *this;

    std::sort(m_str.begin(), m_str.end());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
int CTextT<T>::toInteger(bool& bOk) const
{
    int number;
    std::basic_istringstream<T> iss(m_str);
    iss >> number;
    bOk = !iss.fail();
    return number;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
double CTextT<T>::toDouble(bool& bOk) const
{
    double d;
    std::basic_istringstream<T> iss(m_str);
    iss >> d;
    bOk = !iss.fail();
    return d;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
unsigned int CTextT<T>::toUInteger(bool& bOk) const
{
    unsigned int number;
    std::basic_istringstream<T> iss(m_str);
    iss >> number;
    bOk = !iss.fail();
    return number;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
unsigned int CTextT<T>::toBinary(bool& bOk)
{
    if(length() > 32 || !isBinary())
    {
        bOk = false;
        return 0;
    }

    return std::bitset< 32 >(str()).to_ulong();
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
int CTextT<T>::ToHex(T c, bool& bOk)  //TODO optimize
{
    bOk = true;

    T chu = upper(c);

    for(int k = 0; k < 16; k++)
    {
        if(chu == HexDigits[k])  
            return k;
    }

    bOk = false;
    return 0;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
unsigned int CTextT<T>::toHexNumber(bool& bOk)
{
    unsigned int number;
    std::basic_istringstream<T> iss(m_str);
    iss >> std::hex >> number;
    bOk = !iss.fail();
    return number;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::toBytes(unsigned char* buf, size_t maxlen) const
{
    size_t len = sizeof(T) * length();
    if(!len)
        return 0;
    memcpy(buf, (unsigned char*)str(), std::min(len, maxlen));
    return len;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
size_t CTextT<T>::toHexBytes(Num* buf, size_t maxlen) const
{
    const T* ptr = str();
    T c = *ptr++;
    size_t len = 0;
    size_t nReaded = 0;
    int h1=0, h2=0;
    bool bOk;
    while(c)
    {
        // skip spaces
        if(!IsFormating(c))
        {
            h1 = ToHex(c, bOk);

            if(!bOk) // error, c is not a hex digit
                return std::string::npos;

            if(nReaded++ % 2)
                buf[len++] = static_cast<unsigned char>(h2 + h1);
            else
                h2 = h1 << 4;

            if(len >= maxlen)
                break;
        }

        c = *ptr++;
    }

    return len;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename Num, typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::fromChars(const C& container)
{
    clear();
    for(auto c : container)
        append(T(c));
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename Num, typename C, typename Val, typename X>
bool CTextT<T>::toChars(C& container, bool asHex) const
{
    const T* ptr = str();
    T c = *ptr++;
    size_t nReaded = 0;
    container.clear();

    if(!asHex)
    {
        while(c)
        {
            container.push_back((Val)c);
            c = *ptr++;
        }
    }
    else
    {
        int h1 = 0, h2 = 0;
        bool bOk = true;
        while(c)
        {
            // skip spaces
            if(!IsFormating(c))
            {
                h1 = ToHex(c, bOk);

                if(!bOk)
                    return std::string::npos;

                if(nReaded++ % 2)
                    container.push_back(static_cast<unsigned char>(h2 + h1));
                else
                    h2 = h1 << 4;
            }

            c = *ptr++;
        }
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename Num, typename C, typename Val, typename X>
bool CTextT<T>::toArray(C& container, T sep, bool asHex) const
{
    if(!sep)
        return toChars<Num, C>(container, asHex);

    bool bOk = true;
    container.clear();
    Num num;
    std::basic_istringstream<T> iss(m_str);
    T c;

    bool hasEOL = false;

    if(sep == *SPACE)
        iss >> std::noskipws;

    else if(sep == *EOL)
        hasEOL = true;  
    
    if(asHex)
        iss >> std::hex;

    iss >> num;
    bOk = !iss.fail();
    if(!bOk || iss.eof())
        return false;

    container.push_back(num);       
    
    if(!hasEOL)
    {
        while(bOk && iss >> c)
        {
            bOk = (c == sep);
            if(!bOk)
                return false;

            if(iss >> num)
                container.push_back(num);
            else
                bOk = false;
        }
    }
    else  //separator is EOL
    {
        while(!iss.eof() && iss >> num)
            container.push_back(num);
    }

    return bOk;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
bool CTextT<T>::ToArray(const T* str, Num* arr, size_t& n, T sep, bool asHex) 
{
    bool bOk = true;

    Num num;
    std::basic_istringstream<T> iss(str);
    T c;
    bool hasEOL = false;

    if(sep == *SPACE)
        iss >> std::noskipws;

    else if(sep == *EOL || sep == 0)
        hasEOL = true;

    if(asHex)
        iss >> std::hex;

    iss >> num;
    bOk = !iss.fail();
    if(!bOk || iss.eof())
        return false;

    size_t len = 0;

    arr ? arr[len++] = num : len++;

    if(!hasEOL)
    {
        while(bOk && iss >> c)
        {
            bOk = (c == sep);
            if(!bOk)
                return false;

            if(iss >> num)
                arr ? arr[len++] = num : len++;
            else
                bOk = false;

            if(arr && (len > n))
                return false;
        }
    }
    else  //separator is EOL
    {
        while(!iss.eof() && iss >> num)
        {
            arr ? arr[len++] = num : len++;

            if(arr && (len > n))
                return false;
        }
    }

    if(!arr) n = len;
    return bOk;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
bool CTextT<T>::toArray(Num* arr, size_t& n, T sep, bool asHex) const
{
    return ToArray(str(), arr, n, sep, asHex);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
bool CTextT<T>::toArray(size_t& pos, Num* arr, size_t n, const T* sep) const
{
    //TODO - optimize
    Num number;
    std::basic_stringstream<T> iss;

    CTextT word;
    size_t num = 0;
    bool bOk;
    while(nextWord(pos, word, sep) && num < n)
    {
        number = word.toInteger(bOk);
        if(!bOk)
            return false;
        arr[num++] = number;
    }

    return num == n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename Num, typename C, typename Val, typename X>
bool CTextT<T>::toMatrix(std::vector<C>& container, T sep, const T* sepLine) const
{
    size_t n = 0;
    std::vector<CTextT> lines;
    collectLines(lines, false, sepLine);

    for(const CTextT& s : lines)
    {
        std::vector<Num > v;
        if(!s.toArray<Num>(v, sep, false))
            return false;

        container.push_back(std::move(v));
        n += v.size();
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
bool CTextT<T>::toMatrix(Num* arr, size_t& w, size_t& h, T sep, const T* sepLine)
{
    std::vector<CTextT> lines;
    collectLines(lines, false, sepLine);

    if(arr && lines.size() != h)
        return false;
    else
        h = lines.size();

    size_t w_last = std::string::npos;
    for(const CTextT& s : lines)
    {
        if(!s.toArray<Num>(arr, w, sep))
            return false;

        if(!arr && w_last != std::string::npos && w != w_last)
            return false;

        w_last = w;

        if(arr)
            arr += w;
    }

    w = w_last;
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
bool CTextT<T>::toMatrix(size_t& pos, Num* arr, size_t w, size_t h, const T* sep, const T* sepLine)
{
    Num number;
    CTextT word;
    size_t start, count, posWord;
    size_t idx = 0, j,i=0;
    bool bOk;
    while(nextExcluding(pos, start, count, false, sepLine) && i < h)
    {
        j = 0;
        posWord = start;
        while(nextWord(posWord, word, sep))
        {
            number = word.toInteger(bOk);
            if(!bOk)
                return false;

            if(j++ >= w)
                return false;

            arr[idx++] = number;

            if(posWord >= start + count)
                break;
        }

        if(j != w)
            return false;

        i++;
    }

    if(i != h)
        return false;
  
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::resize(size_t newLen, T c)
{
    m_str.resize(newLen, c);
    return m_str.size() == newLen;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::randomNumber(size_t len)
{
    clear();
    resize(len);
    m_str[0] = T('1') + rand() % 9;  // must not begin with 0

    for(size_t k = 1; k < len; k++)
        m_str[k] = T('0') + rand() % 10;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::random(const T* cList, size_t len)
{
    clear();
    resize(len);
    size_t range = Strlen(cList);

    for(size_t k = 0; k < len; k++)
        m_str[k] = cList[rand() % range];

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::randomAlpha(size_t len)
{
    CTextT<T> s;
    s.appendRange(T('a'), T('z')).appendRange(T('A'), T('Z'));
    random(s.str(), len);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::randomAlphaNumeric(size_t len)
{
    CTextT<T> s;
    s.appendRange(T('a'), T('z')).appendRange(T('A'), T('Z')).appendRange(T('0'), T('9'));
    random(s.str(), len);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::ArePermutation(const CTextT& a, const CTextT& b)
{
    if(a.length() != b.length())
        return false;

    std::map<T, int> count_a, count_b;
    a.countChars(count_a);
    b.countChars(count_b);
    return count_a == count_b;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
void CTextT<T>::Permute(C& container, CTextT<T>& a, size_t l, size_t r)
{
    // Base case  
    if(l == r)
        container.push_back((const T*)a);
    else
    {
        // Permutations made  
        for(size_t i = l; i <= r; i++)
        {
            // Swapping done  
            std::swap(a[l], a[i]);

            // Recursion called  
            Permute(container, a, l + 1, r);

            //backtrack  
            std::swap(a[l], a[i]);
        }
    }
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::GeneratePermutations(C& container, CTextT<T>& a)
{
    container.clear();
    Permute(container, a, 0, a.length() - 1);
    return container.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::countChars(std::map<T, int>& container, bool bCase) const
{
    container.clear();
    for(T c : m_str)
    {
        if(!bCase)
            c = upper(c);

        container[c] ++;
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::Swab(const T* src, T* dst, size_t len)
{
    for(size_t k = 0; k < len / 2; k++)
    {
        *dst++ = *(src + 1);
        *dst++ = *src;
        src += 2;
    }
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::Swap(CTextT& a, CTextT& b)
{
    std::swap(a.m_str, b.m_str);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::SkipSpaces(const T* str, const T* sep)
{
    while(IsOneOf(*str, sep))
        str++;

    return str;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::wordsSort(const T* sep, const T* sepNew) // words sort in ascending order
{
    std::vector<CTextT> words;
    split(words, false, sep);  //TODO - add case
    std::sort(words.begin(), words.end(), [](const CTextT& a, const CTextT& b) { return a < b; });
    fromArray(words, sepNew);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::wordsReverse(const T* sep) // reverse words
{
    RangeVector pos;
    if(findWordPositions(pos, 1, sep))
        reverseAt(pos);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::findLinePositions(RangeVector& pos, size_t skip, bool appendSeparators, const T* sep) const
{
    return findPositions(pos, skip, appendSeparators, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::findWordPositions(RangeVector& pos, size_t skip, const T* sep) const
{
    return findPositions(pos, skip, false, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesRemoveEmpty(size_t minLen, const T* sep)
{
    if(isEmpty())
        return 0;
    size_t posNext = 0, start, count;
    RangeVector pos;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        size_t posEnd = start + count - 1;
        const T* pLine = str(start);
        const T* pLineEnd = str(posEnd);
        while(pLine < pLineEnd)
        {
            if(!IsFormating(*pLine))
                break;
            pLine++;
        }
     
        // check if line is empty
        if(pLine == pLineEnd || posEnd - start + 1 < minLen)
            pos.push_back(std::make_pair(start, posNext-1));
        else
        {
            size_t n = countUnique(sep, posEnd + 1, posNext);
            if(posNext - posEnd - 1 > n)
                pos.push_back(std::make_pair(posEnd + n + 1, posNext-1));
        }
    }

    removeAt(pos);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesCutAfterLast(const T* s, bool bAny, const T* sep)
{
    if(isEmpty())
        return 0;
    size_t posNext = 0, start, count;
    RangeVector pos;
    CTextT line;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        line = substring(start, count);
        size_t idx = bAny ? line.lastIndexOfAny(s) : line.lastIndexOf(s);
        if(idx != std::string::npos)
        {
            idx += bAny ? 1 : Strlen(s);
            pos.push_back(std::make_pair(start + idx, start + line.length()-1));
        }
    }

    removeAt(pos);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesCutBeforeLast(const T* s, bool bAny, const T* sep)
{
    if(isEmpty())
        return 0;
    size_t posNext = 0, start, count;
    RangeVector pos;
    CTextT line;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        line = substring(start, count);
        size_t idx = bAny ? line.lastIndexOfAny(s) : line.lastIndexOf(s);
        if(idx != std::string::npos)
            pos.push_back(std::make_pair(start, start + idx - 1));
    }

    removeAt(pos);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesCutBeforeFirst(const T* s, bool bAny, const T* sep)
{
    if(isEmpty())
        return 0;
    size_t posNext = 0, start, count;
    RangeVector pos;
    CTextT line;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        line = substring(start, count);
        size_t idx = bAny ? line.indexOfAny(s) : line.indexOf(s);
        if(idx != std::string::npos && idx > 0)
            pos.push_back(std::make_pair(start, start + idx - 1));
    }

    removeAt(pos);
    return pos.size();
}



//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesCutAfterFirst(const T* s, bool bAny, const T* sep)
{
    if(isEmpty())
        return 0;
    size_t posNext = 0, start, count;
    RangeVector pos;
    CTextT line;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        line = substring(start, count);
        size_t idx = bAny ? line.indexOfAny(s) : line.indexOf(s);
        if(idx != std::string::npos && idx > 0)
            pos.push_back(std::make_pair(start + idx, start + line.length() - 1));
    }

    removeAt(pos);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesCutNCharsFromBegin(size_t n_chars, const T* sep)
{
    if(isEmpty())
        return 0;

    if(n_chars <= 0)
        return 0;

    size_t posNext = 0, start, count;
    RangeVector pos;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        if(count <= n_chars) // remove the whole line
            pos.push_back(std::make_pair(start, posNext - 1));
        else
            pos.push_back(std::make_pair(start, start + n_chars - 1));
    }

    removeAt(pos);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesCutNCharsFromEnd(size_t n_chars, const T* sep)
{
    if(isEmpty())
        return 0;

    if(n_chars <= 0)
        return 0;

    size_t posNext = 0, start, count;
    RangeVector pos;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        if(count <= n_chars) // remove the whole line
            pos.push_back(std::make_pair(start, posNext - 1));
        else
            pos.push_back(std::make_pair(start + count - n_chars, start + count - 1));
    }

    removeAt(pos);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::insertAtEnd(const T* s, size_t skip, const T* sep)
{
    if(isEmpty())
        return 0;
    RangeVector pos;
    if(findPositions(pos, skip, false, sep))
        insertAt(pos, nullptr, s);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesInsertAtEnd(const T* s, size_t skip, const T* sep)
{
    return insertAtEnd(s, skip, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::wordsInsertAtEnd(const T* s, const T* sep)
{
    return insertAtEnd(s, 1, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::insertAtBegin(const T* s, size_t skip, const T* sep)
{
    if(isEmpty())
        return 0;
    RangeVector pos;
    if(findPositions(pos, skip, false, sep))
        insertAt(pos, s, nullptr);
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesInsertAtBegin(const T* s, size_t skip, const T* sep)
{
    return insertAtBegin(s, skip, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::wordsInsertAtBegin(const T* s, const T* sep)
{
    return insertAtBegin(s, 1, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::nextBlock(size_t& pos, size_t& start, size_t& count, const T* cListBegin, const T* cListEnd) const
{
    if(isEmpty() || pos == std::string::npos || pos >= length())
        return false;
    
    size_t idx = 0;
    int nBlocks = 0;

    const T* s1 = str(pos);

    if(!*s1)
        return false;

    while(*s1 && !IsOneOf(*s1, cListBegin, true, &idx))
        s1++;

    if(!*s1)
        return false;

    start = s1 - str();

    nBlocks = 1;

    const T* s2 = s1;

    s2++;

    while(*s2)
    {
        if(*s2 == cListEnd[idx])
        {
            nBlocks--;
            if(nBlocks == 0)
                break;
        }
        else if(*s2 == *s1)
        {
            nBlocks++;
        }
        s2++;
    }

    if(nBlocks)
        return false; // unclosed block ;

    count = s2 - s1 + 1;

    s2++;

    *s2 ? pos = static_cast<size_t> (s2 - str()) : pos = std::string::npos;

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::findBlockPositions(const T* sepBegin, const T* sepEnd, std::vector< std::pair<size_t, size_t>>& pos, bool bCase) const
{
    if(isEmpty())
        return 0;

    pos.clear();
    size_t posNext = 0, start, count;
    while(nextBlock(posNext, start, count, sepBegin, sepEnd))
        pos.push_back(std::make_pair(start, start + count - 1));
    
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::split(C& container, bool appendSeparators, const T* sep) const
{
    container.clear();
    size_t posNext = 0, start, count;
    while(nextExcluding(posNext, start, count, appendSeparators, sep))
        container.push_back(substring(start, count).str());
    return container.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::splitAt(size_t count, CTextT& first, CTextT& second, bool exclude) const
{
    if(count >= length())
    {
        first = *this;
        second.clear();
        return true;
    }
    first = left(count);
    size_t nRight = length() - count;
    if(exclude && nRight > 0)
        nRight--;
    second = right(nRight);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::splitAtFirst(T c, CTextT& first, CTextT& second, bool exclude) const
{
    size_t idx = indexOf(c);

    if(idx == std::string::npos) //not found
        return false;

    return splitAt(idx, first, second, exclude);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::splitAtLast(T c, CTextT& first, CTextT& second, bool exclude) const
{
    size_t idx = lastIndexOf(c);

    if(idx == std::string::npos) //not found
        return false;

    return splitAt(idx, first, second, exclude);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::splitAtFirstOfAny(const T* cList, CTextT& first, CTextT& second, bool exclude, bool bCase)
{
    size_t idx = indexOfAny(cList, 0, bCase);

    if(idx == std::string::npos) //not found
        return false;

    return splitAt(idx, first, second, exclude);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::splitAtLastOfAny(const T* cList, CTextT& first, CTextT& second, bool exclude, bool bCase)
{
    size_t idx = lastIndexOfAny(cList, 0, bCase);

    if(idx == std::string::npos) //not found
        return false;

    return splitAt(idx, first, second, exclude);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::splitAtFirst(const T* s, CTextT& first, CTextT& second, bool exclude, bool bCase)
{
    size_t idx = indexOf(s, 0, bCase);

    if(idx == std::string::npos) //not found
        return false;

    if(!exclude)
        return splitAt(idx, first, second);

    first = left(idx);

    size_t nRight = length() - idx - Strlen(s);

    second = right(nRight);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::splitAtLast(const T* s, CTextT& first, CTextT& second, bool exclude, bool bCase)
{
    int idx = lastIndexOf(str, 0, bCase);

    if(idx == std::string::npos) //not found
        return false;

    if(!exclude)
        return splitAt(idx, first, second);

    first = left(idx);

    int nRight = length() - idx - Strlen(s);
    if(nRight < 0)
        nRight = 0;

    second = right(nRight);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::fromMap(std::map<T, int>& container, const T* sep, const T* sepLine)
{
    clear();
    bool first = false;
    for(auto& v : container)
    {
        if(first && sep)
            append(sepLine);
        else
            first = true;

        append(v.first);
        append(sep);
        fromInteger(v.second, true);
    }
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Value, typename X  >
CTextT<T>& CTextT<T>::fromMap(const C& container, const T* sep, const T* sepLine)
{
    clear();
    bool first = false;
    for(auto& v : container)
    {
        if(first && sep)
            append(sepLine);
        else
            first = true;

        append(v.second);
        append(sep);
        fromInteger(v.first, true);        
    }
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::fromArray(const C& container, const T* sep)
{
    clear();
    std::basic_stringstream<T> ss;
    bool first = false;
    for(auto v : container)
    {
        if(!EmptyOrNull(sep))
        {
            if(first)
                ss << sep;
            else
                first = true;
        }

        // TODO - manage char type
        ss << v;
    }

    m_str = ss.str();
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename Num, typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::fromArray(const C& container, bool asHex, size_t wHex, const T* sep)
{
    clear();
    std::basic_stringstream<T> ss;
    bool first = false;

    //ss << std::fixed;

    for(auto v : container)
    {
        if(!EmptyOrNull(sep))
        {
            if(first)
                ss << sep;
            else
                first = true;
        }

        if(asHex)
            ss << std::hex << std::uppercase << std::setfill(T('0')) << std::setw(wHex);

        // TODO - manage char type
        ss << v ;
    }

    m_str = ss.str();
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
CTextT<T>& CTextT<T>::fromArray(const Num* buf, size_t len, bool asHex, size_t wHex, const T* sep)
{
    clear();
    std::basic_stringstream<T> ss; 
    bool first = false;
    for(size_t k = 0; k < len; k++)
    {
        if(!EmptyOrNull(sep))
        {
            if(first)
                ss << sep;
            else
                first = true;
        }

        if(asHex)
            ss << std::hex << std::uppercase << std::setfill(T('0')) << std::setw(wHex);

        ss << ((sizeof(Num) == 1) ? *buf++ : (int)*buf++);
    }

    m_str = ss.str();
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
CTextT<T>& CTextT<T>::fromBytes(const Num* buf, size_t len, int lineSize, bool asHex, size_t wHex, const T* sep)
{
    clear();
    std::basic_stringstream<T> ss; 

    bool first = false;
    for(size_t k = 0; k < len; k++)
    {
        if(!EmptyOrNull(sep))
        {
            if(first)
                ss << sep;
            else
                first = true;
        }

        if(asHex)
            ss << std::hex << std::uppercase << std::setfill(T('0')) << std::setw(wHex);

        ss << ((sizeof(Num) == 1) ? *buf++ : (int)*buf++);

        if(lineSize && ((k + 1) % lineSize == 0))
            ss << *EOL;
    }

    m_str = ss.str();
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
CTextT<T>& CTextT<T>::fromMatrix(const Num* buf, size_t w, size_t h, bool asHex, size_t wHex, const T* sep, const T* sepLine)
{
    std::basic_stringstream<T> ss;

    bool first_y = false;
    for(size_t i = 0; i < h; i++)
    {
        if(!EmptyOrNull(sepLine))
        {
            if(first_y)
                ss << sepLine;
            else
                first_y = true;
        }

        bool first_x = false;
        for(size_t k = 0; k < w; k++)
        {
            if(!EmptyOrNull(sep))
            {
                if(first_x)
                    ss << sep;
                else
                    first_x = true;
            }

            if(asHex)
                ss << std::hex << std::uppercase << std::setfill(T('0')) << std::setw(wHex);

            ss << ((sizeof(Num) == 1) ? *buf++ : (int)*buf++);
        }
    }

    m_str = ss.str();
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::nextExcluding(size_t& pos, size_t& start, size_t& count, bool appendSeparators, const T* cList) const
{
    if(isEmpty() || pos == std::string::npos || pos >= length())
        return false;

    const T* s1 = str(pos);

//    while(!IsOneOf(*s1, cList) && s1 > m_str)
//        s1--;

    while(IsOneOf(*s1, cList))
        s1++;

    const T* s2 = s1;

    while(*s2 && !IsOneOf(*s2, cList))
        s2++;

    start = s1 - str();

    if(appendSeparators)
    {
        while(*s2 && IsOneOf(*s2, cList))
            s2++;
    }
    
    count = s2 - s1;

    if(s2 == s1) // it is empty
        return false;

    // move iterator position for the next search
    while(IsOneOf(*s2, cList))
        s2++;

    *s2 ? pos = static_cast<size_t> (s2 - str()) : pos = length();

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::nextIncluding(size_t& pos, size_t& start, size_t& count, const T* cList) const
{
    if(isEmpty() || pos >= length())
        return false;

    const T* s1 = str(pos);

    while(*s1 && !IsOneOf(*s1, cList))
        s1++;

    if(!*s1)
        return false;

    const T* s2 = s1;

    while(*s2 && IsOneOf(*s2, cList))
        s2++;

    start = s1 - str();
    count = s2 - s1;
    pos = s2 - str() + 1;
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::nextLine(size_t& pos, CTextT<T>& line, bool appendSeparators, const T* sep) const
{
    size_t start, count;
    line.clear();
    if(!nextExcluding(pos, start, count, appendSeparators, sep))
        return false;
    line = substring(start, count);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename S, typename X >
bool CTextT<T>::nextWord(size_t& pos, S& word, const T* sep) const
{
    size_t start, count;
    word.clear();
    if(!nextExcluding(pos, start, count, false, sep))
        return false;
    word = substring(start, count);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
T CTextT<T>::nextChar(size_t pos, const T* sep) const
{
    if(pos >= length())
        return 0;
    const T* s = str(pos);
    while(*s && IsOneOf(*s, sep))
        s++;
    return *s;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::count(T c, size_t from) const
{
    if(from >= length())
        return 0;
    return std::count(m_str.begin() + from, m_str.end(), c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::countAny(const T* cList, size_t from) const
{
    size_t nChars = 0;
    while(*cList)
    {
        nChars += count(*cList, from);
        cList++;
    }

    return nChars;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t  CTextT<T>::count(const T* s, bool bCase) const
{
    if(EmptyOrNull(s))
        return 0;

    size_t len = Strlen(s);

    if(len == 1)
        return count(*s);  // return single-character version

    size_t pos = 0;
    size_t num = 0;

    while((pos = indexOf(s, pos, bCase)) != std::string::npos)
    {
        pos += len;
        num++;
    }
    return num;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::countChains(T c) const
{
    if(isEmpty() || !c || length() < 2)
        return 0;

    auto from = m_str.begin() + 1;
    size_t n = 0;
    bool first = true;

    while(from != m_str.end())
    {
        if(*from++ == c)
        {
            if(first)
            {
                first = false;
                n++;
            }
        }
        else
            first = true;
    }

    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::countChainsAny(const T* cList) const
{
    if(isEmpty() || EmptyOrNull(cList) || length() < 2)
        return 0;

    auto from = m_str.begin() + 1;
    size_t n = 0;
    bool first = true;

    while(from != m_str.end())
    {
        if(IsOneOf(*from++, cList))
        {
            if(first)
            {
                first = false;
                n++;
            }
        }
        else
            first = true;
    }

    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::wordsCount(const T* sep) const
{
    return countSubstrings(sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::countSubstrings(const T* sep) const
{
    size_t posNext = 0, start, count;
    size_t n = 0;
    while(nextExcluding(posNext, start, count, false, sep))
        n++;
    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename S, typename X >
size_t CTextT<T>::countWordFrequencies(std::multimap < int, S, std::greater<int>>& container, bool bCase, const T* sep) const
{
    container.clear();
    size_t posNext = 0, start, count;
    std::map<CTextT<T>, int> freq;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        CTextT<T> word = substring(start, count);
        if(!bCase)
            word.toLower();
        freq[word]++;
    }

    for(auto & v : freq)
        container.insert(std::make_pair(v.second, v.first.str()));

    return container.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename S, typename X >
size_t CTextT<T>::countWordFrequencies (std::vector<std::pair<int, S>> & container, bool bCase, const T* sep) const
{
    container.clear();
    size_t posNext = 0, start, count;
    std::map<CTextT<T>, int> freq;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        CTextT<T> word = substring(start, count);
        if(!bCase)
            word.toLower();
        freq[word]++;
    }

    for(auto & v : freq)
        container.push_back(std::make_pair(v.second, v.first.str()));

    std::sort(container.begin(), container.end(), [](auto& i, auto& j) { return i.first > j.first; });

    return container.size();
}



//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::wordsCapitalize(const T* sep)
{
    if(isEmpty())
        return *this;
    size_t posNext = 0, start, count;
    while(nextExcluding(posNext, start, count, false, sep))
        m_str[start] = upper(m_str[start]);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collect(C& container, const T* cList) const
{
    container.clear();
    size_t posNext = 0, start, count;
    while(nextIncluding(posNext, start, count, cList))
        container.push_back(substring(start, count).str());
    return container.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collectSubstrings(C& container, const C* begin, const C* end, const C* has, const T* sep) const
{
    container.clear();
    size_t posNext = 0, start, count;
    CTextT<T> word;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        word = substring(start, count);
        // apply filter
        if((begin && word.startsWithAny(*begin)) ||
            (end && word.endsWithAny(*end)) ||
            (has && word.containAny(*has)))
            container.push_back(word.str());
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collectLines(C& container, bool appendSeparators, const T* sep) const
{
    return split(container, appendSeparators, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collectWords(C& container, const T* sep) const
{
    return split(container, false, sep);
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collectBlocks(C& container, const T* sepBegin, const T* sepEnd, bool all, const T* sep) const
{
    container.clear();
    size_t posNext = 0, start, count, pos2 = 0;
    while(nextBlock(posNext, start, count, sepBegin, sepEnd))
    {
        if(all)
        {
            size_t start2, count2;
            while(nextExcluding(pos2, start2, count2, false, sep) && start2+count2 < start)
            {
                if(start2 + count2 < start)
                    container.push_back(substring(start2, count2).str());
            }
            pos2 = posNext;
        }
        container.push_back(substring(start, count).str());
    }

    if(posNext < length() - 1)
    {
        pos2 = posNext;
        size_t start2, count2;
        while(nextExcluding(pos2, start2, count2, false, sep))
            container.push_back(substring(start2, count2).str());
    }

    return container.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collectSentences(C& container, const T* sep, const T* sepWords) const
{
    container.clear();
    size_t pos = 0, start, count;
    CTextT<T> sentence;
    CTextT<T> old;
    while(nextExcluding(pos, start, count, true, sep))
    {
        sentence = substring(start, count+1);
        // check if the next character is Upper
        T c = nextChar(pos, sepWords);
        if(IsUpper(c) || !c)
        {
            if(old.length())
            {
                old += sentence;
                old.trim(sepWords);
                container.push_back(old.str());
                old.clear();
            }
            else
            {
                sentence.trim(sepWords);
                container.push_back(sentence.str());
            }
        }
        else // collect 
        {
            old = sentence;
        }
    }

    if(old.length())
    {
        old.trim(sepWords);
        container.push_back(old.str());
    }
    return container.size();
}
//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::findPositions(RangeVector& pos, const C* begin, const C* end, const C* has, const T* sep) const
{
    if(isEmpty())
        return 0;

    pos.clear();
    size_t posNext = 0, start, count;
    CTextT<T> word;
    while(nextExcluding(posNext, start, count, false, sep))
    {
        word = substring(start, count);
        // apply filter
        if((begin && word.startsWithAny(*begin)) ||
            (end && word.endsWithAny(*end)) ||
            (has && word.containAny(*has)) ||
            (!begin && !end && !has))
            pos.push_back(std::make_pair(start, start+count-1));
    }
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::Substring(const T* str, size_t from, size_t nCount)
{
    CTextT<T> dest;
    // out-of-bounds requests return sensible things
    if(from < 0)
        from = 0;

    size_t len = Strlen(str);

    if(nCount == 0)
        nCount = len - from;

    if(nCount <= 0)
        return dest;

    if(from + nCount > len)
        nCount = len - from;

    if(from > len)
        nCount = 0;

    // optimize case of returning entire string
    if(from <= 0 && from + nCount >= len)
        return dest;

    dest.equal(str, nCount, from);
    return dest;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
bool CTextT<T>::fromBinary(Num i)
{
    if (sizeof(i) == 1)
        m_str = std::bitset< 8 >(i).to_string<T>();
    else if(sizeof(i) == 2)
        m_str = std::bitset< 16 >(i).to_string<T>();
    else if(sizeof(i) <= 4)
        m_str = std::bitset< 32 >(i).to_string<T>();
    else if(sizeof(i) <= 8)
        m_str = std::bitset< 64 >(i).to_string<T>();
    else
        m_str = std::bitset< 256 >(i).to_string<T>();
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
bool CTextT<T>::fromInteger(Num i, bool append, int padd, T paddValue)
{
    std::basic_stringstream<T> ss;
    ss << ((sizeof(Num) == 1) ? (int)i:i);

    if(!padd)
        append ? m_str.append(ss.str()) : m_str = ss.str();
    else
    {
        CTextT str = ss.str();
        if(padd > 0)
            str.paddLeft(paddValue, padd);
        else if(padd < 0)
            str.paddRight(paddValue, -padd);
        append ? m_str.append(str.str()) : m_str = str.str();
    }
    return !ss.fail();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::fromDouble(double d, int precision, bool fixed, bool nozeros, bool append)
{
    std::basic_stringstream<T> ss;
    if(fixed) ss << std::fixed;
    else      ss << std::scientific;
    ss << std::setprecision(precision) << d;
    append ? m_str.append(ss.str()) : m_str = ss.str();
    if(nozeros)
        trimRight(T('0'));
    return !ss.fail();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num, typename X>
bool CTextT<T>::fromHexNumber(Num i, bool hasBase, bool upper, bool append)
{
    std::basic_stringstream<T> ss;
    if(hasBase) ss << T('0') << T('x');
    if(upper) ss << std::uppercase;
    ss << std::setfill(T('0')) << std::setw(sizeof(Num) * 2) << std::hex << ((sizeof(Num) == 1) ? i : (int)i);
    if(append)
        m_str += ss.str();
    else
        m_str = ss.str();
    return !ss.fail();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::fromSingle(const char* s)
{
    *this = FromSingle(s);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::fromWide(const wchar_t* s)
{
    *this = FromWide(s);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::fromTChars(const char* s)
{
    return fromSingle(s);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::fromTChars(const wchar_t* s)
{
    return fromWide(s);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<char> CTextT<T>::toSingle()
{
    CTextT<char> res;
    if(isEmpty())
        return res;
    
    return ToSingle(str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<wchar_t> CTextT<T>::toWide()
{
    std::basic_string<wchar_t> res;
    if(isEmpty())
        return res;
    
    return ToWide(str());
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::format(const T* format, ...)
{
    m_str.clear();
    size_t length;
    va_list ap;
    va_start(ap, format);

    va_list apStrLen;
    va_copy(apStrLen, ap);
    length = Vsnprintf(nullptr, 0, format, apStrLen);
    va_end(apStrLen);

    if(length <= 0)
    {
        va_end(ap);
        return false;
    }

    m_str.resize(length);
    size_t n = Vsnprintf((T *)m_str.data(), m_str.size() + 1, format, ap);
    if(n > capacity())
        return false;

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsNumber(const T* s, bool allowSign)
{
    if(allowSign && (*s == '-' || *s == '+')) s++;
    if(EmptyOrNull(s))   return false;

    T ch = *s;

    while(ch)
    {
        if(!IsDigit(ch))
            return false;
        ch = *++s;
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::IsDouble(const T* str, bool allowTrim, const T* sep)
{
    if(allowTrim)
        str = SkipSpaces(str, sep);

    int n = 0;
    bool dot = false, power = false, sign = false;
    T ch = *str;

    if(ch == '-' || ch == '+')  // first char allowed to be sign
        str++;

    while((ch = *str++))
    {
        if(!(ch >= '0' && ch <= '9'))
        {
            if(ch == '.' || ch == ',')
            {
                if(dot)
                    return false;

                dot = true;
                continue;
            }

            if(ch == 'E' || ch == 'e')
            {
                if(power)
                    return false;

                power = true;
                continue;
            }

            if(ch == '-' || ch == '+')  // sign allowed once after e
            {
                if(!power || sign)
                    return false;

                sign = true;

                continue;
            }

            // if this flag is set we allow trailing spaces
            if(allowTrim)
            {
                str = SkipSpaces(str, sep);

                if(!*str)
                    return n ? true : false;
            }


            return false;
        }
        n++;
    }
    return true;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::replace(T cOld, T cNew)
{
    int nCount = 0;

    if(!cOld)
        return 0;

    if(!cNew)
        return erase(cOld);

    // short-circuit the nop case
    if(cOld != cNew)
    {
        // otherwise modify each character that matches in the string
        auto from = m_str.begin();

        while(from != m_str.end())
        {
            // replace instances of the specified character only
            if(*from == cOld)
            {
                *from = cNew;
                nCount++;
            }

            from++;
        }
    }
    return nCount;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::replace(const T* what, const T* with, bool bCase)
{
    if(isEmpty() || EmptyOrNull(what))
        return 0;

    if(EmptyOrNull(with))
        return remove(what, bCase);

    size_t lenWhat = Strlen(what);
    size_t lenWith = Strlen(with);

    if(lenWith > lenWhat)
    {
        // collect the posiitions of all instances of what in our string
        // calculate a new size
        std::vector<size_t> pos;
        const T* from = str();
        while(*from)
        {
            if(StartsWith(from, what, bCase))
            {
                from += lenWhat;
                pos.push_back(from - str());
                continue;
            }

            from++;
        }

        if(!pos.size())
            return 0;

        size_t lenOld = length();
        size_t lenNew = lenOld + (lenWith - lenWhat)*pos.size();

        m_str.resize(lenNew);
        // start from the back of the string
        // optionally, this can be replaced with memmove
        size_t posSrcEnd = lenOld;
        auto dst = m_str.begin() + lenNew;
        for(size_t k = pos.size(); k > 0; k--)
        {
            size_t len = posSrcEnd - pos[k - 1];
            const T* src = str(posSrcEnd);
            posSrcEnd -= len + lenWhat;

            while(len--)
                *--dst = *--src;

            len = lenWith;
            src = with + len;
            while(len--)
                *--dst = *--src;
        }

        return pos.size();
    }
    else
    {
        size_t nRemoved = 0;

        const T* from = str();
        auto to = m_str.begin();

        while(*from)
        {
            if(StartsWith(from, what, bCase))
            {
                nRemoved++;
                from += lenWhat;
                const T* src = with;
                while(*src)
                    *to++ = *src++;
                continue;
            }

            if(nRemoved)
                *to = *from;
            to++;
            from++;
        }

        if(to != m_str.end())
            m_str.erase(to, m_str.end());

        return nRemoved;
    }
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>&  CTextT<T>::replace(size_t from, size_t count, const T* s)
{
    if(isEmpty() || EmptyOrNull(s) || from >= length())
        return *this;

    auto it = m_str.begin() + from;
    while(it != m_str.end() && count && *s)
    {
        *it++ = *s++;
        count--;
    }
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>&  CTextT<T>::replace(size_t from, size_t count, T c)
{
    if(isEmpty() || from >= length())
        return *this;

    auto it = m_str.begin() + from;
    while(it != m_str.end() && count)
    {
        *it++ = c;
        count--;
    }
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::replaceAny(const T* cList, T c, bool bCase)
{
    if(isEmpty() || EmptyOrNull(cList))
        return 0;

    auto from = m_str.begin();
    size_t nCount = 0;
    while(from != m_str.end())
    {
        // replace instances of the specified character only
        if(IsOneOf(*from, cList, bCase))
        {
            *from = c;
            nCount++;
        }

        from++;
    }

    return nCount;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::replaceAny(const T* cList1, const T* cList2, bool bCase)
{
    if(isEmpty() || EmptyOrNull(cList1) || EmptyOrNull(cList2))
        return 0;

    auto from = m_str.begin();
    size_t nCount = 0;
    size_t idx;
    while(from != m_str.end())
    {
        // replace instances of the specified character only
        if(IsOneOf(*from, cList1, bCase, &idx))
        {
            *from = cList2[idx];
            nCount++;
        }

        from++;
    }

    return nCount;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::replaceControlCharacters()
{
    if(isEmpty())
        return *this;

    auto src = m_str.begin();
    auto dst = m_str.begin();
    T prev = 0;
    while(src != m_str.end())
    {
        if(*src == T('\\'))
        {
            if(prev != T('\\') )
            {
                T c = *++src ;

                if(c == T('n'))
                {
                    *dst++ = T('\n');
                    ++src;
                    continue;
                }

                if(c == T('r'))
                {
                    *dst++ = T('\r');
                    ++src;
                    continue;
                }

                if(c == T('t'))
                {
                    *dst++ = T('\t');
                    ++src;
                    continue;
                }

                if(c == T('b'))
                {
                    *dst++ = T('\b');
                    ++src;
                    continue;
                }
            }
            else
            {
                prev = 0;
                continue;
            }

            //TODO - manage cases with four slashes
        }

        if(dst != src)
            *dst = *src;

        prev = *src;
        src++;
        dst++;
    }

    if(dst != m_str.end())
        m_str.erase(dst, m_str.end());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::replaceAny(const C& what, const T c, bool bCase, bool useTrie)
{
    RangeVector v;
    while(findPositions(what, v, bCase, useTrie))
        replaceAt(v, c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::replaceAny(const C& container, const T* with, bool bCase, bool useTrie)
{
    RangeVector v;
    if(findPositions(container, v, bCase, useTrie))
        replaceAt(v, with);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::wordsReplace(const C& list, const T* with, bool bCase, const T* sep)
{
    RangeVector pos;
    if(findWordPositions(list, pos, bCase, sep))
        replaceAt(pos, with);
    return *this;
}

template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::wordsReplace(const C& what, const C& with, bool bCase, const T* sep)
{
    if(what.size() != with.size())
        return *this;
    RangeVector pos;
    std::vector<size_t> indexes;
    if(findWordPositions(what, pos, bCase, sep, &indexes))
        replaceAt(pos, indexes, with);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::wordsReplaceWithChar(const C& list, const T c, bool bCase, const T* sep)
{
    RangeVector pos;
    if(findWordPositions(list, pos, bCase, sep))
        replaceAt(pos, c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::replaceFirst(T c)
{
    if(length() > 0)
        m_str[0] = c;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::replaceLast(T c)
{
    if(length() > 0)
        m_str[length() - 1] = c;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::replaceAny(std::initializer_list<const T*> what, std::initializer_list<const T*> with, bool bCase)
{
    std::vector<const T*> cWhat;
    for(const T* v : what)
        cWhat.push_back(v);

    std::vector<const T*> cWith;
    for(const T* v : with)
        cWith.push_back(v);

    return replaceAny(cWhat, cWith, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::replaceAny(const C& what, const C& with, bool bCase, bool useTrie)
{
    if(what.size() != with.size())
        return *this;
    RangeVector v;
    std::vector<size_t> indexes;
    if(findPositions(what, v, bCase, useTrie, &indexes))
        replaceAt(v, indexes, with);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::replaceAt(const RangeVector& pos, const T* with) const
{
    if(isEmpty() || !pos.size() || pos[0].first >= length())
        return CTextT<T>();

    // calculate the new length
    size_t lenReplace = Strlen(with);
    size_t newLen = length();
    for(size_t k = 0; k < pos.size(); k++)
    {
        if(pos[k].first >= 0 && pos[k].second < length())
        {
            size_t nBlockSize = pos[k].second - pos[k].first + 1;
            newLen += (lenReplace - nBlockSize);
        }
    }

    CTextT<T> sNew;
    if(!sNew.resize(newLen))
        return CTextT<T>();

    const T* psrc = str();
    auto pdst = sNew.m_str.begin();
    size_t idx = 0;
    *pdst = 0;
    size_t idxBlock = 0;
    while(idx < length())
    {
        if(idxBlock < pos.size() && idx >= pos[idxBlock].first && idx <= pos[idxBlock].second)
        {
            size_t nBlockSize = pos[idxBlock].second - pos[idxBlock].first + 1;

            psrc += nBlockSize;  //move source only
            idx += nBlockSize;

            const T* pWith = with;
            while(*pWith)
                *pdst++ = *pWith++;

            idxBlock++;
        }
        else
        {
            *pdst++ = *psrc++;
            idx++;
        }
    }
    return sNew;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::replaceAt(const RangeVector& pos, const T* with)
{
    if(isEmpty() || !pos.size() || pos[0].first >= length())
        return *this;

    *this = static_cast<const CTextT<T>*>(this)->replaceAt(pos, with);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::replaceAt(const RangeVector& pos, const T c)
{
    if(isEmpty() || !pos.size() || pos[0].first >= length())
        return *this;

    for(size_t k = 0; k < pos.size(); k++)
    {
        size_t nBlockSize = pos[k].second - pos[k].first + 1;
        replace(pos[k].first, nBlockSize, c);
    }
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::replaceAt(const RangeVector& pos, const std::vector<size_t>& indexes, const C& with)
{
    if(isEmpty() || !pos.size() || pos[0].first >= length())
        return *this;

    *this = static_cast<const CTextT<T>*>(this)->replaceAt(pos, indexes, with);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T> CTextT<T>::replaceAt(const RangeVector& pos, const std::vector<size_t>& indexes, const C& with) const
{
    CTextT<T> sNew;
    if(isEmpty() || !pos.size() || pos[0].first >= length() || pos.size() != indexes.size())
        return sNew;

    // calculate the new length
    size_t newLen = length();
    for(size_t k = 0; k < pos.size(); k++)
    {
        if(pos[k].first >= 0 && pos[k].second < length())
        {
            size_t lenReplace = Strlen(with[k]);
            size_t nBlockSize = pos[k].second - pos[k].first + 1;
            newLen += (lenReplace - nBlockSize);
        }
    }

    if(!sNew.resize(newLen))
        return CTextT<T>();

    const T* psrc = str();
    auto pdst = sNew.m_str.begin();
    size_t idx = 0;
    *pdst = 0;
    size_t idxBlock = 0;
    while(idx < length())
    {
        if(idxBlock < pos.size() && idx >= pos[idxBlock].first && idx <= pos[idxBlock].second)
        {
            size_t nBlockSize = pos[idxBlock].second - pos[idxBlock].first + 1;

            psrc += nBlockSize;  //move source only
            idx += nBlockSize;

            const T* pWith = ToStr(with[idxBlock]);
            while(*pWith)
                *pdst++ = *pWith++;

            idxBlock++;
        }
        else
        {
            *pdst++ = *psrc++;
            idx++;
        }
    }

    return sNew;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::insert(size_t from, T c, size_t count)
{
    if(from >= length())
        append(c, count);
    else
        m_str.insert(from, count, c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::insert(size_t from, const T* s)
{
    if(from >= length())
        append(s);
    else
        m_str.insert(from, s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::insert(size_t from, size_t count, const T* s)
{
    if(from >= length())
        append(s, count);
    else
        m_str.insert(from, s, count);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::insertAt(const RangeVector& pos, const T* begin, const T* end)
{
    if(isEmpty() || !pos.size() || pos[0].first >= length())
        return *this;

    *this = static_cast<const CTextT<T>*>(this)->insertAt(pos, begin, end);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::insertAt(const RangeVector& pos, const T* begin, const T* end) const
{
    if(isEmpty() || !pos.size() || pos[0].first >= length())
        return CTextT<T>();

    // calculate the new length
    size_t lenBegin = Strlen(begin);
    size_t lenEnd = Strlen(end);
    size_t newLen = length() + pos.size() * (lenBegin + lenEnd);

    CTextT<T> sNew;
    if(!sNew.resize(newLen))
        return CTextT<T>();

    const T* psrc = str();
    auto pdst = sNew.m_str.begin();
    size_t idx = 0;
    *pdst = 0;
    size_t idxBlock = 0;
    while(idx < length())
    {
        if(idxBlock < pos.size() && idx >= pos[idxBlock].first && idx <= pos[idxBlock].second)
        {
            size_t nBlockSize = pos[idxBlock].second - pos[idxBlock].first + 1;

            if(begin)
            {
                const T* pBegin = begin;
                while(*pBegin)
                    *pdst++ = *pBegin++;
            }

            idx += nBlockSize;

            while(nBlockSize--)
                *pdst++ = *psrc++;

            if(end)
            {
                const T* pEnd = end;
                while(*pEnd)
                    *pdst++ = *pEnd++;
            }

            idxBlock++;
        }
        else
        {
            *pdst++ = *psrc++;
            idx++;
        }
    }
    return sNew;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::push_back(T c)
{
    append(c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::push_front(T c)
{
    insert(0, c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::push_back(const T* s)
{
    append(s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::push_front(const T* s)
{
    insert(0, s);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::paddRight(T c, size_t len)
{
    if(length() < len)
        append(c, len - length());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::paddLeft(T c, size_t len)
{
    if(length() < len)
        insert(0, c, len - length());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::enclose(T c)
{
    insert(0, c);
    append(c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::enclose(T begin, T end, bool checkEnds)
{
    if(!checkEnds || !startsWith(begin))
        insert(0, begin);
    if(!checkEnds || !endsWith(end))
        append(end);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::enclose(const T* begin, const T* end, bool checkEnds)  //TODO - optimize
{
    if(!checkEnds || !startsWith(begin))
        insert(0, begin);
    if(!checkEnds || !endsWith(end))
        append(end);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::unenclose(T begin, T end)
{
    size_t left = 0;
    size_t right = 0;

    while(startsWith(begin, left))
        left++;

    while(endsWith(end, right))
        right++;

    if(left > 0 || right > 0)
        cutEnds(left, right);

    return left + right;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::quote()
{
    return enclose(Literal, Literal);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::unquote()
{
    return unenclose(Literal, Literal);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::wordsEnclose(const T* sBegin, const T* sEnd, const C* start, const C* end, const C* has, const T* sep)
{
    RangeVector pos;
    if(findPositions(pos, start, end, has, sep))
        insertAt(pos, sBegin, sEnd);
    return *this;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::wordsRemove(const C* begin, const C* end, const C* has, const T* sep)
{
    RangeVector pos;
    if(findPositions(pos, begin, end, has, sep))
        removeAt(pos);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::wordsEnclose(const T* sBegin, const T* sEnd, const T* sep)
{
    RangeVector pos;
    if(findWordPositions(pos, 1, sep))
        insertAt(pos, sBegin, sEnd);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::checkBalance(const T* sepBegin, const T* sepEnd)
{
    std::stack<T> b;
    size_t idx;

    for(T c : m_str)
    {
        if(IsOneOf(c, sepBegin, true, &idx))
        {
            // this is the case when separator for begin and end is the same
            if(sepBegin[idx] == sepEnd[idx] && !b.empty() && b.top() == c)
                b.pop();
            else
                b.push(c);
        }

        else if(IsOneOf(c, sepEnd, true, &idx))
        {
            if(b.empty() || b.top() != sepBegin[idx])
                return false;
            b.pop();
        }
    }

    if(!b.empty())
        return false;

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename CharT, typename>
bool CTextT<T>::writeFile(const CharT* filePath, int encoding, bool asHex)
{
    return asHex ? WriteFileAsHex(filePath, *this) : WriteFile <CharT, void> (filePath, str(), (EncodingType)encoding);
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename CharT, typename>
bool CTextT<T>::readFile(const CharT* path, bool asHex)
{
    clear();

    return asHex ? ReadFileAsHex<CharT> (path, *this) : ReadFile<CharT, void>(path, *this);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::Levenshtein(const T *s1, const T *s2)
{
    size_t len1 = Strlen(s1);
    size_t len2 = Strlen(s2);
    size_t x, y, lastdiag, olddiag;
    size_t* column = new size_t[len1 + 1];
    for(y = 1; y <= len1; y++)
        column[y] = y;
    for(x = 1; x <= len2; x++)
    {
        column[0] = x;
        for(y = 1, lastdiag = x - 1; y <= len1; y++)
        {
            olddiag = column[y];
            column[y] = std::min(std::min(column[y] + 1, column[y - 1] + 1), lastdiag + (s1[y - 1] == s2[x - 1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    size_t ret = column[len1];
    delete[] column;
    return ret;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::HammingDistance(const T *s1, const T *s2)
{
    size_t len1 = Strlen(s1);
    size_t len2 = Strlen(s2);

    if(len1 != len2)
        return std::string::npos;

    size_t dist = 0;
    while(*s1 != 0)
        if(*s1++ != *s2++)
            dist++;

    return dist;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesTrim(const T* cList, const T* sep, const T* sepNew)
{
    std::vector<CTextT> lines;
    collectLines(lines, false, sep);
    for(CTextT& s : lines)
        s.trim(cList);
    fromArray(lines, sepNew);
    return lines.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesPaddRight(T c, size_t len, const T* sep, const T* sepNew)
{
    std::vector<CTextT> lines;
    collectLines(lines, false, sep);
    for(CTextT& s : lines)
        s.paddRight(c, len);
    fromArray(lines, sepNew);
    return lines.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t  CTextT<T>::linesSort(const T* sep, const T* sepNew)
{
    int pos = 0;
    std::vector<CTextT> lines;
    collectLines(lines, false, sep);
    std::sort(lines.begin(), lines.end(), [](const CTextT& a, const CTextT& b) { return a < b; });
    fromArray(lines, sepNew);
    return lines.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t  CTextT<T>::linesCount(const T* sep) const
{
    if(isEmpty())
        return 0;

    return count(sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename C, typename Val, typename CharT, typename X, typename Enable>  
size_t CTextT<T>::ReadLinesFromFile(const CharT* filePath, C& container, const T* sep)
{
    CTextT<T> s;
    if (!s.readFile(filePath))
        return 0;

    return s.collectLines(container);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::GetExtension(const T* path, size_t len)
{
    if(EmptyOrNull(path) || !len)
        return nullptr;

    const T* psz = path + len - 1;

    size_t nRight = 0;
    while(psz >= path)
    {
        nRight++;
        psz--;
        if(*psz == T('.'))
            break;

        if(IsOneOf(*psz, Slash))
            return nullptr;  // path has no extension
    }

    //if no extension return 0 (not safe)
    if(!nRight || len == nRight)
        return nullptr;

    return path + len - nRight - 1;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::GetExtension(const T* path)
{
    if(EmptyOrNull(path))
        return nullptr;

    return GetExtension(path, Strlen(path));
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::getExtension() const
{
    if(isEmpty())
        return nullptr;

    return GetExtension(str(), length());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::GetFileName(const T* path, size_t len)
{
    if(!len || len == std::string::npos)
        return nullptr;

    const T* name = nullptr;
    const T* psz = path + len - 1;

    while(psz >= path)
    {
        if(IsOneOf(*psz, Slash))
        {
            name = psz + 1;
            break;
        }

        psz--;
    }

    return name;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::GetFileName(const T* path)
{
    if(EmptyOrNull(path))
        return nullptr;

    return GetFileName(path, Strlen(path));
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
const T* CTextT<T>::getFileName() const
{
    if(isEmpty())
        return nullptr;

    return GetFileName(str(), length());
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::removeFileName(bool keepSlash)
{
    size_t i1 = lastIndexOf(T('.'));
    size_t i2 = lastIndexOfAny(Slash);

    if(i1 != std::string::npos && i2 != std::string::npos && i1 > i2)
    {
        if(length() > i2)
            limit(keepSlash?i2+1:i2);
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::removeExtension()
{
    size_t i = lastIndexOf(T('.'));

    if(i == std::string::npos || length() <= i)
        return false;

    limit(i);

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::GetDir(const T* path)
{
    CTextT<T> dir(path);
    size_t i = dir.lastIndexOfAny(Slash);
    if(i != std::string::npos && dir.length() > i)
        dir.limit(i + 1);
    return dir;
}

//-----------------------------------------------------------------------------------------------------------
// get a folder from full module path
template <typename T>
CTextT<T> CTextT<T>::getDir()
{
    return GetDir(str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::removeAfterSlash(bool bRetNoneEmpty)
{
    if(isEmpty())
        return false;

    size_t i = lastIndexOfAny(Slash);
    bool ret = true;

    if(i == std::string::npos)
    {
        if(bRetNoneEmpty)   return false;
        else
        {
            i = 0;
            ret = false;
        }
    }

    if(i != std::string::npos && length() > i)
        limit(i);

    return ret;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::pathCombine(const T* path)
{
    while(*path == T('.'))
    {
        path++;
        if(*path++ != T('.'))
            return false;

        if(!IsOneOf(*path, Slash))
            return false;

        path++;

        if(!removeAfterSlash())
            break;
    }

    if(!endsWithAny(Slash))
    {
        append(T('\\'));
    }

    if(IsOneOf(*path, Slash))
        path++;

    append(path);

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::replaceExtension(const T* newExt)
{
    if(removeExtension() || getFileName() != nullptr)
    {
        append(newExt);
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::replaceFileName(const T* newFileName)
{
    CTextT<T> ext = getExtension();
    if(removeFileName())
    {
        append(newFileName);
        append(ext);
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::addToFileName(const T* str)
{
    CTextT<T> ext = getExtension();
    if(removeExtension())
    {
        append(str);
        append(ext);
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::replaceLastFolder(const T* newFolderName)
{
    if(isEmpty())
        return false;

    size_t i2 = lastIndexOfAny(Slash);

    if(i2 == std::string::npos)
        return false; 

    size_t offset = length() - i2;
    size_t i1 = lastIndexOfAny(Slash, offset);

    if(i1 == std::string::npos)
    {
        // insert at offset
        insert(i2++, T('\\'));
        insert(i2, newFolderName);
    }
    else
    {
        i1++;
        if(i2 > i1)
        {
            RangeVector pos;
            pos.push_back(std::make_pair(i1, i2-1));
            replaceAt(pos, newFolderName);
        }
        else
        {
            insert(i1, newFolderName);
        }
    }

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::IndexOfFirstDiff(const T *str1, const T *str2)
{
    const T* s1 = str1;
    const T* s2 = str2;
    while(*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }

    return (size_t)(s1 - str1);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::IndexOfLastDiff(const T *str1, const T *str2)
{
    const T* s1 = str1 + Strlen(str1);
    const T* s2 = str2 + Strlen(str2);
    while(s1 >= str1 && s2 >= str2 && *s1 == *s2)
    {
        s1--;
        s2--;
    }

    return (size_t)(s1 - str1);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::removeWhileBegins(const T* s)
{
    if(isEmpty())
        return false;

    size_t idx = IndexOfFirstDiff(str(), s);

    if(idx == 0)
        return false;

    cutLeft(idx);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::removeWhileEnds(const T* s)
{
    if(isEmpty())
        return false;

    size_t idx = IndexOfLastDiff(str(), s);

    if(idx == 0)
    {
        clear();
        return true;
    }

    if(idx >= length() - 1)
    {
        return false;
    }

    limit(idx + 1);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::terminatePath()
{
    trimRight();
    if(!endsWithAny(Slash))
        append('/');
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::unterminatePath()
{
    trimRight();
    while(endsWithAny(Slash))
        removeLast();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::SplitPath(const T* path, CTextT& drv, CTextT& dir, CTextT& name, CTextT& ext)
{
    const T* end; // end of processed string
    const T* p;   // search pointer 
    const T* s;   // copy pointer
    
    drv.clear();
    // extract drive name 
    if(path[0] && path[1] == T(':'))
    {
        drv.append(*path++);
        drv.append(*path++);
    }

    //search for end of string or stream separator
    for(end = path; *end && *end != T(':'); )
        end++;

    // search for begin of file extension */
    for(p = end; p > path && *--p != '\\' && *p != '/'; )
    {
        if(*p == '.')
        {
            end = p;
            break;
        }
    }

    s = end;
    ext.clear();
    while(*s)
        ext.append(*s++);

    // search for end of directory name 
    for(p = end; p > path; )
    {
        if(*--p == '\\' || *p == '/')
        {
            p++;
            break;
        }
    }

    name.clear();
    s = p;
    while(s < end)
        name.append(*s++);

    dir.clear();
    s = path;
    while(s < p)
        dir.append(*s++);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::ToByteArrayFromHexString(const T* s, unsigned char* arr, size_t max_len)
{
    size_t n = 0;
    bool bOk;

    while(*s && n < max_len)
    {
        if(IsFormating(*s))
        {
            s++;
            continue;
        }

        unsigned char a = ToHex(*s++, bOk);
        if(!bOk)
            return std::string::npos;
        unsigned char b = ToHex(*s++, bOk);
        if(!bOk)
            return std::string::npos;

        if(arr)
            arr[n] = (a << 4) + b;

        n++;
    }

    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename CharT, typename>
bool CTextT<T>::ReadFileAsHex(const CharT* filePath, CTextT& s)
{
    //open file
    std::ifstream ifs(filePath, std::ios::binary);

    if(!ifs.is_open())// Unable to open file
        return false;

    //get length of file
    ifs.seekg(0, std::ios::end);
    size_t len = ifs.tellg();
    ifs.seekg(0, std::ios::beg);
    
    unsigned char* buf = new unsigned char[len];

    if(buf == nullptr)
    {
        ifs.close();
        return false;
    }

    //read file
    ifs.read((char*)buf, len);
    ifs.close();
    s.fromBytes(buf, len, 0, true, 2);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename CharT, typename>
bool CTextT<T>::WriteFileAsHex(const CharT* filePath, CTextT& s)
{
    //open file
    std::ofstream ofs(filePath, std::ios::binary);

    // just close the file
    if(s.isEmpty())
    {
        ofs.flush();
        ofs.close();
        return true;
    }

    std::vector<unsigned char> bytes;
    if(!s.toChars<unsigned char>(bytes, true))
    {
        // string does not contains hex array, exit
        ofs.close();
        return false;
    }

    ofs.write((char*)bytes.data(), bytes.size());
    return ofs.bad() == false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::toHex(const T* sep)
{
    std::vector<int> bytes;
    if(!toChars<int>(bytes))
        return false;
    fromArray<int>(bytes, true, 2, sep);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::fromHex(const T* s)
{
    if(!EmptyOrNull(s))
        equal(s);

    std::vector<int> bytes;
    if(!toChars<int>(bytes, true))
        return false;
    fromChars<int>(bytes);
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::regexMatch(const T* regexp) const
{
    std::basic_regex<T> e(regexp);
    return std::regex_match(m_str, e);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::regexMatch(const T* regexp, size_t from, size_t count) const
{
    if(length() < from)
        return false;
    if(count == std::string::npos || from + count >= length())
        count = length() - from;
    std::basic_regex<T> e(regexp);
    return std::regex_match(m_str.begin() + from, m_str.begin() + from + count, e);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::regexSearch(C& container, const T* regexp) const
{
    container.clear();
    std::basic_regex<T> e(regexp);
    std::regex_iterator<decltype(m_str.cbegin())> it(m_str.cbegin(), m_str.cend(), e), it_end;
    for(; it != it_end; ++it)
        container.push_back((*it)[0].str());
    return 0;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::regexCollectWords(C& container, const T* regexp, const T* sep) const
{
    container.clear();
    RangeVector pos;
    if(regexCollectWordsPositions(pos, regexp, sep))
    {
        for(auto p : pos)
            container.push_back(substring(p.first, p.second-p.first+1).str());
    }
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::regexCollectLines(C& container, const T* regexp, const T* sep) const
{
    container.clear();
    RangeVector pos;
    if(regexCollectLinesPositions(pos, regexp, sep))
    {
        for(auto p : pos)
            container.push_back(substring(p.first, p.second - p.first + 1).str());
    }
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T> CTextT<T>::regexReplace(const T* regexp, const T* fmt) const
{
    std::basic_regex<T> e(regexp);
    return std::regex_replace(m_str, e, fmt);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::regexReplace(const T* exp, const T* fmt) 
{
    *this = static_cast<const CTextT<T>*>(this)->regexReplace(exp, fmt);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::regexCollectWordsPositions(RangeVector& pos, const T* regexp, const T* sep) const
{
    return regexCollectPositions(pos, regexp, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::regexCollectLinesPositions(RangeVector& pos, const T* regexp, const T* sep) const
{
    return regexCollectPositions(pos, regexp, sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::regexCollectPositions(RangeVector& pos, const T* regexp, const T* sep) const
{
    if(isEmpty())
        return 0;
    pos.clear();
    try
    {
        std::basic_regex<T> e(regexp);

        size_t posNext = 0, start, count;
        while(nextExcluding(posNext, start, count, false, sep))
        {
            if(std::regex_match(m_str.begin() + start, m_str.begin() + start + count, e))
                pos.push_back(std::make_pair(start, start + count - 1));
        }
        return pos.size();
    }
    catch(...)
    {
        // error, regexp is not Ok
        return std::string::npos;
    }
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::CopyAsTchar(const char* str, T* tstr, size_t max_len)
{
    size_t n = 0;
    T c = *str++;
    while(c && n < max_len)
    {
        tstr[n++] = c;
        c = *str++;
    }

    tstr[n] = 0;
    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::Vsscanf(const T*& buf, const T *s, va_list ap)
{
    size_t count, noassign, width, base = 10, lflag;
    T tmp[256];

    const T*		start = buf;

    count = noassign = width = lflag = 0;

    T ccList[16];
    CopyAsTchar("dibouxcsefgn%", ccList, 16);
    T dList[16];
    CopyAsTchar("dobxu%", dList, 16);

    while(*s && *buf)
    {
        while(IsSpace(*s))
            s++;

        if(*s == '%')
        {
            s++;
            for(; *s; s++)
            {
                if(StrFindCh(ccList, *s))
                    break;

                if(*s == '*')
                    noassign = 1;

                else if(*s == 'l' || *s == 'L')
                    lflag = 1;
                /*
                                else if (*s >= '1' && *s <= '9')
                                {
                                    for (tc = s; isdigit (*s); s++);
                                    strncpy (tmp, tc, s - tc);
                                    tmp[s - tc] = '\0';
                                    atob (&width, tmp, 10);
                                    s--;
                                }
                */
            }
            if(*s == 's')
            {
                while(IsSpace(*buf))
                    buf++;
                if(!width)
                    width = Strcspn(buf, Separators);
                if(!noassign)
                    *va_arg(ap, CTextT<T>*) = CTextT(buf, width); // TODO    //Strncpy(va_arg(ap, T *), buf, width); // TODO
                
                buf += width;
            }

            else if(*s == 'c')
            {
                if(!width)
                    width = 1;
                if(!noassign)
                    Strncpy(va_arg(ap, T *), buf, width);
                buf += width;
            }
            else if(*s == 'n')
            {
                int nReaded = buf - start;
                *va_arg(ap, int *) = nReaded;
            }

            else if(StrFindCh(dList, *s))
            {
                while(IsSpace(*buf))
                    buf++;
                if(*s == 'd' || *s == 'u')
                    base = 10;
                else if(*s == 'x')
                    base = 16;
                else if(*s == 'o')
                    base = 8;
                else if(*s == 'b')
                    base = 2;
                if(!width)
                {
                    if(IsSpace(*(s + 1)) || *(s + 1) == 0)
                        width = Strcspn(buf, Separators);
                    else
                    {
                        const T* p = StrFindCh(buf, *(s + 1));
                        if(!p)
                            return 0;

                        width = p - buf;
                    }
                }
                Strncpy(tmp, buf, width);
                tmp[width] = 0;
                buf += width;
                if(!noassign)
                    if(!atoi(va_arg(ap, int *), tmp, base))
                        return 0;
            }

            if(!noassign)
                count++;
            width = noassign = lflag = 0;
            s++;
        }

        else
        {
            while(IsSpace(*buf))
                buf++;

            if(*s != *buf)
                break;
            else
                s++, buf++;
        }
    }

    return count;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::Sscanf(const T* & buf, const T *fmt, ...)
{
    size_t count;
    va_list ap;

    va_start(ap, fmt);
    count = Vsscanf(buf, fmt, ap);
    va_end(ap);
    return count;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::sscanf(size_t& pos, const T *fmt, ...)
{
    size_t count;
    va_list ap;
    
    const T* p = str(pos);

    va_start(ap, fmt);
    count = Vsscanf(p, fmt, ap);
    va_end(ap);

    if(count)
        pos = p - str();

    return count;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::atoi(int *vp, const T *str, int base)
{
    int digit, value;
    T c, sign;

    //	while ( IsSpace(*str) )
    //        ++p;

    c = *str++;

    sign = c;
    if(c == '-' || c == '+')
        c = *str++;    // skip sign 

    value = *vp = 0;

    while(c)
    {
        if(c >= '0' && c <= '9')
            digit = c - '0';
        else if(c >= 'a' && c <= 'f')
            digit = c - 'a' + 10;
        else if(c >= 'A' && c <= 'F')
            digit = c - 'A' + 10;
        else
            return false;

        if(digit >= base)
            return false;
        value *= base;
        value += digit;

        c = *str++;
    }

    if(sign == '-')
        *vp = -value;
    else
        *vp = value;;

    return 1;
}

