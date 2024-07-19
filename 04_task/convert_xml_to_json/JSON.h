#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class XmlToJsonConverter
{
public:
    XmlToJsonConverter(const std::string& xmlFilePath)
    {
        std::ifstream xmlFile(xmlFilePath);
        if (!xmlFile.is_open())
        {
            throw std::runtime_error("Failed to open XML file.");
        }
        boost::property_tree::read_xml(xmlFile, pt);
    }

    void convertToJson(std::ostream& output)
    {
        convertNodeToJson(pt, output, 0);
    }

    void saveJsonToFile(const std::string& jsonFilePath)
    {
        std::ofstream jsonFile(jsonFilePath);
        if (jsonFile.is_open())
        {
            convertToJson(jsonFile);
            jsonFile.close();
            std::cout << "Formatted JSON data saved to " << jsonFilePath << std::endl;
        }
        else
        {
            throw std::runtime_error("Failed to open output file for writing.");
        }
    }

private:
    boost::property_tree::ptree pt;

    void convertNodeToJson(const boost::property_tree::ptree& node, std::ostream& output, int indent)
    {
        for (const auto& child : node)
        {
            output << std::string(indent, ' ') << "\"" << child.first << "\": ";
            if (!child.second.empty())
            {
                output << "{" << std::endl;
                convertNodeToJson(child.second, output, indent + 4);
                output << std::string(indent, ' ') << "}";
            }
            else
            {
                output << "\"" << child.second.data() << "\"";
            }
            if (&child != &(*node.rbegin()))
            {
                output << ",";
            }
            output << std::endl;
        }
    }
};