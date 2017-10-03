//
//  PairedDGEIlluminaFASTQSequence.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Granville Xiong on 7/8/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#ifndef PairedDGEIlluminaFASTQSequence_hpp
#define PairedDGEIlluminaFASTQSequence_hpp

// Note: DGEIlluminaFASTQSequence.hpp must be included before
// PairedFASTQSequenceCreator.hpp for the instantiation of the latter.
#include <vector>
#include "DGEIlluminaFASTQSequence.hpp"
#include "PairedFASTQSequenceCreator.hpp"

namespace hts
{

using PairedDGEIlluminaFASTQSequence = PairedFASTQSequenceCreator<DGEIlluminaFASTQSequence>;
using PairedDGEIlluminaFASTQSequences = std::vector<PairedDGEIlluminaFASTQSequence>;

// Output of paired DGE FASTQ sequence.
std::ostream& operator<<(std::ostream& os, const PairedDGEIlluminaFASTQSequence& seq);

}

#endif /* PairedDGEIlluminaFASTQSequence_hpp */
