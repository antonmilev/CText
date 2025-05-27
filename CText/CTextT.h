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
#include <cstring>
#include <algorithm>
#include <regex>
#include "CharTrie.h"

#ifdef _WIN32
#pragma warning(disable : 4996)
#pragma warning(disable : 4702)  // C4702 : unreachable code
#endif

// will be removed when switched completely to C++17
#ifdef _WIN32
#define inline_t 
#elif __GNUC__
// for GCC define static inline to avoid multiple definition errors when this header is 
// included in several translation units
#define inline_t inline
#else
#define inline_t
#endif

#define ContS template<typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_convertible<Val, std::basic_string<T> >::value || std::is_convertible<Val, const T*>::value || std::is_constructible<Val, const T*>::value >  >
#define ContC template<typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_same<Val, T>::value || std::is_convertible<Val, std::basic_string<T> >::value || std::is_convertible<Val, const T* >::value || std::is_constructible<Val, const T*>::value  >>
#define ContST template <typename C, typename Val = typename C::value_type, typename CharT, typename X = std::enable_if_t< std::is_convertible<Val, std::basic_string<T>>::value || std::is_convertible<Val, const T*>::value || std::is_constructible<Val, const T*>::value>, typename Enable = std::enable_if_t< std::is_same<CharT, char>::value || std::is_same<CharT, wchar_t>::value>>
#define ContN template<typename Num, typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_convertible<Val, Num>::value && (std::is_integral<Num>::value || std::is_floating_point<Num>::value) >  >
#define ContB template<typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_same<Val, T>::value || std::is_convertible<Val, std::basic_string<T> >::value || std::is_convertible<Val, const T* >::value || std::is_constructible<Val, const T*>::value || std::is_integral<Val>::value || std::is_floating_point<Val>::value >  >
#define MapI template<typename C, typename Value = typename C::value_type, typename X = std::enable_if_t < std::is_convertible<Value, std::pair<int,CTextT<T>>>::value ||  std::is_convertible<Value, std::pair<int,std::basic_string<T>>>::value, int > >
#define DefN template <typename Num, typename X = std::enable_if_t< std::is_integral<Num>::value || std::is_floating_point<Num>::value>>
#define DefI template <typename Num, typename X = std::enable_if_t< std::is_integral<Num>::value >>
#define DefS template <typename S, typename X = std::enable_if_t < std::is_convertible<std::remove_const_t<std::remove_reference_t<S>>, const T* >::value || std::is_constructible<std::remove_const_t<std::remove_reference_t<S>>, const T*>::value ||  std::is_convertible<S, std::basic_string<T> >::value>>
#define DefT template <typename CharT, typename X = std::enable_if_t< std::is_same<CharT, char>::value || std::is_same<CharT, wchar_t>::value>>

template <typename T>
class CTextT
{
public:
    CTextT();
    CTextT(const std::basic_string<T>& s);
    CTextT(std::basic_string<T>&& s) noexcept;
    CTextT(const T* s);
    CTextT(const T* s, size_t len);
    CTextT(T c, size_t len = 1);
    CTextT(const CTextT& s);
    CTextT(CTextT&& s) noexcept;
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
    CTextT& operator=(CTextT&& s) noexcept;
    CTextT& operator=(const std::basic_string<T>& s);
    CTextT& operator=(std::basic_string<T>&& s) noexcept;
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
    friend CTextT operator+(const T* str, const CTextT& string)              { return Add(str, string); }
    friend CTextT operator+(const CTextT& string, T ch)                      { return Add(string, ch); }
    friend CTextT operator+(T ch, const CTextT& string)                      { return Add(ch, string); }

    const CTextT& operator+=(const T* str);
    const CTextT& operator+=(const CTextT& string);
    const CTextT& operator+=(T ch);

    CTextT& operator<<(const T* s);
    CTextT& operator<<(const std::basic_string<T>& s);
    CTextT& operator<<(const T c);
    CTextT& operator<<(const CTextT& s)  ;
    DefI CTextT& operator << (Num i);  // integral types
    CTextT& operator << (double f);  // float types

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

	bool		 addToFileName(const T* s); //modifies a filename, adds the provided string to file name but keeps extension and path
    bool         alloc(size_t len);
    CTextT&      append(const CTextT& s);
    CTextT&      append(const T* s); // append string
    CTextT&      append(const T* s, size_t len); // append part of a string
    CTextT&      append(T c, size_t count = 1); //append characters
    CTextT&      append(std::initializer_list<T> cList); // append the characters in the list
    CTextT&      append(std::initializer_list<const T*> sList); // append characters in the list
 ContC CTextT&   append(const C& container);  // append single character or string buffer, supports all value-type STL containers 
    CTextT&      appendRange(T cBegin, T cEnd);  // append all characters in the range 
    bool         between(T cLeft, T cRight, bool include = false); // keeps the part of the string between the first and last characters cLeft and cRight (by default separators are not included)
    bool         between(const T* sLeft, const T* sRight, bool include = false); // keeps the part of the string between the first and last sub-strings sLeft and sRight (by default separattors are not included)
    size_t       capacity() const;
    bool         checkBalance(const T* sepBegin, const T* sepEnd); // checks if the blocks defined with the given separators are balanced
    void         clear(bool bRelease = false);  // clear content (but does not release string memory)
    ContS size_t collect(C& container, const T* cList) const;  // fill the container with substrings containing only characters from the list
    ContS size_t collectBlocks(C& container, const T* sepBegin, const T* sepEnd, bool all = false, const T* sep = Separators) const;
    ContS size_t collectLines(C& container, bool appendSeparators = false, const T* sep = SeparatorsLine) const;  // fills a STL container with the collected lines
    ContS size_t collectSentences(C& container, const T* sep = SeparatorsSentence, const T* sepWords = Separators) const;
    ContS size_t collectSubstrings(C& container, const C* start = nullptr, const C* end = nullptr, const C* contain = nullptr, const T* sep = Separators) const;  // fill the container with the found substrings after applying the conditions 
    ContS size_t collectWords(C& container, const T* sep = SeparatorsWord) const;  // fill container with all found words
    int          compare(const T* s, bool bCase = true) const; // return - 0 equal. -1 p1 < p2, or 1 - p1 > p2
    bool         contain(T c, bool bCase = true) const;  // returns true if our string contains character c
    bool         contain(const T* s, bool bCase = true) const; // returns true if our string contains another string  
    bool         containAny(std::initializer_list<T> cList); // returns true if our string contains any of the characters of the list
    ContS bool   containAny(const C& container, bool bCase = true, bool useTrie = false) const;  // returns true if contains any of the strings provided by the container
    bool         containAny(const T* cList, bool bCase = true) const; // returns true if our string contains any of the characters of the list
    bool         containOnly(const T* cList, bool bCase = true) const; // returns true if our string contains only characters from the list   
    bool         contain(const T c, size_t from, size_t to) const; // search in range
	void	     copyTo(T* s);  //copy the string data to the external buffer (should be large enough)
    void	     copyTo(T* s, size_t max_len); //copy the string data to the external buffer (should be large enough)
    size_t       count(T c, size_t from = 0) const;  //returns the count of occurences of the given character
    size_t       count(const T* s, bool bCase = false) const;  //returns the count of occurences of the given substring
    size_t       countAny(const T* cList, size_t from = 0) const;  //returns the count of occurences of any of the characters in the list
    size_t       countChains(T c) const;  // return count of blocks containing only character c (chains)
    size_t       countChainsAny(const T* cList) const;  // return count of blocks containing only of the characters in the list
    size_t       countChars(std::map<T, int>& container, bool bCase = true) const; // fill the map container with character counts
    size_t       countSubstrings(const T* sep) const; // return number of found substrings divided by sep
    DefS size_t  countWordFrequencies(std::vector < std::pair<int, S > > & container, bool bCase = true, const T* sep = SeparatorsWord) const;
    DefS size_t  countWordFrequencies(std::multimap < int, S, std::greater<int>> & container, bool bCase = true, const T* sep = SeparatorsWord) const;
    //MapI size_t  countWordFrequencies(C& container, bool bCase = true, const T* sep = SeparatorsWord) const; // fill the container with the words frequency counts
    size_t       countUnique(const T* cList, size_t from = 0, size_t to = std::string::npos);
    CTextT&      cutAfterFirst(T c, bool include = false, bool bCase = true); //leaves everyting left from c, c is not included, everything after is removed
    CTextT&      cutAfterFirst(const T* s, bool include = false, bool bCase = true); // same as above but perfomed over zero-teminated string, s is not included
    CTextT&      cutAfterFirstOfAny(const T* cList, bool include = false, bool bCase = true); //cut after the first occurence of any character from the list 
    CTextT&      cutAfterLast(T c, bool include = false, bool bCase = true); //leaves everyting left from the last character, c is not included
    CTextT&      cutAfterLast(const T* s, bool include = false, bool bCase = true); // leaves everyting left from last s, s is not included
    CTextT&      cutAfterLastOfAny(const T* cList, bool include = false, bool bCase = true); // leaves everyting left from last ch in the list, ch is not included
    CTextT&		 cutBeforeFirst(T c, bool include = false, bool bCase = true); //leaves everyting after first c, include - c is included
    CTextT&		 cutBeforeFirst(const T* s, bool include = false, bool bCase = true); //cut everything before the first occurence of string str, include - s is included
    CTextT&      cutBeforeFirstOfAny(const T* cList, bool include = false, bool bCase = true);  //cut everything before the first occurence of any character from the list or leave intact, include - c is included
    CTextT&      cutEnds(size_t count); //remove count of characters from left and right
    CTextT&      cutEnds(size_t fromLeft, size_t fromRight);  //cut number of charcters from left and right
    CTextT&      cutLeft(size_t count);  //removes count characters from left
    CTextT&      cutRight(size_t count); //cut number of characters from right, if count is too big empty the string
    CTextT&		 enclose(T c);  // enclose with same character
    CTextT&      enclose(T begin, T end, bool checkEnds = true); //enclose with the provided character separators (if not already ends and begins with them)
    CTextT&      enclose(const T* begin, const T* end, bool checkEnds = true); //enclose with the provided text separators (if not already ends and begins with them)
    CTextT&      equal(const CTextT& s);  // make our string equal to str
    CTextT&      equal(const T* s);  // make equal to str
    CTextT&      equal(T c, size_t len);  // init with len number of ch
    CTextT&      equal(const T* s, size_t len, size_t offset = 0);  // init to len characters from string at offset   
    bool         endsWith(T c, size_t from = 0, bool bCase = true) const;
    DefS bool    endsWith(const S& s, size_t from = 0, bool bCase = true) const; // return true if ends with the provided string
    bool         endsWith(std::initializer_list<T> cList);
    bool         endsWithAny(const T* cList, bool bCase = true) const;
    ContS bool   endsWithAny(const C& list, size_t from = 0, bool bCase = true, bool useTrie = false, size_t* idx = nullptr) const;  //returns true if end with any of the provided strings
    size_t       erase(size_t from, size_t count = 1);  // delete count characters starting at zero-based index
	const T*     find(const T c, bool bCase = true) const;// return a pointer to the first occurence of the character, or 0 pointer if not found
    const T*     find(const T *s, bool bCase = true) const; // return a pointer to the first occurence of the string, or 0 pointer if not found
    size_t       findBlockPositions(const T* sepBegin, const T* sepEnd, std::vector< std::pair<size_t, size_t>>& pos, bool bCase = true) const; //find begin/end positions of all blocks beggining and ending with the given separators
    size_t       findPositions(RangeVector& pos, size_t skip, bool appendSeparators = false, const T* sep = SeparatorsLine) const;
    ContS size_t findPositions(const C& start, RangeVector& pos, bool bCase = true, bool useTrie = false, std::vector<size_t>* indexes = nullptr) const;
    ContS size_t findPositions(RangeVector& pos, const C* start, const C* end, const C* has, const T* sep) const;    
    size_t       findLinePositions(RangeVector& pos, size_t skip = 1, bool appendSeparators = false, const T* sep = SeparatorsLine) const;
    size_t       findWordPositions(RangeVector& pos, size_t skip = 1, const T* sep = SeparatorsWord) const;
    ContS size_t findWordPositions(const C& list, RangeVector& pos, bool bCase, const T* sep = SeparatorsWord, std::vector<size_t>* indexes = nullptr) const;
    T            first() const; //return first character or 0 if empty
    bool         format(const T* format, ...);
    DefN bool    fromBinary(Num i);  // create a binary string from the number
    DefI bool    fromInteger(Num i, bool append = false, int padd = 0, T paddValue = T('0')); // convert the decimal integer to string
    bool         fromHex(const T* s); // reverse of toHex, text "48 65 6C 6C 6F 20 57 6F 72 6C 64" --> "HelloWorld" 
    DefN bool    fromHexNumber(Num i, bool hasBase = true, bool upper = false, bool append = false); // create a hexadecimal string from the number
    bool         fromDouble(double d, int precision = 6, bool fixed = true, bool nozeros = false, bool append = false);
    void         fromSingle(const char* s);  // init with single-char ANSI string, make string -> wstring convert if necessary
    void         fromWide(const wchar_t* s);  // init with UNICODE string, make wstring -> string convert if necessary
    bool         fromTChars(const char * s);
    bool         fromTChars(const wchar_t * s);
 ContS CTextT&   fromArray(const C& container, const T* sep = SPACE); // compose back the string using the given separator, if asHex is set will convert values in the array to hex strings
 ContN CTextT&   fromArray(const C& container, bool asHex = false, size_t wHex = 2, const T* sep = SPACE); // compose a string from array using the given separator, if asHex is set will convert values in the array to hex strings
  DefI CTextT&   fromArray(const Num* buf, size_t len, bool asHex = false, size_t w = 2, const T* sep = SPACE);   //  array {1,2,3} will create text filled with  "1 2 3", if hex flag is set, {10,20,30} will be converted as "A 14 1E"
  DefI CTextT&   fromBytes(const Num* buf, size_t len, int lineSize = 0, bool asHex = false, size_t wHex = 2, const T* sep = SPACE);   //  array {1,2,3} will create text filled with "1 2 3", if hex flag is set, {10,20,30} will be converted as "A 14 1E", lineSize - if >0 then the text will be multiline with the given max line size
 ContN CTextT&   fromChars(const C& container); // append back values in the container (interpret as characters type T)
  MapI CTextT&   fromMap(const C& container, const T* sep = SPACE, const T* sepLine = EOL);
  CTextT&        fromMap(std::map<T, int>& container, const T* sep = SPACE, const T* sepLine = EOL);
  DefN CTextT&   fromMatrix(const Num* buf, size_t w, size_t h, bool asHex = false, size_t wHex = 2, const T* sep = SPACE, const T* sepLine = EOL);  //compose string from a 2D numerical matrix
    CTextT		 getDir(); // get a folder from a full module path
    const T*	 getExtension() const;   //if our string contains file path, return pointer to the extension, will return 0 if empty or extension not found!, dot is included
    const T*	 getFileName() const;  //if our string contains file path, return pointer to the file name, will return 0 if empty or file name not found!!!!
    size_t       indexOf(T c, size_t from = 0, bool bCase = true) const;    // finds the index of the first character starting at zero-based index and going right, return ch index or -1 if not found
    size_t       indexOf(const T* s, size_t from = 0, bool bCase = true) const; // finds the index of the first instance of the substring starting at zero-based index, return substring index or -1 if not found
    size_t       indexOfAny(const T* cList, size_t from = 0, bool bCase = true) const;
    ContS size_t indexOfAny(const C& list, size_t from = 0, bool bCase = true, bool useTrie = false, size_t* idxList = nullptr) const; // find the offset of the first instance of the strings in the list, return string index or -1 if not found
    size_t       indexOfNot(T c, size_t from = 0, bool bCase = true) const; // return index of the first character different than c
    size_t	     indexOfNotAny(const T* cList, size_t from = 0, bool bCase = true) const; // return index of the first character not included also in the passed list
    CTextT&      insert(size_t from, T c, size_t count = 1);    // insert the character at zero-based index, if index is past end of string 
    CTextT&      insert(size_t from, const T* s);   // insert substring at zero-based index; concatenates, if index is past end of string
    CTextT&      insert(size_t from, size_t count, const T* s); // insert substring at zero-based index, count is the number of max characters to insert
    CTextT<T>    insertAt(const RangeVector& pos, const T* begin, const T* end) const;  //insert given strings at the range beggining and end
    CTextT&      insertAt(const RangeVector& pos, const T* begin, const T* end);
    size_t       insertAtBegin(const T* s, size_t skip = 1, const T* sep = Separators);
    size_t       insertAtEnd(const T* s, size_t skip = 1, const T* sep = Separators);
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
    CTextT&      keep(size_t from, size_t count); //keeps count characters starting from given position, returns number of deleted characters
    size_t       keepEnds(size_t count); //keeps the middle characters, count characters are removed from both ends, returns number of deleted characters
    CTextT&      keepLeft(size_t count); // keeps count characters from left and removes the rest, returns number of deleted characters
    size_t       keepRight(size_t count); // keeps count characters from right and removes the rest, returns number of deleted characters
    T            last() const; //return last character or 0 if empty
    size_t       lastIndexOf(T c, size_t from = 0, bool bCase = true) const; // find the first character position starting at right, where from is the offset from the end and the returned idx is from the beggining
    size_t       lastIndexOf(const T* s, size_t from = 0, bool bCase = true) const; // find the first substring position starting at right, where the returned idx is from the beggining
    size_t       lastIndexOfAny(const T* cList, size_t from = 0, bool bCase = true) const;   // find the character position starting at right, from - offset from the end to start the search
    size_t       lastIndexOfNot(T c, bool bCase = true) const;
    CTextT       left(size_t count) const;  // return new string containing first count characters 
 inline size_t   length() const;  // returns the number of characters in our string
    size_t       linesCount(const T* sep = EOL) const;  // returns the number of the lines in the string
    size_t       linesCutAfterLast(const T* s, bool bAny = false, const T* sep = SeparatorsLine);
    size_t       linesCutBeforeLast(const T* s, bool bAny = false, const T* sep = SeparatorsLine);
    size_t       linesCutAfterFirst(const T* s, bool bAny = false, const T* sep = SeparatorsLine);
    size_t       linesCutBeforeFirst(const T* s, bool bAny = false, const T* sep = SeparatorsLine);
    size_t	     linesCutNCharsFromBegin(size_t n_chars, const T* sep = SeparatorsLine);
    size_t	     linesCutNCharsFromEnd(size_t n_chars, const T* sep = SeparatorsLine);
    size_t       linesInsertAtBegin(const T* s, size_t skip = 1, const T* sep = SeparatorsLine);
    size_t       linesInsertAtEnd(const T* s, size_t skip = 1, const T* sep = SeparatorsLine);  // append text to lines end
    size_t       linesPaddRight(T c, size_t len, const T* sep = SeparatorsLine, const T* sepNew = EOL);
    size_t       linesSort(const T* sep = SeparatorsLine, const T* sepNew = EOL);
    size_t		 linesRemoveEmpty(size_t minLen = 0, const T* sep = SeparatorsLine); // remove empty lines (containing only white spaces)
    size_t       linesTrim(const T* cList, const T* sep = SeparatorsLine, const T* sepNew = EOL);
    CTextT&      limit(size_t maxLen); //limit the the length, if our text length is smaller nothing is done
    size_t       makeUnique();  //make sure that all characters occurs only once
    size_t       makeUnique(T c);  // make sure that character c occurs only once, leaves the first one
    CTextT&      makeUniqueAny(const T* cList); // make sure that any character from the list occurs only once, leaves the first one
    CTextT       mid(size_t count);  //leaves the middle characters, count characters are cut from both ends, returns new string
    T            nextChar(size_t pos, const T* sep = Separators) const; // return next character starting at the given position and excluding characters in the list
    bool         nextExcluding(size_t& pos, size_t& start, size_t& count, bool appendSeparators = false, const T* cList = Separators) const; //find the next substring not containing any of the characters in the list, if appendSeparators is set the separators will be added at the end
    bool         nextIncluding(size_t& pos, size_t& start, size_t& count, const T* cList) const; //find the next substring containing only any of the characters in the list
    bool         nextBlock(size_t& pos, size_t& start, size_t& count, const T* cListBegin, const T* cListEnd) const;
    bool         nextLine(size_t& pos, CTextT<T>& line, bool appendSeparators = false, const T* sep = SeparatorsLine) const;
 DefS bool       nextWord(size_t& pos, S& word, const T* sep = SeparatorsWord) const;
    bool		 pathCombine(const T* path);  //assumes that this contains path,  "C:\Temp" + "..\Folder" = "C:\Folder", no check if both paths are valid or absolute!
    CTextT&      push_back(T c);
    CTextT&      push_back(const T* s);
    CTextT&      push_front(T c);
    CTextT&      push_front(const T* s);
    CTextT&      paddLeft(T c, size_t len);  // fills from start with c characters until lenght "len" size is reached, increase the length and realloc if necessary
    CTextT&      paddRight(T c, size_t len);  // fills with c characters until lenght "len" size is reached
    CTextT&      quote(); // enclose with literals
    CTextT&      random(const T* cList, size_t len); // generate random text with size len using character from the list
    CTextT&      randomAlpha(size_t len = 32); // generate text containing random alpha upper and lower characters 
    CTextT&      randomAlphaNumeric(size_t len = 32); // generate text containing random alphanumeric upper and lower characters 
    CTextT&      randomNumber(size_t len = 10);// generate text containing a random integer with the given length
    DefT bool    readFile(const CharT* path, bool asHex = false); // read a whole text file into our string, note: filepath can be Unicode or ANSI even if CText is defined as char template (CTextA)
    bool         readLinesFromFile(const T* path, size_t lineStart, size_t lineEnd); // read only number of lines, can be used for very large files
    size_t       reduceChain(T c);  //reduces chains of some character to a single instances, for example: replace multiple spaces by one space
    CTextT&      reduceChainAny(const T* cList = Separators);
    CTextT&      reduceChain(const T* cList = SeparatorsWord, T cNew = *SPACE); // replace blocks of all separators from the list
    void         reduceToNumber();  //strip text from non-numbers
    bool         regexMatch(const T* regexp) const;  // test our string with the provided Regex expression
    bool         regexMatch(const T* regexp, size_t from, size_t count = std::string::npos) const;  // test our string with the provided Regex expression
    size_t       regexCollectPositions(RangeVector& pos, const T* regexp, const T* sep = SeparatorsLine) const;
    size_t       regexCollectLinesPositions(RangeVector& pos, const T* regexp, const T* sep = SeparatorsLine) const;
    size_t       regexCollectWordsPositions(RangeVector& pos, const T* regexp, const T* sep = SeparatorsWord) const;
   ContS size_t  regexCollectLines(C& container, const T* regexp, const T* sep = SeparatorsLine) const; // collect all lines matching the regex
   ContS size_t  regexCollectWords(C& container, const T* regexp, const T* sep = SeparatorsWord) const; // collect all words matching the regex
   ContS size_t  regexSearch(C& container, const T* regexp) const; // collect substrings using the provided Regex expression and regex_iterator
   CTextT        regexReplace(const T* regexp, const T* fmt) const;  // replace strings matching the provided Regex expression
   CTextT&       regexReplace(const T* regexp, const T* fmt) ;  // replace strings using the provided Regex expression
    size_t       remove(T c, size_t from = 0); // delete all occurrences of the character stsrting from the zero-bsased index
    size_t       remove(const T* s, bool bCase = true); // delete all occurences of the sub-string s, returns the number of the removed strings s (or 0 if nothing is removed)
    size_t       remove(std::initializer_list<T> cList);
    size_t       removeAny(const T* cList, bool bCase = true);  //delete all of provided in the list characters
   ContS size_t  removeAny(const C& container, bool bCase = true, bool useTrie = false); //remove any from the provided in the list strings
    size_t       removeAny(std::initializer_list<const T*> list, bool bCase = true);
    CTextT&      removeAt(const RangeVector& pos); //remove from the positions at the provided index arrays
    size_t       removeBlocks(const T* sepBegin, const T* sepEnd);  //removes any block from the strings begining and ending with the given separators
    bool		 removeAfterSlash(bool bRetNoneEmpty = true);  //removes everything after the last slash (slash is also removed), if bRetNoneEmpty is false zeroes the string if it does not contain slash
    bool		 removeExtension();  //remove the extension from a file path
    bool		 removeFileName(bool keepSlash = true); // if our string contain file path, remove the file name, return true on success
    bool         removeLast();  // removes the last character, return true if not empty and sucessful
    bool		 removeWhileBegins(const T* str);  //remove characters from str while equals to characters from m_str
    bool		 removeWhileEnds(const T* str);  //remove characters from str end while equals to characters from the m_str, starting from end
    size_t       replace(T cOld, T cNew);   // replace occurrences of the character cOld with cNew, return number of replaced characters
    size_t       replace(const T* what, const T* with, bool bCase = true);// replace all occurrences of substring "what" with substring "with", empty "with" removes all instances of "what", return number of replaced substrings
    CTextT&      replace(size_t from, size_t count, T c); // replace range with sizngle character
    CTextT&      replace(size_t from, size_t count, const T* s);  // replace range with the content of the string (in incrementing order)
    size_t       replaceAny(const T* cList, T c, bool bCase = true); //replace any of the old characters with a new single character
    size_t       replaceAny(const T* cList1, const T* cList2, bool bCase = true);
   ContS CTextT& replaceAny(const C& what, const T c, bool bCase = true, bool useTrie = false);  // replace strings from the list with single character
   ContS CTextT& replaceAny(const C& what, const C& with, bool bCase = true, bool useTrie = false);  // replace found strings in list 'what' with corresponding strings in list 'with'
   ContS CTextT& replaceAny(const C& what, const T* s, bool bCase = true, bool useTrie = false);
    CTextT&      replaceAny(std::initializer_list<const T*> what, std::initializer_list<const T*> with, bool bCase = true);
    CTextT&      replaceAt(const RangeVector& pos, const T c);
    CTextT&      replaceAt(const RangeVector& pos, const T* with);
    CTextT       replaceAt(const RangeVector& pos, const T* with) const;
   ContS CTextT& replaceAt(const RangeVector& pos, const std::vector<size_t>& indexes, const C& with);
   ContS CTextT  replaceAt(const RangeVector& pos, const std::vector<size_t>& indexes, const C& with) const;
   CTextT<T>&    replaceControlCharacters();
    bool		 replaceExtension(const T* newExt); //will change the file name or file path extension
    bool		 replaceFileName(const T* newFileName); //change the filename in a path but leaves the extension, our string must contain valid path 
    bool         replaceLastFolder(const T* newFolderName); // having a file path like "c:/folder/file.txt" changes it to  "c:/folder2/file.txt", if there is no last folder like "c:/file.txt" again converts to "c:/folder2/file.txt"
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
    size_t	     sscanf(size_t& pos, const T *fmt, ...);
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
    bool         startsWith(T c, size_t from = 0, bool bCase = true, size_t * count = nullptr) const;  //return true if text starts with character ch at position from
    DefS bool    startsWith(const S& s, size_t from = 0, bool bCase = true, size_t * count = nullptr) const;  //return true if text starts with string str at position from
    bool         startsWith(std::initializer_list<T> cList);
    DefS bool    startsWithAny(const S& cList, size_t from = 0, bool bCase = true, size_t* idx = nullptr, size_t* count = nullptr) const;   //return true if starts with any of the provided characters, the optional parameter idx will contain the index of the found character
    ContS bool   startsWithAny(const C& container, size_t from = 0, bool bCase = true, bool useTrie = false, size_t* idx = nullptr, size_t* count = nullptr) const;
inline T*        str(); // return modiable chars buffer 
inline const T*  str(size_t from = 0) const; //return pointer to modifiable buffer (valid after C++11)
    CTextT       substring(size_t from, size_t count) const;    // returns a new sub-string with count characters starting at zero-based offset
    CTextT       substringBeforeFirst(T c, bool include = false) const;//same as cutAfterFirst above but return a new CText, by default c is not included
    CTextT       substringBeforeFirst(const T* str) const; //same as cutAfterFirst above but return a new CText object
    CTextT       substringBetween(T cLeft, T cRight, bool include = false);
    CTextT       substringBetween(const T* sLeft, const T* sRight, bool include = false);
    CTextT       substringRight(size_t from) const; // return new string with all characters starting at a zero-based index and continuing to the end
    CTextT       substringLeft(size_t count) const;  // returns new string with count characters from left
    void		 terminatePath(); //makes sure that path ends with slash
  unsigned int   toBinary(bool& bOk); //if the string contains a binary number, convert it   
  bool           toHex(const T* sep = SPACE);  // convert string to hex values, "Hello World" ---> "48 65 6C 6C 6F 20 57 6F 72 6C 64"
  unsigned int   toHexNumber(bool& bOk);  //if the string contains a hex number convert it , "1E" --> 30  
    double       toDouble(bool& bOk) const;
    int          toInteger(bool& bOk) const;
   unsigned int  toUInteger(bool& bOk) const;
   ContN bool    toArray(C& container, T sep = *SPACE, bool asHex = false) const; // parse our string to integers array divided by the given separator, can be used to parse CSV of integers, if asHex is set expects our string to contain hexadecimal values
   DefN bool     toArray(Num* arr, size_t& n, T sep, bool asHex = false) const;  // if arr is null will set n to the number of found values, will return 0 on failure, if asHex is set expects our string to contain hexadecimal values
   DefN bool     toArray(size_t& pos, Num* arr, size_t n, const T* sep = SeparatorsWord) const;
    size_t       toBytes(unsigned char* buf, size_t maxlen) const; // just getting the internal string buffer as bytes
   ContN bool    toChars(C& container, bool asHex = false) const; // fill the container with single characters 
   DefN size_t   toHexBytes(Num* buf, size_t maxlen) const;  // interpret the string as containing hex bytes, skips standard separators, "1A2B3C4D5E6F" ---> {26, 43, 60, 77, 94, 111}
    CTextT&      toLower(); // conversion to lowercase (in place) 
   ContN bool    toMatrix(std::vector<C>& container, T sep, const T* sepLine = EOL) const;  // parse to matrix
   DefN bool     toMatrix(Num* arr, size_t& w, size_t& h, T sep = *SPACE, const T* sepLine = EOL); // parse to matrix buffer, if arr is null will fill the w and h values
   DefN bool     toMatrix(size_t& pos, Num* arr, size_t w, size_t h, const T* sep = SeparatorsWord, const T* sepLine = SeparatorsLine);
    CTextT&      toUpper(); // conversion to uppercase (in place)
 CTextT<char>    toSingle();  // conversion to UTF8 (ANSI)
 CTextT<wchar_t> toWide();  // conversion to Unicode
    CTextT&      trim(const T* cList = Separators); // trim string from both sides
    CTextT&      trimLeft(const T c); //// remove continuous occurrence of ch starting from left
    CTextT&      trimLeft(const T* cList = Separators);  // remove from left continuous occurrence of all characters from the provided list
    CTextT&      trimRight(const T c); //// remove continuous occurrence of character c, starting from right
    CTextT&      trimRight(const T* cList = Separators); // remove from right continuous occurrence of all characters from the provided list  
    size_t       unenclose(T begin, T end); //opposite of enclose
    void		 unterminatePath(); //makes sure that path do not ends with slash
    size_t       unquote();  //removes literal sign if ends with it
    CTextT<T>&   wordsCapitalize(const T* sep = Separators);  // make all words in a text start with upper character
    size_t       wordsCount(const T* sep = SeparatorsWord) const; // return number of the found words divided by sep
    CTextT&      wordsEnclose(const T* sBegin, const T* sEnd, const T* sep = SeparatorsWord);  // enclose all words
  ContS CTextT&  wordsEnclose(const T* sBegin, const T* sEnd, const C* begin = nullptr, const C* end = nullptr, const C* has = nullptr, const T* sep = SeparatorsWord); //enclose all words using provided block begin and end strings and the given condition
    size_t       wordsInsertAtBegin(const T* s, const T* sep = SeparatorsWord);
    size_t       wordsInsertAtEnd(const T* s, const T* sep = SeparatorsWord);
  ContS CTextT&  wordsRemove(const C* begin = nullptr, const C* end = nullptr, const C* has = nullptr, const T* sep = SeparatorsWord); //remove all words using provided block begin and end strings and the given condition
  ContS CTextT&  wordsReplace(const C& list, const T* with, bool bCase = true, const T* sep = SeparatorsWord);  // replace whole words matching the list
  ContS CTextT&  wordsReplace(const C& what, const C& with, bool bCase = true, const T* sep = SeparatorsWord);  // replace whole words matching the list with words from another list
  ContS CTextT&  wordsReplaceWithChar(const C& list, const T c, bool bCase = true, const T* sep = SeparatorsWord);  //"replace all found words from the list with a single character
    size_t       wordsReverse(const T* sep = Separators); // reverse words inplace
    CTextT&      wordsSort(const T* sep = Separators, const T* sepNew = SPACE); // sort text words in ascending order
  DefT bool      writeFile(const CharT* filePath, int encoding = ENCODING_UTF8, bool asHex = false); // write our string to a text file with the given encoding

    // static routines
    static CTextT<T>  Add(const CTextT&, const CTextT&);  // returns the concatenation of the both strings
    static CTextT<T>  Add(const CTextT&, const T*);
    static CTextT<T>  Add(const T*, const CTextT&);
    static CTextT<T>  Add(const CTextT&, T c);
    static CTextT<T>  Add(T c, const CTextT<T>& str);
    static bool       ArePermutation(const CTextT& a, const CTextT& b);
    static CTextT<T>  GetDir(const T* path);
    ContC static size_t  GeneratePermutations(C& container, CTextT& s);
    static bool       IsPalindrome(const T* s, bool bCase = true, size_t len = std::string::npos);
    static void       SplitPath(const T* path, CTextT& drv, CTextT& dir, CTextT& name, CTextT& ext);
    static const T*   SkipSpaces(const T* str, const T* sep = Separators);
    static  void      Swap(CTextT& a, CTextT& b);  // exchanges the values of two strings
  DefT static bool    ReadFileAsHex(const CharT* filePath, CTextT& s);
    static int        ToHex(T c, bool& bOk);  // 'a' --> 10
  DefT static bool    WriteFileAsHex(const CharT* filePath, CTextT& s);

    // static functions overloads 
    static size_t            CopyAsTchar(const char* str, T* tstr, size_t max_len);
    inline static CTextT     FromSingle(const char* s);
    inline static CTextT     FromWide(const wchar_t* s);
  DefT inline static bool    ReadFile(const CharT* filePath, CTextT& s);
 ContST static size_t        ReadLinesFromFile(const CharT* filePath, C& container, const T* sep = SeparatorsLine);  // read lines from a text file into a container
inline static CTextT<char>   ToSingle(const T* s);
inline static CTextT<wchar_t>ToWide(const T* s);
   DefT static bool          WriteFile(const CharT* filePath, const T* s, EncodingType encoding = ENCODING_UTF8);
    inline static size_t     Vsnprintf(T* s, size_t n, const T * fmt, va_list args);  //encapsulate vsnprintf, return number of characters written
           static size_t     Vsscanf(const T*&  buf, const T *s, va_list ap);

    // static string routines
    static bool	    atoi(int* vp, const T *str, int base);
    static bool     Contain(const T* text, const T* str, bool bCase = true);
    static bool     EmptyOrNull(const std::basic_string<T>& s) { return s.length() == 0 ; }
    static bool     EmptyOrNull(const T* s) { return (s == 0 || *s == 0); }
    static bool     EndsWith(const T* text, const T* str, bool bCase = true, size_t len = std::string::npos);
    static const T* GetExtension(const T* path);
    static const T* GetExtension(const T* path, size_t len);  // if string contains file path return pointer to its extension (include dot), if no extension or empty string return nullptr 
    static const T* GetFileName(const T* path); // if string contains file path return pointer to the file or last folder name, if no filename found return 0
    static const T* GetFileName(const T* path, size_t len);
    static size_t   IndexOf(const T* s, T c, bool bCase = false);
    static size_t	IndexOfFirstDiff(const T *str1, const T *str2);  // finds the offset from beginning of first character where str1 and str2 are different
    static size_t   IndexOfLastDiff(const T *str1, const T *str2); // finds the offset from beginning of first character where str1 and str2 are different, start search from strings ends
    static bool     IsAlpha(const T* s);
    static bool     IsBinary(const T* s);
    static bool     IsLower(const T* s, bool strict = false);
    static bool     IsDouble(const T* str, bool allowTrim = true, const T* sep = Separators);
    static bool     IsHexNumber(const T* s);
    static bool     IsNumber(const T* s, bool allowSign = true);
    static bool     IsOneOf(T c, const T* list, bool bCase = true, size_t* idx = nullptr); //return true if c occurs in the provided 0-terminated characters list, otherwise returns false, idx - optional position in the list
    static bool     IsUpper(const T* s, bool strict = true);
    static size_t   LastIndexOf(const T* str, size_t len, T c, bool bCase = true);
    static size_t   LastIndexOf(const T* str, size_t len, const T* s, bool bCase = true);
    static size_t   Levenshtein(const T *s1, const T *s2);  //calculate Levenshtein distance
    static size_t   HammingDistance(const T *s1, const T *s2);  //calculate Hamming distance
    static size_t	Sscanf(const T* & buf, const T *fmt, ...);
    static bool     StartsWith(const T* str, const T* s, bool bCase = true, size_t max_len = 0, size_t* count = nullptr); //return true if string str starts with the string s,  max_len - max number of chars to check, if count is different than 0 will provide the length of the search text 
DefS static size_t  Strlen(const S& s) { return s.length();  }
    static size_t   Strlen(const T* s); //safe strlen, return -1 if str is 0
    static T*       Strcpy(T* dst, const T* src); // (strcpy)
    static T*       Strncpy(T *dst, const T *src, size_t n); // (strncpy)
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
    static size_t   ToByteArrayFromHexString(const T* s, unsigned char* arr, size_t max_len);  //"00141E32" will return 4 and set the bytes array to {0,20,30,50}, on error will return -1, TODO - max len
DefN static bool    ToArray(const T* str, Num* arr, size_t& n, T sep = *SPACE, bool asHex = false);
    static const T* ToStr(const CTextT<T>& s) { return s.str(); }
    static const T* ToStr(const std::basic_string<T>& s) { return s.c_str(); }
    static const T* ToStr(const T* s) { return s; } ; //safe strlen, return -1 if str is 0

    static bool IsAlpha(T c);
    static bool IsAlphanumeric(T c);
    static bool IsDigit(T c);
    static bool IsFormating(T c);  // return true if EOL, TAB or SPACE
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
    ContS static CharTrie BuildTrie(C& container, bool bCase = true, bool reverse = false);


protected:
    std::basic_string<T>  m_str;

public:
    static inline_t const T  CC;                 // control character '\'
    static inline_t const T* Slash;              // folder separators (\\,/)
    static inline_t const T  Literal;            // symbol "
    static inline_t const T* Literals;           // literals symbols ' and "
    static inline_t const T* Separators;         // all standard separators ( \r\n\t )
    static inline_t const T* SeparatorsWord;     // word separators
    static inline_t const T* SeparatorsLine;     // line separators (\r\n)
    static inline_t const T* SeparatorsSentence; // sentence separators (.?!)
    static inline_t const T* EOL;                // single character \n       
    static inline_t const T* TAB;                // single character \t    
    static inline_t const T* CR;                 // single character \r
    static inline_t const T* SeparatorsRow;      // row separators ( \t)
    static inline_t const T  HexDigits[16];      // the 16 hexagonal letters 
    static inline_t const T* SPACE;              // single character " " 
};

#include "CTextT.inl"
