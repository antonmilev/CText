#include <iostream>
#include "../CTEXT/CText.h"
#include "tchar_utils.h"

int main()
{    
    const char* input_name = "/Columbus.txt";
    const char* output_name = "/Columbus_Word_Frequencies.txt";

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

    std::multimap<int, CText, std::greater<int> > freq;

    str.countWordFrequencies(freq, true);

    str.compose(freq);

    str.writeFile(pathOut.str(), CText::ENCODING_ASCII);
    return 0;
}
