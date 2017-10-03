//
//  main.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 5/2/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "hts/FASTQSequenceParserArguments.hpp"
#include "hts/DGEIlluminaFASTQFile.hpp"
#include "hts/ConvIlluminaFASTQFile.hpp"
#include "hts/DGEIlluminaFASTQSequenceDemuxer.hpp"
#include "hts/ConvIlluminaFASTQSequenceDemuxer.hpp"
#include "hts/FASTQFileDemuxer.hpp"

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;

    try
    {
        // Retrieve input arguments from command line.
        hts::FASTQSequenceParserArguments args(argc, argv, 6, 12);
        // Check input arguments.
        args.check();

        // Demultiplex FASTQ files for DGE or Conv sequence data.
        if(args.seq_data_type == "DGE")
        {
            // Initialize the parameters for reading input DGE FASTQ sequences.
            bool parse_seq {true}, parse_seq_id_level_1 {true}, parse_seq_id_level_2 {false};
            // Initialize the parameters for creating output DGE FASTQ sequences.
            bool parse_pair_seq=true, parse_compos_seq=true;
            // Initialize the DGE FASTQ file demultiplexer.
            hts::FASTQFileDemuxer<hts::DGEIlluminaFASTQFile, hts::DGEIlluminaFASTQSequenceDemuxer> dge_file_demuxer(args.fastq_file_paths_file_path, args.well_barcode_file_path, args.demux_file_name, args.demux_file_dir, parse_seq, parse_seq_id_level_1, parse_seq_id_level_2, args.n_read_seqs, args.n_group_seqs, args.flush_ostream, args.fastq_paths_file_line_delim_type, args.well_barcode_file_line_delim_type, args.fastq_data_file_line_delim_type);
            // Run DGE FASTQ file demultiplexer.
            dge_file_demuxer.run(parse_pair_seq, parse_compos_seq);
            // Print demultiplexing summary for DGE FASTQ files.
            dge_file_demuxer.summary();
        }
        else if(args.seq_data_type == "CONV")
        {
            // Initialize the parameters for reading input DGE FASTQ sequences.
            bool parse_seq {true}, parse_seq_id_level_1 {true}, parse_seq_id_level_2 {true};
            // Initialize the parameters for creating output Conv FASTQ sequences.
            bool parse_pair_seq=true;
            // Initialize the Conv FASTQ file demultiplexer.
            hts::FASTQFileDemuxer<hts::ConvIlluminaFASTQFile, hts::ConvIlluminaFASTQSequenceDemuxer> conv_file_demuxer(args.fastq_file_paths_file_path, args.well_barcode_file_path, args.demux_file_name, args.demux_file_dir, parse_seq, parse_seq_id_level_1, parse_seq_id_level_2, args.n_read_seqs, args.n_group_seqs, args.flush_ostream, args.fastq_paths_file_line_delim_type, args.well_barcode_file_line_delim_type, args.fastq_data_file_line_delim_type);
            // Run DGE FASTQ file demultiplexer.
            conv_file_demuxer.run(parse_pair_seq);
            // Print demultiplexing summary for DGE FASTQ files.
            conv_file_demuxer.summary();
        }
        else throw std::logic_error("Sequence Type must be: either DGE or Conv");
    }
    catch (const std::logic_error& e)
    {
        std::cerr << "Logical error: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Other error: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    
    return exit_code;
}
