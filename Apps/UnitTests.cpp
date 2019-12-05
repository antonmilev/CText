/**
 * @file UnitTests.cpp
 * @brief Advanced Text Proccessing Library
 * @author Anton Milev, baj.mile@abv.bg
 * @version 1.0
 * @date November, 2019
 */

// Unit Tests for CText

#include <iostream>
#include "../CTEXT/CText.h"
#include "UnitTests.h"
#include "terminal.h"
#include "tchar_utils.h"

#ifdef _WIN32
#pragma warning(disable : 4702)
#endif

using namespace std;

int test_init()   // test constructors and assign operators
{
    try
    {
        {
            CText s;
            if(s.length() != 0 || !s.isEmpty() || !s.capacity())
                goto error;

            CText s2(_T('A'), 10);
            if(!(s2 == _T("AAAAAAAAAA")) || s2 != _T("AAAAAAAAAA"))
                goto error;

            CText s3(s2);
            if(!(s3 == _T("AAAAAAAAAA")) || s3 != _T("AAAAAAAAAA") || s2 != s3)
                goto error;

            CText s4(_T("AAAAAAAAAA"));
            if(!(s4 == _T("AAAAAAAAAA")) || s4 != _T("AAAAAAAAAA") || s2 != s4)
                goto error;

            CText s5(_T("AAAAAAAAAA"), 5);
            if(!(s5 == _T("AAAAA")) || s5 != _T("AAAAA") || s2 == s5)
                goto error;

            s.equal(_T('B'), 10);
            if(s != _T("BBBBBBBBBB") || !(s == _T("BBBBBBBBBB")))
                goto error;

            s.equal(s2);
            if(!(s == _T("AAAAAAAAAA")) || s != _T("AAAAAAAAAA"))
                goto error;

            s.equal(_T('B'), 5);
            if(s != _T("BBBBB"))
                goto error;

            s.equal(_T("ABC"));
            if(s != _T("ABC"))
                goto error;

            s.equal(_T("ABCD"), 2, 1);
            if(s != _T("BC"))
                goto error;

            if(s.str(std::string::npos) != nullptr)
                goto error;

            s = nullptr;
            if(!s.isEmpty())
                goto error;
        }
        {
            CText s = _T("text");
            if(s != _T("text"))
                goto error;
            s.equal(nullptr);
            if(!s.isEmpty())
                goto error;

            s = _T("text");
            s.equal(nullptr, 2, 1);
            if(!s.isEmpty())
                goto error;
        }

        {
            CText s = {_T("AA"), _T("BB"), _T("CC")};
            if(s != _T("AABBCC"))
                goto error;
        }

        {
            CText a(_T("AA"));
            CText b(_T("BB"));
            CText c(_T("CC"));
            CText s = {a.str(), b.str(), c.str()};
            if(s != _T("AABBCC"))
                goto error;
        }

        {
            CText s = {'1', '2', '3', '4', '5'};
            if(s != _T("12345"))
                goto error;
        }

        {
            CText a[10];
            for(int k = 0; k < 10; k++)
            {
                if(a[k].length() != 0)
                    goto error;
            }
        }

        {
            CText* a = new CText[10];
            for(int k = 0; k < 10; k++)
            {
                if(a[k].length() != 0)
                    goto error;
            }
            delete[] a;
        }

        // std::string compatibility
        {
            CText a = CText::tstring(_T("text"));
            if(a != _T("text"))
                goto error;

            CText::tstring b(_T("text2"));
            CText c = b;
            if(c != _T("text2"))
                goto error;

            // explicit conversions are allowed
            CText::tstring s = (const CText::Char*)c;
            if(s != _T("text2"))
                goto error;

            s = a.str();

            c = a;
            if(c != _T("text"))
                goto error;
        }

        printResult("test_init()", true);
        return 0;

    error:
        printResult("test_init()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_init() [exception]", false);
        return 1;
    }
}

int test_add()
{
    try
    {
        {
            CText s(_T("123"));
            s.append(_T('4'));
            if(s != _T("1234"))
                goto error;
            s.append(_T('5'), 2);
            if(s != _T("123455"))
                goto error;
            s.append(_T("666"));
            if(s != _T("123455666"))
                goto error;
            s.append(nullptr);
            if(s != _T("123455666"))
                goto error;
        }

        {
            CText s;
            s.append({_T("11"), _T("22")});
            if(s != _T("1122"))
                goto error;
        }

        {
            CText s;
            s.append({_T("11"), _T("22"), _T("33")});
            if(s != _T("112233"))
                goto error;
        }

        {
            CText s;
            s.append({_T("11"), _T("22"), _T("33"), _T("44")});
            if(s != _T("11223344"))
                goto error;
        }

        {
            CText a(_T("one")), b(_T("two"));
            CText c = CText::Add(a, b);
            if(c != _T("onetwo"))
                goto error;
        }

        {
            CText s;
            CText a(_T("11")), b(_T("22"));
            s.append({a.str(), b.str(), _T("33")});
            if(s != _T("112233"))
                goto error;
        }

        {
            CText s;
            s.append({_T('1'), _T('2'), _T('3')});
            if(s != _T("123"))
                goto error;
        }

        {
            vector< CText::Char> vec = {_T('a'), _T('b'), _T('c')};
            list< CText::Char> l = {_T('c'), _T('d'), _T('f')};
            set< CText::Char> m = {_T('g'), _T('h'), _T('k')};
            CText s;
            s.append(vec);
            if(s != _T("abc"))
                goto error;
            s.append(l);
            if(s != _T("abccdf"))
                goto error;
            s.append(m);
            if(s != _T("abccdfghk"))
                goto error;
        }

        {
            vector< const CText::Char*> vec = {_T("aa"), _T("bb"), _T("cc")};
            CText s;
            s.append(vec);
            if(s != _T("aabbcc"))
                goto error;

            vector <CText> vec2 = {_T("dd"), _T("ee"), _T("ff")};
            s.append(vec2);
            if(s != _T("aabbccddeeff"))
                goto error;
        }

        {
            CText s;
            s.appendRange(_T('0'), _T('9'));
            if(s != _T("0123456789"))
                goto error;
        }

        {
            CText c = CText::Add(CText(_T("one")), _T("two"));
            if(c != _T("onetwo"))
                goto error;
        }

        {
            CText c = CText::Add(CText(_T("123")), _T('4'));
            if(c != _T("1234"))
                goto error;
        }

        {
            CText str = _T("Some");
            str += _T(' ');
            str += _T("Text");
            if(str != _T("Some Text"))
                goto error;
        }

        {
            CText str1 = _T("Some");
            CText str2 = _T(" Text");
            str1 += str2;
            if(str1 != _T("Some Text"))
                goto error;
        }

        {
            CText s1(_T("First"));
            CText s2 = _T("Second");
            CText s = s1 + s2;

            if(s != _T("FirstSecond"))
                goto error;

            if(s.length() != 11)
                goto error;
        }


        {
            CText a1 = _T("a1 ");
            CText a2 = _T("a2 ");
            CText a3 = _T("a3");
            CText a4 = a1 + a2 + a3;

            if(a4 != _T("a1 a2 a3"))
                goto error;
        }

        {
            CText s;
            const TCHAR* digits = _T("0123456789");
            for(int k = 0; k < 10; k++)
            {
                s.clear();
                for(int j = 0; j < 10; j++)
                    s += digits[j];;

                if(s != digits)
                    goto error;

                if(s.length() != 10)
                    goto error;
            }
        }


        {
            CText val = CText::Add(CText(_T("one")), _T("second"));
            if(val != _T("onesecond"))
                goto error;
        }

        printResult("test_add()", true);
        return 0;

    error:
        printResult("test_add()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_add() [exception]", false);
        return 1;
    }
}

int test_static()  // test several static string routines
{
    try
    {
        {
            const CText::Char* str = _T("some text");
            CText::Char dst[50];

            CText::Strncpy(dst, str, 4);

            if(CText::Strcmp(dst, _T("some")) != 0)
                goto error;

            str = _T("some");
            CText::Strncpy(dst, str, 4);

            if(CText::Strcmp(dst, _T("some")) != 0)
                goto error;
        }

        {
            CText::Char str1[] = _T("Sample string");
            CText::Char str2[40];
            CText::Char str3[40];
            CText::Strcpy(str2, str1);
            CText::Strcpy(str3, _T("copy successful"));

            if(CText::Strcmp(str2, _T("Sample string")) != 0)
                goto error;

            if(CText::Strcmp(str3, _T("copy successful")) != 0)
                goto error;
        }


        {
            CText::Char s1[40] = _T("some");
            CText::Strcat(s1, _T("thing"));
            if(CText::Strcmp(s1, _T("something")) != 0)
                goto error;
            CText::Strncat(s1, _T(" something"), 5);
            if(CText::Strcmp(s1, _T("something some")) != 0)
                goto error;
        }

        {
            CText::Char str1[20];
            CText::Char str2[20];
            CText::Strcpy(str1, _T("To be "));
            CText::Strcpy(str2, _T("or not to be"));
            CText::Strncat(str1, str2, 6);
            if(CText::Strcmp(str1, _T("To be or not")) != 0)
                goto error;
        }

        printResult("test_static()", true);
        return 0;

    error:
        printResult("test_static()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_static() [exception]", false);
        return 1;
    }
}
int test_find()
{
    try
    {
        {
            CText s = _T("The quick brown fox jumps over the lazy dog");
            if(!s.startsWith('T'))
                goto error;
            if(!s.startsWith(_T("The")))
                goto error;

            if(!s.startsWith('q', 4, true))
                goto error;
            if(!s.startsWith(_T("Q"), 4, false))
                goto error;

            if(s.startsWith({_T('p'), _T('q'), _T('r'), _T('s')}))
                goto error;
            if(!s.startsWith({_T('s'), _T('H'), _T('T'), _T('r')}))
                goto error;

            if(!s.startsWith(_T("THE"), 0, false))
                goto error;
            if(s.startsWith(_T("THE"), 0, true))
                goto error;
            if(!s.startsWith(_T("QUICK"), 4, false))
                goto error;
            if(!CText::StartsWith(s.str(), _T("T")))
                goto error;
            if(!CText::StartsWith(s.str(), _T("The")))
                goto error;

            CText a(_T("A"));
            if(s.startsWith(a))
                goto error;
            a = _T("THE");
            if(!s.startsWith(a, 0, false))
                goto error;
        }

        {
            CText s = _T("The quick brown fox jumps over the lazy dog");
            if(s.startsWithAny(_T("abcd"), 4))
                goto error;
            if(!s.startsWithAny(_T("pqrs"), 4))
                goto error;
            if(!s.startsWithAny(_T("PQRS"), 4, false))
                goto error;
            if(s.startsWithAny(_T("qtrs")))
                goto error;
            if(!s.startsWithAny(_T("QTRS"), false))
                goto error;

            CText chars(_T("abcd"));
            if(s.startsWithAny(chars, 4))
                goto error;

            // check only the first 2 characters from text
            if(CText::StartsWith(s.str(), _T("The"), true, 2) == true)
                goto error;

            if(CText::StartsWith(s.str(), _T("Th"), true, 2) == false)
                goto error;

            s = _T("The");
            if(CText::StartsWith(s.str(), _T("The quick")))
                goto error;
        }

        {
            CText s = _T("The quick brown fox jumps over the lazy dog");
            array<const CText::Char*,3> words = {_T("fox"), _T("dog"), _T("the")};

            if(s.startsWithAny(words))
                goto error;
            if(!s.startsWithAny(words, 16))
                goto error;
            if(s.startsWithAny(words, 0, true))
                goto error;
            if(!s.startsWithAny(words, 0, false))
                goto error;

            vector< CText::Char > vec2 = {_T('f'), _T('d'), _T('t')};
            if(s.startsWithAny(vec2))
                goto error;
            if(!s.startsWithAny(vec2, 0, false))
                goto error;

            vector< const CText::Char* > vec = {_T("fox"), _T("dog"), _T("the")};
            if(s.startsWithAny(vec))
                goto error;
            if(!s.startsWithAny(vec, 0, false))
                goto error;

            std::vector<CText> words2 = {_T("fox"), _T("dog")};
            if(s.startsWithAny(words2))
                goto error;

        }


        {
            CText s = _T("The quick brown fox jumps over the lazy dog");
            if(!s.endsWith(_T('g')))
                goto error;
            if(s.endsWith(_T('G')))
                goto error;
            if(s.last() != 'g')
                goto error;
            if(!s.endsWith(_T('G'), 0, false))
                goto error;

            if(!s.endsWithAny(_T("pqgs")))
                goto error;
            if(s.endsWith({_T('s'), _T('H'), _T('T'), _T('r')}))
                goto error;
            if(!s.endsWith({_T('d'), _T('g')}))
                goto error;
            if(!s.endsWith({_T('g'), _T('d')}))
                goto error;
            if(!s.endsWith(_T("dog")))
                goto error;
            if(!s.endsWith(_T("lazy"), 4))
                goto error;
            if(s.endsWith(_T("Lazy"), 4))
                goto error;
            if(!s.endsWith(_T("Lazy"), 4, false))
                goto error;

            s = _T("good is one");
            if(!CText::EndsWith(s.str(), _T("one")))
                goto error;

            if(CText::EndsWith(s.str(), _T("One")))
                goto error;
        }

        {
            CText s = _T("The quick brown fox jumps over the lazy dog");
            vector< const CText::Char* > vec = {_T("fog"), _T("cog"), _T("man")};
            vector< CText::Char > vec2 = {_T('f'), _T('d'), _T('t')};
            vector< CText > vec3 = {_T("fog"), _T("cog"), _T("man")};
            if(s.endsWithAny(vec))
                goto error;
            if(s.endsWithAny(vec3))
                goto error;
            vec.push_back(_T("dog"));
            if(!s.endsWithAny(vec))
                goto error;
            if(s.endsWithAny(vec2))
                goto error;
            vec2.push_back(_T('g'));
            if(!s.endsWithAny(vec2))
                goto error;
            s = _T("The quick brown fox jumps over the lazy doG");
            if(s.endsWithAny(vec2))
                goto error;
            if(!s.endsWithAny(vec2, 0, false))  // test without case
                goto error;
            if(s.endsWithAny(vec))
                goto error;
            if(!s.endsWithAny(vec, 0, false))
                goto error;
        }

        {
            CText empty;
            if(empty.last() != 0 || empty.first())
                goto error;
        }

        {
            CText str = _T("The quick brown fox jumps over the lazy dog.");

            if(!str.contain(_T("dog")) || str.contain(_T("cat")))
                return false;

            CText subStr = str.find(_T("fox"));

            if(subStr != _T("fox jumps over the lazy dog."))
                goto error;

            subStr = str.reverseFind(_T("the"));

            if(subStr != _T("the lazy dog."))
                goto error;

            subStr = str.find(_T('f'));

            if(subStr != _T("fox jumps over the lazy dog."))
                goto error;

            subStr = str.find(_T('D'));

            if(!subStr.isEmpty())
                goto error;
        }

        {
            CText s = _T("abcd");
            if(!s.contain(_T('b')) || s.contain(_T('f')))
                goto error;

            if(!s.contain(_T('A'), false))
                goto error;

            if(!s.contain(_T('d'), 0, 10))
                goto error;

            if(s.contain(_T('c'), 0, 1))
                goto error;

            s = _T("something");
            if(s.containAny(_T("abc")))
                goto error;
            if(!s.containAny(_T("edfg")))
                goto error;
            if(s.containAny({_T('a'), _T('b')}))
                goto error;
            if(!s.containAny({_T('d'), _T('e')}))
                goto error;

            s = _T("alabala");
            if(!s.containOnly(_T("abl")) || s.containOnly(_T("ab")))
                goto error;
        }

        {
            CText s = _T("The quick brown fox jumps over the lazy dog.");
            vector<CText::Char> vec = {_T('A'), _T('B'), _T('C'), _T('D')};
            if(s.containAny(vec))
                goto error;

            // test case-incensitive
            if(!s.containAny(vec, false))
                goto error;

            vec.push_back(_T('T'));
            if(!s.containAny(vec))
                goto error;

            vector<const CText::Char*> vec3 = {_T("cat"), _T("mouse"), _T("Dog")};
            vector<CText> vec4 = {_T("cat"), _T("mouse"), _T("Dog")};
            if(s.containAny(vec3))
                goto error;

            if(s.containAny(vec4))
                goto error;

            if(!s.containAny(vec3, false))
                goto error;

            array<const TCHAR*,2> words = {_T("or"), _T("and")};
            if(s.containAny(words, false))
                goto error;
        }

        {
            array<const CText::Char*,2> wordsToFind = {_T("fox"), _T("dog")};
            CText s = _T("The quick brown fox jumps over the lazy dog");

            vector< pair <size_t, size_t> > v;

            size_t nWords = s.findPositions(wordsToFind, v);

            if(nWords != 2)
                goto error;

            if(v[0].first != 16 || v[1].first != 40 || v[0].second != 18 || v[1].second != 42)
                goto error;

            s.removeAt(v);
            if(s != _T("The quick brown  jumps over the lazy "))
                goto error;

            s = _T("The quick brown fox jumps over the lazy dog");
            s.reverseAt(v);
            if(s != _T("The quick brown xof jumps over the lazy god"))
                goto error;
        }

        printResult("test_find()", true);
        return 0;

    error:
        printResult("test_find()", false);
        return 1;
    }

    catch(...)
    {
        printResult("test_find() [exception]", false);
        return 1;
    }
}

int test_compare()
{
    try
    {
        {
            CText a(_T("text1"));

            CText b(_T("tExt1"));

            if(a == b)
                goto error;

            if(a == _T("text"))
                goto error;

            if(a.compare(_T("text1")) != 0)
                goto error;

            if(a != _T("text1"))
                goto error;

            // test case-incensitive compare
            if(a.compare(b.str(), false) != 0)
                goto error;

            if((a != b) == false)
                goto error;

            if(a < b || b > a)
                goto error;

            if(a < _T("W") || _T("W") > a)
                goto error;

            // test with empty strings
            a.clear();

            // in this case must be b > a
            if(a >= b)
                goto error;

            if(a.compare(b.str()) >= 0)  // < 0
                goto error;

            if(a.compare(nullptr) != 0)  // < 0
                goto error;

            a = _T("text1");
            b.clear();

            // in this case must be a > b
            if(b >= a)
                goto error;

            // if both strings are empty should return 0
            a.clear();
            if(b != a)
                goto error;
        }

        // test case-incensitive compare
        {
            CText c1 = _T("open");
            CText c2 = _T("OPEN");
            if(!c1.isEqual(c2.str(), false))
                goto error;
            if(c1.isEqual(c2.str(), true))
                goto error;
            c1.clear();
            if(!c1.isEqual(nullptr)) //nullptr is empty string
                goto error;
        }

        printResult("test_compare()", true);
        return 0;

    error:
        printResult("test_compare()", false);
        return 1;

    }
    catch(...)
    {
        printResult("test_compare() [exception]", false);
        return 1;
    }
}

int test_modify()
{
    try
    {
        {
            CText s = _T("1234");

            if(s[0] != _T('1') || s[1] != _T('2') || s[2] != _T('3') || s[3] != _T('4'))
                goto error;

            s[0] = s[3];
            s[1] = s[2];
            s[2] = _T('2');
            s[3] = _T('1');

            if(s[0] != _T('4') || s[1] != _T('3') || s[2] != _T('2') || s[3] != _T('1'))
                goto error;

            printResult("test_modify()", true);
            return 0;

        }

        {
            CText s = _T("1234");

            if(s.at(0) != _T('1') || s.at(1) != _T('2') || s.at(2) != _T('3') || s.at(3) != _T('4'))
                goto error;

            s.at(0) = s.at(3);
            s.at(1) = s.at(2);
            s.at(2) = _T('2');
            s.at(3) = _T('1');

            if(s.at(0) != _T('4') || s.at(1) != _T('3') || s.at(2) != _T('2') || s.at(3) != _T('1'))
                goto error;

            printResult("test_modify()", true);
            return 0;
        }

        // test out of bound exception
        {
            CText s = _T("1234");
            try
            {
                if(s.at(4) == 0)
                    goto error;

                goto error;
            }
            catch(std::out_of_range)
            {
                // it is Ok
            }
            catch(...)
            {
                goto error;
            }

            try
            {
                if(s.at(4) == _T('5'))
                    goto error;

                goto error;
            }
            catch(std::out_of_range)
            {
                // it is Ok
            }
            catch(...)
            {
                goto error;
            }
        }

    error:
        printResult("test_modify()", false);
        return 1;
    }

    catch(...)
    {
        printResult("test_compare() [exception]", false);
        return 1;
    }
}


int test_transform()
{
    try
    {
        {
            CText s = _T("this is a simple text");
            s.reverse();
            if(s != _T("txet elpmis a si siht"))
                goto error;
        }

        {
            CText s = _T("this is a simple text");
            array<const CText::Char*,2> words = {_T("this"), _T("text")};
            s.reverseAny(words);
            if(s != _T("siht is a simple txet"))
                goto error;
        }

        {
            CText s = _T("ABCDE");
            s.rotateLeft(2);
            if(s != _T("CDEAB"))
                goto error;
            s.rotateRight(2);
            if(s != _T("ABCDE"))
                goto error;
        }

        {
            CText text = _T("tHis is a simple TEXT");

            if(text.isLower() || text.isUpper())
                goto error;

            CText textU = text;
            textU.toUpper();
            CText textL = text;
            textL.toLower();

            if(textU != _T("THIS IS A SIMPLE TEXT"))
                goto error;

            if(textL != _T("this is a simple text"))
                goto error;

            if(textU.isUpper() || textL.isLower())
                goto error;

            if(!textU.substring(0, 4).isUpper() || !textL.substring(0, 4).isLower())
                goto error;

            if(!textU.isUpper(false) || !textL.isLower(false))
                goto error;
        }

        {
            CText s = _T("Abcd");
            if(!s.isAlpha())
                goto error;
            s = _T("Ab cd");
            if(s.isAlpha())
                goto error;
        }

        {
            CText s = _T("hjvgiluhbniphjni");
            s.sort();
            if(s != _T("bghhhiiijjlnnpuv"))
                goto error;
        }

        {
            CText a = _T("First");
            CText b = _T("Second");
            CText::Swap(a, b);
            if(a != _T("Second") || b != _T("First"))
                goto error;
        }

        {
            CText a = _T("Random");
            CText b(a);
            a.shuffle();
            if(!CText::ArePermutation(a, b))
                goto error;
            a.shuffle();
            if(!CText::ArePermutation(a, b))
                goto error;
        }

        {
            if(CText::IsPalindrome(_T("Mom")))
                goto error;

            if(!CText::IsPalindrome(_T("Mom"), false))
                goto error;

            if(!CText::IsPalindrome(_T("racecar"), false))
                goto error;
        }

        {
            CText s, s2;
            s.randomNumber(10);
            s2.appendRange(_T('0'), _T('9'));
            if(!s.containOnly(s2.str()) || s.length() != 10)
                goto error;

            s.randomNumber(6);
            bool bOk;
            s.toInteger(bOk);
            if(!bOk || s.length() != 6)
                goto error;

            s.random(_T("0123456789"), 8);
            if(!s.containOnly(s2.str()) || s.length() != 8)
                goto error;

            s.toInteger(bOk);
            if(!bOk || s.length() != 8)
                goto error;

            CText s3;
            s3.appendRange(_T('a'), _T('z'));
            s.randomAlpha(20);
            if(!s.containOnly(s3.str(), false) || s.length() != 20)
                goto error;

            CText s4;
            s4.appendRange(_T('a'), _T('z')).appendRange(_T('0'), _T('9'));
            s.randomAlphaNumeric(30);
            if(!s.containOnly(s4.str(), false) || s.length() != 30)
                goto error;

            CText a = _T("abc");
            CText b = _T("bac");
            if(a.hash() == b.hash())
                return false;
            b = _T("abc");
            if(a.hash() != b.hash())
                return false;
        }

        {
            CText s;
            bool bOk;
            s = _T("100001");
            unsigned int i = s.toBinaryNumber(bOk);
            if(!bOk || i != 33)
                goto error;

            s = _T("103001");
            i = s.toBinaryNumber(bOk);
            if(bOk)
                goto error;

            s = _T("1E");
            i = s.toHexNumber(bOk);
            if(!bOk || i != 30)
                goto error;

            s = _T("1E1E");
            i = s.toHexNumber(bOk);
            if(!bOk || i != 7710)
                goto error;
        }

        printResult("test_transform()", true);
        return 0;

    error:
        printResult("test_transform()", false);
        return 1;

    }
    catch(...)
    {
        printResult("test_transform() [exception]", false);
        return 1;
    }
}

int test_words()
{
    try
    {
        {

            {
                CText s = _T("The quick brown fox jumps over the lazy dog");
                s.wordsSort();
                if(s != _T("The brown dog fox jumps lazy over quick the"))
                    goto error;
            }

            {
                CText s = _T("The quick brown fox jumps over the lazy dog");
                s.wordsReverse();
                if(s != _T("ehT kciuq nworb xof spmuj revo eht yzal god"))
                    goto error;
            }

            {
                CText s = _T("The quick brown fox jumps over the lazy dog");
                s.wordsCapitalize();
                if(s != _T("The Quick Brown Fox Jumps Over The Lazy Dog"))
                    goto error;
            }

            {
                CText s = _T("The quick brown fox jumps over the lazy dog");
                s.wordsEnclose(_T("<"), _T(">"));

                if(s != _T("<The> <quick> <brown> <fox> <jumps> <over> <the> <lazy> <dog>"))
                    goto error;
            }

        }

        printResult("test_words()", true);
        return 0;

    error:
        printResult("test_words()", false);
        return 1;

    }
    catch(...)
    {
        printResult("test_words() [exception]", false);
        return 1;
    }
}

int test_count()
{
    try
    {
        {
            CText s1 = _T("1234567890967854321");
            if(s1.count(_T('4')) != 2 || s1.count(_T('0')) != 1)
                goto error;

            if(s1.countAny(_T("456")) != 6)
                goto error;

            if(s1.count(_T("78")) != 2 || s1.count(_T("4")) != 2 || s1.count(_T("854")) != 1)
                goto error;
        }

        {
            CText s = _T("12345678909678543213");
            map<CText::Char, int> freq;
            s.countChars(freq);

            if(freq.find(_T('a')) != freq.end())
                goto error;

            if(freq[_T('0')] != 1 || freq[_T('1')] != 2 || freq[_T('2')] != 2 || freq[_T('3')] != 3)
                goto error;
        }

        {
            CText s = _T("abCbBAdda");
            map<CText::Char, int> freq;
            s.countChars(freq);
            if(freq.find(_T('a')) == freq.end() || freq[_T('a')] != 2)
                goto error;
            s.countChars(freq, false);
            if(freq.find(_T('A')) == freq.end() || freq[_T('A')] != 3)
                goto error;
        }

        {
            CText s = _T("    the quick brown fox     jumps     over  the lazy dog ");
            if(s.countChains(_T(' ') != 10))
                goto error;

            if(s.countWords() != 9)
                goto error;

            s = _T("    the quick brown fox  .-,   jumps   ,,,,  over - the lazy dog!");
            if(s.countChainsAny(_T(" .,-!")) != 10)
                goto error;

            if(s.countWords(_T(" .,-!")) != 9)
                goto error;
        }

        {
            CText s = _T("Nory was a Catholic because her mother was a Catholic, and Nory's mother was a Catholic because her father was a Catholic, and her father was a Catholic because his mother was a Catholic, or had been.");
            std::multimap<int, CText, std::greater<int> > freq;
            s.countWordFrequencies(freq);
            auto it = freq.begin();
            if(it == freq.end() || it->first != 6 || it->second != _T("Catholic"))
                goto error;
            it++;
            if(it == freq.end() || it->first != 6 || it->second != _T("a"))
                goto error;
        }


        {
            vector<CText::tstring> vec;
            CText s = _T("1Text 56 containig [12] several; 222 numbers:100");
            CText list;
            list.appendRange(_T('0'), _T('9'));
            if(s.collect(vec, list.str()) != 5)
                goto error;
            std::vector<CText::tstring> v_target = {_T("1"), _T("56"), _T("12"), _T("222"), _T("100")};
            if(vec != v_target)
                goto error;
        }

        {
            CText a = _T("ABC");
            CText b = _T("BCA");
            if(!CText::ArePermutation(a, b))
                goto error;

            std::vector<CText::tstring> v;
            if(CText::GeneratePermutations(v, a) != 6)
                goto error;

            std::vector<CText::tstring> v_target = {_T("ABC"), _T("ACB"), _T("BAC"), _T("BCA"), _T("CBA"), _T("CAB")};
            if(v != v_target)
                goto error;
        }

        printResult("test_count()", true);
        return 0;

    error:
        printResult("test_count()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_count() [exception]", false);
        return 1;
    }
}

int test_remove()
{
    try
    {
        {
            CText s = _T("abcabc");
            if(s.remove(_T('a')) != 2 || s != _T("bcbc"))
                goto error;

            s = _T("This is a monkey job!");
            if(s.remove(_T('!')) != 1 || s != _T("This is a monkey job"))
                goto error;
        }

        {
            CText s = _T("This is a monkey job!");
            if(s.erase(10, 7) != 7)
                goto error;
            if(s != _T("This is a job!"))
                goto error;
            if(s.erase(10, 5) != 4)
                goto error;
            if(s != _T("This is a "))
                goto error;
            s.removeLast();
            if(s != _T("This is a"))
                goto error;
        }

        {
            CText s = _T("This is a monkey job!");
            s.remove({_T(' '), _T('!')});
            if(s != _T("Thisisamonkeyjob"))
                goto error;
        }

        {
            CText s = _T("abaaaacaacd");
            if(s.reduceChain(_T('a')) != 4)
                goto error;
            if(s != _T("abacacd"))
                goto error;
        }

        {
            CText s = _T("111222223333334444444");
            s.reduceChainAny(_T("1234"));
            if(s != _T("1234"))
                goto error;
        }
        {
            CText s = _T("text1 2 abc3sc 2");
            s.reduceToNumber();
            if(s != _T("1232"))
                goto error;
        }

        {
            CText s = _T("this is some text");
            s.makeUnique(_T('s'));

            if(s != _T("this i ome text"))
                goto error;

            s = _T("123BXXXXAAAAAXXXXXXBBBBBXXXU");
            s.makeUnique();

            if(s != _T("123BXAU"))
                goto error;

            s = _T("11111111111111111111");
            s.makeUnique();
            if(s != _T("1"))
                goto error;
        }

        {
            //test limit
            CText s = _T("longlongword");
            s.limit(8);

            if(s != _T("longlong"))
                goto error;
        }

        {
            CText s1 = _T("This is a monkey job!");
            CText s2 = s1;
            s2.erase(0, 5);
            if(s2 != _T("is a monkey job!"))
                goto error;

            s2 = s1;
            s2.erase(5, 3);
            if(s2 != _T("This a monkey job!"))
                goto error;

            s2 = s1;
            s2.keep(5, 2);
            if(s2 != _T("is"))
                goto error;

            s2 = s1;
            s2.cutLeft(8);
            if(s2 != _T("a monkey job!"))
                goto error;
            s2 = s1;
            s2.cutRight(12);
            if(s2 != _T("This is a"))
                goto error;
            s2 = s1;
            s2.keepEnds(5);
            if(s2 != _T("This  job!"))
                goto error;
            s2 = s1;
            s2.cutEnds(5, 5);
            if(s2 != _T("is a monkey"))
                goto error;

            s2 = s1;
            s2.keepLeft(4);
            if(s2 != _T("This"))
                goto error;

            s2 = s1;
            s2.keepLeft(40);
            if(s2 != s1)
                goto error;

            s2 = s1;
            s2.keepRight(4);
            if(s2 != _T("job!"))
                goto error;

            s2 = s1;
            s2.cutAfterFirst(' ');
            if(s2 != _T("This"))
                goto error;

            s2 = s1;
            s2.cutAfterFirst('s', true);
            if(s2 != _T("This"))
                goto error;

            s2 = s1;
            s2.cutAfterFirst('5');
            if(s2 != _T("This is a monkey job!"))
                goto error;

            s2 = s1;
            s2.cutAfterFirst('T');
            if(s2 != _T("") || !s2.isEmpty())
                goto error;

            s2 = s1;
            s2.cutAfterFirstOfAny(_T("omn"));
            if(s2 != _T("This is a "))
                goto error;

            s2 = s1;
            s2.cutAfterFirst(_T("monkey"));
            if(s2 != _T("This is a "))
                goto error;

            if(s1.substringBeforeFirst(_T("monkey")) != _T("This is a "))
                goto error;

            s2 = s1;
            s2.cutAfterLast('s');
            if(s2 != _T("This i"))
                goto error;

            s2 = s1;
            s2.cutAfterLast('y', true);
            if(s2 != _T("This is a monkey"))
                goto error;

            s2 = s1;
            s2.cutAfterLast(_T("monkey"));
            if(s2 != _T("This is a "))
                goto error;

            s2 = s1;
            s2.cutAfterLastOfAny(_T("mon"), true);
            if(s2 != _T("This is a monkey jo"))
                goto error;
        }

        {
            CText s = _T("123a4b55cc90");
            s.removeAny(_T("abc"));
            if(s != _T("12345590"))
                goto error;
        }

        {
            CText s = _T("the quick brown fox jumps over the lazy dog");
            CText span = s.spanIncluding(_T("abcdghst"));
            if(span != _T("th"))
                goto error;
            span = s.spanExcluding(_T(" !,-"));
            if(span != _T("the"))
                goto error;
        }

        {
            CText s = _T(" \t\n   lazy dog");
            s.trimLeft();
            if(s != _T("lazy dog"))
                goto error;
            s = _T("000000000000101");
            s.trimLeft(_T("0"));
            if(s != _T("101"))
                goto error;

            s = _T("000000000000101");
            s.trimLeft(_T('0'));
            if(s != _T("101"))
                goto error;

            s = _T("lazy dog  \t\n            ");
            s.trimRight();
            if(s != _T("lazy dog"))
                goto error;

            s = _T("101000000000000");
            s.trimRight(_T('0'));
            if(s != _T("101"))
                goto error;

            s = _T("000000000000101");
            s.trimRight(_T('0'));
            if(s != _T("000000000000101"))
                goto error;

            s = _T(" \t\n   lazy dog   \t\n    ");
            s.trim();
            if(s != _T("lazy dog"))
                goto error;
        }

        {
            CText s = _T(" (value) ");
            if(s.substringBetween(_T('('), _T(')')) != _T("value"))
                goto error;

            if(!s.substringBetween(_T('['), _T(']')).isEmpty())
                goto error;

            s.between(_T('('), _T(')'));
            if(s != _T("value"))
                goto error;

            s = _T(" (value) ");
            s.between(_T('('), _T(')'), true);
            if(s != _T("(value)"))
                goto error;

            s = _T(" <begin>value<end>");
            s.between(_T("<begin>"), _T("<end>"));
            if(s != _T("value"))
                goto error;
            s = _T(" <begin>value<end>");
            s.between(_T("<begin>"), _T("<end>"), true);
            if(s != _T("<begin>value<end>"))
                goto error;
        }

        {
            CText s = _T("This is a monkey job!");
            s.remove(_T("monkey"));
            s.reduceChain(' ');
            if(s != _T("This is a job!"))
                goto error;
            s.remove(_T("This"));
            s.trim();
            if(s != _T("is a job!"))
                goto error;

            s = _T("WORD is upper of word");
            s.remove(_T("monkey"));
            s.reduceChain(' ');
            if(s != _T("WORD is upper of word"))
                goto error;

            s.remove(_T("word"));
            s.reduceChain(' ');

            if(s != _T("WORD is upper of "))
                goto error;

            s = _T("word is word");
            s.remove(_T("word"));
            s.reduceChain(' ');
            s.trim();

            if(s != _T("is"))
                goto error;

            s = _T("WORD is upper of word");
            s.remove(_T("word"), false);
            s.reduceChain(' ');
            s.trim();

            if(s != _T("is upper of"))
                goto error;
        }

        {
            CText s = _T("one and two or three or five");
            array<const CText::Char*,2> words = {_T("or"), _T("and")};
            s.removeAny(words);
            s.reduceChain(' ');
            if(s != _T("one two three five"))
                goto error;

            s = _T("one and two or three or five");
            vector <const CText::Char*> vec = {_T("or"), _T("and")};
            s.removeAny(vec);
            s.reduceChain(' ');
            if(s != _T("one two three five"))
                goto error;

            s = _T("one and two or three or five");
            s.removeAny({_T("or"), _T("and")});
            s.reduceChain(' ');
            if(s != _T("one two three five"))
                goto error;
        }

        {
            CText s = _T("Text containing <several> [blocks] separated by {brackets}");
            s.removeBlocks(_T("<[{"), _T(">]}"));
            s.reduceChain(' ');
            if(s != _T("Text containing separated by "))
                goto error;

            s = _T("Can \"Remove\" 'Literals' from a text");
            s.removeBlocks(_T("'\""), _T("\'\""));
            s.reduceChain(' ');
            if(s != _T("Can from a text"))
                goto error;
        }

        {
            CText::Char from[] = _T("BADCF");
            CText::Char to[] = _T(".....");
            CText::Swab(from, to, sizeof(from));
        }

        printResult("test_remove()", true);
        return 0;

    error:
        printResult("test_remove()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_remove() [exception]", false);
        return 1;
    }
}


int test_substring()
{
    try
    {
        {
            CText s1(_T("12345678"));
            CText s2 = s1.left(5);
            if(s2 != _T("12345"))
                goto error;
            s2 = s1.right(5);
            if(s2 != _T("45678"))
                goto error;
            s2 = s1.substringRight(4);
            if(s2 != _T("5678"))
                goto error;
            s2 = s1.substringLeft(4);
            if(s2 != _T("1234"))
                goto error;
            s2 = s1.substring(2, 3);
            if(s2 != _T("345"))
                goto error;
            s2 = s1.substringRight(s1.indexOf('3'));
            if(s2 != _T("345678"))
                goto error;
            s2 = s1.left(s1.indexOf('3'));
            if(s2 != _T("12"))
                goto error;
            s2 = s1.mid(2);
            if(s2 != _T("3456"))
                goto error;

            s1 = _T("ABCDEF");
            s2 = s1.substring(0, 2) + s1.substringRight(2);
            if(s2 != s1)
                goto error;
        }

        {
            CText s = _T("first and second or third and four");

            array<const CText::Char*,2> words = {_T("or"), _T("and")};

            size_t pos;
            size_t idx = s.indexOfAny(words, 0, true, &pos);

            if(idx != 6 || pos != 1)
                goto error;

            vector< const CText::Char* > vec = {_T("or"), _T("and")};

            idx = s.indexOfAny(vec, 0, true);

            if(idx != 6 || pos != 1)
                goto error;

            idx = s.indexOfAny(_T("stch"));

            if(idx != 3)
                goto error;


        }

        {
            CText s = CText::Substring(_T("Some Text"), 5);
            if(s != _T("Text"))
                goto error;
        }

        {
            CText s = _T("This is a monkey job!");
            if(s.substringBeforeFirst(_T('m')) != _T("This is a "))
                goto error;

            if(s.substringBeforeFirst(_T('m'), true) != _T("This is a m"))
                goto error;


        }



        printResult("test_substring()", true);
        return 0;

    error:
        printResult("test_substring()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_substring() [exception]", false);
        return 1;
    }
}

int test_convert()
{
    try
    {
        // integer
        {
            CText s = _T("123456");
            bool bOk;
            int ia = s.toInteger(bOk);
            if(ia != 123456 || !bOk)
                goto error;

            s = _T("BlaBla");
            ia = s.toInteger(bOk);
            if(bOk)
                goto error;

            s = _T("-2147483648");
            ia = s.toInteger(bOk);
            if(ia != -2147483647 - 1 || !bOk)
                goto error;

            s = _T("2147483647");
            ia = s.toInteger(bOk);
            if(ia != 2147483647 || !bOk)
                goto error;

            s = _T("2147483648");
            ia = s.toInteger(bOk);
            if(bOk)
                goto error;

            s = _T("-2147483649");
            ia = s.toInteger(bOk);
            if(bOk)
                goto error;
        }
        {
            CText s;
            s.fromInteger(2147483647);
            if(s != _T("2147483647"))
                goto error;
        }

        {
            // test with unsigned int
            CText s;
            s.fromInteger(4294967295);
            if(s != _T("4294967295"))
                goto error;
            bool bOk;
            unsigned int num = s.toUInteger(bOk);
            if(!bOk || num != 4294967295)
                goto error;
        }

        // test with long long
        {
            CText s;
            s.fromInteger(9223372036854775807);
            if(s != _T("9223372036854775807"))
                goto error;

        }

        {
            CText s;
            double d = 1234567890.78787878787878;
            s.fromDouble(d);
            if(s != _T("1234567890.787879"))
                goto error;
            s.fromDouble(d, 2);
            if(s != _T("1234567890.79"))
                goto error;
            bool bOk;
            double d2 = s.toDouble(bOk);
            if(d2 != 1234567890.79)
                goto error;
        }


        {
            CText s;
            s.fromBinary(123456);
            if(s != _T("00000000000000011110001001000000"))
                goto error;
            s.trimLeft(_T('0'));
            if(s != _T("11110001001000000"))
                goto error;

            s.fromBinary('A');
            if(s != _T("01000001"))
                goto error;
        }


        {
            CText s;
            s.fromHex(123456);
            if(s != _T("0x0001e240"))
                goto error;
            s.fromHex(123456, false, true);
            if(s != _T("0001E240"))
                goto error;
            s.fromHex((short)1234);
            if(s != _T("0x04d2"))
                goto error;
            s.fromHex((unsigned char)65);
            if(s != _T("0x41"))
                goto error;
        }


        {
            CText s(_T("123456"));
            if(!s.isNumber())
                goto error;
            s = _T("123a456");
            if(s.isNumber())
                goto error;
            s = _T("4536758698078098089089089678676968");
            if(!s.isNumber())
                goto error;
        }

        {
            CText s(_T("12AB56FE"));
            if(!s.isHexNumber())
                goto error;
        }

        {
            CText s(_T("01111011100001"));
            if(!s.isBinary())
                goto error;

            s = _T("01111011200001");
            if(s.isBinary())
                goto error;
        }

        // test format
        {
            CText s1;
            s1.format(_T("%d"), 5500);
            if(s1 != _T("5500"))
                goto error;

            s1.format(_T("Some %s and numbers (%d %d)"), _T("text"), 1300, 5500);
            if(s1 != _T("Some text and numbers (1300 5500)"))
                goto error;

            s1.format(_T("%0.2f"), 33.33333f);
            if(s1 != _T("33.33"))
                goto error;

            s1.format(_T("Format Text: %d%%"), 100);
            if(s1 != _T("Format Text: 100%"))
                goto error;

            s1.format(_T("Format float: %0.2f"), 1.55555);
            if(s1 != _T("Format float: 1.56"))
                goto error;
        }

        // integers array
        {
            CText s = _T("1,2,3,4,5,6,7,8,9");
            vector<int> v;
            vector<int> v_target = {1, 2, 3, 4, 5, 6, 7, 8, 9};

            if(!s.toArray<int>(v, _T(',')))
                goto error;

            if(v != v_target)
                goto error;

            s = _T("1,2,A,4,5,6,7,8,9");
            if(s.toArray<int>(v, _T(',')))
                goto error;

            s = _T("A,2,3,4,5,6,7,8,9");
            if(s.toArray<int>(v, _T(',')))
                goto error;

            s = _T("1|2,3,4,5,6,7,8,9");
            if(s.toArray<int>(v, _T(',')))
                goto error;

            s = _T("1|2|3|4|5|6|7|8|9");
            if(!s.toArray<int>(v, _T('|')))
                goto error;

            if(v != v_target)
                goto error;

            s = _T("1|2|3|4|5|6|7|8|9|");
            if(s.toArray<int>(v, _T('|')))
                goto error;

            s = _T("|1|2|3|4|5|6|7|8|9");
            if(s.toArray<int>(v, _T('|')))
                goto error;

            s = _T("1|2   |3|4  \t|5| \t 6|  \n  7|8|9");
            if(!s.toArray<int>(v, _T('|')))
                goto error;

            if(v != v_target)
                goto error;

            s = _T("1 2 3 4 5 6 7 8 9");
            if(!s.toArray<int>(v))
                goto error;
            if(v != v_target)
                goto error;

            s = _T("1\n2\n3\n4\n5\n6\n7\n8\n9");
            if(!s.toArray<int>(v, _T('\n')))
                goto error;
            if(v != v_target)
                goto error;
        }

        //test with other types
        {
            CText s = _T("1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9");
            vector<float> v;
            vector<float> v_target = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
            if(!s.toArray<float>(v, _T(',')))
                goto error;
            if(v != v_target)
                goto error;
        }


        //test with other types
        {
            CText s = _T("1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9");
            vector<double> v;
            vector<double> v_target = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};

            if(!s.toArray<double>(v, _T(',')))
                goto error;

            if(v != v_target)
                goto error;
        }

        //test with other types
        {
            CText s = _T("a, b, c, d");
            vector<CText::Char> v;
            vector<CText::Char> v_target = {_T('a'), _T('b'), _T('c'), _T('d')};

            if(!s.toArray<CText::Char>(v, _T(',')))
                goto error;
            if(v != v_target)
                goto error;
        }

        {
            CText s = _T("0A 1E 2A 1B");
            vector<int> v;
            vector<int> v_target = {10, 30, 42, 27};

            if(!s.toArray<int>(v, _T(' '), true))
                goto error;

            if(v != v_target)
                goto error;
        }

        {
            CText s = _T("1a:2b:3c:4d:5e:6f");
            vector<int> v;
            if(!s.toArray<int>(v, _T(':'), true))
                goto error;
            vector<int> v_target = {26, 43, 60, 77, 94, 111};
            if(v != v_target)
                goto error;
        }

        // test without separator
        {
            CText s = _T("0A1E2A1B");
            vector<int> v;
            vector<int> v_target = {10, 30, 42, 27};

            // interpret characters as hex (two bytes)
            if(!s.toArray<int>(v, 0, true))
                goto error;

            if(v != v_target)
                goto error;

            // convert each character to one byte (the default)
            if(!s.toArray<int>(v, _T('\0')))
                goto error;

            vector<int> v_target_2 = {48, 65, 49, 69, 50, 65, 49, 66};
            if(v != v_target_2)
                goto error;
        }

        // convert hex to chars string 
        {
            CText s = _T("48 65 6C 6C 6F 20 57 6F 72 6C 64");
            std::vector<int> bytes;
            if(!s.toChars<int>(bytes, true))
                goto error;
            s.fromChars<int>(bytes);
            if(s != _T("Hello World"))
                goto error;
        }

        // integers matrix
        {
            std::vector<std::vector<int>> m;
            std::vector<std::vector<int>> m_target =
            {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9},
            };
            CText s = _T("1 2 3\n4 5 6\n7 8 9");
            if(!s.toMatrix<int>(m, _T(' ')))
                goto error;
            if(m != m_target)
                goto error;
        }

        // floats matrix
        {
            std::vector<std::vector<float>> m;
            std::vector<std::vector<float>> m_target =
            {
                {1.0, 2.0, 3.0},
                {4.0, 5.0, 6.0},
                {7.0, 8.0, 9.0},
            };
            CText s = _T("1.0 2.0 3.0\n4.0 5.0 6.0\n7.0 8.0 9.0");
            if(!s.toMatrix<float>(m, _T(' ')))
                goto error;
            if(m != m_target)
                goto error;
        }


        {
            CText s;
            CText::tstring s2(_T("fox"));
            s << _T("The ") << _T("quick ") << s2;
            if(s != _T("The quick fox"))
                goto error;

            CText s3(_T(" jumps"));
            s << s3;

            if(s != _T("The quick fox jumps"))
                goto error;

        }

        {
            CText s;
            s << 5 << 6 << '0' << 'A' << 'Z';
            if(s != _T("560AZ"))
                goto error;
        }

        {
            CText s;
            s << 5.1111 ;
            if(s != _T("5.1111"))
                goto error;
        }

        printResult("test_convert()", true);
        return 0;

    error:
        printResult("test_convert()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_convert() [exception]", false);
        return 1;
    }
}

int test_replace()
{
    try
    {
        // characters replace
        {
            CText s = _T("The quick brown fox jumps over the lazy dog");
            s.replace(_T('e'), _T('E'));
            if(s != _T("ThE quick brown fox jumps ovEr thE lazy dog"))
                goto error;
            s.replaceAny(_T("abcd"), _T('X'));
            if(s != _T("ThE quiXk Xrown fox jumps ovEr thE lXzy Xog"))
                goto error;

            s = _T("abc");
            s.replaceFirst('c').replaceLast('a');
            if(s != _T("cba"))
                goto error;
        }

        {
            CText s = _T("The quick fox");
            s.replace(4, 5, _T("12345"));
            if(s != _T("The 12345 fox"))
                goto error;

            CText s2 = _T("12345");
            s = _T("The quick fox");
            s.replace(4, 5, s2.str());

            s = _T("Text with word quick word replace word");
            s.replace(_T("word"), _T("longer"));
            if(s != _T("Text with longer quick longer replace longer"))
                goto error;
            s.replace(_T("longer"), _T("word"));
            if(s != _T("Text with word quick word replace word"))
                goto error;

            s.replace(_T("Text"), _T("Something"));
            if(s != _T("Something with word quick word replace word"))
                goto error;

            s.replace(_T("Something"), _T("Text"));
            if(s != _T("Text with word quick word replace word"))
                goto error;
        }

        {
            CText s = _T("The quick brown fox jumps over the lazy dog");
            array<const CText::Char*,3> words = {_T("quick"), _T("fox"), _T("dog")};
            s.replaceAny(words, _T("****"));
            if(s != _T("The **** brown **** jumps over the lazy ****"))
                goto error;

            s = _T("The quick brown fox jumps over the lazy dog");
            vector<const CText::Char*> vec = {_T("quick"), _T("fox"), _T("dog")};
            s.replaceAny(vec, _T("xxxx"));
            if(s != _T("The xxxx brown xxxx jumps over the lazy xxxx"))
                goto error;

            s = _T("The quick brown fox jumps over the lazy dog");
            s.replaceAny(words, _T('-'));
            if(s != _T("The ----- brown --- jumps over the lazy ---"))
                goto error;

            s = _T("The quick brown fox jumps over the lazy dog");
            s.replaceAny(vec, _T('-'));
            if(s != _T("The ----- brown --- jumps over the lazy ---"))
                goto error;
        }

        {
            array<const CText::Char*, 2> words1 = {_T("fox"), _T("dog")};
            array<const CText::Char*, 2> words2 = {_T("dog"), _T("fox")};
            CText s = _T("The quick brown fox jumps over the lazy dog");
            s.replaceAny(words1, words2);
            if(s != _T("The quick brown dog jumps over the lazy fox"))
                goto error;
        }

        {
            std::vector<CText> words1 = {_T("fox"), _T("dog")};
            std::vector<CText> words2 = {_T("dog"), _T("fox")};
            CText s = _T("The quick brown fox jumps over the lazy dog");
            s.replaceAny(words1, words2);
            if(s != _T("The quick brown dog jumps over the lazy fox"))
                goto error;
        }

        {
            std::vector<const CText::Char*> words1 = {_T("fox"), _T("dog")};
            std::vector<const CText::Char*> words2 = {_T("dog"), _T("fox")};
            CText s = _T("The quick brown fox jumps over the lazy dog");
            s.replaceAny(words1, words2);
            if(s != _T("The quick brown dog jumps over the lazy fox"))
                goto error;
        }

        {
            CText s = _T("The quick brown fox jumps over the lazy dog");
            s.replaceAny({_T("fox"), _T("dog")}, {_T("dog"), _T("fox")});
            if(s != _T("The quick brown dog jumps over the lazy fox"))
                goto error;
        }

        {
            CText s = _T("The quick brown Fox jumps over the lazy Dog");
            s.replaceAny({_T("fox"), _T("dog")}, {_T("dog"), _T("fox")}, false);
            if(s != _T("The quick brown dog jumps over the lazy fox"))
                goto error;
        }

        printResult("test_replace()", true);
        return 0;

    error:
        printResult("test_replace()", false);
        return 1;

    }
    catch(...)
    {
        printResult("test_replace() [exception]", false);
        return 1;
    }
}

int test_split()
{
    try
    {
        {
            CText text(_T("Text Splited by a character test"));
            CText s1, s2, s3;

            if(!text.splitAt(4, s1, s2))
                goto error;

            if(s1 != _T("Text") || s2 != _T(" Splited by a character test"))
                goto error;

            if(!text.splitAt(0, s1, s2))
                goto error;

            if(s1 != _T("") || s2 != _T("Text Splited by a character test"))
                goto error;

            if(!text.splitAt(text.length(), s1, s2))
                goto error;

            if(s2 != _T("") || s1 != _T("Text Splited by a character test"))
                goto error;

            if(!text.splitAt(4, s1, s2, true))
                goto error;

            if(s1 != _T("Text") || s2 != _T("Splited by a character test"))
                goto error;

            if(!text.splitAt(text.length(), s1, s2, true))
                goto error;

            if(s2 != _T("") || s1 != _T("Text Splited by a character test"))
                goto error;

            if(!text.splitAtFirst(_T('a'), s1, s2))
                goto error;

            if(s1 != _T("Text Splited by ") || s2 != _T("a character test"))
                goto error;

            if(!text.splitAtFirst(_T('T'), s1, s2))
                goto error;

            if(s1 != _T("") || s2 != _T("Text Splited by a character test"))
                goto error;

            if(!text.splitAtLast('a', s1, s2))
                goto error;

            if(s1 != _T("Text Splited by a char") || s2 != _T("acter test"))
                goto error;

            if(!text.splitAtFirstOfAny(_T("abcd"), s1, s2))
                goto error;

            if(s1 != _T("Text Splite") || s2 != _T("d by a character test"))
                goto error;

            if(!text.splitAtLastOfAny(_T("abcd"), s1, s2))
                goto error;

            if(s1 != _T("Text Splited by a chara") || s2 != _T("cter test"))
                goto error;

            if(!text.splitAtFirst(_T("by"), s1, s2))
                goto error;

            if(s1 != _T("Text Splited ") || s2 != _T("by a character test"))
                goto error;
        }

        {
            CText s = _T("line 1\r\nLine2\n\nLine3\n");
            vector<CText> v;
            s.collectLines(v);
            vector<CText> v_target = {_T("line 1"), _T("Line2"), _T("Line3")};
            if(v != v_target)
                goto error;
        }


        printResult("test_split()", true);
        return 0;

    error:
        printResult("test_split()", false);
        return 1;

    }
    catch(...)
    {
        printResult("test_split() [exception]", false);
        return 1;
    }
}

int test_insert()
{
    try
    {
        {
            CText s1 = _T("This is  monkey job!");
            CText s2 = s1;
            s2.insert(8, _T('a'));
            if(s2 != _T("This is a monkey job!"))
                goto error;

            s2.insert(100, _T('!'));
            if(s2 != _T("This is a monkey job!!"))
                goto error;

            s1 = _T("This is job!");
            s2 = s1;
            s2.insert(7, _T(" monkey"));
            if(s2 != _T("This is monkey job!"))
                goto error;

            s1 = _T("This is monkey ");
            s1.insert(s1.length(), _T("job"));
            if(s1 != _T("This is monkey job"))
                goto error;

            s2 = _T("This is job!");
            s2.insert(7, 5, _T(" monkey"));
            if(s2 != _T("This is monk job!"))
                goto error;

            s1 = _T("Hello");
            s1.paddRight('X', 10);

            if(s1 != _T("HelloXXXXX") || s1.length() != 10)
                goto error;

            s1.paddLeft('0', 15);

            if(s1 != _T("00000HelloXXXXX") || s1.length() != 15)
                goto error;
        }

        {
            CText s = _T("Test");
            s.enclose(_T('('), _T(')'));
            if(s != _T("(Test)"))
                goto error;
            s.enclose(_T('('), _T(')'));
            if(s != _T("(Test)"))
                goto error;
            s.enclose(_T('('), _T(')'), false);
            if(s != _T("((Test))"))
                goto error;
            s.unenclose(_T('('), _T(')'));
            if(s != _T("Test"))
                goto error;

            s = _T("Test");
            s.enclose(_T("begin "), _T(" end"));
            if(s != _T("begin Test end"))
                goto error;

            s = _T("Test");
            s.quote();
            if(s != _T("\"Test\""))
                goto error;
            s.unquote();
            if(s != _T("Test"))
                goto error;
        }

        printResult("test_insert()", true);
        return 0;

    error:
        printResult("test_insert()", false);
        return 1;

    }
    catch(...)
    {
        printResult("test_insert() [exception]", false);
        return 1;
    }
}

int test_blocks()
{
    try
    {
        {
            CText s = _T("{{[[(())]]}}");
            if(!s.checkBalance(_T("({["), _T(")}]")))
                goto error;

            s = _T("{[(])}");
            if(s.checkBalance(_T("({["), _T(")}]")))
                goto error;

            s = _T("{  [  (expression)]  } ");
            if(!s.checkBalance(_T("({["), _T(")}]")))
                goto error;
        }

        printResult("test_blocks()", true);
        return 0;

    error:
        printResult("test_blocks()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_blocks() [exception]", false);
        return 1;
    }
}

int test_collect()
{
    try
    {
        {
            CText s = _T("The quick  brown fox jumps  over the lazy dog");
            vector<CText> words;
            if(s.split(words) != 9)
                goto error;
            vector<CText> words_target = {_T("The"), _T("quick"), _T("brown"), _T("fox"), _T("jumps"), _T("over"), _T("the"), _T("lazy"), _T("dog")};
            if(words != words_target)
                goto error;
            s = _T("The,quick,brown,fox,jumps,over,the,lazy,dog");
            if(s.split(words, false, _T(",")) != 9)
                goto error;
            if(words != words_target)
                goto error;
            s.fromArray(words, _T("|"));
            if(s != _T("The|quick|brown|fox|jumps|over|the|lazy|dog"))
                goto error;

        }

        printResult("test_collect()", true);
        return 0;

    error:
        printResult("test_collect()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_collect() [exception]", false);
        return 1;
    }
}

int test_unicode()
{
    try
    {
        // test initialize from unicode strings
        {
            CText s;
            CText::FromSingle("Hello World", s);
            if(s != _T("Hello World"))
                goto error;

            s.fromSingle("Hello World");
            if(s != _T("Hello World"))
                goto error;

            CText::FromWide(L"Hello World", s);
            if(s != _T("Hello World"))
                goto error;

            s.fromWide(L"Hello World");
            if(s != _T("Hello World"))
                goto error;
        }

        {
            CText s(_T("Hello World"));
            CTextT<char> s2 = s.toSingle();
            if(s2 != "Hello World")
                goto error;
#ifdef _UNICODE
            if(CText::IsWide())
            {
                s = _T("Привет");
                s2 = s.toSingle();
                if(s2 != u8"Привет")
                    goto error;
            }
#endif
        }

        {
            CText s(_T("Hello World"));
            CTextT<wchar_t> s2 = s.toWide();
            if(s2 != L"Hello World")
                goto error;
        }

        printResult("test_unicode()", true);
        return 0;

    error:
        printResult("test_unicode()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_unicode() [exception]", false);
        return 1;
    }
}

int test_edit_distances()
{
    try
    {
        {
            if(CText::Levenshtein(_T("GUMBO"), _T("GAMBOL")) != 2)
                goto error;

            if(CText::Levenshtein(_T("gas"), _T("mass")) != 2)
                goto error;

            if(CText::Levenshtein(_T("ghost"), _T("host")) != 1)
                goto error;

            if(CText::Levenshtein(_T("gamble"), _T("gang")) != 4)
                goto error;
        }

        {
            if(CText::HammingDistance(_T("ball"), _T("rainball")) != std::string::npos)
                goto error;  //

            if(CText::HammingDistance(_T("ball"), _T("call")) != 1)
                goto error;  //

            if(CText::HammingDistance(_T("horror"), _T("mirror")) != 2)
                goto error;  //
        }

        printResult("test_edit_distances()", true);
        return 0;

    error:
        printResult("test_edit_distances()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_edit_distances() [exception]", false);
        return 1;
    }
}


int test_file()
{
    try
    {
        // test read from ASCI text file
        {
            CText path = getcwd(0, 0);
            path += _T("/test.txt");
            CText s;
            if(!s.readFile(path.str()))
                goto error;

            if(s != _T("Hello World"))
                goto error;
        }

        // test read from UTF8 file
        {
#ifdef _UNICODE
            {
                CText path = getcwd(0, 0);
                path += _T("/test_UTF8.txt");
                CText s;
                if(!s.readFile(path.str()))
                    goto error;
                if(s != _T("Привет"))
                    goto error;
            }
#endif
        }
#ifdef _UNICODE
        //  test with UTF16LE file
        {
            if(CText::IsWide())
            {
                CText path = getcwd(0, 0);
                path += _T("/test_UTF16LE.txt");
                CText s;
                if(!s.readFile(path.str()))
                    goto error;
                if(s != _T("Привет"))
                    goto error;
            }
        }
#endif
#ifdef _UNICODE
        //  test with UTF16BE file
        {
            if(CText::IsWide())
            {
                CText path = getcwd(0, 0);
                path += _T("/test_UTF16BE.txt");
                CText s;
                s.readFile(path.str());
                if(s != _T("Привет"))
                    goto error;
            }
        }
#endif
        // test write ANSI file
        {
            if(!CText::IsWide())
            {
                CText s(_T("Hello World"));
                CText path = getcwd(0, 0);
                path += _T("/test2.txt");
                s.writeFile(path.str(), CText::ENCODING_ASCII);
                CText s2;
                if(!s2.readFile(path.str()))
                    goto error;
                if(s != s)
                    goto error;
            }
        }

        // test write UTF8 file
        {
            CText s(_T("Hello World"));
            CText path = getcwd(0, 0);
            path += _T("/test2_UTF8.txt");
            s.writeFile(path.str(), CText::ENCODING_UTF8);
            CText s2;
            s2.readFile(path.str());
            if(s != s)
                goto error;
        }

        // test write UTF16LE
        {
#ifdef _UNICODE
            {
                CText s(_T("Привет"));
                CText path = getcwd(0, 0);
                path += _T("/test2_UTF16LE.txt");
                s.writeFile(path.str(), CText::ENCODING_UTF16LE);
                s.readFile(path.str());
                if(s != _T("Привет"))
                    goto error;
            }
#endif
        }
        {
            if(!CText::IsWide())
            {
                CText s(_T("Hello World"));
                CText path = getcwd(0, 0);
                path += _T("/test2_UTF16LE_2.txt");
                s.writeFile(path.str(), CText::ENCODING_UTF16LE);
                s.readFile(path.str());

                if(s != _T("Hello World"))
                    goto error;
            }
        }

        {
            //if(!CText::IsWide())
            {
                CText s(_T("Hello World"));
                CText path = getcwd(0, 0);
                path += _T("/test2_UTF16BE_2.txt");
                s.writeFile(path.str(), CText::ENCODING_UTF16BE);
                s.readFile(path.str());
                if(s != _T("Hello World"))
                    goto error;
            }
        }
        printResult("test_file()", true);
        return 0;

    error:
        printResult("test_file()", false);
        return 1;
    }
    catch(...)
    {
        printResult("test_file() [exception]", false);
        return 1;
    }
}

int unitTest()
{
    int errors = 0;
    errors += test_init();
    errors += test_add();
    errors += test_static();
    errors += test_find();
    errors += test_compare();
    errors += test_modify();
    errors += test_transform();
    errors += test_words();
    errors += test_count();
    errors += test_remove();
    errors += test_substring();
    errors += test_convert();
    errors += test_replace();
    errors += test_split();
    errors += test_insert();
    errors += test_blocks();
    errors += test_collect();
    errors += test_unicode();
    errors += test_edit_distances();
    errors += test_file();

    return errors;
}




