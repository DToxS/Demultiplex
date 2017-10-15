//
//  LineReader.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 9/7/17.
//  Copyright © 2017 Granville Xiong. All rights reserved.
//

#include <sstream>
#include <utility>
#include "LineReader.hpp"
#include "SystemProperties.hpp"

namespace utk
{

/// \brief Cross-platform line reader for text file
/// This class reads in a line from a text file and removes all line delimiter
/// characters:
///     Unix: \n
///     Windows: \r\n
///     Classic Macintosh: \r
    
LineReader::LineReader() :
    std::ifstream(),
    line_delim{widen('\0')},
    pre_delim{widen('\0')},
    file_end{false} {}

LineReader::LineReader(const std::string& file_name_arg, const std::string& line_delim_type_arg) :
    std::ifstream(file_name_arg),
    file_name{file_name_arg},
    line_delim_type{line_delim_type_arg},
    line_delim{widen(FileSystem::line_delims.at(line_delim_type))},
    pre_delim{widen(FileSystem::pre_delims.at(line_delim_type))},
    file_end{false}
{
    checkOpen();
}

LineReader::LineReader(LineReader&& file) :
    std::ifstream(std::move(file)),
    file_name{std::move(file.file_name)},
    line_delim_type{std::move(file.line_delim_type)},
    line_delim{file.line_delim},
    pre_delim{file.pre_delim},
    file_end{file.file_end} {}

LineReader::~LineReader() noexcept {}

LineReader& LineReader::operator=(LineReader&& file)
{
    if(this != &file)
    {
        std::ifstream::operator=(std::move(file));
        file_name = std::move(file.file_name);
        line_delim_type = std::move(file.line_delim_type);
        line_delim = file.line_delim;
        pre_delim = file.pre_delim;
        file_end = file.file_end;
    }
    return *this;
}

void LineReader::checkOpen()
{
    if(!is_open())
    {
        std::stringstream str;
        str << file_name << " cannot be read";
        throw std::runtime_error(str.str());
    }
}

/// Open file and initialize parameters.
void LineReader::open(const std::string& file_name_arg, const std::string& line_delim_type_arg)
{
    file_name = file_name_arg;
    std::ifstream::open(file_name);
    checkOpen();
    line_delim_type = line_delim_type_arg;
    line_delim = widen(FileSystem::line_delims.at(line_delim_type));
    pre_delim = widen(FileSystem::pre_delims.at(line_delim_type));
}

/// Read a text line and remove line delimiters.
bool LineReader::readLine(std::string& line)
{
    // Read a line.
    bool status = static_cast<bool>(std::getline(*this, line, line_delim));

    // Remove non-empty pre-delim character if the type of line delimiter
    // is different from the type of current operating system.
    if(status && !line.empty() && pre_delim != '\0' && line_delim_type != OperatingSystem::type) line.pop_back();

    // Set the flag if file end is reached.
    if(eof()) file_end = true;

    return status;
}

/// Read multiple text lines.
LineReader::LinesType LineReader::readLines(std::size_t n_lines)
{
    // Initialize lines.
    LinesType lines;

    // Start reading multiple lines.
    if(!file_end)
    {
        if(n_lines > 0)
        {
            // Read specified number of lines.
            for(std::size_t counts = 0; counts < n_lines; ++counts)
            {
                if(std::string line; readLine(line)) lines.push_back(std::move(line));
                else break;
            }
        }
        else
        {
            // Read all lines.
            for(std::string line; readLine(line);) lines.push_back(std::move(line));
        }
    }

    return lines;
}

}
