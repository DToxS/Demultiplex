//
//  DGEIlluminaFASTQFile.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Granville Xiong on 5/9/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#ifndef DGEIlluminaFASTQFile_hpp
#define DGEIlluminaFASTQFile_hpp

#include "DGEIlluminaFASTQSequence.hpp"
#include "FASTQFileReader.hpp"

namespace hts
{

using DGEIlluminaFASTQFile = FASTQFileReader<DGEIlluminaFASTQSequence, bool, bool, bool>;

}

#endif /* DGEIlluminaFASTQFile_hpp */
