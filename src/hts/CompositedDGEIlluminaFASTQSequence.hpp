//
//  CompositedDGEIlluminaFASTQSequence.hpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 8/7/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#ifndef CompositedDGEIlluminaFASTQSequence_hpp
#define CompositedDGEIlluminaFASTQSequence_hpp

#include <vector>
#include "PairedDGEIlluminaFASTQSequence.hpp"

namespace hts
{

// Create a compoiste DGE FASTQ sequence from a pair of DGE FASTQ sequence.
class CompositedDGEIlluminaFASTQSequence : public FASTQSequence
{
protected:

    // Sequence Identifier info.
    std::string instrument_id;
    std::size_t run_number {0};
    std::string flowcell_id;
    std::size_t lane_number {0};
    std::size_t tile_number {0};
    std::size_t x_pos {0};
    std::size_t y_pos {0};

    // Well barcode.
    std::string well_barcode;

    // UMI barcode.
    std::string umi_barcode;

protected:

    // Set the group ID of FASTQ sequence using sequence information.
    virtual void setGroupId() override
    {
        group_id = well_barcode;
    }

public:

    CompositedDGEIlluminaFASTQSequence(const PairedDGEIlluminaFASTQSequence& paired_dge_seq, bool parse_dge_seq=false);

    CompositedDGEIlluminaFASTQSequence(PairedDGEIlluminaFASTQSequence&& paired_dge_seq, bool parse_dge_seq=false);

    // Retrieve the well barcode of DGE FASTQ sequence.
    const std::string& getWellBarcode() const
    {
        return well_barcode;
    }

    // Retrieve the well barcode of DGE FASTQ sequence.
    std::string& getWellBarcode()
    {
        return well_barcode;
    }

    // Retrieve the UMI barcode of DGE FASTQ sequence.
    const std::string& getUMIBarcode() const
    {
        return umi_barcode;
    }

    // Retrieve the UMI barcode of DGE FASTQ sequence.
    std::string& getUMIBarcode()
    {
        return umi_barcode;
    }
};

using CompositedDGEIlluminaFASTQSequences = std::vector<CompositedDGEIlluminaFASTQSequence>;

}

#endif /* CompositedDGEIlluminaFASTQSequence_hpp */
