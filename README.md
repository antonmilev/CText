# CText
# C++ Advanced text processing library

## About
I have started to rewrite on Modern C++ some text processing routines and this is the result so far. CText can solve many complicated tasks that otherwise are taking too much time in C++, some of these like lines and words splitting are available on higher level languages like C#, Java and Python but not and in C++. But C++ gives much more control and except supporting the missing text functions CText also implements hundreds of optimized text routines. The library can be used to quickly solve various pre-processing problems for different NLP and ML tasks or just to practice Modern C++. 

Please feel free to contact me for any questions, requests or even critics.

## Features

* **Modern C++ Template library**: You only need to include one header, very simple to use.
* **Unicode Support**: - you can have both UNICODE and ANSI in the project.
* **Hundreds of optimized text processing methods**: - Many standard and non-standard text processing operations are covered. I have a long TODO list with much more to add. 
* **Clean and easy to understand code**: - You can use CText to quickly start more complicated text processing applications and abstracting from the too many lower level details and optimizations.
* **Portable**:  I am using CText with VS2017/VS2019 and GCC 7.4 but it easily can be ported to other platforms.
* **Stand alone**:  CText do not depends on any other libraries, the only requirments are C++11 and STL
* **Scalable**:  All text routines are easily to be extended further for all supported char types and platforms. 

## Build the CText Unit Test and Demo projects

<br>To build the UnitTest project and the demos with CMake and Visual Studio:
<br> open terminal in the folder \Apps and type
<br>cmake .
<br>Alternatively, you can load in VS2017 or later \Apps\CMakeLists.txt from File->Open->CMake.., after generates cache is completed, choose CMake->Build All

<br>To compile with GCC in Debug or Rlease:
<br>cmake -D CMAKE_BUILD_TYPE=Release .
<br>cmake -D CMAKE_BUILD_TYPE=Debug .
<br>
<br>This will build a console application that runs the Unit Tests.
<br>
<br> Also there is a Visual Studio solution (CText.sln) with all projects. Run UnitTests project first to see if all tests pass.
<br>
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
    s.replace(_T("brown"), _T("red"));
    cout << s << endl;
```
Output:
```
   The quick red fox jumps over the lazy dog 
```  

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

### File paths 
```cpp
CText filepath = _T("D:\\Folder\\SubFolder\\TEXT\\File.dat");
cout << filepath.getExtension() << endl;
cout << filepath.getFileName() << endl;
cout << filepath.getDir() << endl;
filepath.replaceExtension(_T(".bin"));
cout << filepath << endl;
filepath.removeExtension();
cout << filepath << endl;
filepath.replaceExtension(_T(".dat"));
cout << filepath << endl;
filepath.replaceFileName(_T("File2"));
cout << filepath << endl;
filepath.addToFileName(_T("_mask"));
cout << filepath << endl;
filepath.replaceLastFolder(_T("Temp"));
cout << filepath << endl;
filepath.removeAfterSlash();
cout << filepath << endl;

```

Output
```
.dat
File.dat
D:\Folder\SubFolder\TEXT\
D:\Folder\SubFolder\TEXT\File.bin
D:\Folder\SubFolder\TEXT\File
D:\Folder\SubFolder\TEXT\File.dat
D:\Folder\SubFolder\TEXT\File2.dat
D:\Folder\SubFolder\TEXT\File2_mask.dat
D:\Folder\SubFolder\Temp\File2_mask.dat
D:\Folder\SubFolder\Temp
```

```cpp
CText path1(_T("C:\\Temp"));
CText path2(_T("..\\Folder"));
path1.pathCombine(path2.str());
cout << path1 << endl;
```

Output
```
C:\\Folder
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

    str.fromArray(sentences, _T("\n\n") );

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
s.fromMap(freq);
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
CText s = _T("1 2 3 4 5 6 7 8 9");
vector<int> v;
s.toArray<int>(v);
``` 

Output:
```
{1,2,3,4,5,6,7,8,9}
```

```cpp
CText s = _T("1,2,3,4,5,6,7,8,9");
vector<int> v;
s.toArray<int>(v, _T(','));
``` 

Output:
```
{1,2,3,4,5,6,7,8,9}
```

```cpp
CText s = _T("1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9");
vector<double> v;
s.toArray<double>(v, _T(','));
```

Output:
```
{1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9}
```

From hexadecimal numbers array:
```cpp
CText s = _T("0A 1E 2A 1B");
vector<int> v;
s.toArray<int>(v, _T(' '), true);
```

Output:
```
{10, 30, 42, 27}
```

```cpp
CText s = _T("1a:2b:3c:4d:5e:6f");
vector<int> v;
s.toArray<int>(v, _T(':'), true);
```

Output:
```
{26, 43, 60, 77, 94, 111}
```

Without separator:
```cpp
CText s = _T("0A1E2A1B");
s.toArray<int>(v, 0, true);
```

Output:
```
{10, 30, 42, 27}
```

```cpp
Convert hex to chars string 
CText s = _T("48 65 6C 6C 6F 20 57 6F 72 6C 64");
std::vector<int> bytes;
s.toChars<int>(bytes, true);
s.fromChars<int>(bytes);
cout << s << endl;
```

Output:
```
Hello World
```

Parse numerical matrix:
```cpp
std::vector<std::vector<int>> m;
CText s = _T("1 2 3\n4 5 6\n7 8 9");
s.toMatrix<int>(m, _T(' '));
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
* **More methods for words,lines,sentences and complex expressions**:  There are lots more methods that can be added to support diferent NLP and lexical tasks.
* **Further improve containers abstraction**: CText needs more convertion routines to/from STL and other containers and generic data structures.
* **Regular Expressions**: - Partial or full support to regular expressions.
* **Other char types**: - Character types like char_32 can be also supported
* **Mini Text Editor**: - This is a text editor based on CText that I plan to port on Modern C++.
* **Export to Python**: - I want to export CText library to Python-3
* **Performance Test**: - Add performance tests comparing with STL string.



