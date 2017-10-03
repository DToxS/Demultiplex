//
//  DGEIlluminaFASTQSequenceDemuxer.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 8/10/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#ifndef DGEIlluminaFASTQSequenceDemuxer_hpp
#define DGEIlluminaFASTQSequenceDemuxer_hpp

#include "FASTQFileGroupOutputStreams.hpp"
#include "DGEIlluminaFASTQSequence.hpp"
#include "CompositedDGEIlluminaFASTQSequence.hpp"
#include "FASTQSequenceDemuxer.hpp"

namespace hts
{

using DGEIlluminaFASTQSequenceDemuxerType = FASTQSequenceDemuxer<FASTQFileGroupOutputStreams, CompositedDGEIlluminaFASTQSequence, DGEIlluminaFASTQSequence, DGEIlluminaFASTQSequence, bool, bool>;

/// \brief Demultiplexer of DGE FASTQ sequence
/// The demultiplexer of compoiste DGE FASTQ sequence.
class DGEIlluminaFASTQSequenceDemuxer : public DGEIlluminaFASTQSequenceDemuxerType
{
protected:

    // Create a compoiste DGE FASTQ sequence from a pair of DGE FASTQ sequence.
    virtual CompositedDGEIlluminaFASTQSequence makeSequence(const DGEIlluminaFASTQSequence& seq_r1, const DGEIlluminaFASTQSequence& seq_r2, const bool& parse_pair_seq=true, const bool& parse_compos_seq=true) override;

public:

    DGEIlluminaFASTQSequenceDemuxer(const std::string& table_file_path, const std::string& main_file_name, const std::string& file_dir, std::size_t max_seqs=0, bool flush=true, const std::string& line_delim_type="unix", bool verb=false);

    DGEIlluminaFASTQSequenceDemuxer(const WellBarcodeTable& table, FASTQFileGroupOutputStreams&& ostreams, std::size_t max_seqs=0, bool flush=true, bool verbose=false);
};

}

#endif /* DGEIlluminaFASTQSequenceDemuxer_hpp */
