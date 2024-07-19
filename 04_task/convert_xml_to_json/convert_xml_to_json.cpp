#include "JSON.h"

int main() 
{
    XmlToJsonConverter converter("D:\\2.4.xml");
    //converter.convertToJson(std::cout);
    converter.saveJsonToFile("output.json");

    return 0;
}