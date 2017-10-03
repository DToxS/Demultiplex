//
//  FASTQSequenceParserArguments.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Granville Xiong on 10/1/17.
//  Copyright © 2017 Granville Xiong. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "FASTQSequenceParserArguments.hpp"
#include "utk/SystemProperties.hpp"
#include "utk/StringUtils.hpp"
#include "utk/FileUtils.hpp"

namespace hts
{

/// Retrieve input arguments.
FASTQSequenceParserArguments::FASTQSequenceParserArguments(int argc, const char** argv, int min_argc, int max_argc) :
    utk::ProgramArguments(argc, argv, min_argc, max_argc),
    n_read_seqs{131072},
    n_group_seqs{131072},
    fastq_paths_file_line_delim_type{"unix"},
    well_barcode_file_line_delim_type{"unix"},
    fastq_data_file_line_delim_type{"unix"} {}

/// Assign mandatory input arguments
void FASTQSequenceParserArguments::assignMandatoryArguments()
{
    // Assign mandatory arguments.
    fastq_file_paths_file_path = argv[1];
    well_barcode_file_path = argv[2];
    demux_file_name = argv[3];
    demux_file_dir = argv[4];
    seq_data_type = utk::toUpperString(argv[5]);
}

/// Assign optional input arguments
void FASTQSequenceParserArguments::assignOptionalArguments()
{
    // Assign optional arguments.
    // 6th argument.
    if(argc > 6) n_read_seqs = utk::convert<std::size_t>(utk::toLowerString(argv[6]));
    // 7th argument.
    if(argc > 7) n_group_seqs = utk::convert<std::size_t>(utk::toLowerString(argv[7]));
    // 8th argument.
    if(argc > 8) fastq_paths_file_line_delim_type = utk::toLowerString(argv[8]);
    // 9th argument.
    if(argc > 9) well_barcode_file_line_delim_type = utk::toLowerString(argv[9]);
    // 10th argument.
    if(argc > 10) fastq_data_file_line_delim_type = utk::toLowerString(argv[10]);
}

/// Check input arguments.
void FASTQSequenceParserArguments::validateArguments()
{
    // Check the path of a text file containing a list of input paired FASTQ
    // files.
    utk::checkFileReadability(fastq_file_paths_file_path);

    // Check the path of a text file containing a list of sample barcodes.
    utk::checkFileReadability(well_barcode_file_path);

    // Check the main name of generated demultiplexed FASTQ files.
    if(demux_file_name.empty())
    {
        throw std::logic_error("Demux Main Name cannot be empty");
    }

    // Check the path of the directory for generated demultiplexed FASTQ
    // files.
    if(!utk::FileSystem::isDir(demux_file_dir))
    {
        std::stringstream str;
        str << demux_file_dir << " is not found";
        throw std::runtime_error(str.str());
    }

    // Check sequencing data type: DGE or Conv (case-insensitive).
    if(seq_data_type != "DGE" && seq_data_type != "CONV")
    {
        throw std::logic_error("Sequence Type must be: either DGE or Conv");
    }

    // Check the number of input FASTQ sequences in each reading operation.
    if(n_read_seqs > SIZE_MAX)
    {
        throw std::logic_error("Sequences Read Number is out of range");
    }

    // Check the number of demultiplexed FASTQ sequences in each writing operation.
    if(n_group_seqs > SIZE_MAX)
    {
        throw std::logic_error("Sequences Write Number is out of range");
    }

    // Check the type of line delimiter of FASTQ data files.
    if(fastq_paths_file_line_delim_type != "windows" && fastq_paths_file_line_delim_type != "unix" && fastq_paths_file_line_delim_type != "macintosh")
    {
        throw std::logic_error("Line Delimiter Type of FASTQ Path File must be one of: unix, windows, or macintosh");
    }

    // Check the type of line delimiter of FASTQ data files.
    if(well_barcode_file_line_delim_type != "windows" && well_barcode_file_line_delim_type != "unix" && well_barcode_file_line_delim_type != "macintosh")
    {
        throw std::logic_error("Line Delimiter Type of Well-Barcode File must be one of: unix, windows, or macintosh");
    }

    // Check the type of line delimiter of FASTQ data files.
    if(fastq_data_file_line_delim_type != "windows" && fastq_data_file_line_delim_type != "unix" && fastq_data_file_line_delim_type != "macintosh")
    {
        throw std::logic_error("Line Delimiter Type of FASTQ Data File must be one of: unix, windows, or macintosh");
    }
}

/// Print help messages on program usage.
void FASTQSequenceParserArguments::helpMessage()
{
    std::cerr << "Usage: " << prog_name << " [FASTQ List File] [Well-Barcode File] [Demux Main Name] [Demux Directory] [Sequence Type] [Sequences Read Number] [Sequences Write Number] [Line Delimiter Type of FASTQ Path File] [Line Delimiter Type of Well-Barcode File] [Line Delimiter Type of FASTQ Data File]" << '\n';
    std::cerr << "where:" << '\n';
    std::cerr << "       " << "[FASTQ Path File]: text file containing the paths of input FASTQ data files (Format: Read1, Read2)." << '\n';
    std::cerr << "       " << "[Well-Barcode File]: text file containing a list of sample barcodes (Format: Plate, Well, Barcode)." << '\n';
    std::cerr << "       " << "[Demux Main Name]: main name of generated demultiplexed FASTQ files." << '\n';
    std::cerr << "       " << "[Demux Directory]: directory for generated demultiplexed FASTQ files." << '\n';
    std::cerr << "       " << "[Sequence Type]: type of input FASTQ sequences: DGE or Conv." << '\n';
    std::cerr << "       " << "[Sequences Read Number]: number of input FASTQ sequences to read each time (Default: 131072)." << '\n';
    std::cerr << "       " << "[Sequences Write Number]: number of demultiplexed FASTQ sequences to write each time (Default: 131072)." << '\n';
    std::cerr << "       " << "[Line Delimiter Type of FASTQ Path File]: type of line delimiter of FASTQ path file: unix or windows (Default: unix)." << '\n';
    std::cerr << "       " << "[Line Delimiter Type of Well-Barcode File]: type of line delimiter of well-barcode file: unix or windows (Default: unix)." << '\n';
    std::cerr << "       " << "[Line Delimiter Type of FASTQ Data File]: type of line delimiter of FASTQ data files: unix or windows (Default: unix)." << std::endl;
}

}
