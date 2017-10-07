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

/// \brief Demultiplexer of DGE FASTQ sequence
/// The demultiplexer of compoiste DGE FASTQ sequence.
using DGEIlluminaFASTQSequenceDemuxer = FASTQSequenceDemuxer<FASTQFileGroupOutputStreams, CompositedDGEIlluminaFASTQSequence, DGEIlluminaFASTQSequence, DGEIlluminaFASTQSequence, bool, bool>;

}

#endif /* DGEIlluminaFASTQSequenceDemuxer_hpp */
