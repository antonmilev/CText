/**
 * @file CText.h
 * @brief Advanced Text Proccessing Library
 * @author Anton Milev, baj.mile@abv.bg
 * @version 1.0
 * @date November, 2019
 */
#pragma once 
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <initializer_list>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <array>
#include <stack>
#include <cstdarg>
#include <fstream>
#include <codecvt>
#include <random>      
#include <chrono>      
#include <cassert>
#include <locale>
#include <unordered_map>

#ifdef _WIN32
#pragma warning(disable : 4996)
#endif 

#define ContS template<typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_convertible<Val, std::basic_string<T> >::value || std::is_convertible<Val, const T*>::value || std::is_constructible<Val, const T*>::value >  >
#define ContC template<typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_same<Val, T>::value || std::is_convertible<Val, std::basic_string<T> >::value || std::is_convertible<Val, const T* >::value || std::is_constructible<Val, const T*>::value  >  >
#define ContN template<typename Num, typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_convertible<Val, Num>::value && (std::is_integral<Num>::value || std::is_floating_point<Num>::value) >  >
#define MapI template<typename C, typename Value = typename C::value_type, typename X = std::enable_if_t < std::is_convertible<Value, std::pair<int,CTextT<T>>>::value  > >
#define DefN template <typename Num> 
#define DefS template <typename S, typename X = std::enable_if_t < std::is_convertible<std::remove_const_t<std::remove_reference_t<S>>, const T* >::value || std::is_constructible<std::remove_const_t<std::remove_reference_t<S>>, const T*>::value >>
#define DefT template <typename CharT, typename X = std::enable_if_t< std::is_same<CharT, char>::value || std::is_same<CharT, wchar_t>::value  >>


template <typename T>
class CTextT
{
public:
    CTextT();
    CTextT(const std::basic_string<T>& s);
    CTextT(std::basic_string<T>&& s);
    CTextT(const T* s);
    CTextT(const T* s, size_t len);
    CTextT(T c, size_t len = 1);
    CTextT(const CTextT& s);
    CTextT(CTextT&& s);
    CTextT(std::initializer_list<T> list);
    CTextT(std::initializer_list<const T*> list);
    ~CTextT();

    enum EncodingType
    {
        ENCODING_ASCII = 0,
        ENCODING_UTF8 = 1,
        ENCODING_UTF16LE = 2,
        ENCODING_UTF16BE = 3
    };

    CTextT& operator=(const CTextT& s);
    CTextT& operator=(CTextT&& s);
    CTextT& operator=(const std::basic_string<T>& s);
    CTextT& operator=(std::basic_string<T>&& s);
    CTextT& operator=(const T* s);

    inline friend bool  operator==(const CTextT& s1, const CTextT& s2)       { return s1.m_str == s2.m_str; }
    inline friend bool  operator==(const CTextT& s1, const T* s2)            { return s1.m_str == s2; }
    inline friend bool  operator==(const T* s1, const CTextT& s2)            { return s2.m_str == s1; }
    inline friend bool  operator!=(const CTextT& s1, const CTextT& s2)       { return s1.m_str != s2.m_str; }
    inline friend bool  operator!=(const CTextT& s1, const T* s2)            { return s1.m_str != s2; }
    inline friend bool  operator!=(const T* s1, const CTextT& s2)            { return s2.m_str != s1; }
    inline friend bool  operator< (const CTextT& s1, const CTextT& s2)       { return s1.m_str < s2.m_str; }
    inline friend bool  operator< (const CTextT& s1, const T* s2)            { return s1.m_str < s2; }
    inline friend bool  operator< (const T* s2, const CTextT& s1)            { return s1.m_str > s2; }
    inline friend bool  operator> (const CTextT& s1, const CTextT& s2)       { return s1.m_str > s2.m_str; }
    inline friend bool  operator> (const CTextT& s1, const T* s2)            { return s1.m_str > s2; }
    inline friend bool  operator> (const T* s2, const CTextT& s1)            { return s1.m_str < s2; }
    inline friend bool  operator<=(const CTextT& s1, const CTextT& s2)       { return s1.m_str <= s2.m_str; }
    inline friend bool  operator<=(const CTextT& s1, const T* s2)            { return s1.m_str <= s2; }
    inline friend bool  operator<=(const T* s2, const CTextT& s1)            { return s1.m_str >= s2; }
    inline friend bool  operator>=(const CTextT& s1, const CTextT& s2)       { return s1.m_str >= s2.m_str; }
    inline friend bool  operator>=(const CTextT& s1, const T* s2)            { return s1.m_str >= s2; }
    inline friend bool  operator>=(const T* s2, const CTextT& s1)            { return s1.m_str <= s2; }

    friend CTextT operator+(const CTextT& string1, const CTextT& string2)    { return Add(string1, string2); }
    friend CTextT operator+(const CTextT& string, const T* str)              { return Add(string, str); }
    friend CTextT operator+(const T* str, const CTextT& string)              { return Add(string, str); }
    friend CTextT operator+(const CTextT& string, T ch)                      { return Add(string, ch); }
    friend CTextT operator+(T ch, const CTextT& string)                      { return Add(string, ch); }

    const CTextT& operator+=(const T* str);
    const CTextT& operator+=(const CTextT& string);
    const CTextT& operator+=(T ch);

    CTextT& operator<<(const T* s);
    CTextT& operator<<(const std::basic_string<T>& s);
    CTextT& operator<<(const T c);
    DefN CTextT& operator<<(Num i);

    explicit operator const T*() const { return str(); }  // cast operator
    T operator[](size_t pos) const;  //returns character at given position (coomented to avoid operators connflict)
    T& operator[](size_t pos); // returns modifiable reference to the character at the given position
    T at(size_t pos) const; // same as [] but throws out_of_range excepton
    T& at(size_t pos);
    operator bool() const = delete;
    operator T() const = delete;

    friend std::basic_ostream<T>& operator<<(std::basic_ostream<T>& out, const CTextT<T>& s)
    {
        out << s.m_str;
        return out;
    }

    friend std::basic_ostream<T>& operator<<(std::basic_ostream<T>& out, CTextT<T>& s)
    {
        out << s.m_str;
        return out;
    }

    friend std::basic_istream<T>& operator>>(std::basic_istream<T>& in, CTextT& s)
    {
        return in >> s.m_str;
    }

    typedef std::vector<std::pair<size_t, size_t>> RangeVector;

    bool         alloc(size_t len);
    CTextT&      append(const CTextT& s);
    CTextT&      append(const T* s); // append string
    CTextT&      append(const T* s, size_t len); // append part of a string
    CTextT&      append(T c, size_t count = 1); //append single character
    CTextT&      append(std::initializer_list<T> cList); // append the characters in the list
    CTextT&      append(std::initializer_list<const T*> sList); // append characters in the list
    ContC void   append(const C& container);  // append single character or string buffer, supports all value-type STL containers 
    CTextT&      appendRange(T cBegin, T cEnd);  // append all characters in the range 
    bool         between(T cLeft, T cRight, bool include = false); // keeps the part of the string between the first and last characters cLeft and cRight (by default separators are not included)
    bool         between(const T* sLeft, const T* sRight, bool include = false); // keeps the part of the string between the first and last sub-strings sLeft and sRight (by default separattors are not included)
    size_t       capacity() const;
    bool         checkBalance(const T* sepBegin, const T* sepEnd); // checks if the blocks defined with the given separators are balanced
    void         clear(bool bRelease = false);  // clear content (but does not release string memory)
    ContS size_t collect(C& container, const T* cList) const;  // fill the container with substrings containing only characters from the list
    ContS size_t collectSubstrings(C& container, const C* start = nullptr, const C* end = nullptr, const C* contain = nullptr, const T* sep = Separators) const;  // fill the container with the found substrings after applying the conditions 
    ContS size_t collectPositions(RangeVector& pos, const C* start, const C* end, const C* has, const T* sep) const;
    ContS size_t collectLines(C& container, bool appendSeparators = false, const T* sep = SeparatorsLine) const;  // fills a STL container with the collected lines
    ContS size_t collectSentences(C& container, const T* sep = SeparatorsSentence, const T* sepWords = Separators) const;
    ContS size_t collectWords(C& container, const T* sep = Separators) const;  // fill container with all found words
    int          compare(const T* s, bool bCase = true) const; // return - 0 equal. -1 p1 < p2, or 1 - p1 > p2
    bool         contain(T c, bool bCase = true) const;  // returns true if our string contains character c
    bool         contain(const T* s, bool bCase = true) const; // returns true if our string contains another string  
    bool         containAny(std::initializer_list<T> cList); // returns true if our string contains any of the characters of the list
    ContC bool   containAny(const C& container, bool bCase = true) const;  // returns true if contains any of the strings provided by the container
    bool         containAny(const T* cList, bool bCase = true) const; // returns true if our string contains any of the characters of the list
    bool         containOnly(const T* cList, bool bCase = true) const; // returns true if our string contains only characters from the list   
    bool         contain(const T c, size_t from, size_t to) const; // search in range
    size_t       count(T c) const;  //returns the count of occurences of the given character
    size_t       count(const T* s) const;  //returns the count of occurences of the given substring
    size_t       countAny(const T* cList) const;  //returns the count of occurences of any of the characters in the list
    size_t       countChains(T c) const;  // return count of blocks containing only character c (chains)
    size_t       countChainsAny(const T* cList) const;  // return count of blocks containing only of the characters in the list
    size_t       countChars(std::map<T, int>& container, bool bCase = true) const; // fill the map container with character counts
    size_t       countSubstrings(const T* sep) const; // return number of found substrings divided by sep
    size_t       countWords(const T* sep = SeparatorsWord) const; // return number of the found words divided by sep
    MapI size_t  countWordFrequencies(C& container, bool bCase = true, const T* sep = SeparatorsWord) const; // fill the container with the words frequency counts
    bool         cutAfterFirst(T c, bool include = false);//leaves everyting left from c, c is not included
    bool         cutAfterFirst(const T* s, bool include = false); // same as above but perfomed over zero-teminated string, s is not included
    bool         cutAfterFirstOfAny(const T* cList, bool include = false, bool bCase = true); //cut after the first occurence of any character from the list 
    bool         cutAfterLast(T c, bool include = false); //leaves everyting left from the last character, c is not included
    bool         cutAfterLast(const T* s, bool include = false); // leaves everyting left from last s, s is not included
    bool         cutAfterLastOfAny(const T* chList, bool include = false, bool bCase = true); // leaves everyting left from last ch in the list, ch is not included
    size_t       cutEnds(size_t count); //remove count of characters from left and right
    size_t       cutEnds(size_t fromLeft, size_t fromRight);  //cut number of charcters from left and right
    size_t       cutLeft(size_t count);  //removes count characters from left
    CTextT&      cutRight(size_t count); //cut number of characters from right, if count is too big empty the string
    CTextT&      enclose(T begin, T end, bool checkEnds = true); //enclose with the provided character separators (if not already ends and begins with them)
    CTextT&      enclose(const T* begin, const T* end, bool checkEnds = true); //enclose with the provided text separators (if not already ends and begins with them)
    void         equal(const CTextT& s);  // make our string equal to str
    void         equal(const T* s);  // make equal to str
    void         equal(T c, size_t len);  // init witb len number of ch
    void         equal(const T* s, size_t len, size_t offset = 0);  // init to len characters from string at offset   
    bool         endsWith(T c, size_t from = 0, bool bCase = true) const;
    DefS bool    endsWith(const S& s, size_t from = 0, bool bCase = true) const;
    bool         endsWith(std::initializer_list<T> cList);
    bool         endsWithAny(const T* cList, bool bCase = true) const;
    ContC bool   endsWithAny(const C& container, size_t from = 0, bool bCase = true, size_t* idx = nullptr) const;
    size_t       erase(size_t from, size_t count = 1);  // delete count characters starting at zero-based index
    const T*     find(const T c, bool bCase = true) const;// return a pointer to the first occurence of the character, or 0 pointer if not found
    const T*     find(const T *s, bool bCase = true) const; // return a pointer to the first occurence of the string, or 0 pointer if not found
    size_t       findBlockPositions(const T* sepBegin, const T* sepEnd, std::vector< std::pair<size_t, size_t>>& pos, bool bCase = true) const; //find begin/end positions of all blocks beggining and ending with the given separators
    ContC size_t findPositions(const C& list, RangeVector& pos, bool bCase = true, std::vector<size_t>* indexes = nullptr) const;
    size_t       findWordPositions(RangeVector& pos, const T* sep) const;
    T            first() const; //return first character or 0 if empty
    bool         format(const T* format, ...);
    DefN bool    fromBinary(Num i);  // create binary string from the number
    DefN bool    fromInteger(Num i, bool append = false);
    DefN bool    fromHex(Num i, bool hasBase = true, bool upper = false);    
    bool         fromDouble(double d, int precision = 6, bool fixed = true, bool append = false);
    bool         fromChars(const char* s);  // init with single-char ANSI string, make string -> wstring convert if necessary
    bool         fromWChars(const wchar_t* s);  // init with UNICODE string, make wstring -> string convert if necessary
    ContC void   fromArray(const C& container, const T* sep = EOL); // compose back the string using the gicen separator
    MapI  void   fromMap(const C& container, const T* sep = SPACE, const T* sepLine = EOL);
    void         fromMap(std::map<T, int>& container, const T* sep = SPACE, const T* sepLine = EOL);
    size_t       indexOf(T c, size_t from = 0, bool bCase = true) const;    // finds the index of the first character starting at zero-based index and going right, return ch index or -1 if not found
    size_t       indexOf(const T* s, size_t from = 0, bool bCase = true) const; // finds the index of the first instance of the substring starting at zero-based index, return substring index or -1 if not found
    size_t       indexOfAny(const T* cList, size_t from = 0, bool bCase = true) const;
    ContC size_t indexOfAny(const C& container, size_t from = 0, bool bCase = true, size_t* idxList = nullptr) const; // find the first instance of the string in the list, return string index or -1 if not found
    size_t       indexOfNot(T c, bool bCase = true) const; // return index of the first character different than c
    CTextT&      insert(size_t from, T c, size_t count = 1);    // insert the character at zero-based index, if index is past end of string 
    CTextT&      insert(size_t from, const T* s);   // insert substring at zero-based index; concatenates, if index is past end of string
    CTextT&      insert(size_t from, size_t count, const T* s); // insert substring at zero-based index, count is the number of max characters to insert
    CTextT<T>    insertAt(const RangeVector& pos, const T* begin, const T* end) const;  //insert given strings at the range beggining and end
    CTextT<T>&   insertAt(const RangeVector& pos, const T* begin, const T* end);
    bool         isAlpha() const;  // return true if contains only alphabeta characters
    bool         isBinary() const; // return true if contains only 0s and 1s
    bool         isEmpty() const; // return true if empty
    bool         isEqual(const T* s, bool bCase = true) const;  //checks if equal to string s, allows case-incensitive comparison
    bool         isHexNumber() const; // return true if contains only hexadecimal digits
    bool         isLower(bool strict = true) const;
    bool         isNumber(bool allowSign = true) const;  // return true if contains only decimal digits
    bool         isPalindrome() const;
    bool         isUpper(bool strict = true) const;
    size_t       hash() const;
    size_t       keep(size_t from, size_t count); //keeps count characters starting from given position, returns number of deleted characters
    size_t       keepEnds(size_t count);  //keeps the middle characters, count characters are removed from both ends, returns number of deleted characters
    size_t       keepLeft(size_t count);  // keeps count characters from left, returns number of deleted characters
    size_t       keepRight(size_t count); // keeps count characters from right, returns number of deleted characters
    T            last() const; //return last character or 0 if empty
    size_t       lastIndexOf(T c, bool bCase = true) const; // find the first character position starting at right, where from is offset from end and the returned idx is from the beggining
    size_t       lastIndexOf(const T* s, bool bCase = true) const; // find the first substring position starting at right, where the returned idx is from the beggining
    size_t       lastIndexOfAny(const T* cList, bool bCase = true) const;   // find the character position starting at right, from - offset from the end to start the search
    size_t       lastIndexOfNot(T c, bool bCase = true) const;
    CTextT       left(size_t count) const;  // return new string containing first count characters 
    size_t       length() const;  // returns the number of characters in our string
    size_t       linesCount(const T* sep = EOL) const;  // returns the number of lines in the string
    size_t       linesPaddRight(T c, size_t len, const T* sep = SeparatorsLine, const T* sepNew = EOL);
    size_t       linesSort(const T* sep = SeparatorsLine, const T* sepNew = EOL);
    size_t       linesTrim(const T* cList, const T* sep = SeparatorsLine, const T* sepNew = EOL);
    CTextT&      limit(size_t maxLen); //makes the the text to be with the given max limit, if text length is smaller nothing is done
    CTextT&      makeUnique();  //make sure that all characters occurs only once
    CTextT&      makeUnique(T c);  // make sure that character c occurs only once, leaves the first one
    CTextT       mid(size_t count);  //leaves the middle characters, count characters are cut from both ends, returns new string
    T            nextChar(size_t pos, const T* sep = Separators) const; // return next character starting at the given position and excluding characters in the list
    bool         nextExcluding(size_t& pos, CTextT& word, bool appendSeparators = false, const T* cList = Separators, size_t* posBegin = nullptr, size_t* posEnd = nullptr) const; //find the next substring not containing any of the characters in the list, if appendSeparators is set the separators will be added at the end
    bool         nextIncluding(size_t& pos, CTextT<T>& substr, const T* cList, size_t* posBegin = nullptr, size_t* posEnd = nullptr) const; //find the next substring containing only any of the characters in the list
    CTextT&      push_back(T c);
    CTextT&      push_back(const T* s);
    CTextT&      push_front(T c);
    CTextT&      push_front(const T* s);
    CTextT&      paddLeft(T c, size_t len);  // fills from start with c characters until lenght "len" size is reached, increase the length and realloc if necessary
    CTextT&      paddRight(T c, size_t len);  // fills with c characters until lenght "len" size is reached
    CTextT&      quote(); // enclose with literals
    void         random(const T* cList, size_t len); // generate random text with size len using character from the list
    void         randomAlpha(size_t len); // generate text containing random alpha upper and lower characters 
    void         randomAlphaNumeric(size_t len); // generate text containing random alphanumeric upper and lower characters 
    void         randomNumber(size_t len);// generate text containing a random integer with the given length
    DefT bool    readFile(const CharT* path); // read a whole text file into our string, note: filepath can be Unicode or ANSI even if CText is defined as char template (CTextA)
    size_t       reduceChain(T c);  //reduces chains of some character to a single instances, for example: replace multiple spaces by one space
    CTextT&      reduceChainAny(const T* cList);
    void         reduceToNumber();  //strip text from non-numbers
    size_t       remove(T c, size_t from = 0); // delete all occurrences of the character stsrting from the zero-bsased index
    size_t       remove(const T* s, bool bCase = true); // delete all occurences of the sub-string s, returns the number of the removed strings s (or 0 if nothing is removed)
    size_t       remove(std::initializer_list<T> cList);
    size_t       removeAny(const T* cList, bool bCase = true);  //delete all of provided in the list characters
   ContS CTextT& removeAny(const C& container, bool bCase = true); //remove any from the provided in the list strings
   CTextT&       removeAny(std::initializer_list<const T*> list, bool bCase = true); 
    CTextT&      removeAt(const RangeVector& pos); //remove from the positions at the provided index arrays
    size_t       removeBlocks(const T* sepBegin, const T* sepEnd);  //removes any block from the strings begining and ending with the given separators
    bool         removeLast();  // removes the last character, return true if not empty and sucessful
    size_t       replace(T cOld, T cNew);   // replace occurrences of the character cOld with cNew, return number of replaced characters
    size_t       replace(const T* what, const T* with, bool bCase = true);// replace all occurrences of substring "what" with substring "with", empty "with" removes all instances of "what", return number of replaced substrings
    CTextT&      replace(size_t from, size_t count, T c); // replace range with sizngle character
    CTextT&      replace(size_t from, size_t count, const T* s);  // replace range with the content of the string (in incrementing order)
    size_t       replaceAny(const T* cOld, T cNew, bool bCase = true); //replace any of the old characters with the new
   ContS CTextT& replaceAny(const C& what, const T c, bool bCase = true);
   ContS CTextT& replaceAny(const C& what, const C& with, bool bCase = true);
   ContS CTextT& replaceAny(const C& what, const T* s, bool bCase = true);
    CTextT&      replaceAny(std::initializer_list<const T*> what, std::initializer_list<const T*> with, bool bCase = true);
    CTextT&      replaceAt(const RangeVector& pos, const T c);
    CTextT&      replaceAt(const RangeVector& pos, const T* with);
    CTextT       replaceAt(const RangeVector& pos, const T* with) const;
   ContS CTextT& replaceAt(const RangeVector& pos, const std::vector<size_t>& indexes, const C& with);
   ContS CTextT  replaceAt(const RangeVector& pos, const std::vector<size_t>& indexes, const C& with) const;
    CTextT&      replaceFirst(T c);
    CTextT&      replaceLast(T c);
    bool         resize(size_t newLen, T c = 0);
    CTextT&      reverse(); // reverse string right-to-left
   ContS CTextT& reverseAny(const C& container, bool bCase = true);
    CTextT<T>&   reverseAt(const RangeVector& pos);  //reverse inplace, in one pass all provided ranges
    const T*     reverseFind(const T* s, bool bCase = true) const;
    CTextT       right(size_t count) const; // return new string with count characters from the end of our string   
    CTextT&      rotateLeft(size_t n); // rotate tne string to the left
    CTextT&      rotateRight(size_t n); // rotate tne string to the right
    CTextT&      shuffle();
    CTextT&      sort(); // per character sort in ascending order
    CTextT       spanIncluding(const T* cList) const;   //  characters from beginning that are also in passed string
    CTextT       spanExcluding(const T* cList) const;   // characters from beginning that are not also in passed string   
    ContS size_t split(C& container, bool appendSeparators = false, const T* sep = Separators) const;  // fills the STL container with the collected substrings
    bool         splitAt(size_t pos, CTextT& first, CTextT& second, bool exclude = false) const;  // split into two strings at the given distance from the left
    bool         splitAtFirst(T ch, CTextT& first, CTextT& second, bool exclude = false) const; // split into two strings at the first occurence of ch or return false, if exclude is false ch goes in the second part, otherwise is omitted
    bool         splitAtFirst(const T* s, CTextT& first, CTextT& second, bool exclude = false, bool bCase = true); // split into two strings at the first occurence of string s or return false, if exclude is false str goes in the second part, otherwise is omitted
    bool         splitAtFirstOfAny(const T* cList, CTextT& first, CTextT& second, bool exclude = false, bool bCase = true); // split into two strings at the first occurence of any character from the list or return false, if exclude is false ch goes in the second part, otherwise is omitted   
    bool         splitAtLast(T ch, CTextT& first, CTextT& second, bool exclude = false) const; // split into two strings at the last occurence of ch or return false, if exclude is false ch goes in the second part, otherwise is omitted
    bool         splitAtLast(const T* s, CTextT& first, CTextT& second, bool exclude = false, bool bCase = true); // split into two strings at the first occurence of string s or return false, if exclude is false ch goes in the second part, otherwise is omitted    
    bool         splitAtLastOfAny(const T* cList, CTextT& first, CTextT& second, bool exclude = false, bool bCase = true); // split into two strings at the last occurence of any character from the list or return false, if exclude is false ch goes in the second part, otherwise is omitted 
    bool         startsWith(T c, size_t from = 0, bool bCase = true) const;  //return true if text starts with character ch at position from
    DefS bool    startsWith(const S& s, size_t from = 0, bool bCase = true) const;  //return true if text starts with string str at position from
    bool         startsWith(std::initializer_list<T> cList);
    DefS bool    startsWithAny(const S& cList, size_t from = 0, bool bCase = true, size_t* idx = nullptr) const;   //return true if starts with any of the provided characters, the optional parameter idx will contain the index of the found character
    ContC bool   startsWithAny(const C& container, size_t from = 0, bool bCase = true, size_t* idx = nullptr) const;
    T*           str();
    const T*     str(size_t from = 0) const; //return pointer to modifiable buffer (valid after C++11)
    CTextT       substring(size_t from, size_t count) const;    // returns a new sub-string with count characters starting at zero-based offset
    CTextT       substringBeforeFirst(T c, bool include = false) const;//same as cutAfterFirst above but return a new CText, by default c is not included
    CTextT       substringBeforeFirst(const T* str) const; //same as cutAfterFirst above but return a new CText object
    CTextT       substringBetween(T cLeft, T cRight, bool include = false);
    CTextT       substringBetween(const T* sLeft, const T* sRight, bool include = false);
    CTextT       substringRight(size_t from) const; // return new string with all characters starting at a zero-based index and continuing to the end
    CTextT       substringLeft(size_t count) const;  // returns new string with count characters from left
  unsigned int   toBinaryNumber(bool& bOk); //if the string contains a binary number, convert it   
  unsigned int   toHexNumber(bool& bOk);  //if the string contains a hex number convert it , "1E" --> 30   
  CTextT<char>   toChars();  // conversion to UTF8 (ANSI)
    double       toDouble(bool& bOk) const;
    int          toInteger(bool& bOk) const;
   unsigned int  toUInteger(bool& bOk) const;
   ContN bool    toArray(C& container, T sep) const; // parse our string to integers array divided by the given separator, can be used to parse CSV of integers
   ContN bool    toMatrix(std::vector<C>& container, T sep,  const T* sepLine = EOL) const;  // parse to matrix
    CTextT&      toLower(); // conversion to lowercase (in place)  
    CTextT&      toUpper(); // conversion to uppercase (in place)
 CTextT<wchar_t> toWChars();  // conversion to Unicode
    CTextT&      trim(const T* cList = Separators);
    CTextT&      trimLeft(const T c); //// remove continuous occurrence of ch starting from left
    CTextT&      trimLeft(const T* cList = Separators);  // remove from left continuous occurrence of all characters from the provided list
    CTextT&      trimRight(const T c); //// remove continuous occurrence of character c, starting from right
    CTextT&      trimRight(const T* cList = Separators); // remove from right continuous occurrence of all characters from the provided list  
    size_t       unenclose(T begin, T end); //opposite of enclose
    size_t       unquote();  //removes literal sign if ends with it
    size_t       wordsCapitalize(const T* sep = Separators);  // make all words in a text start with upper character
    CTextT&      wordsEnclose(const T* sBegin, const T* sEnd, const T* sep = SeparatorsWord);
  ContC CTextT&  wordsEnclose(const T* sBegin, const T* sEnd, const C* start = nullptr, const C* end = nullptr, const C* has = nullptr, const T* sep = SeparatorsWord); //enclose all words using provided block begin and end strings and the given condition
    CTextT&      wordsReverse(const T* sep = Separators);
    CTextT&      wordsSort(const T* sep = Separators, const T* sepNew = SPACE); // words sort in ascending order
    DefT bool    writeFile(const CharT* filePath, EncodingType encoding = ENCODING_UTF8); // write our string to a text file with the given encoding

    // static routines
    static CTextT<T>  Add(const CTextT&, const CTextT&);  // returns the concatenation of the both strings
    static CTextT<T>  Add(const CTextT&, const T*);
    static CTextT<T>  Add(const CTextT&, T c);
    static bool       ArePermutation(const CTextT& a, const CTextT& b);
 ContC static size_t  GeneratePermutations(C& container, CTextT& s);
    static bool       IsPalindrome(const T* s, bool bCase = true, size_t len = std::string::npos);
    static  void      Swap(CTextT& a, CTextT& b);  // exchanges the values of two strings

    // static functions overloads 
    inline static bool       FromChars(const char* s, CTextT& res);
    inline static bool       FromWChars(const wchar_t* s, CTextT& res);
  DefT inline static bool    ReadFile(const CharT* filePath, CTextT& s);
  inline static CTextT<char> ToChars(const T* s);
inline static CTextT<wchar_t>ToWChars(const T* s);
  DefT inline static bool    WriteFile(const CharT* filePath, CTextT& s, EncodingType encoding = ENCODING_UTF8);
    inline static size_t     Vsnprintf(T* s, size_t n, const T * fmt, va_list args);  //encapsulate vsnprintf, return number of characters written

    // static string routines
    static bool     EmptyOrNull(const T* s) { return (s == 0 || *s == 0); }
    static bool     EndsWith(const T* text, const T* str, bool bCase = true, size_t len = std::string::npos);
    static size_t   IndexOf(const T* s, T c, bool bCase = false);
    static bool     IsAlpha(const T* s);
    static bool     IsBinary(const T* s);
    static bool     IsLower(const T* s, bool strict = false);
    static bool     IsHexNumber(const T* s);
    static bool     IsNumber(const T* s, bool allowSign = true);
    static bool     IsOneOf(T c, const T* list, bool bCase = true, size_t* idx = nullptr); //return true if c occurs in the provided 0-terminated characters list, otherwise returns false, idx - optional position in the list
    static bool     IsUpper(const T* s, bool strict = true);
    static size_t   LastIndexOf(const T* str, size_t len, T c, bool bCase = true);
    static size_t   LastIndexOf(const T* str, size_t len, const T* s, bool bCase = true);
    static size_t   Levenshtein(const T *s1, const T *s2);  //calculate Levenshtein distance
    static size_t   HammingDistance(const T *s1, const T *s2);
    static bool     StartsWith(const T* str, const T* s, bool bCase = true, size_t max_len = std::string::npos, size_t* idx = nullptr); //return true if string str starts with the string s,  max_len - max number of chars to check, if idx is different than 0 will provide the length of the text in str which is in the beggining
    static size_t   Strlen(const T* str); //safe strlen, return -1 if str is 0
    static T*       Strcpy(T* dst, const T* src); // (strcpy)
    static T*       Strncpy(T *dst, const T *src, int n); // (strncpy)
    static T*       Strcat(T *dst, const T *src); // (strcat)
    static T*       Strncat(T *dst, const T *src, size_t n); //(strncat)
    static int      Strcmp(const T* p1, const T* p2, bool bCase = true);
    static const T* StrFind(const T* s, const T* text, bool bCase = true);  // (strstr) finds a pointer to the first occurence of text in str, return 0 pointer if not found
    static const T* StrFindCh(const T* s, T c, bool bCase = true);  // (strchr) finds a pointer to the first occurence of a character in the passed string or returns 0 if not found
    static const T* StrFindChAny(const T* s, const T* chList, bool bCase = true); //same as StrFindCh but checks all the character from the list
    static const T* StrFindChNot(const T* s, const T* cList, bool bCase = true); // returns pointer to the first character in string s not contained in the list or 0 if all characters are contained, if list is empty return pointer to the beggining
    static size_t   Strspn(const T* s1, const T* s2);  // (strspn) return length of initial segment of str that consists entirely of characters from s 
    static size_t   Strcspn(const T* s1, const T* s2); // (strcspn) return length of initial segment of str that do not contain any characters from s 
    static size_t   Strrspn(const T* s1, const T* s2); // (strrspn) return length of last segment of str that consists entirely of characters from s 
    static T*       Strrev(T *str);
    static void     Strrev(T* begin, T* end);  //reverse inplace, ABC -> CBA
    static void     Swab(const T* src, T* dst, size_t len);
    static CTextT   Substring(const T* s, size_t from, size_t nCount = 0); // return count characters starting at zero-based offset, return new string
  
    static bool IsAlpha(T c);
    static bool IsAlphanumeric(T c);
    static bool IsDigit(T c);
    static bool IsHex(T c);
    static bool IsLower(T c);
    static bool IsSpace(T c);
    static bool IsUpper(T c);
    static T    lower(T ch);
    static T    upper(T ch);

    typedef T Char;
    typedef std::basic_string<T> tstring;
    static int CharSize() { return sizeof(Char); }
    static bool IsWide() { return CharSize() > 1; }

protected:
    ContS static void Permute(C& container, CTextT& a, size_t l, size_t r);

protected:
    std::basic_string<T>  m_str;

public:
    static const T  CC;                 // control character '\'
    static const T* Slash;              // folder separators (\\,/)
    static const T  Literal;            // symbol "
    static const T* Literals;           // literals symbols ' and "
    static const T* Separators;         // all standard separators ( \r\n\t )
    static const T* SeparatorsWord;     // word separators
    static const T* SeparatorsLine;     // line separators (\r\n)
    static const T* SeparatorsSentence; // sentence separators (.?!)
    static const T* EOL;                // single character \n       
    static const T  TAB;                // single character \t    
    static const T* SeparatorsRow;      // row separators ( \t)
    static const T  HexDigits[16];      // the 16 hexagonal letters 
    static const T* SPACE;              // single character " " 
};

#include "CTextT.inl"
