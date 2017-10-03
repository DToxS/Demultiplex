//
//  FileUtils.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 9/26/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#ifndef FileUtils_hpp
#define FileUtils_hpp

#include <string>

namespace utk
{

/// Check if a file can be read.
bool isFileReadable(const std::string& file_path);

/// Check if a file can be read.
void checkFileReadability(const std::string& file_path);

#endif /* FileUtils_hpp */

}
