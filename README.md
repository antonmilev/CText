# CText
# Advanced text processing library for C++ & Python 

## About

CText is a Modern C++ library that offers a wide range of text processing routines. It addresses many complex tasks that can be time-consuming in both C++ and Python. While features like line and word manipulation are readily available in higher-level languages such as C#, Java, and Python, they are often lacking in C++. CText fills this gap by providing those missing capabilities while preserving the low-level control that C++ offers. In addition to essential functions, it includes numerous optimized routines for efficient text handling. The library is highly flexible and scalable, making it easy to extend with custom processing routines. It’s well-suited for tackling preprocessing challenges in NLP and machine learning tasks, or simply for honing your Modern C++ skills.


## Main Features
* **Modern C++ Template library**: Simple to use, just include a single header file.
* **Unicode Support**: - Seamlessly handle both UNICODE and ANSI in the same project.
* **Extensive Text Processing Features**: - Includes hundreds of optimized methods for both standard and advanced operations, with many more planned.
* **Clean and Readable Codebase**: - Designed to help you build complex text-processing applications quickly, abstracting away low-level details and optimizations.
* **Cross-Platform Compatibility**:  Tested with Visual Studio and GCC 7.4, easily portable to other environments.
* **No External Dependencies**:  CText do not depends on any other libraries, the only requirements are C++11 and STL
* **Easily Extensible**:  Text routines are designed to be scalable and adaptable across character types and platforms.
* **Python Integration**:  Compatible with all versions of Python 

Have questions or suggestions? Feel free to reach out: [email](mailto:amil@abv.bg).

### Python
To install CText:
```
pip install ctextlib
```

To test if CText is installed:

```python
import ctextlib
a = ctextlib.Text("Hello World")
print(a)
```

Or:

```python
from ctextlib import Text as text
a = text("Hello World")
print(a)
```


Python methods reference:

<b>addToFileName</b>
```python
a = text("C:\\Temp\\Temp2\\File.bmp")
a.addToFileName("_mask")
print(a)
```

```
C:\Temp\Temp2\File_mask.bmp
```

<b>append</b>
```python
a = text("Hello ")
a.append("World")
```

```
Hello World
```

```python
a = text("123")
a.append('4',4)
```

```
1234444
```

```python
a = text("")
a.append(['Hello', ' ', 'World'])
```

```
Hello World
```

<b>appendRange</b>
```python
a = text()
a.appendRange('a','z').appendRange('0','9')

```

```
abcdefghijklmnopqrstuvwxyz0123456789
```

<b>between</b>
```python
a = text('The quick brown fox jumps over the lazy dog')
a.between('q','d')
print(a)
```

```
uick brown fox jumps over the lazy
```

```python
a = text('The quick brown fox jumps over the lazy dog')
a.between('quick','lazy')
print(a)
```

```
 brown fox jumps over the
```

<b>contain</b>
```python
a = text('The quick brown fox jumps over the lazy dog')
if a.contain('quick') :
    print("contain 'quick'")
```

```
contain 'quick'
```
    
Case-incensitive
   
```python
a = text('The quick brown fox jumps over the lazy dog')
if a.contain('Quick', False) :
    print("contain 'quick'")
```

```
contain 'quick'
```

```python
a = text('The quick brown fox jumps over the lazy dog')
if a.contain(['slow','fast','quick']):
    print("contain 'quick'")
```

```
contain 'quick'
```

<b>containAny</b>
```python
a = text('Hello World')
a.containAny('abcd')
True
```
<b>containOnly</b>
```python
a = text('4365767')
a.containOnly('0123456789')
True
```

<b>count</b>
```python
a = text('The quick brown fox jumps over the lazy dog')
a.count('the', False)
```

```
2
```

<b>countWordFrequencies</b>
```python
from ctextlib import Text as text
a = text("The quick brown fox jumps over the lazy dog")
a.countWordFrequencies(False)
```

```
[(2, 'the'), (1, 'brown'), (1, 'dog'), (1, 'fox'), (1, 'jumps'), (1, 'lazy'), (1, 'over'), (1, 'quick')]
```

<b>cutAfterFirst</b>
```python
s = text('The quick brown fox jumps over the lazy dog')
a.cutAfterFirst('o')
```

```
The quick br
```

<b>cutAfterLast</b>
```python
s = text('The quick brown fox jumps over the lazy dog')
a.cutAfterLast('o')
```

```
The quick brown fox jumps over the lazy d
```


<b>cutBeforeFirst</b>
```python
s = text('The quick brown fox jumps over the lazy dog')
a.cutBeforeFirst('o')
```

```
own fox jumps over the lazy dog
```

<b>cutEnds</b>
```python
s = text('The quick brown fox jumps over the lazy dog')
a.cutEnds(4)
```

```
quick brown fox jumps over the lazy
```

<b>cutLeft</b>
```python
s = text("Hello World")
s.cutLeft(6)
```

```
World
```

<b>cutRight</b>
```python
s = text("Hello World")
s.cutRight(6)
```

```
Hello
```

<b>enclose</b>
```python
a = text("Hello World")
a.enclose('<','>')
a.enclose('"')
```

```
<Hello World>
"Hello World"
```

<b>endsWith</b>
```python
a = text("Hello World")
if a.endsWith('World'):
    print("ends with 'World'")
```


```
ends with 'World'
```

With case-insensitive search:

```python
a = text("Hello World")
if a.endsWith('world', False):
    print("ends with 'world'")
```

```
ends with 'world'
```

<b>endsWithAny</b>
```python
if(a.endsWithAny(['cat','dog'])):
    print('end to animal...')
```

```
end to animal...
```

<b>erase</b>
```python
a = text('The quick brown fox jumps over the lazy dog')
a.erase(8, 10)
print(a)
```

``` 
The quicx jumps over the lazy dog
``` 

<b>equal</b>
```python
a = text()
a.equal('A',10)
```

```
AAAAAAAAAA
```

<b>find</b>
```python
a = text('The quick brown fox jumps over the lazy dog')
a.find('brown')
```

```
'brown fox jumps over the lazy dog'
```

With case-incensitive search:

```python
a = text('The quick brown fox jumps over the lazy dog')
a.find('Brown', False)
```

```
'brown fox jumps over the lazy dog'
```

<b>fromArray</b>
```python
a = text()
a.fromArray([1,2,3,4])
print(a)
```

```
1 2 3 4
```

```python
a = text()
a.fromArray([1,2,3,4], '|')
print(a)
```

```
1|2|3|4
```

```python
a = text()
a.fromArray([1,2,3,4], '')
print(a)
```

```
1234
```

Array of floats

```python
a = text()
a.fromArray([1.1,2.2,3.3,4.4])
print(a)
```

```
1.1 2.2 3.3 4.4
```

Array of strings
```python
a = text()
a.fromArray(['hello','world'])
print(a)
```

```
hello world
```

```python
import numpy as np
a = text()
a.fromArray(np.array(["hello","world"]))
print(a)
```

```
hello world
```

<b>fromArrayAsHex</b>
```python
a = text()
a.fromArrayAsHex([10,20,30,40])
print(a)
```

```
0A 14 1E 28
```

Use without separator

```python
a.fromArrayAsHex([10,20,30,40],2,'')
print(a)
```

```
0A141E28
```

```python
a = text()
a.fromArrayAsHex([1000,2000,3000,4000])
print(a)
```

```
3E8 7D0 BB8 FA0
```

```python
a = text()
a.fromArrayAsHex([1000,2000,3000,4000], 4, ',')
print(a)
```

```
03E8,07D0,0BB8,0FA0
```

<b>fromBinary</b>
```python
a = text()
a.fromBinary(12345)
print(a)
```

```
00000000000000000011000000111001
```

<b>fromDouble</b>
```python
a = text()
a.fromDouble(3.333338478)
print(a)
a.fromDouble(3.33989, 4)
print(a)
a.fromDouble(3.333338478, 10)
```

```
3.333338
3.3399
3.3333384780
```

<b>fromHex</b>
```python
a = text()
a.fromHex(1234567)
a.fromHex('a')
a.fromHex("48 65 6C 6C 6F 20 57 6F 72 6C 64")
```

```
0012D687
61
Hello World
```

<b>fromInteger</b>
```python
a = text()
a.fromInteger(358764)
print(a)
```

```
358764
```

<b>fromMatrix</b>
```python
from ctextlib import Text as text
import numpy as np
x = np.array([[10, 20, 30], [40, 50, 60]])
a = text()
a.fromMatrix(x)
print(a)
```

```
10 20 30
40 50 60
```

```python
from ctextlib import Text as text
import numpy as np
x = np.array([[10, 20, 30], [40, 50, 60]])
a = text()
a.fromMatrix(x, ',')

```

```
10,20,30
40,50,60
```

<b>fromMatrixAsHex</b>
```python
from ctextlib import Text as text
import numpy as np
x = np.array([[10, 20, 30], [40, 50, 60]])
a = text()
a.fromMatrixAsHex(x)
print(a)
```

```
0A 14 1E
28 32 3C
```

```python
from ctextlib import Text as text
import numpy as np
x = np.array([[1000, 2000, 3000], [4000, 5000, 6000]])
a = text()
a.fromMatrixAsHex(x,4)
print(a)
```

```
03E8 07D0 0BB8
0FA0 1388 1770
```

<b>getDir</b>
```python
a = text("D:\\Folder\\SubFolder\\TEXT\\file.dat")
a.getDir()
```

```
D:\Folder\SubFolder\TEXT\
```

<b>getExtension</b>
```python
a = text("D:\\Folder\\SubFolder\\TEXT\\file.dat")
a.getExtension()
```

```
'.dat'
```

<b>getFileName</b>
```python
a = text("D:\\Folder\\SubFolder\\TEXT\\file.dat")
a.getFileName()
```

```
'file.dat'
```

<b>hash</b>
```python
s.hash()
```

```
9257130453210036571
```

<b>indexOf</b>
```python
a = text("The quick brown fox jumps over the lazy dog.")
a.indexOf("brown")
```

```
10
```

<b>indexOfAny</b>
```python
a = text("The quick brown fox jumps over the lazy dog.")
a.indexOfAny(["fox", "dog"])
```

```
16
```

<b>indexOfAny</b>

```python
a = text("The quick brown fox jumps over the lazy dog.")
a.indexOfAny("abc")
```

```
7
```

<b>insert</b>
```python
a = text("abc")
a.insert(1,'d',2)
```

```
addbc
```

```python
a = text("The quick jumps over the lazy dog.")
a.insert(10,"fox ")
```

```
The quick fox jumps over the lazy dog.
```

<b>insertAtBegin</b>
<br><b>insertAtEnd</b>
```python
a = text("Hello")
a.insertAtBegin("<begin>")
a.insertAtEnd("</begin>")
```

```
<begin>abc</begin>
```

<b>isAlpha</b>
```python
a = text("Abcd")
a.isAlpha()
True
```

<b>isBinary</b>
```python
a = text("01111011100001")
a.isBinary()
True
```

<b>isEmpty</b>
```python
a = text()
a.isEmpty()
True
```

<b>isHexNumber</b>
```python
a = text("12AB56FE")
a.isHexNumber()
True
```

<b>isNumber</b>
```python
a = text("123456")
a.isNumber()
True
```

<b>isLower</b>
```python
a = text("hello world")
a.isLower()
True
```

<b>isUpper</b>
```python
a = text("HELLO WORLD")
a.isUpper()
True
```

<b>isPalindrome</b>
```python
a = text("racecar")
a.isPalindrome()
True
```

<b>keep</b>
```python
s = text("Hello World").keep(3,5)
```

```
lo Wo
```

<b>keepLeft</b>
```python
a = text("The quick jumps over the lazy dog.")
a.keepLeft(10)
```

```
The quick
```

<b>keepRight</b>
```python
a = text("The quick jumps over the lazy dog.")
a.keepRight(10)
```

```
 lazy dog.
```

<b>lastIndexOf</b>
```python
s = text("Hello World")
s.lastIndexOf('l')
```

```
9
```

<b>lines</b>
```python
a = text("L1\nL2\n\nL3\nL4\n  \n\nL5")
a.lines()
```

```
['L1', 'L2', 'L3', 'L4', 'L5']
```

<b>linesCount</b>
```python
a = text("L1\nL2\n\nL3\nL4\n  \n\nL5")
a.linesCount()
```

```
7
```

<b>linesRemoveEmpty</b>
```python
a = text("L1\nL2\n\nL3\nL4\n  \n\nL5")
a.linesRemoveEmpty()
print(a)
```

```
L1
L2
L3
L4
L5
```

Several per line methods
<br><b>linesAppend</b>
<br><b>linesInsertAtBegin</b>
<br><b>linesSort</b>
<br><b>linesPaddRight</b>
<br><b>linesTrim</b>
<br>Example of opening a text file, sort all lines, and save it with another name
```python
from ctextlib import Text as text
s = text()
s.readFile('Unordered.txt')
s.linesSort()
s.writeFile('Sorted_python.txt')
```

<b>limit</b>
```python
s = text("Hello World")
s.limit(6)
```

```
Hello
```

<b>lower</b>
```python
s = text("Hello World")
s.lower()
```

```
hello world
```

<b>makeUnique</b>
```python
a = text()
a.appendRange('a','z').appendRange('a','z')
abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz
a.makeUnique()
print(a)
```

```
abcdefghijklmnopqrstuvwxyz
```

<b>mid</b>
```python
a = text("Hello World").mid(3)
```

```
lo Wo
```

<b>nextLine</b>
```python
# Example of iterating all lines
from ctextlib import Text as text
a = text("Line1\nLine2\nLine3")
line = text()
pos = 0
while(pos >= 0):
    pos = a.nextLine(pos,line)
    print(line)
```

```
Line1
Line2
Line3
```

<b>nextWord</b>
```python
# Example of iterating all words
from ctextlib import Text as text
a = text('The quick brown fox jumps over the lazy dog')
word = text()
pos = 0
while(pos >= 0):
    pos = a.nextWord(pos,word)
    print(word)
```

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

<b>paddLeft</b>
```python
s = text("Abra")
s.paddLeft('.', 16)
```

```
............Abra
```

<b>paddRight</b>
```python
s = text("Abra")
s.paddRight('.', 16)
```

```
Abra............
```

<b>pathCombine</b>
```python
a = text("C:\\Temp")
a.pathCombine("..\\Folder")
```

```
C:\Folder
```

<b>quote</b>
```python
a = text("Hello")
a.quote()
```

```
"Hello"
```

<b>random</b>
```python
a = text()
a.random()
"P1kAlMiG2Kb7FzP5"
a.sort()
"1257AFGKMPPbiklz"
a.shuffle()
"k2lF7KAPG5M1Pzbi"
a.random(32)
P1kAlMiG2Kb7FzP5tM1QBI6DSS92c31A
```

<b>randomAlpha</b>
```python
s = text()
s.randomAlpha()
IkEffmzNiMKKASVW
```

<b>randomNumber</b>
```python
s = text()
s.randomNumber()
3892795431
s.randomNumber(32)
33341138742779319865028602486509
```

<b>readFile</b>
```python
# demontrates how to read a whole text file
from ctextlib import Text as text
a = text()
a.readFile('test.txt')
print(a)
```

```
Hello World
```


<b>regexMatch</b>
```python
s = text("+336587890078")
if(s.regexMatch("(\\+|-)?[[:digit:]]+")):
    print("it is a number")
```

```
it is a number
```

<b>regexLines</b>
```txt
animals.txt
------------
Cat
Dog
Giraffe
Lion
Llama
Monkey
Mouse
Parrot
Poodle
Scorpion
Snake
Weasel
```

```python
# collect all lines starting with given characters
from ctextlib import Text as text
a = text()
a.readFile("animals.txt")
a.regexLines("^[A-G][a-z]+")
```

```
['Cat', 'Dog', 'Giraffe']
```

<b>regexReplace</b>    
```python
from ctextlib import Text as text
a = text("there is sub-sequence in the sub-way string")
a.regexReplace("\\b(sub)([^ ]*)", "sub-$2")
```

```
there is sub--sequence in the sub--way string
```

<b>regexSearch</b>    
```python
# collect all words using regex
from ctextlib import Text as text
a = text("The quick brown fox jumps over the lazy dog")
a.regexSearch("\\w+")
```
   
```
'The', 'quick', 'brown', 'fox', 'jumps', 'over', 'the', 'lazy', 'dog']
```

<b>regexWords</b>    
```python
# collect all words starting with given characters
from ctextlib import Text as text
a = text("The quick brown fox jumps over the lazy dog")
a.regexWords("^[a-n][a-z]+")
```
   
```
['brown', 'fox', 'jumps', 'lazy', 'dog']   
```
   
<b>remove</b>
```python
a = text('we few, we happy few, we band of brothers.')
a.remove('we')
a.reduceChain()
a.trim()
```

```
few happy few band of brothers
```

<b>removeAny</b>
```python
from ctextlib import Text as text
a = text('The quick brown fox jumps over the lazy dog')
a.removeAny(['brown','quick','lazy'])
a.reduceChain()
```

```
The fox jumps over the dog
```

<b>removeExtension</b>
```python
a = text("D:\\Folder\\SubFolder\\TEXT\\File.dat")
a.removeExtension()
```

```
D:\Folder\SubFolder\TEXT\File
```

<b>removeFileName</b>
```python
a = text("D:\\Folder\\SubFolder\\TEXT\\File.dat")
a.removeFileName()
```

```
D:\Folder\SubFolder\TEXT\
```

<b>removeWhileBegins</b>
```python
a = text("Some text ending with something")
a.removeWhileBegins("Some text ")
print(a)
```

```
ending with something
```

<b>removeWhileEnds</b>
```python
a = text("Some text ending with something")
a.removeWhileEnds(" something")
print(a)
```

```
Some text ending with
```

<b>replace</b>
```python
a = text("The quick brown fox jumps over the lazy dog")
a.replace("fox", "cat")
print(a)
```

```
The quick brown cat jumps over the lazy dog
```

```python
a = text("The quick brown fox jumps over the lazy dog")
a.replace(["fox", "cat","dog","quick"], "-")
```

```
The ----- brown --- jumps over the lazy ---
```

<b>replaceAny</b>
```python
a = text("The quick brown fox jumps over the lazy dog")
a.replaceAny(["fox", "cat","dog"], "***")
print(a)
```

```
The quick brown *** jumps over the lazy ***
```

```python
a = text("The quick brown fox jumps over the lazy dog")
a.replaceAny(["fox", "dog"], ["dog", "fox"])
```

```
The quick brown dog jumps over the lazy fox
```

<b>reverse</b>
```python
a = text("Hello")
a.reverse()
```

```
olleH
```






<b>right</b>
```python
a = text("Hello World")
a.right(5)
```

```
World
```

<b>rotate</b>
```python
a = text("Hello World")
a.rotateLeft(2)
a.rotateRight(4)
```

Output
```
llo WorldHe
ldHello Wor
```

<b>split</b>
```python
# by default split uses the standard separators (" \t\r\n")
a = text("The quick brown fox jumps over the lazy dog")
a.split()
```

```
['The', 'quick', 'brown', 'fox', 'jumps', 'over', 'the', 'lazy', 'dog']
```

```python
# split can be used with any list of separator characters
a = text("The quick, brown....fox,,, ,jumps over,the  lazy.dog")
a.split(",. ")
```

```
['The', 'quick', 'brown', 'fox', 'jumps', 'over', 'the', 'lazy', 'dog']
```

<b>toBinary</b>
```python
bOk = False
a = text("100001")
a.toBinary(bOk)
33
```

<b>toHex</b>
```python
a = text("Hello World")
a.toHex()
print(a)
```

```
48 65 6C 6C 6F 20 57 6F 72 6C 64
```

Using separator character. 

```python
a = text("Hello World")
a.toHex(',')
print(a)
```

```
48,65,6C,6C,6F,20,57,6F,72,6C,64
```

<b>toHex</b>
```python
bOk = False
a = text("1E1E")
a.toHex(bOk)
7710
```

<b>trim</b>
```python
a = text(" \t\n   lazy dog  \t\n   ")
a.trim()
lazy dog
a = text("000000000000101")
a.trimLeft("0")
101
a = ("101000000000000")
a.trimRight('0')
101
a = text("0000000101000000000")
a.trim("0")
101
```

<b>upper</b>
```python
s = text("Hello World")
s.upper()
```

```
HELLO WORLD
```

<b>words</b>
```python
a = text("The quick brown fox jumps over the lazy dog")
a.words()
```

```
['The', 'quick', 'brown', 'fox', 'jumps', 'over', 'the', 'lazy', 'dog']
```

```python
a = text("The|quick|brown|fox|jumps|over|the|lazy|dog")
a.words('|')
```

```
['The', 'quick', 'brown', 'fox', 'jumps', 'over', 'the', 'lazy', 'dog']
```

<b>wordsCapitalize</b>
```python
a = text("The quick brown fox jumps over the lazy dog")
a.wordsCapitalize()
```

```
The Quick Brown Fox Jumps Over The Lazy Dog
```

<b>wordsCount</b>
```python
a = text('The quick brown fox jumps over the lazy dog')
a.wordsCount()
```

```
9
```

<b>wordsEnclose</b>
```python
a = text("The quick brown fox jumps over the lazy dog")
a.wordsEnclose('[',']')
```

```
[The] [quick] [brown] [fox] [jumps] [over] [the] [lazy] [dog]
```

<b>wordsReverse</b>
```python
a = text("The quick brown fox jumps over the lazy dog")
a.wordsReverse()
```

```
ehT kciuq nworb xof spmuj revo eht yzal god
```


<b>wordsSort</b>
```python
a = text('The quick brown fox jumps over the lazy dog')
a.wordsSort()
```

Output
```
The brown dog fox jumps lazy over quick the
```

<b>writeFile</b>
```python
# demontrates how to write to a text file
from ctextlib import Text as text
a = text("Hello World")
a.writeFile('test.txt')
print(a)
```

## Static methods

<b>ReadFile</b>

```python
import ctextlib as CText
str = CText.ReadFile('test.txt')
print(str)
```

Output
```
The quick brown fox jumps over the lazy dog
```

Or to import to global space:

```python
from ctextlib import *
str = ReadFile('test.txt')
print(str)
```

Output
```
The quick brown fox jumps over the lazy dog
```

<b>ReadWords</b>

```python
import ctextlib as CText
words = CText.ReadWords('test.txt')
print(words)
```

Output
```
The quick brown fox jumps over the lazy dog
```

<b>ReadLines</b>

```Lines.txt
Line1
Line2
Line3
```

```python
# demontrates how to read all lines from a text file
import ctextlib as text
lines = text.ReadLines("Lines.txt")
```

Output
```
['Line1', 'Line2', 'Line3']
```

<b>WriteFile</b>

```python
import ctextlib as CText
CText.WriteFile('test.txt','The quick brown fox jumps over the lazy dog')
```
Output
```
test.txt
```


## UNICODE for Python
Python is using UTF8 as strings representation. When using Python texts containing non-English Unicode characters it is recommended to use the Unicode version of CText as demonstrated below:
```python
# demonstrate text processing of Swedish unicode text
from ctextlib import TextU as text
s = text('Den snabbbruna räven hoppar över den lata hunden')
>>> s.cutBeforeFirst('ö')
```

```
över den lata hunden
```

```python
# demonstrate text processing of Russian unicode text
from ctextlib import TextU as text
s = text('Быстрая коричневая лиса прыгает на ленивую собаку')
s.cutAfterLast('ы')
```

```
Быстрая коричневая лиса пр
```

```python
# demonstrate text processing of Czech unicode text
from ctextlib import TextU as text
s = text('Rychlá hnědá liška skočí přes líného psa')
s.cutAfterFirst('á', True)
```

```
Rychlá
```


```python
# demonstrate text processing of Greek unicode text
from ctextlib import TextU as text
s = text('Η γρήγορη καφέ αλεπού πηδάει πάνω από το τεμπέλικο σκυλί')
s.cutAfterFirst('έ', True)
```

```
Η γρήγορη καφέ
```


```python
# demonstrate text processing of Armenian unicode text
from ctextlib import TextU as text
s = text('Արագ շագանակագույն աղվեսը ցատկում է ծույլ շան վրա')
s.cutBeforeFirst('է')
```
 
```
է ծույլ շան վրա
```

```python
# demonstrate text processing of Georgian unicode text
from ctextlib import TextU as text
s = text('სწრაფი ყავისფერი მელა გადაბმულია ზარმაცი ძაღლი')
s.cutBeforeFirst('მ')
```

```
მელა გადაბმულია ზარმაცი ძაღლი
```

For the full info type help(text).


## Build CText Unit Test and Demo projects

<br>To build the UnitTest project and the demos with CMake and Visual Studio:
<br> open terminal in the folder \Apps and type
<br>cmake .
<br>Alternatively, you can load in VS2017 or later \Apps\CMakeLists.txt from File->Open->CMake.., after generates cache is completed, choose CMake->Build All

<br>To compile with GCC in Debug or Release:
<br>cmake -D CMAKE_BUILD_TYPE=Release .
<br>cmake -D CMAKE_BUILD_TYPE=Debug .
<br>
<br>This will build a console application that runs the Unit Tests.
<br>
<br> Also there is a Visual Studio solution (CText.sln) with all projects. Run UnitTests project first to see if all tests pass.


<br>
## C++ Examples

For all examples how to use CText please see the Unit Test project.

### Sort all lines in a text file

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
