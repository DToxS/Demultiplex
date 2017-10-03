//
//  DGEIlluminaFASTQSequenceDemuxer.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 8/10/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include "DGEIlluminaFASTQSequenceDemuxer.hpp"

namespace hts
{

/// \brief Demultiplexer of DGE FASTQ sequence
/// The demultiplexer of compoiste DGE FASTQ sequence.
DGEIlluminaFASTQSequenceDemuxer::DGEIlluminaFASTQSequenceDemuxer(const std::string& table_file_path, const std::string& main_file_name, const std::string& file_dir, std::size_t max_seqs, bool flush, const std::string& line_delim_type, bool verb) : DGEIlluminaFASTQSequenceDemuxerType(table_file_path, main_file_name, file_dir, max_seqs, flush, line_delim_type, verb) {}

DGEIlluminaFASTQSequenceDemuxer::DGEIlluminaFASTQSequenceDemuxer(const WellBarcodeTable& table, FASTQFileGroupOutputStreams&& ostreams, std::size_t max_seqs, bool flush, bool verbose) : DGEIlluminaFASTQSequenceDemuxerType(table, std::move(ostreams), max_seqs, flush, verbose) {}

// Create a compoiste DGE FASTQ sequence from a pair of DGE FASTQ sequence.
CompositedDGEIlluminaFASTQSequence DGEIlluminaFASTQSequenceDemuxer::makeSequence(const DGEIlluminaFASTQSequence& seq_r1, const DGEIlluminaFASTQSequence& seq_r2, const bool& parse_pair_seq, const bool& parse_compos_seq)
{
    return CompositedDGEIlluminaFASTQSequence(PairedDGEIlluminaFASTQSequence(seq_r1, seq_r2, parse_pair_seq), parse_compos_seq);
}

}
