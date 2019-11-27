#include <iostream>
#include "../CTEXT/CText.h"
#include "tchar_utils.h"

int main()
{    
    const char* input_name = "/Unsorted.txt";
    const char* output_name = "/Padded.txt";

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
    str.linesPaddRight(_T('.'), 60);
    str.writeFile(pathOut.str(), CText::ENCODING_ASCII);
    return 0 ;
}
