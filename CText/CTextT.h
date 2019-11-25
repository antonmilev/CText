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
#include <stack>
#include <cstdarg>
#include <fstream>
#include <codecvt>
#include <random>      
#include <chrono>      
#include <cassert>
#include <locale>
#include <unordered_map>

#pragma warning(disable : 4996)

#define ContC template<typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_same<Val, T>::value || std::is_convertible<Val, const T*>::value >  >
#define ContS template<typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_same<Val, T>::value || std::is_convertible<Val, std::basic_string<T> >::value || std::is_convertible<Val, const T* >::value  >  >
#define ContN template<typename Num, typename C, typename Val = typename C::value_type, typename X = std::enable_if_t<std::is_convertible<Val, Num>::value && (std::is_integral<Num>::value || std::is_floating_point<Num>::value) >  >
#define MapI template<typename C, typename Value = typename C::value_type, typename X = std::enable_if_t < std::is_convertible<Value, std::pair<int,CTextT<T>>>::value  > >
#define DefNum template <typename Num> 

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

    // for variadic routines - do not use: template<typename... Args> void append(T first, Args... args)!
    enum EncodingType
    {
        ENCODING_ASCII = 0,
        ENCODING_UTF8 = 1,
        ENCODING_UTF16LE = 2,
        ENCODING_UTF16BE = 3
    };

    bool	     alloc(size_t len);
    CTextT&	     append(const CTextT& s);
    CTextT&	     append(const T* s); // append string
    CTextT&	     append(const T* s, size_t len); // append part of a string
    CTextT&		 append(T c, size_t count = 1); //append single character
    CTextT&      append(std::initializer_list<T> cList); // append characters in the list
    CTextT&      append(std::initializer_list<const T*> sList); // append characters in the list
    ContC void   append(const C& container);  // append single character or string buffer, supports all value-type STL containers 
    CTextT&	     appendRange(T cBegin, T cEnd);  // append all character in the range 
    bool	     appendUnique(T c);  //append the character only if is not already contained
    bool         appendUnique(const T* s); //append the string only if is not already contained
    bool		 between(T cLeft, T cRight, bool include = false); // keeps the part of the string between the first and last characters cLeft and cRight (by default separators are not included)
    bool		 between(const T* sLeft, const T* sRight, bool include = false); // keeps the part of the string between the first and last sub-strings sLeft and sRight (by default separattors are not included)
    size_t		 capacity() const;
    bool         checkBlocksBalance(const T* sepBegin, const T* sepEnd); // checks if the blocks defined with the given separators are balanced
    void         clear(bool bRelease = false);
    ContS size_t collect(C& container, const T* cList) const;  // fill the container with substrings containing only characters from the list
    //ContS size_t filterSubstrings(C& container, const C& start, const C& end, const C& contain, const T* sep) const;  // fill the container with the substrings 
    ContS size_t collectLines(C& container, bool appendSeparators = false, const T* sep = SeparatorsLine) const;  // fills a STL container with the collected lines
    ContS size_t collectSentences(C& container, const T* sep = SeparatorsSentence, const T* sepWords = Separators) const;
    ContS size_t collectWords(C& container, const T* sep = Separators) const;
    int		     compare(const T* s, bool bCase = true) const; // return - 0 equal. -1 p1 < p2, or 1 - p1 > p2
    ContS void   compose(const C& container, const T* sep = EOL); // compose back the string using the gicen separator
    MapI  void   compose(const C& container, const T* sep = SPACE, const T* sepLine = EOL);
    void         compose(std::map<T, int>& container, const T* sep = SPACE, const T* sepLine = EOL);
    bool		 contain(T c, bool bCase = true) const;  // returns true if our string contains character c
    bool         contain(const T c, size_t from, size_t to) const; // search in range
    bool         contain(const T* s) const;  // returns true if our string contains another string
    bool	     contain(const T* s, bool bCase) const; // 
    bool         containAny(std::initializer_list<T> cList); // returns true if our string contains any of the characters of the list
    bool		 containAny(const T* cList, bool bCase = true) const; // returns true if our string contains any of the characters of the list
    bool		 containAny(const T** list, size_t n, bool bCase = true) const; //return true if contains any of the strings in the list
    ContC bool   containAny(const C& container, bool bCase = true) const;  // returns true if contains any of the characters or strings provided by the container
    bool         containOnly(T c, bool bCase = true) const; // return true if contain only character c
    bool         containOnly(const T* cList, bool bCase = true) const; // returns true if our string contains only characters from the list
    void	     copyto(T* s);  //copy the string data to the external buffer (should be large enough)
    size_t	     count(T c) const;  //returns the count of occurences of the given character
    size_t	     count(const T* s) const;  //returns the count of occurences of the given substring
    size_t	     countAny(const T* cList) const;  //returns the count of occurences of any of the characters in the list
    int          countChars(std::map<T, int>& container, bool bCase = true) const; // fill the map container with character counts
    int          countChains(T c) const;  // return count of blocks containing only character c (chains)
    int          countChainsAny(const T* cList) const;  // return count of blocks containing only of the characters in the list
    MapI size_t  countWordFrequencies(C& container, bool bCase = true, const T* sep = SeparatorsWord) const; // fill the container with the words frequency counts
    int          countSubstrings(const T* sep) const; // return number of found substrings divided by sep
    int          countWords(const T* sep = SeparatorsWord) const; // return number of the found words divided by sep
    bool		 cutAfterFirst(T c, bool include = false);//leaves everyting left from c, c is not included
    bool		 cutAfterFirst(const T* s, bool include = false); // same as above but perfomed over zero-teminated string, s is not included
    bool		 cutAfterFirstOfAny(const T* cList, bool include = false, bool bCase = true); //cut after the first occurence of any character from the list 
    bool		 cutAfterLast(T c, bool include = false); //leaves everyting left from the last character, c is not included
    bool		 cutAfterLast(const T* s, bool include = false); // leaves everyting left from last s, s is not included
    bool		 cutAfterLastOfAny(const T* chList, bool include = false, bool bCase = true); // leaves everyting left from last ch in the list, ch is not included
    size_t       cutEnds(size_t count); //remove count of characters from left and right
    size_t  	 cutEnds(size_t fromLeft, size_t fromRight);  //cut number of charcters from left and right
    size_t		 cutLeft(size_t count);  //removes count characters from left
    CTextT&		 cutRight(size_t count); //cut number of characters from right, if count is too big empty the string
    CTextT&		 enclose(T begin, T end, bool checkEnds = true); //enclose with the provided character separators (if not already ends and begins with them)
    CTextT&		 enclose(const T* begin, const T* end, bool checkEnds = true); //enclose with the provided text separators (if not already ends and begins with them)
    bool		 endsWith(const T& c, size_t from = 0, bool bCase = true) const;
    bool		 endsWith(const T* str, size_t from = 0, bool bCase = true) const;
    bool         endsWith(std::initializer_list<T> cList);
    bool		 endsWithAny(const T* cList, bool bCase = true) const;
    size_t 		 erase(size_t from, size_t count = 1);  // delete count characters starting at zero-based index
    void	     equal(const CTextT& str);  // make our string equal to str
    void	     equal(const T* s);  // make equal to str
    void	     equal(T c, size_t len);  // init witb len number of ch
    void	     equal(const T* s, size_t len, size_t offset = 0);  // init to len characters from string at offset   
    void         equalRange(T cBegin, T cEnd); // // init with all character in the range 
    const T*     find(const T c, bool bCase = true) const;// return a pointer to the first occurence of the character, or 0 pointer if not found
    const T*	 find(const T *s, bool bCase = true) const; // return a pointer to the first occurence of the substring, or 0 pointer if not found
    const T*     findAny(const T* cList, bool bCase = true) const; // return a pointer to the first occurence of any of the characters in the list, or 0 pointer if nothing found
    const T*     findNot(const T* cList, bool bCase = true) const; // return a pointer to the first occurence not of any of the characters in the list, or 0 pointer if all found
    size_t		 findBlockPositions(const T* sepBegin, const T* sepEnd, std::vector< std::pair<size_t, size_t>>& pos, bool bCase = true) const;//find begin/end positions of all blocks beggining and ending with the given separators
    size_t	     findPositions(const T** list, size_t n, std::vector<std::pair<size_t, size_t>>& pos, bool bCase = true, std::vector<size_t>* indexes = nullptr) const;
    ContC size_t findPositions(const C& container, std::vector<std::pair<size_t, size_t>>& pos, bool bCase = true, std::vector<size_t>* indexes = nullptr) const;
    size_t       findWordPositions(std::vector<std::pair<size_t, size_t>>& pos, const T* sep) const;
    T            first() const; //return first character or 0 if empty
    bool         format(const T* format, ...);
    DefNum bool  fromBinary(Num i);  // create binary string from the number
    DefNum bool  fromInteger(Num i, bool append = false);
    DefNum bool  fromHex(Num i, bool hasBase = true, bool upper = false);
    bool         fromDouble(double d, int precision = 6, bool fixed = true);
    bool         fromChars(const char* s);  // init with single-char ANSI string, make string -> wstring convert if necessary
    bool         fromWChars(const wchar_t* s);  // init with UNICODE string, make wstring -> string convert if necessary
    size_t		 indexOf(T c, size_t from = 0, bool bCase = true) const;	// finds the index of the first character starting at zero-based index and going right, return ch index or -1 if not found
    size_t		 indexOf(const T* s, size_t from = 0, bool bCase = true) const; // finds the index of the first instance of the substring starting at zero-based index, return substring index or -1 if not found
    size_t		 indexOfAny(const T* cList, size_t from = 0, bool bCase = true) const; 	// find first instance of any character in passed string, return substring index or -1
    ContC size_t indexOfAny(const C& container, size_t from = 0, bool bCase = true) const;
    size_t		 indexOfAny(const T** list, size_t n, size_t from = 0, bool bCase = true, size_t* idxList = 0) const;// find the first instance of any substring in the list, return string index or -1 if not found
    size_t		 indexOfNot(T c, bool bCase = true) const; // return index of the first character different than c
    CTextT&		 insert(size_t from, T c, size_t count = 1);	// insert the character at zero-based index, if index is past end of string 
    CTextT&		 insert(size_t from, const T* s);	// insert substring at zero-based index; concatenates, if index is past end of string
    CTextT&		 insert(size_t from, size_t count, const T* s); // insert substring at zero-based index, count is the number of max characters to insert
    bool         isAlpha() const;
    bool         isBinary() const;
    bool         isEmpty() const;
    bool	     isEqual(const T* s, bool bCase = true) const;  //checks if equal to string s, allows case-incensitive comparison
    bool         isHexNumber() const;
    bool         isLower(bool strict = true) const;
    bool         isNumber(bool allowSign=true) const;
    bool         isPalindrome() const;
    bool         isUpper(bool strict = true) const;
    size_t       hash() const;
    size_t       keep(size_t from, size_t count); //keeps count characters starting from given position, returns number of deleted characters
    size_t 		 keepEnds(size_t count);  //keeps the middle characters, count characters are removed from both ends, returns number of deleted characters
    size_t       keepLeft(size_t count);  // keeps count characters from left, returns number of deleted characters
    size_t       keepRight(size_t count); // keeps count characters from right, returns number of deleted characters
    CTextT		 left(size_t count) const;	// return new string containing first count characters 
    CTextT&		 limit(size_t maxLen); //makes the the text to be with the given max limit, if text length is smaller nothing is done
    T            last() const; //return last character or 0 if empty
    size_t		 lastIndexOf(T c, bool bCase = true) const;	// find the first character position starting at right, where from is offset from end and the returned idx is from the beggining
    size_t		 lastIndexOf(const T* s, bool bCase = true) const; // find the first substring position starting at right, where the returned idx is from the beggining
    size_t		 lastIndexOfAny(const T* cList, bool bCase = true) const;	// find the character position starting at right, from - offset from the end to start the search
    size_t       lastIndexOfNot(T c, bool bCase = true) const; 
    size_t		 length() const;  // returns the number of characters in our string
    size_t	     linesCount(const T* sep = EOL) const;  // returns the number of lines in the string
    size_t	     linesPaddRight( T c, size_t len, const T* sep = SeparatorsLine, const T* sepNew = EOL);
    size_t	     linesSort(const T* sep = SeparatorsLine, const T* sepNew = EOL);
    size_t       linesTrim(const T* cList, const T* sep = SeparatorsLine, const T* sepNew = EOL);
    CTextT&		 makeUnique();  //make sure that all characters occurs only once
    CTextT&      makeUnique(T c);  // make sure that character c occurs only once, leaves the first one
    CTextT		 mid(size_t count);  //leaves the middle characters, count characters are cut from both ends, returns new string
    T            nextChar(size_t pos, const T* sep = Separators) const; // return next character starting at the given position and excluding characters in the list
    bool		 nextExcluding(size_t& pos, CTextT& word, bool appendSeparators = false, const T* cList = Separators, size_t* posBegin = nullptr, size_t* posEnd = nullptr) const; //find the next substring not containing any of the characters in the list, if appendSeparators is set the separators will be added at the end
    bool         nextIncluding(size_t& pos, CTextT<T>& substr, const T* cList, size_t* posBegin = nullptr, size_t* posEnd = nullptr) const; //find the next substring containing only any of the characters in the list
    CTextT&		 paddLeft(T c, size_t len);  // fills from start with c characters until lenght "len" size is reached, increase the length and realloc if necessary
    CTextT&		 paddRight(T c, size_t len);  // fills with c characters until lenght "len" size is reached
    CTextT&		 quote(); // enclose with literals
    void         random(const T* cList, int len); // generate random text with size len using character from the list
    void         randomAlpha(int len); // generate text containing random alpha upper and lower characters 
    void         randomAlphaNumeric(int len); // generate text containing random alphanumeric upper and lower characters 
    void		 randomNumber(int len);// generate text containing a random integer with the given length
    bool         readFile(const T* filePath); // read a whole text file into our string
    size_t 		 reduceChain(T c);  //reduces chains of some character to a single instances, for example: replace multiple spaces by one space
    CTextT&      reduceChainAny(const T* cList);
    void		 reduceToNumber();  //strip text from non-numbers
    size_t 		 remove(T c, size_t from = 0); // delete all occurrences of the character stsrting from the zero-bsased index
    size_t	     remove(const T* s, bool bCase = true); // delete all occurences of the sub-string s, returns the number of the removed strings s (or 0 if nothing is removed)
    size_t       remove(std::initializer_list<T> cList);
    int			 removeAny(const T* cList, bool bCase = true);  //delete all of provided in the list characters
    CTextT&		 removeAny(const T** list, size_t n, bool bCase = true);  //remove any from the provided in the list strings
   ContC CTextT& removeAny(const C& container, bool bCase = true); //remove any from the provided in the list strings
   CTextT&       removeAny(std::initializer_list<const T*> list, bool bCase = true);
   CTextT&		 removeAtPositions(const std::vector<std::pair<size_t, size_t>>& pos); //remove from the positions at the provided index arrays
    size_t		 removeBlocks(const T* sepBegin, const T* sepEnd);  //removes any block from the strings begining and ending with the given separators
    bool         removeLast();  // removes the last character, return true if not empty and sucessful
    bool	     resizeToContent(); //if capacity is bigger then content, free the extra space
    size_t		 replace(T cOld, T cNew);	// replace occurrences of the character cOld with cNew, return number of replaced characters
    size_t   	 replace(const T* what, const T* with, bool bCase = true);// replace all occurrences of substring "what" with substring "with", empty "with" removes all instances of "what", return number of replaced substrings
    CTextT&	     replace(size_t from, size_t count, T c); // replace range with sizngle character
    CTextT&		 replace(size_t from, size_t count, const T* s);  // replace range with the content of the string (in incrementing order)
    int			 replaceAny(const T* cOld, T cNew); //replace any of the old characters with the new
    CTextT&		 replaceAny(const T** list, size_t n, const T* with, bool bCase = true);  	//replace any of the strings in the list with the string with
    CTextT&      replaceAny(const T** list, size_t n, const T** with, bool bCase = true);
    CTextT&      replaceAny(std::initializer_list<const T*> what, std::initializer_list<const T*> with, bool bCase = true);
   ContC CTextT& replaceAny(const C& what, const C& with, bool bCase = true);
    CTextT&		 replaceAny(const T** list, size_t n, const T c, bool bCase = true);  	//replace any of the strings in the list with the character c
   ContC CTextT& replaceAny(const C& container, const T* with, bool bCase = true);
    CTextT&      replaceAtPositions(const std::vector<std::pair<size_t, size_t>>& pos, const T* with);
    CTextT       replaceAtPositions(const std::vector<std::pair<size_t, size_t>>& pos, const T* with) const;
    CTextT&      replaceAtPositions(const std::vector<std::pair<size_t, size_t>>& pos, const std::vector<size_t>& indexes, const T** with) ;
    CTextT       replaceAtPositions(const std::vector<std::pair<size_t, size_t>>& pos, const std::vector<size_t>& indexes, const T** with) const;
   ContC CTextT& replaceAtPositions(const std::vector<std::pair<size_t, size_t>>& pos, const std::vector<size_t>& indexes, const C& with) ; 
   ContC CTextT  replaceAtPositions(const std::vector<std::pair<size_t, size_t>>& pos, const std::vector<size_t>& indexes, const C& with) const;
    CTextT&      replaceAtPositions(const std::vector<std::pair<size_t, size_t>>& pos, const T c);
    CTextT&      replaceFirst(T c);
    CTextT&      replaceLast(T c);
    bool         resize(size_t newLen, T c = 0);
    CTextT&		 reverse();	// reverse string right-to-left
   ContC CTextT& reverseAny(const C& container, bool bCase = true);
    CTextT&		 reverseAny(const T** list, size_t n, bool bCase = true);  //reverse inplace all occurrences of the provided in the list string 
    CTextT<T>&   reverseAtPositions(const std::vector<std::pair <size_t, size_t>>& pos);
    const T*     reverseFind(const T* s, bool bCase = true) const;
    CTextT&      reverseWords(const T* sep = Separators); 
    CTextT		 right(size_t count) const;	// return new string with count characters from the end of our string   
    CTextT&      rotateLeft(int n); // rotate tne string to the left
    CTextT&      rotateRight(int n); // rotate tne string to the right
    CTextT&      shuffle();
    CTextT		 spanIncluding(const T* cList) const;	//  characters from beginning that are also in passed string
    CTextT		 spanExcluding(const T* cList) const;	// characters from beginning that are not also in passed string   
    CTextT&	     sort(); // per character sort in ascending order
    ContS size_t split(C& container, bool appendSeparators = false, const T* sep = Separators) const;  // fills the STL container with the collected substrings
    bool		 splitAt(size_t pos, CTextT& first, CTextT& second, bool exclude = false) const;  // split into two strings at the given distance from the left
    bool		 splitAtFirst(T ch, CTextT& first, CTextT& second, bool exclude = false) const; // split into two strings at the first occurence of ch or return false, if exclude is false ch goes in the second part, otherwise is omitted
    bool		 splitAtFirst(const T* s, CTextT& first, CTextT& second, bool exclude = false, bool bCase = true); // split into two strings at the first occurence of string s or return false, if exclude is false str goes in the second part, otherwise is omitted
    bool		 splitAtFirstOfAny(const T* cList, CTextT& first, CTextT& second, bool exclude = false, bool bCase = true); // split into two strings at the first occurence of any character from the list or return false, if exclude is false ch goes in the second part, otherwise is omitted	
    bool		 splitAtLast(T ch, CTextT& first, CTextT& second, bool exclude = false) const; // split into two strings at the last occurence of ch or return false, if exclude is false ch goes in the second part, otherwise is omitted
    bool		 splitAtLast(const T* s, CTextT& first, CTextT& second, bool exclude = false, bool bCase = true); // split into two strings at the first occurence of string s or return false, if exclude is false ch goes in the second part, otherwise is omitted	
    bool		 splitAtLastOfAny(const T* cList, CTextT& first, CTextT& second, bool exclude = false, bool bCase = true); // split into two strings at the last occurence of any character from the list or return false, if exclude is false ch goes in the second part, otherwise is omitted	
    bool		 startsWith(const T& c, size_t from = 0, bool bCase = true) const;	//return true if text starts with character ch at position from
    bool		 startsWith(const T* s, size_t from = 0, bool bCase = true, size_t* offset = nullptr) const;  //return true if text starts with string str at position from
    bool         startsWith(std::initializer_list<T> cList);
    bool		 startsWithAny(const T* cList, size_t from = 0, bool bCase = true, T* chFound = nullptr) const;   //return true if starts with any of the provided characters, the optional parameter chFound will contain the found character
    ContC bool   startsWithAny(const C& container, size_t from = 0, bool bCase = true, size_t* idx = 0) const;
    bool		 startsWithAny(const T** list, size_t n, size_t from = 0, bool bCase = true, size_t* idx = 0) const ; // return true if starts with any of the provided strings, idx is optional position in the list
    CTextT		 substring(size_t from, size_t count) const;	// returns a new sub-string with count characters starting at zero-based offset
    CTextT		 substringBeforeFirst(T c, bool include = false) const;//same as cutAfterFirst above but return a new CText, by default c is not included
    CTextT       substringBeforeFirst(const T* str) const; //same as cutAfterFirst above but return a new CText object
    CTextT       substringBetween(T cLeft, T cRight, bool include = false);
    CTextT		 substringBetween(const T* sLeft, const T* sRight, bool include = false);
    CTextT		 substringRight(size_t from) const;	// return all characters starting at the zero-based from and continuing to the last
    CTextT       substringLeft(size_t count) const;  // returns new string with count characyters from left
    const T*     str() const;
    T*           str(); //return pointer to modifiable buffer (valid after C++11)
    const T*     str(size_t from) const;   
   unsigned long toBinaryNumber(bool& bOk); //if the string contains binary number, convert it to number
    bool         toChars(std::basic_string<char>& s);  // conversion to UTF8
    double       toDouble(bool& bOk) const;
    int          toInteger(bool& bOk) const;
   unsigned int  toUInteger(bool& bOk) const;
    ContN size_t toArray(C& container, T sep, bool& bOk) const; // parse our string to integers array divided by the given separator, can be used to parse CSV of integers
    ContN size_t toMatrix(std::vector<C>& container, T sep, bool& bOk, const T* sepLine = EOL) const;  // parse to matrix
    CTextT&		 toLower();	// conversion to lowercase (in place)
    CTextT&		 toUpper();	// conversion to uppercase (in place)
    bool         toWChars(std::basic_string<wchar_t>& s);  // conversion to Unicode
    CTextT&      trim(const T* cList = Separators);
    CTextT&      trimLeft(const T c); //// remove continuous occurrence of ch starting from left
    CTextT&      trimLeft(const T* cList = Separators);  // remove from left continuous occurrence of all characters from the provided list
    CTextT&      trimRight(const T c); //// remove continuous occurrence of character c, starting from right
    CTextT&      trimRight(const T* cList = Separators); // remove from right continuous occurrence of all characters from the provided list
    int		     unenclose(T begin, T end); //opposite of enclose
    int 		 unquote();  //removes literal sign if ends with it
    int          wordsCapitalize(const T* sep = Separators);  // make all words in a text start with upper character
    CTextT&	     wordsSort(const T* sep = Separators, const T* sepNew = SPACE); // words sort in ascending order
    bool         writeFile(const T* filePath, EncodingType encoding = ENCODING_UTF8); // write our string to a text file with the given encoding

    // static routines
    static CTextT<T>  Add(const CTextT&, const CTextT&);  // returns the concatenation of the both strings
    static CTextT<T>  Add(const CTextT&, const T*);
    static CTextT<T>  Add(const CTextT&, T c);
    static bool       ArePermutation(const CTextT& a, const CTextT& b);
    static bool       FromChars(const char* s, CTextT<T>& res);
    static bool       FromWChars(const wchar_t* s, CTextT<T>& res);
    ContS static size_t  GeneratePermutations(C& container, CTextT& s);
    static bool       IsPalindrome(const T* s, bool bCase = true, size_t len = std::string::npos);
    static bool       ReadFile(const T* filePath, CTextT<T>& s);  
    static  void      Swap(CTextT& a, CTextT& b);  // exchanges the values of two strings
    static bool       ToChars(const T* s, std::basic_string<char>& res);
    static bool       ToWChars(const T* s, std::basic_string<wchar_t>& res);
    static bool       WriteFile(const T* filePath, CTextT<T>& s, EncodingType encoding = ENCODING_UTF8);

    // static string routines
    static bool     EmptyOrNull(const T* s) { return (s == 0 || *s == 0); }
    static bool     EndsWith(const T* text, const T* str, bool bCase = true, size_t len = std::string::npos);
    static size_t   IndexOf(const T* s, size_t len, T c, bool bCase = false) ;
    static bool     IsAlpha(const T* s);
    static bool     IsBinary(const T* s);
    static bool     IsLower(const T* s, bool strict = false);
    static bool     IsHexNumber(const T* s);
    static bool     IsNumber(const T* s, bool allowSign = true);
    static bool	    IsOneOf(T c, const T* list, bool bCase = true, size_t* idx = 0); //return true if c occurs in the provided 0-terminated characters list, otherwise returns false, idx - optional position in the list
    static bool     IsUpper(const T* s, bool strict = true);
    static size_t   LastIndexOf(const T* str, size_t len, T c, bool bCase = true);
    static size_t   LastIndexOf(const T* str, size_t len, const T* s, bool bCase = true);
    static size_t	Levenshtein(const T *s1, const T *s2);  //calculate Levenshtein distance
    static size_t	HammingDistance(const T *s1, const T *s2);
    static bool	    StartsWith(const T* str, const T* s, bool bCase = true, int max_len = -1, size_t* idx = 0);	//return true if string str starts with the string s,  max_len - max number of chars to check, if idx is different than 0 will provide the length of the text in str which is in the beggining
    static size_t	Strlen(const T* str); //safe strlen, return -1 if str is 0
    static T*	    Strcpy(T* dst, const T* src); // (strcpy)
    static T*	    Strncpy(T *dst, const T *src,int n); // (strncpy)
    static T*	    Strcat(T *dst, const T *src); // (strcat)
    static T*	    Strncat(T *dst, const T *src, size_t n); //(strncat)
    static int	    Strcmp(const T* p1, const T* p2, bool bCase = true);
    static const T*	StrFind(const T* s, const T* text, bool bCase = true);  // (strstr) finds a pointer to the first occurence of text in str, return 0 pointer if not found
    static const T*	StrFindCh(const T* s, T c, bool bCase = true);  // (strchr) finds a pointer to the first occurence of a character in the passed string or returns 0 if not found
    static const T*	StrFindChAny(const T* s, const T* chList, bool bCase = true); //same as StrFindCh but checks all the character from the list
    static const T*	StrFindChNot(const T* s, T c, bool bCase = true); // (strchr) finds a pointer to the first occurence of a character different than c in the passed string or returns 0 if not found
    static const T*	StrFindChNot(const T* s, const T* cList, bool bCase = true); // returns pointer to the first character in string s not contained in the list or 0 if all characters are contained, if list is empty return pointer to the beggining
    static size_t   Strspn(const T* s1, const T* s2);  // (strspn) return length of initial segment of str that consists entirely of characters from s 
    static size_t   Strcspn(const T* s1, const T* s2); // (strcspn) return length of initial segment of str that do not contain any characters from s 
    static size_t   Strrspn(const T* s1, const T* s2); // (strrspn) return length of last segment of str that consists entirely of characters from s 
    static T*       Strrev(T *str);
    static void     Strrev(T* begin, T* end);  //reverse inplace, ABC -> CBA
    static void     Swab(const T* src, T* dst, size_t len);
    static CTextT   Substring(const T* str, size_t from, size_t nCount = 0); // return count characters starting at zero-based offset, return new string
    static size_t   Vsnprintf(T * str, size_t n, const T * fmt, va_list args);  //encapsulate vsnprintf, return number of characters written
    
    static bool	IsAlpha(T c);
    static bool IsAlphanumeric(T c);
    static bool IsDigit(T c);
    static bool IsHex(T c);
    static bool IsLower(T c);
    static bool IsSpace(T c);
    static bool IsUpper(T c);
    static T	lower(T ch);
    static T	upper(T ch);

    CTextT& operator=(const CTextT& s) ;
    CTextT& operator=(CTextT&& s);
    CTextT& operator=(const std::basic_string<T>& s);
    CTextT& operator=(std::basic_string<T>&& s);
    CTextT& operator=(const T* s) ;
    CTextT& operator=(const T c);

    operator const T*() const { return str(); }  // cast operator
    //operator T*() { return str(); }  // cast operator (it is risky)
    T operator[](int pos) const;  //returns character at given position
    T& operator[](int pos); // returns modifiable reference to the character at given position
    //operator std::basic_string<T>() const { return m_str; }
    //operator std::basic_string<T>()  { return m_str; }
    T at(size_t pos) const; // same as [] but throws out_of_range excepton
    T& at(size_t pos);

    const CTextT& operator+=(const T* str);
    const CTextT& operator+=(const CTextT& string);
    const CTextT& operator+=(T ch);

    friend CTextT operator+(const CTextT& string1, const CTextT& string2)  { return Add(string1,string2); }
    friend CTextT operator+(const CTextT& string, const T* str)		       { return Add(string,str); }
    friend CTextT operator+(const T* str,const CTextT& string)			   { return Add(string,str); }
    friend CTextT operator+(const CTextT& string, T ch)					   { return Add(string,ch); }
    friend CTextT operator+(T ch, const CTextT& string)					   { return Add(string,ch); }

    inline friend bool  operator==(const CTextT& s1, const CTextT& s2)       { return s1.m_str == s2.m_str; }
    inline friend bool  operator==(const CTextT& s1, const T* s2)            { return s1.m_str == s2; }
    inline friend bool  operator==(const T* s1, const CTextT& s2)	         { return s2.m_str == s1; }
    inline friend bool  operator!=(const CTextT& s1, const CTextT& s2)       { return s1.m_str != s2.m_str; }
    inline friend bool  operator!=(const CTextT& s1, const T* s2)            { return s1.m_str != s2; }
    inline friend bool  operator!=(const T* s1, const CTextT& s2)	         { return s2.m_str != s1; }
    inline friend bool  operator< (const CTextT& s1, const CTextT& s2)	     { return s1.m_str < s2.m_str; }
    inline friend bool  operator< (const CTextT& s1, const T* s2)			 { return s1.m_str < s2; }
    inline friend bool  operator< (const T* s2, const CTextT& s1)			 { return s1.m_str > s2; }
    inline friend bool  operator> (const CTextT& s1, const CTextT& s2)	     { return s1.m_str > s2.m_str; }
    inline friend bool  operator> (const CTextT& s1, const T* s2)			 { return s1.m_str > s2; }
    inline friend bool  operator> (const T* s2, const CTextT& s1)			 { return s1.m_str < s2; }
    inline friend bool  operator<=(const CTextT& s1, const CTextT& s2)	     { return s1.m_str <= s2.m_str; }
    inline friend bool  operator<=(const CTextT& s1, const T* s2)			 { return s1.m_str <= s2; }
    inline friend bool  operator<=(const T* s2, const CTextT& s1)			 { return s1.m_str >= s2; }
    inline friend bool  operator>=(const CTextT& s1, const CTextT& s2)	     { return s1.m_str >= s2.m_str; }
    inline friend bool  operator>=(const CTextT& s1, const T* s2)			 { return s1.m_str >= s2; }
    inline friend bool  operator>=(const T* s2, const CTextT& s1)			 { return s1.m_str <= s2; }

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


    friend std::basic_istream<T>& operator>>(std::basic_istream<T>& in, CTextT& s)          { return in >> s.m_str; }

    typedef T Char;
    typedef std::basic_string<T> tstring;
    static int CharSize() { return sizeof(Char); }
    static bool IsWide() { return CharSize() > 1; }

protected:
    ContS static void Permute(C& container, CTextT& a, size_t l, size_t r);
    
protected:
    std::basic_string<T>  m_str;

    static const T  CC;                 // control character '\'
    static const T* Slash;	            // folder separators (\\,/)
    static const T  Literal;            // symbol "
    static const T* Literals;           // literals symbols ' and "
    static const T* Separators;		    // all standard separators ( \r\n\t )
    static const T* SeparatorsWord;	    // all standard separators ( \r\n\t )
    static const T* SeparatorsLine;     // line separators (\r\n)
    static const T* SeparatorsSentence; // sentence separators (.?!)
    static const T* EOL;                // single character \n       
    static const T  TAB;                // single character \t    
    static const T* SeparatorsRow;      // row separators ( \t)
    static const T	HexDigits[16];      // the 16 hexagonal letters 
    static const T* SPACE;              // single character " " 
};

#include "CTextT.inl"

