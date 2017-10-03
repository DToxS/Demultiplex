//
//  PairedDGEIlluminaFASTQSequence.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Granville Xiong on 7/8/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include "PairedDGEIlluminaFASTQSequence.hpp"

namespace hts
{

// Output of paired DGE FASTQ sequence.
std::ostream& operator<<(std::ostream& os, const PairedDGEIlluminaFASTQSequence& seq)
{
    const DGEIlluminaFASTQSequence& seq_1 = seq.getSequence1();
    os << seq_1[FASTQSequence::Identifier] << '\n';
    os << seq_1[FASTQSequence::Sequence] << '\n';
    os << seq_1[FASTQSequence::Option] << '\n';
    os << seq_1[FASTQSequence::Quality] << '\n';
    const DGEIlluminaFASTQSequence& seq_2 = seq.getSequence2();
    os << seq_2[FASTQSequence::Identifier] << '\n';
    os << seq_2[FASTQSequence::Sequence] << '\n';
    os << seq_2[FASTQSequence::Option] << '\n';
    // Flush paired sequence lines to output stream in the end.
    os << seq_2[FASTQSequence::Quality] << '\n';
    return os;
}

}
