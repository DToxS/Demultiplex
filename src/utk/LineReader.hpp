//
//  LineReader.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 9/7/17.
//  Copyright © 2017 Granville Xiong. All rights reserved.
//

#ifndef LineReader_hpp
#define LineReader_hpp

#include <string>
#include <vector>
#include <fstream>

namespace utk
{

/// \brief Cross-platform line reader for text file
/// This class reads in a line from a text file and removes all line delimiter
/// characters:
///     Unix: \n
///     Windows: \r\n
///     Classic Macintosh: \r
class LineReader : public std::ifstream
{
public:

    using LinesType = std::vector<std::string>;

private:

    /// \brief Name of input FASTQ file
    std::string file_name;

    /// \brief Type of line delimiter of FASTQ file.
    std::string line_delim_type;

    /// \brief Line delimiter of FASTQ file.
    std::ios::char_type line_delim;

    /// \brief Character before the line delimiter
    std::ios::char_type pre_delim;

    /// \brief Flag for reaching the end of file
    bool file_end;

private:
    
    /// \brief Check if input can be opened
    void checkOpen();
    
public:

    LineReader();

    LineReader(const std::string& file_name_arg, const std::string& line_delim_type_arg);

    LineReader(const LineReader& file) = delete;

    LineReader(LineReader&& file);

    virtual ~LineReader() noexcept;

    LineReader& operator=(const LineReader& file) = delete;

    LineReader& operator=(LineReader&& file);

    /// \brief Open file and initialize parameters
    void open(const std::string& file_name_arg, const std::string& line_delim_type_arg);

    const std::string& getFileName() const
    {
        return file_name;
    }

    /// \brief Check if the end of file is reached
    bool isFileEnd() const
    {
        return file_end;
    }

    /// \brief Reset the flag of reaching the end of file
    void reset()
    {
        file_end = false;
    }

    /// \brief Read a text line and remove line delimiters
    bool readLine(std::string& line);

    /// \brief Read multiple text lines
    LinesType readLines(std::size_t n_lines=0);
};

}

#endif /* LineReader_hpp */
