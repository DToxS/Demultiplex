//
//  FileUtils.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 9/26/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <stdexcept>
#include "FileUtils.hpp"

namespace utk
{

/// Check if a file can be read.
bool isFileReadable(const std::string& file_path)
{
    return std::ifstream(file_path).is_open();
}

/// Check if a file can be read.
void checkFileReadability(const std::string& file_path)
{
    if(!std::ifstream(file_path).is_open())
    {
        std::stringstream str;
        str << file_path << " cannot be read";
        throw std::runtime_error(str.str());
    }
}

}
