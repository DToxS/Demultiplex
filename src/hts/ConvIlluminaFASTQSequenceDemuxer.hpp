//
//  ConvIlluminaFASTQSequenceDemuxer.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 8/11/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#ifndef ConvIlluminaFASTQSequenceDemuxer_hpp
#define ConvIlluminaFASTQSequenceDemuxer_hpp

#include "PairedFASTQFileGroupOutputStreams.hpp"
#include "PairedConvIlluminaFASTQSequence.hpp"
#include "FASTQSequenceDemuxer.hpp"

namespace hts
{

using ConvIlluminaFASTQSequenceDemuxerType = FASTQSequenceDemuxer<PairedFASTQFileGroupOutputStreams, PairedConvIlluminaFASTQSequence, ConvIlluminaFASTQSequence, ConvIlluminaFASTQSequence, bool>;

/// \brief Demultiplexer of Conv FASTQ sequence
/// The demultiplexer of paired Conv FASTQ sequence.
class ConvIlluminaFASTQSequenceDemuxer : public ConvIlluminaFASTQSequenceDemuxerType
{
protected:

    virtual PairedConvIlluminaFASTQSequence makeSequence(const ConvIlluminaFASTQSequence& seq_r1, const ConvIlluminaFASTQSequence& seq_r2, const bool& parse_pair_seq=true) override;

public:

    ConvIlluminaFASTQSequenceDemuxer(const std::string& table_file_path, const std::string& main_file_name, const std::string& file_dir, std::size_t max_seqs=0, bool flush=true, const std::string& line_delim_type="unix", bool verb=false);

    ConvIlluminaFASTQSequenceDemuxer(const WellBarcodeTable& table, PairedFASTQFileGroupOutputStreams&& ostreams, std::size_t max_seqs=0, bool flush=true, bool verbose=false);
};

}

#endif /* ConvIlluminaFASTQSequenceDemuxer_hpp */
