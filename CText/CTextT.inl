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
CTextT<T>::CTextT(std::basic_string<T>&& s) : m_str(std::move(s))
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
CTextT<T>::CTextT(CTextT&& str) : m_str(std::move(str.m_str))
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
CTextT<T>& CTextT<T>::operator=(CTextT&& s)
{
    if(&s == this)
        return *this;

    m_str = std::move(s.m_str);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::operator=(std::basic_string<T>&& s)
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
template <typename Num>
CTextT<T>& CTextT<T>::operator<<(Num i)
{
    std::basic_stringstream<T> ss;
    ss << i;
    fromInteger(i, true);
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
void CTextT<T>::equal(T c, size_t len)
{
    m_str.assign(len, c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::equal(const CTextT<T>& s)
{
    m_str.assign(s.m_str);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::equal(const T* s)
{
    if(EmptyOrNull(s))
        clear();
    else
        m_str.assign(s);
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::equal(const T* s, size_t len, size_t offset)
{
    if(EmptyOrNull(s))
        clear();
    else
        m_str.assign(s + offset, len);
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
CTextT<T> CTextT<T>::Add(const CTextT<T>& str, T c)
{
    CTextT<T> res;
    res.m_str = str.m_str + c;
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
void CTextT<T>::append(const C& container)
{
    for(auto& v : container)
        append(v);
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
        return std::string::npos;

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
T* CTextT<T>::Strncpy(T *dst, const T *src, int n)
{
    if(!dst || !src || !n)
        return dst;

    T* d = dst;

    while(*src && n--)
        *d++ = *src++;

    // force ending zero 
    if(n == -1)
        *d++ = 0;

    while(n-- > 0)
        *d++ = 0;

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
    return ::toupper(c);
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
bool CTextT<T>::StartsWith(const T* text, const T* str, bool bCase, int max_len, size_t* offset)
{
    if(!*text || !*str)
        return false;

    const T* text_start = text;

    while(*text != 0 && *str != 0)
    {
        if(0 != *str && (bCase ? (*text != *str) : (upper(*text) != upper(*str))))
            return false;
        text++;
        str++;

        // check if the maximal number of characters is reached
        if(max_len > 0 && text - text_start >= max_len)
            break;
    }

    if(*str != 0)
        return false;

    if(offset)
        *offset = text - text_start - 1;

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::startsWith(T c, size_t from, bool bCase) const
{
    if(isEmpty() || from >= length())
        return false;

    T first = *(str(from));

    if(bCase)
        return first == c;
    else
        return upper(first) == upper(c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename S, typename X>
bool CTextT<T>::startsWith(const S& s, size_t from, bool bCase) const
{
    if(isEmpty() || EmptyOrNull((const T*)s) || from >= length())
        return false;

    return StartsWith(str(from), (const T*)s, bCase, -1);
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
bool CTextT<T>::startsWithAny(const C& list, size_t from, bool bCase, size_t* idx) const
{
    size_t pos = 0;
    for(auto& s : list)
    {
        if(startsWith(s, from, bCase))
        {
            if(idx) *idx = pos;
            return true;
        }
        pos++;
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
bool CTextT<T>::startsWithAny(const S& cList, size_t from, bool bCase, size_t* idx) const
{
    if(from >= length() || EmptyOrNull((const T*)cList))
        return false;
    bool bRes = IsOneOf(m_str[from], (const T*)cList, bCase);
    if(bRes)
        if(idx) *idx = from;
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
    if(isEmpty() || EmptyOrNull((const T*)s) || from >= length())
        return false;

    from = length() - from;  //from is calculated from the back

    return EndsWith(str(), (const T*)s, bCase, from);
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
bool CTextT<T>::endsWithAny(const C& container, size_t from, bool bCase, size_t* idx) const
{
    size_t pos = 0;
    for(auto v : container)
    {
        if(endsWith(v, from, bCase))
        {
            if(idx) *idx = pos;
            return true;
        }
        pos++;
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
    size_t idx = lastIndexOf(s, bCase);

    if(idx == std::string::npos)
        return nullptr;

    return str(idx);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::lastIndexOf(T c, bool bCase) const
{
    if(isEmpty())
        return std::string::npos;

    return LastIndexOf(str(), length(), c, bCase);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::lastIndexOf(const T* s, bool bCase) const
{
    if(EmptyOrNull(s))
        return std::string::npos;

    return LastIndexOf(str(), length(), s, bCase);
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
            return ((int)(p - str));
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
    return -1;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::indexOfAny(const C& container, size_t from, bool bCase, size_t* idxList) const
{
    if(isEmpty())
        return std::string::npos;

    size_t idx = from;
    size_t pos;
    while(idx < length())
    {
        if(startsWithAny(container, idx, bCase, &pos))
        {
            if(idxList)
                *idxList = pos;
            return idx;
        }
        idx++;
    }

    return std::string::npos;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::indexOfAny(const T* cList, size_t from, bool bCase) const
{
    if(isEmpty() || from < 0 || from >= length() || EmptyOrNull(cList))
        return std::string::npos;

    const T* s = StrFindChAny(str(from), cList, bCase);
    return (s == 0) ? std::string::npos : (size_t)(s - str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::indexOf(T c, size_t from, bool bCase) const
{
    if(isEmpty())
        return std::string::npos;

    return IndexOf(str(from), length(), c, bCase);
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
size_t CTextT<T>::IndexOf(const T* str, size_t len, T c, bool bCase)
{
    if(EmptyOrNull(str))
        return std::string::npos;

    // find first single character
    const T* s = StrFindCh(str, c, bCase);

    // return -1 if not found and index otherwise
    return (s == 0) ? -1 : (int)(s - str);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::indexOfNot(T c, bool bCase) const
{
    if(isEmpty())
        return std::string::npos;

    // find last single character
    const T* s = str();

    if(!bCase) c = upper(c);

    while(*s)
    {
        if(bCase ? *s != c : upper(*s) != c)
            return ((int)(s - str()));
        s++;
    }

    // return -1 if contain only c, distance from beginning otherwise
    return std::string::npos;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t  CTextT<T>::lastIndexOfAny(const T* cList, bool bCase) const
{
    if(isEmpty())
        return std::string::npos;

    // find last single character
    const T* s = str(length() - 1);
    while(s >= str())
    {
        if(IsOneOf(*s, cList, bCase))
            return ((int)(s - str()));

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
            return ((int)(s - str()));
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
bool CTextT<T>::containAny(const C& container, bool bCase) const
{
    return (indexOfAny(container, 0, bCase) != std::string::npos);
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
template<typename C, typename Val, typename X>
size_t CTextT<T>::findPositions(const C& list, RangeVector& pos, bool bCase, std::vector<size_t>* indexes) const
{
    if(isEmpty())
        return 0;

    pos.clear();

    size_t idx = 0;
    size_t idxList;
    while(idx < length())
    {
        if(startsWithAny(list, idx, bCase, &idxList))
        {
            size_t len = Strlen((const T*)list[idxList]);
            pos.push_back(std::make_pair(idx, idx + len - 1));
            if(indexes)
                indexes->push_back(idxList);
            idx += len; // will not overlap
            continue;
        }
        idx++;
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
int CTextT<T>::removeAny(const T* cList, bool bCase)
{
    if(isEmpty() || EmptyOrNull(cList))
        return 0;

    auto from = m_str.begin();
    auto to = m_str.begin();

    int n = 0;
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
CTextT<T>& CTextT<T>::removeAny(const C& list, bool bCase)
{
    std::vector< std::pair <size_t, size_t> > v;
    while(findPositions(list, v, bCase))
        removeAt(v);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::removeAny(std::initializer_list<const T*> list, bool bCase)
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
    std::vector< std::pair <size_t, size_t> > v;
    while((nFound = findBlockPositions(sepBegin, sepEnd, v)) > 0)
    {
        removeAt(v);
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
    while(p != s1)
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
    int n = Strlen(str);
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
    if(!pos.size() || pos[0].first >= length())
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
size_t CTextT<T>::keep(size_t from, size_t count)
{
    size_t old_len = length();
    if(from > 0)
        cutLeft(from);
    limit(count);
    return old_len - length();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::keepEnds(size_t count)
{
    return erase(count, length() - 2 * count);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::keepLeft(size_t count)
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
size_t CTextT<T>::cutLeft(size_t count)
{
    return erase(0, count);
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::cutRight(size_t count)
{
    if(count > length())
    {
        clear();
        return *this;
    }

    limit(length() - count);

    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::cutEnds(size_t fromLeft, size_t fromRight)
{
    return keep(fromLeft, length() - fromLeft - fromRight);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::cutEnds(size_t count)
{
    return keep(count, length() - 2 * count);
}
//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::cutAfterFirst(T ch, bool include)
{
    size_t idx = indexOf(ch);

    if(idx == std::string::npos) //not found
        return false;

    if(include)
        idx++;

    keepLeft(idx);

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::cutAfterLast(T c, bool include)
{
    size_t idx = lastIndexOf(c);

    if(idx == std::string::npos)
        return false;

    if(include)
        idx++;

    keepLeft(idx);

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::cutAfterLastOfAny(const T* chList, bool include, bool bCase)
{
    size_t idx = lastIndexOfAny(chList, bCase);

    if(idx == std::string::npos)
        return false;

    if(include)
        idx++;

    keepLeft(idx);

    return true;
}


//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::cutAfterLast(const T* s, bool include)
{
    if(EmptyOrNull(s) || isEmpty())
        return false;

    if(!s[1])
        return cutAfterLast(s[0]);

    size_t idx = lastIndexOf(s);

    if(idx == std::string::npos)
        return false;

    if(include)
        idx += Strlen(s);

    keepLeft(idx);

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::cutAfterFirst(const T* s, bool include)
{
    if(EmptyOrNull(s) || isEmpty())
        return false;

    if(!s[1])
        return cutAfterFirst(s[0], include);

    size_t idx = indexOf(s);

    if(idx == std::string::npos) //not found
        return false;

    if(include)
        idx += Strlen(s);

    keepLeft(idx);

    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::cutAfterFirstOfAny(const T* chList, bool include, bool bCase)
{
    size_t idx = indexOfAny(chList, 0, bCase);

    if(idx == std::string::npos) //not found
        return false;

    if(include)
        idx++;

    keepLeft(idx);

    return true;
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
};

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
CTextT<T>& CTextT<T>::makeUnique(T c)
{
    size_t idx = indexOf(c);

    if(idx != std::string::npos)
        remove(c, idx + 1);

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
CTextT<T>& CTextT<T>::makeUnique()
{
    if(isEmpty())
        return *this;

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
    return *this;
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
CTextT<T>& CTextT<T>::rotateLeft(int n)
{
    if(isEmpty() || !n)
        return *this;

    n = n % length();
    std::rotate(m_str.begin(), m_str.begin() + n, m_str.end());
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::rotateRight(int n)
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
    std::vector< std::pair <size_t, size_t> > v;
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
unsigned int CTextT<T>::toBinaryNumber(bool& bOk)
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
template<typename Num, typename C, typename Val, typename X>
size_t CTextT<T>::toArray(C& container, T sep, bool& bOk) const
{
    container.clear();
    Num num;
    std::basic_istringstream<T> iss(m_str);
    T c;

    bool hasEOL = false;

    if(sep == *SPACE)
        iss >> std::noskipws;

    else if(sep == *EOL)
        hasEOL = true;

    iss >> num;
    bOk = !iss.fail();
    if(!bOk || iss.eof())
        return container.size();

    container.push_back(num);

    if(!hasEOL)
    {
        while(bOk && iss >> c)
        {
            bOk = (c == sep);
            if(!bOk)
                return container.size();

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

    return container.size();;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename Num, typename C, typename Val, typename X>
size_t CTextT<T>::toMatrix(std::vector<C>& container, T sep, bool& bOk, const T* sepLine) const
{
    size_t n = 0;
    std::vector<CTextT> lines;
    collectLines(lines, false, sepLine);

    for(const CTextT& s : lines)
    {
        std::vector<Num > v;

        s.toArray<Num>(v, sep, bOk);

        if(!bOk)
            return n;

        container.push_back(std::move(v));

        n += v.size();
    }

    return n;
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
void CTextT<T>::randomNumber(size_t len)
{
    clear();
    resize(len);
    m_str[0] = '1' + rand() % 9;  // must not begin with 0

    for(int k = 1; k < len; k++)
        m_str[k] = '0' + rand() % 10;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::random(const T* cList, size_t len)
{
    clear();
    resize(len);
    size_t range = Strlen(cList);

    for(size_t k = 0; k < len; k++)
        m_str[k] = cList[rand() % range];
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::randomAlpha(size_t len)
{
    CTextT<T> s;
    s.appendRange(T('a'), T('z')).appendRange(T('A'), T('Z'));
    random(s.str(), len);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::randomAlphaNumeric(size_t len)
{
    CTextT<T> s;
    s.appendRange(T('a'), T('z')).appendRange(T('A'), T('Z')).appendRange(T('0'), T('9'));
    random(s.str(), len);
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
int CTextT<T>::countChars(std::map<T, int>& container, bool bCase) const
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
    swap(a.m_str, b.m_str);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::wordsSort(const T* sep, const T* sepNew) // words sort in ascending order
{
    int pos = 0;
    std::vector<CTextT> words;
    split(words, false, sep);  //TODO - add case
    std::sort(words.begin(), words.end(), [](const CTextT& a, const CTextT& b) { return a < b; });
    compose(words, sepNew);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::wordsReverse(const T* sep) // reverse words
{
    std::vector< std::pair <size_t, size_t> > v;
    if(findWordPositions(v, sep))
        reverseAt(v);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::findWordPositions(RangeVector& pos, const T* sep) const
{
    if(isEmpty())
        return 0;

    pos.clear();
    size_t posNext = 0, posBegin, posEnd;
    CTextT<T> word;
    while(nextExcluding(posNext, word, false, sep, &posBegin, &posEnd))
        pos.push_back(std::make_pair(posBegin, posEnd));
    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::findBlockPositions(const T* sepBegin, const T* sepEnd, std::vector< std::pair<size_t, size_t>>& pos, bool bCase) const
{
    if(!length()) 
        return 0;

    pos.clear();

    size_t posBegin, posEnd;
    const T* s = str();

    while(*s)
    {
        if(!*s)
            break;

        while(*s && !IsOneOf(*s, sepBegin, bCase))
            s++;

        if(!*s)
            break;

        posBegin = s - str();

        s++;

        while(*s && !IsOneOf(*s, sepEnd, bCase))
            s++;

        posEnd = s - str();

        if(!*s || posBegin == posEnd)
            break;

        pos.push_back(std::make_pair(posBegin, posEnd));

        s++;
    }

    return pos.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::split(C& container, bool appendSeparators, const T* sep) const
{
    container.clear();
    size_t pos = 0;
    CTextT<T> s;
    while(nextExcluding(pos, s, appendSeparators, sep))
        container.push_back(s.str());
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
bool CTextT<T>::splitAtLast(T ch, CTextT& first, CTextT& second, bool exclude) const
{
    size_t idx = lastIndexOf(ch);

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
    size_t idx = lastIndexOfAny(cList, bCase);

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
template<typename C, typename Val, typename X>
void CTextT<T>::compose(const C& container, const T* sep)
{
    clear();
    bool first = false;
    for(auto& v : container)
    {
        if(first && sep)
            append(sep);
        else
            first = true;
        append(v);
    }
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
void CTextT<T>::compose(std::map<T, int>& container, const T* sep, const T* sepLine)
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
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Value, typename X  >
void CTextT<T>::compose(const C& container, const T* sep, const T* sepLine)
{
    clear();
    bool first = false;
    for(auto& v : container)
    {
        if(first && sep)
            append(sepLine);
        else
            first = true;

        if(std::is_integral<Value>::value)
        {
            append(v.first);
            append(sep);
            fromInteger(v.second, true);
        }
        else
        {
            append(v.second);
            append(sep);
            fromInteger(v.first, true);
        }
    }
}
//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::nextExcluding(size_t& pos, CTextT<T>& substr, bool appendSeparators, const T* cList, size_t* posBegin, size_t* posEnd) const
{
    if(isEmpty() || pos >= length())
        return false;

    const T* s1 = str(pos);

    while(!IsOneOf(*s1, cList) && s1 > m_str)
        s1--;

    while(IsOneOf(*s1, cList))
        s1++;

    const T* s2 = s1;

    while(*s2 && !IsOneOf(*s2, cList))
        s2++;

    if(posBegin)
        *posBegin = s1 - str();
    if(posEnd)
        *posEnd = s2 - str() - 1;

    if(appendSeparators)
    {
        while(*s2 && IsOneOf(*s2, cList))
            s2++;
    }

    if(s2 == s1) // it is empty
        return false;

    substr = CTextT(s1, s2 - s1);

    // move iterator position for the next search
    while(IsOneOf(*s2, cList))
        s2++;

    pos = static_cast<size_t> (s2 - str());
    return true;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::nextIncluding(size_t& pos, CTextT<T>& substr, const T* cList, size_t* posBegin, size_t* posEnd) const
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

    if(posBegin)
        *posBegin = s1 - str();

    if(posBegin)
        *posEnd = s2 - str();

    substr = CTextT(s1, s2 - s1);

    pos = s2 - str() + 1;

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
size_t CTextT<T>::count(T c) const
{
    return std::count(m_str.begin(), m_str.end(), c);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::countAny(const T* cList) const
{
    size_t nChars = 0;
    while(*cList)
    {
        nChars += count(*cList);
        cList++;
    }

    return nChars;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t  CTextT<T>::count(const T* s) const
{
    if(EmptyOrNull(s))
        return 0;

    size_t len = Strlen(s);

    if(len == 1)
        return count(*s);  // return single-character version

    size_t pos = 0;
    size_t num = 0;

    while((pos = indexOf(s, pos)) != -1)
    {
        pos += len;
        num++;
    }
    return num;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
int CTextT<T>::countChains(T c) const
{
    if(isEmpty() || !c || length() < 2)
        return 0;

    auto from = m_str.begin() + 1;

    T chFrom = 0;
    int n = 0;
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
int CTextT<T>::countChainsAny(const T* cList) const
{
    if(isEmpty() || EmptyOrNull(cList) || length() < 2)
        return 0;

    auto from = m_str.begin() + 1;

    T chFrom = 0;
    int n = 0;
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
int CTextT<T>::countWords(const T* sep) const
{
    return countSubstrings(sep);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
int CTextT<T>::countSubstrings(const T* sep) const
{
    size_t pos = 0;
    int n = 0;
    CTextT<T> word;
    while(nextExcluding(pos, word, false, sep))
        n++;
    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Value, typename X  >
size_t CTextT<T>::countWordFrequencies(C& container, bool bCase, const T* sep) const
{
    container.clear();
    size_t pos = 0;
    CTextT<T> word;
    std::map<CTextT<T>, int> freq;
    while(nextExcluding(pos, word, false, sep))
    {
        if(!bCase)
            word.toLower();
        freq[word]++;
    }

    for(auto & v : freq)
        container.insert(std::make_pair(v.second, v.first));

    return container.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
int CTextT<T>::wordsCapitalize(const T* sep)
{
    if(isEmpty())
        return 0;
    size_t posNext = 0, posBegin, posEnd;
    CTextT<T> word;
    int n = 0;
    while(nextExcluding(posNext, word, false, sep, &posBegin, &posEnd))
    {
        m_str[posBegin] = upper(m_str[posBegin]);
        n++;
    }
    return n;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collect(C& container, const T* cList) const
{
    container.clear();
    size_t pos = 0;
    CTextT<T> word;
    while(nextIncluding(pos, word, cList))
        container.push_back(word.str());
    return container.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collectSubstrings(C& container, const C* start, const C* end, const C* has, const T* sep) const
{
    container.clear();
    size_t pos = 0;
    CTextT<T> word;
    while(nextExcluding(pos, word, false, sep))
    {
        // apply filter
        if((start && word.startsWithAny(*start)) ||
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
size_t CTextT<T>::collectSentences(C& container, const T* sep, const T* sepWords) const
{
    container.clear();
    size_t pos = 0, posBegin, posEnd;
    CTextT<T> sentence;
    CTextT<T> old;
    while(nextExcluding(pos, sentence, true, sep, &posBegin, &posEnd))
    {
        // check if the next character is Upper
        T c = nextChar(pos, sepWords);
        if(IsUpper(c) || !c)
        {
            if(old.length())
            {
                old += sentence;
                old.trim(sepWords);
                container.push_back(old);
                old.clear();
            }
            else
            {
                sentence.trim(sepWords);
                container.push_back(sentence);
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
        container.push_back(old);
    }
    return container.size();
}



//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
size_t CTextT<T>::collectPositions(RangeVector& pos, const C* start, const C* end, const C* has, const T* sep) const
{
    if(isEmpty())
        return 0;

    pos.clear();
    size_t posNext = 0, posBegin, posEnd;
    CTextT<T> word;
    while(nextExcluding(posNext, word, false, sep, &posBegin, &posEnd))
    {
        // apply filter
        if((start && word.startsWithAny(*start)) ||
            (end && word.endsWithAny(*end)) ||
            (has && word.containAny(*has)) ||
            (!start && !end && !has))
            pos.push_back(std::make_pair(posBegin, posEnd));
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
template <typename Num>
bool CTextT<T>::fromBinary(Num i)
{
    if(sizeof(i) == 1)
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
template <typename Num>
bool CTextT<T>::fromInteger(Num i, bool append)
{
    std::basic_stringstream<T> ss;
    ss << i;
    append ? m_str.append(ss.str()) : m_str = ss.str();
    return !ss.fail();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::fromDouble(double d, int precision, bool fixed, bool append)
{
    std::basic_stringstream<T> ss;
    if(fixed) ss << std::fixed;
    else      ss << std::scientific;
    ss << std::setprecision(precision) << d;
    append ? m_str.append(ss.str()) : m_str = ss.str();
    return !ss.fail();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template <typename Num>
bool CTextT<T>::fromHex(Num i, bool hasBase, bool upper)
{
    std::basic_stringstream<T> ss;
    if(hasBase) ss << T('0') << T('x');
    if(upper) ss << std::uppercase;
    ss << std::setfill(T('0')) << std::setw(sizeof(Num) * 2) << std::hex << ((sizeof(Num) == 1) ? i : (int)i);


    m_str = ss.str();
    return !ss.fail();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::fromChars(const char* s)
{
    return FromChars(s, *this);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::fromWChars(const wchar_t* s)
{
    return FromWChars(s, *this);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<char> CTextT<T>::toChars()
{
    CTextT<char> res;
    if(isEmpty())
        return res;
    
    return ToChars(str());
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<wchar_t> CTextT<T>::toWChars()
{
    std::basic_string<wchar_t> res;
    if(isEmpty())
        return res;
    
    return ToWChars(str());
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
int CTextT<T>::replaceAny(const T* cList, T cNew, bool bCase)
{
    if(isEmpty() || EmptyOrNull(cList))
        return 0;

    auto from = m_str.begin();
    int nCount = 0;
    while(from != m_str.end())
    {
        // replace instances of the specified character only
        if(IsOneOf(*from, cList, bCase))
        {
            *from = cNew;
            nCount++;
        }

        from++;
    }

    return nCount;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::replaceAny(const C& what, const T c, bool bCase)
{
    std::vector< std::pair <size_t, size_t> > v;
    while(findPositions(what, v, bCase))
        replaceAt(v, c);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::replaceAny(const C& container, const T* with, bool bCase)
{
    std::vector< std::pair <size_t, size_t> > v;
    while(findPositions(container, v, bCase))
        replaceAt(v, with);
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
CTextT<T>& CTextT<T>::replaceAny(const C& what, const C& with, bool bCase)
{
    std::vector< std::pair <size_t, size_t> > v;
    std::vector<size_t> indexes;
    if(findPositions(what, v, bCase, &indexes))
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
            size_t lenReplace = Strlen((const T*)with[k]);
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

            const T* pWith = (const T*)with[idxBlock];
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

            const T* pBegin = begin;
            while(*pBegin)
                *pdst++ = *pBegin++;

            idx += nBlockSize;

            while(nBlockSize--)
                *pdst++ = *psrc++;

            const T* pEnd = end;
            while(*pEnd)
                *pdst++ = *pEnd++;

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
int CTextT<T>::unenclose(T begin, T end)
{
    int left = 0;
    int right = 0;

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
int CTextT<T>::unquote()
{
    return unenclose(Literal, Literal);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
template<typename C, typename Val, typename X>
CTextT<T>& CTextT<T>::wordsEnclose(const T* sBegin, const T* sEnd, const C* start, const C* end, const C* has, const T* sep)
{
    RangeVector pos;
    if(collectPositions(pos, start, end, has, sep))
        insertAt(pos, sBegin, sEnd);
    return *this;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
CTextT<T>& CTextT<T>::wordsEnclose(const T* sBegin, const T* sEnd, const T* sep)
{
    RangeVector pos;
    if(findWordPositions(pos, sep))
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
bool CTextT<T>::writeFile(const T* filePath, EncodingType encoding)
{
    return WriteFile(filePath, *this, encoding);
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
bool CTextT<T>::readFile(const T* path)
{
    return ReadFile(path, *this);
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
    int pos = 0;
    std::vector<CTextT> lines;
    collectLines(lines, false, sep);
    for(CTextT& s : lines)
        s.trim(cList);
    compose(lines, sepNew);
    return lines.size();
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
size_t CTextT<T>::linesPaddRight(T c, size_t len, const T* sep, const T* sepNew)
{
    int pos = 0;
    std::vector<CTextT> lines;
    collectLines(lines, false, sep);
    for(CTextT& s : lines)
        s.paddRight(c, len);
    compose(lines, sepNew);
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
    compose(lines, sepNew);
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
bool CTextT<T>::readLinesFromFile(const T* path, size_t lineStart, size_t lineEnd)
{
    return ReadLinesFromFile(path, *this, lineStart, lineEnd);
}
