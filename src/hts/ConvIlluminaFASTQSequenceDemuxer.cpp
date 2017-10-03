//
//  ConvIlluminaFASTQSequenceDemuxer.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 8/11/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include "ConvIlluminaFASTQSequenceDemuxer.hpp"

namespace hts
{

ConvIlluminaFASTQSequenceDemuxer::ConvIlluminaFASTQSequenceDemuxer(const std::string& table_file_path, const std::string& main_file_name, const std::string& file_dir, std::size_t max_seqs, bool flush, const std::string& line_delim_type, bool verb) : ConvIlluminaFASTQSequenceDemuxerType(table_file_path, main_file_name, file_dir, max_seqs, flush, line_delim_type, verb) {}

ConvIlluminaFASTQSequenceDemuxer::ConvIlluminaFASTQSequenceDemuxer(const WellBarcodeTable& table, PairedFASTQFileGroupOutputStreams&& ostreams, std::size_t max_seqs, bool flush, bool verbose) : ConvIlluminaFASTQSequenceDemuxerType(table, std::move(ostreams), max_seqs, flush, verbose) {}

PairedConvIlluminaFASTQSequence ConvIlluminaFASTQSequenceDemuxer::makeSequence(const ConvIlluminaFASTQSequence& seq_r1, const ConvIlluminaFASTQSequence& seq_r2, const bool& parse_pair_seq)
{
    return PairedConvIlluminaFASTQSequence(seq_r1, seq_r2, parse_pair_seq);
}

}
