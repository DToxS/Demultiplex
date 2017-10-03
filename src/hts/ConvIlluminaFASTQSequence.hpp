//
//  ConvIlluminaFASTQSequence.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 5/4/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#ifndef ConvIlluminaFASTQSequence_hpp
#define ConvIlluminaFASTQSequence_hpp

#include <vector>
#include "IlluminaFASTQSequence.hpp"

namespace hts
{

class ConvIlluminaFASTQSequence : public IlluminaFASTQSequence
{
protected:

    // Well barcode.
    std::string well_barcode;

protected:

    // Set the group ID of FASTQ sequence using sequence information.
    virtual void setGroupId() override;

    void setBarcode()
    {
        well_barcode = index_sequence;
    }

public:
    
    ConvIlluminaFASTQSequence();
    
    // parse_seq is defaulted to true for the parsing of IlluminaFASTQSequence.
    ConvIlluminaFASTQSequence(const FASTQSequenceLines& lines, bool parse_seq=true, bool parse_seq_id_level_1=false, bool parse_seq_id_level_2=false);
    
    // parse_seq is defaulted to true for the parsing of IlluminaFASTQSequence.
    ConvIlluminaFASTQSequence(FASTQSequenceLines&& lines, bool parse_seq=true, bool parse_seq_id_level_1=false, bool parse_seq_id_level_2=false);

    // parse_seq is defaulted to true for the parsing of IlluminaFASTQSequence.
    ConvIlluminaFASTQSequence(const std::string& line1, const std::string& line2, const std::string& line3, const std::string& line4, bool parse_seq=true, bool parse_seq_id_level_1=false, bool parse_seq_id_level_2=false);

    // parse_seq is defaulted to true for the parsing of IlluminaFASTQSequence.
    ConvIlluminaFASTQSequence(std::string&& line1, std::string&& line2, std::string&& line3, std::string&& line4, bool parse_seq=true, bool parse_seq_id_level_1=false, bool parse_seq_id_level_2=false);

    ConvIlluminaFASTQSequence(const IlluminaFASTQSequence& seq);

    ConvIlluminaFASTQSequence(IlluminaFASTQSequence&& seq);

    ConvIlluminaFASTQSequence(const FASTQSequence& seq, bool parse_seq_id_level_1=false, bool parse_seq_id_level_2=false);

    ConvIlluminaFASTQSequence(FASTQSequence&& seq, bool parse_seq_id_level_1=false, bool parse_seq_id_level_2=false);

    ConvIlluminaFASTQSequence(const ConvIlluminaFASTQSequence& seq);

    ConvIlluminaFASTQSequence(ConvIlluminaFASTQSequence&& seq);

    virtual ~ConvIlluminaFASTQSequence() noexcept;
    
    ConvIlluminaFASTQSequence& operator=(const ConvIlluminaFASTQSequence& seq);
    
    ConvIlluminaFASTQSequence& operator=(ConvIlluminaFASTQSequence&& seq);
    
    // Retrieve the well barcode of Conv FASTQ sequence.
    const std::string& getWellBarcode() const
    {
        return well_barcode;
    }

    // Retrieve the well barcode of Conv FASTQ sequence.
    std::string& getWellBarcode()
    {
        return well_barcode;
    }
};

using ConvIlluminaFASTQSequences = std::vector<ConvIlluminaFASTQSequence>;

}

#endif /* ConvIlluminaFASTQSequence_hpp */
