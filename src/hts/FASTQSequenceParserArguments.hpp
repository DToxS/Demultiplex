//
//  FASTQSequenceParserArguments.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Granville Xiong on 10/1/17.
//  Copyright © 2017 Granville Xiong. All rights reserved.
//

#ifndef FASTQSequenceParserArguments_hpp
#define FASTQSequenceParserArguments_hpp

#include "utk/ProgramArguments.hpp"

namespace hts
{

/// \brief FASTQSequenceParserArguments checks input arguments for entire program
/// This class takes input arguments of main function, checks their validity,
/// and store them in corresponding member variables.
class FASTQSequenceParserArguments : public utk::ProgramArguments
{
public:

    /// \brief Path of a text file containing the paths of input FASTQ data files
    /// Format: two columns of file paths (with a header line: Read1 and Read2).
    std::string fastq_file_paths_file_path;

    /// \brief Path of a text file containing a list of sample barcodes
    /// Format: three columns: Plate, Well, and Barcode (no header line).
    std::string well_barcode_file_path;

    /// \brief Main name of generated demultiplexed FASTQ files
    std::string demux_file_name;

    /// \brief Path of the directory for generated demultiplexed FASTQ files
    std::string demux_file_dir;

    /// \brief Sequencing data type: DGE or Conv (case-insensitive)
    std::string seq_data_type;

    /// \brief Number of input FASTQ sequences in each reading operation
    std::size_t n_read_seqs;

    /// \brief Number of demultiplexed FASTQ sequences in each writing operation
    /// This is the capacity of each sequence group in the demultiplexer.
    std::size_t n_group_seqs;

    /// \brief Flush written sequences from output stream to disk.
    bool flush_ostream;

    /// \brief Type of line delimiter of FASTQ paths file
    std::string fastq_paths_file_line_delim_type;

    /// \brief Type of line delimiter of well-barcode file
    std::string well_barcode_file_line_delim_type;

    /// \brief Type of line delimiter of FASTQ data files
    std::string fastq_data_file_line_delim_type;

protected:

    /// \brief Help messages on program usage
    virtual void helpMessage() override;

    /// \brief Assign mandatory input arguments
    virtual void assignMandatoryArguments() override;

    /// \brief Assign optional input arguments
    virtual void assignOptionalArguments() override;

    /// \brief Validate input arguments
    virtual void validateArguments() override;

public:

    /// \brief Retrieve input arguments
    FASTQSequenceParserArguments(int argc, const char** argv, int min_argc, int max_argc);
};

}

#endif /* FASTQSequenceParserArguments_hpp */
