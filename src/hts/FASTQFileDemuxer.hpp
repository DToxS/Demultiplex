//
//  FASTQFileDemuxer.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 8/26/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#ifndef FASTQFileDemuxer_hpp
#define FASTQFileDemuxer_hpp

#include <memory>
#include <iostream>
#include "PairedFASTQFilePathReader.hpp"
#include "PairedFASTQSequencePipe.hpp"

namespace hts
{

template<typename FASTQFileType, typename FASTQDemuxerType>
class FASTQFileDemuxer
{
public:

    using FASTQDemuxerPtrType = std::unique_ptr<FASTQDemuxerType>;

private:

    /// \brief Path of the file containing all input FASTQ sequence files
    const std::string& fastq_file_paths_file_path;

    /// \brief Path of the file containing well numbers and barcodes
    const std::string& well_barcode_file_path;

    /// \brief Main name for all demultiplexed FASTQ sequence files
    const std::string& demux_file_name;

    /// \brief Output directory for all demultiplexed FASTQ sequence files
    const std::string& demux_file_dir;

    /// \brief Flag for parsing input FASTQ sequence files
    bool parse_seq;

    /// \brief Flag for parsing the first level of sequence ID line of input FASTQ files
    bool parse_seq_id_level_1;

    /// \brief Flag for parsing the second level of sequence ID line of input FASTQ files
    bool parse_seq_id_level_2;

    /// \brief Flush single written sequence from output stream to disk.
    /// Note: this option needs to be switched on in a multi-threading envronment.
    bool flush_seq_ostream;

    /// \brief Number of sequence fragments to read from input FASTQ files in a batch
    std::size_t n_read_seqs;

    /// \brief Number of sequence fragments to store in FASTQ demultiplexer before flushing
    /// This is the capacity of each sequence group in the demultiplexer.
    std::size_t n_group_seqs;

    /// \brief Flush multiple written sequences from output stream to disk.
    /// Note: this option needs to be switched on in a multi-threading envronment.
    bool flush_seqs_ostream;

    /// \brief Type of line delimiter of FASTQ paths file
    std::string fastq_paths_file_line_delim_type;

    /// \brief Type of line delimiter of well-barcode file
    std::string well_barcode_file_line_delim_type;

    /// \brief Type of line delimiter of FASTQ data files
    std::string fastq_data_file_line_delim_type;

    /// \brief Flag for verbose printing
    bool verbose;

    /// \brief Paths of all input FASTQ files
    PairedFASTQFilePaths fastq_file_paths;

    /// \brief FASTQ sequence demultiplexer
    FASTQDemuxerPtrType seq_demuxer_ptr;

public:

    FASTQFileDemuxer(const std::string& fastq_file_paths_file_path, const std::string& well_barcode_file_path, const std::string& demux_file_name, const std::string& demux_file_dir, bool parse_seq=true, bool parse_seq_id_level_1=true, bool parse_seq_id_level_2=false, bool flush_seq_ostream=false, std::size_t n_read_seqs=131072, std::size_t n_group_seqs=131072, bool flush_seqs_ostream=true, const std::string& fastq_paths_file_line_delim_type="unix", const std::string& well_barcode_file_line_delim_type="unix", const std::string& fastq_data_file_line_delim_type="unix", bool verbose=false) :
        fastq_file_paths_file_path{fastq_file_paths_file_path},
        well_barcode_file_path{well_barcode_file_path},
        demux_file_name{demux_file_name},
        demux_file_dir{demux_file_dir},
        parse_seq{parse_seq},
        parse_seq_id_level_1{parse_seq_id_level_1},
        parse_seq_id_level_2{parse_seq_id_level_2},
        flush_seq_ostream{flush_seq_ostream},
        n_read_seqs{n_read_seqs},
        n_group_seqs{n_group_seqs},
        flush_seqs_ostream{flush_seqs_ostream},
        fastq_paths_file_line_delim_type{fastq_paths_file_line_delim_type},
        well_barcode_file_line_delim_type{well_barcode_file_line_delim_type},
        fastq_data_file_line_delim_type{fastq_data_file_line_delim_type},
        verbose{verbose}
    {
        // 1) Initialize the paths of all input FASTQ files.
        PairedFASTQFilePathReader fastq_file_path_reader(fastq_file_paths_file_path, fastq_paths_file_line_delim_type);
        fastq_file_paths = fastq_file_path_reader.read();
        // 2) Setup FASTQ sequence demultiplexer.
        seq_demuxer_ptr = std::make_unique<FASTQDemuxerType>(well_barcode_file_path, demux_file_name, demux_file_dir, n_group_seqs, flush_seqs_ostream, well_barcode_file_line_delim_type, verbose);
    }

    template<typename... ArgTypes>
    void run(const ArgTypes&... args)
    {
        // 3) Demultiplex FASTQ sequences in each paired-end FASTQ file.
        for(const auto& fastq_file_path : fastq_file_paths)
        {
            // Open a pair of FASTQ files.
            FASTQFileType r1_fastq_file(fastq_file_path.first, fastq_data_file_line_delim_type, parse_seq, parse_seq_id_level_1, parse_seq_id_level_2, flush_seq_ostream);
            FASTQFileType r2_fastq_file(fastq_file_path.second, fastq_data_file_line_delim_type, parse_seq, parse_seq_id_level_1, parse_seq_id_level_2, flush_seq_ostream);
            // Send all sequences from paired FASTQ files to sequence demultiplexer.
            PairedFASTQSequencePipe<FASTQFileType, FASTQDemuxerType> seq_pipe(r1_fastq_file, r2_fastq_file, *seq_demuxer_ptr);
            seq_pipe.run(n_read_seqs, args...);
        }
        // 4) Write out remaining FASTQ sequences in demultiplexer.
        seq_demuxer_ptr->writeSequences(true);
    }

    void summary() const
    {
        // Print summary statistics of demultiplexed FASTQ sequences.
        std::cout << "Number of grouped FASTQ sequences: " << seq_demuxer_ptr->getNumberOfGroupedSequences() << ";  Number of un-grouped FASTQ sequences: " << seq_demuxer_ptr->getNumberOfUngroupedSequences() << std::endl;
    }
};

}

#endif /* FASTQFileDemuxer_hpp */
