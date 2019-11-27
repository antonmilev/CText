# CText
# C++ Advanced text processing library

## About
I have started to rewrite on Modern C++ some text processing routines and this is the result so far. CText can solve many complicated tasks that otherwise are taking too much time in C++, some of these like lines and words splitting are available on higher level languages like C#, Java and Python but not and in C++. But C++ gives much more control and except supporting the missing text functions CText also implements hundereds of optimized text routines. The library can be used to quickly solve various text processing problems, preprocessing for different NLP and ML tasks or just to practise Modern C++. 

Please feel free to contact me for any questions, requests or even critics.

## Features

* **Modern C++ Template library**: You only need to include one header, very simple to use.
* **Unicode Support**: - you can have both UNICODE and ANSI in the project.
* **Hudreds of optimized text processing methods**: - Many standard and non-standard text processing operations are covered. I have a long TODO list with much more to add. 
* **Clean and easy to understand code**: - You can use CText to quickly start more complicated text processing applications and abstracting from the too many lower level details and optimizations.
* **Portable**:  CText is stand-alone and don't depends from any others packages. I have built and test it with VS2017/VS2019 and GCC 7.4 but it can be easily ported to other platforms.
* **Stand alone**:  CText do not depends on any other libraries, the only requirments are C++11 and STL
* **Scalable**:  All text routines are easily to be extended further for all supported char types and platforms. 

## Build the CText Unit Test and Demo projects

<br>To build the UnitTest project and the demos with CMake and Visual Studio:
<br>Load CMakeLists.txt from File->Open->CMake.., after generates cache is completed, choose CMake->Build All

<br>To compile with GCC:
<br>cmake -D CMAKE_BUILD_TYPE=Release .
<br>cmake -D CMAKE_BUILD_TYPE=Debug .
<br>
<br>This will build a console application that runs the Unit Tests.

## Examples

For all examples how to use CText please see the Unit Test project.

### Sort lines in a text file

```cpp
// this example reads a text file and sorts all lines in alphabeta order.
#include <iostream>
#include "../CTEXT/CText.h"
#include "tchar_utils.h"

int main()
{    
    const char* input_name = "/Unsorted.txt";
    const char* output_name = "/Sorted.txt";

    CText pathIn = getcwd(0, 0);
    CText pathOut = pathIn;
    pathIn += input_name;
    pathOut += output_name;
    
    CText str;
    if(!str.readFile(pathIn.str()))
    {
        std::cerr << "Error, can not open file: " << pathIn << std::endl;
        return 0;
    }
    str.linesSort();
    str.writeFile(pathOut.str(), CText::ENCODING_ASCII);

    return 0;
}
```

### Replace words
```cpp
    CText s = _T("The quick brown fox jumps over the lazy dog");
    const CText::Char* words[] = {_T("quick"), _T("fox"), _T("dog")};
    s.replaceAny(words, 3, _T('-'));
    cout << s << endl;
```

Output:
```
   The ----- brown --- jumps over the lazy ---     
```  

```cpp
    CText s = _T("The quick brown fox jumps over the lazy dog");
    s.replaceAny({_T("fox"), _T("dog")}, {_T("dog"), _T("fox")});
    cout << s << endl;
```

```cpp
    CText s = _T("The quick brown Fox jumps over the lazy Dog");
    s.replaceAny({_T("fox"), _T("dog")}, {_T("dog"), _T("fox")}, false);
    cout << s << endl;
```

Output:
```
   The quick brown dog jumps over the lazy fox   
```  

```cpp
   CText s = _T("The quick brown fox jumps over the lazy dog");
   const CText::Char* words[] = {_T("quick"), _T("fox"), _T("dog")};
   s.replaceAny(words, 3, _T("****"));
   cout << s << endl;
```

Output:
```
   The **** brown **** jumps over the lazy ****  
```  

### Remove words, blocks and characters
```cpp
   CText s = _T("This is a monkey job!");
   s.remove(_T("monkey"));
   s.reduceChain(' ');
   cout << s << endl;
```

Output:
```
   This is a job!
```  

```cpp
   CText s = _T("Text containing <several> [blocks] separated by {brackets}");
   s.removeBlocks(_T("<[{"), _T(">]}"));
   s.reduceChain(' ');
   s.trim()
   cout << s << endl;
```

Output:
```
   Text containing separated by
```  

```cpp
   s = _T("one and two or three and five");
   s.removeAny({_T("or"), _T("and")});
   s.reduceChain(' ');
   cout << s << endl;
```

Output:
```
   one two three five
```  

### Split and collection routines
```cpp
    CText s = _T("The quick  brown fox jumps  over the lazy dog");
    vector<CText> words;
    if(s.split(words) < 9)
        cout << "Error!" << endl ;
    for(auto& s : words)
        cout << s << endl;
```

```cpp
   CText s = _T("The,quick,brown,fox,jumps,over,the,lazy,dog");
   vector<std::string> words;
   if(s.split(words,false,_T(",")) != 9)
      cout << "Error!" << endl ;
   for(auto& s : words)
      cout << s << endl;
```

 Output:
```
The
quick
brown
fox
jumps
over
the
lazy
dog
```

```cpp
    CText s = "Line 1\r\nLine 2\n\nLine 3\n";
    vector<std::string> lines;
    s.collectLines(lines);
    for(auto& s : lines)
      cout << s << endl;
```

 Output:
```
Line 1
Line 2
Line 3
```


### Read sentences from text file
```cpp
#include <iostream>
#include "../CTEXT/CText.h"
#include "tchar_utils.h"

int main()
{    
    const char* input_name = "/Columbus.txt";
    const char* output_name = "/Columbus_Sentences.txt";

    CText pathIn = getcwd(0, 0);
    CText pathOut = pathIn;
    pathIn += input_name;
    pathOut += output_name;
    
    CText str;
    if(!str.readFile(pathIn.str()))
    {
        std::cerr << "Error, can not open file: " << pathIn << std::endl;
        return 0;
    }
    std::vector<CText> sentences;

    str.collectSentences(sentences);

    str.compose(sentences, _T("\n\n") );

    str.writeFile(pathOut.str(), CText::ENCODING_UTF8);

    return 0;
}
```

### Count characters and words
```cpp
CText s = _T("12345678909678543213");
map<CText::Char, int> freq;
s.countChars(freq);
```

```cpp
CText s = _T("Nory was a Catholic because her mother was a Catholic, and Nory’s mother was a Catholic because her father was a Catholic, and her father was a Catholic because his mother was a Catholic, or had been.");
std::multimap<int, CText, std::greater<int> > freq;
s.countWordFrequencies(freq);
s.compose(freq);
cout << s;
```

Output:
```
Catholic 6
a 6
was 6
because 3
her 3
mother 3
and 2
father 2
Nory 1
Nory's 1
been 1
had 1
his 1
or 1
```

### Conversion routines
```cpp
CText s = _T("1,2,3,4,5,6,7,8,9");
vector<int> v;
bool bOk;
s.toArray<int>(v, _T(','), bOk);
``` 

Output:
```
{1,2,3,4,5,6,7,8,9}
```

```cpp
CText s = _T("1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9");
vector<double> v;
bool bOk;
s.toArray<double>(v, _T(','), bOk);
```

Output:
```
{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}
```

Parse numerical matrix:
```cpp
bool bOk;
std::vector<std::vector<int>> m;
CText s = _T("1 2 3\n4 5 6\n7 8 9");
s.toMatrix<int>(m, _T(' '), bOk);
```

Output:
```
{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
};
```

### Highlight words

Following will make bold all words starting with "Col", "Spa","Isa", ending to "an"), "as" or containing "pe" or "sea":

```cpp
vector<CText> start = {_T("Col"), _T("Spa"), _T("Isa")};
vector<CText> end = {_T("an"), _T("as")};
vector<CText> contain = {_T("pe"), _T("sea")};
str.wordsEnclose(_T("<b>"), _T("</b>"), &start, &end, &contain);
```   
     
Portugal had been the main <b>European</b> power interested in pursuing trade routes <b>overseas</b>. Their next-door neighbors, Castile (predecessor of <b>Spain</b>) had been somewhat slower to begin exploring the Atlantic <b>because</b> of the bigger land area it had to re-conquer (the Reconquista) from the Moors. It <b>was</b> not until the late 15th century, following the dynastic union of the Crowns of Castile and Aragon and the completion of the Reconquista, that the unified crowns of what would become <b>Spain</b> (although countries still legally existing) emerged and became fully committed to looking for new trade routes and colonies <b>overseas</b>. In 1492 the joint rulers conquered the Moorish kingdom of Granada, which had been providing Castile with <b>African</b> goods through tribute. <b>Columbus</b> had previously failed to convince King John II of Portugal to fund his exploration of a western route, but the new king and queen of the re-conquered <b>Spain</b> decided to fund <b>Columbus's</b> expedition in hopes of bypassing Portugal's lock on Africa and the <b>Indian</b> <b>Ocean</b>, reaching Asia by traveling west
<b>Columbus</b> <b>was</b> granted <b>an</b> audience with them; on May 1, 1489, he <b>presented</b> his plans to Queen <b>Isabella</b>, who referred them to a committee. They pronounced the idea impractical, and <b>advised</b> the monarchs not to support the <b>proposed</b> venture


## TODO List
* **More methods for words,lines,sentences and complex expressions processing**:  There are a lot more methods that can be added to support diferent NLP and lexical tasks.
* **Further improve containers abstraction**: CText needs more convertion routines to/from STL and other containers and generic data structures.
* **Regular Expressions**: - Partial or full support to regular expressions.
* **Other char types**: - Character types like char_32 can be also supported
* **Mini Text Editor**: - This is a text editor based on CText that I plan to port on Modern C++.




