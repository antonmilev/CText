#include <iostream>
#include "../CTEXT/CText.h"
#include "tchar_utils.h"

using namespace std;

int main()
{    
    const char* input_name = "/Columbus.txt";
    const char* output_name = "/Columbus_Highlight.html";

    CText pathIn = getcwd(0, 0);
    CText pathOut = pathIn;
    pathIn += input_name;
    pathOut += output_name;
    
    CText str;
    if(!str.readFile(pathIn.str()))
    {
        std::cerr << "Error, con not open file: " << pathIn << std::endl;
        return 0;
    }
    str.linesTrim(_T(". "));

    vector<CText> start = {_T("Col"), _T("Spa"), _T("Isa")};
    vector<CText> end = {_T("an"), _T("as")};
    vector<CText> contain = {_T("pe"), _T("sea")};
    //s.collectSubstrings(result, &start, &end, &contain);

   // str.wordsEnclose(_T("<b><FONT style=\"color: Navy\">"), _T("</b></FONT>"), &start, &end, &contain);

    str.wordsEnclose(_T("<mark>"), _T("</mark>"), &start, &end, &contain);
    str.push_front(_T("<html>\n"));
    str.push_back(_T("\n</html>"));

    str.writeFile(pathOut.str(), CText::ENCODING_ASCII);
    return 0;
}
