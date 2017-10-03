//
//  StringUtils.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 5/6/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include <regex>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include "StringUtils.hpp"

namespace utk
{

/// Split a string using a specified separator.
std::vector<std::string> splitString(const std::string& str, const char* sep)
{
    std::vector<std::string> parts;
    if(!str.empty())
    {
        if(std::strlen(sep) > 0)
        {
            if(std::strcmp(sep,"|") != 0)
            {
                std::regex sep_regex(sep);
                for(auto part_it=std::sregex_token_iterator(str.begin(), str.end(), sep_regex, -1); part_it!=std::sregex_token_iterator(); part_it++)  parts.push_back(*part_it);
            }
            else throw std::logic_error("Character | must be escaped");
        }
        else parts.push_back(str);
    }
    return parts;
}

/// Convert a string to upper case.
std::string toUpperString(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){return std::toupper(c);});
    return str;
}

/// Convert a string to lower case.
std::string toLowerString(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){return std::tolower(c);});
    return str;
}

}
