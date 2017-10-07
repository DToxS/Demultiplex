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

    // Initialize all data members.
    void initialize(const PairedDGEIlluminaFASTQSequence& paired_dge_seq, bool parse_compos_seq=false);

    void initialize(PairedDGEIlluminaFASTQSequence&& paired_dge_seq, bool parse_compos_seq=false);

    // Set the group ID of FASTQ sequence using sequence information.
    virtual void setGroupId() override
    {
        group_id = well_barcode;
    }

public:

    CompositedDGEIlluminaFASTQSequence() {}

    CompositedDGEIlluminaFASTQSequence(const PairedDGEIlluminaFASTQSequence& paired_dge_seq, bool parse_compos_seq=false);

    CompositedDGEIlluminaFASTQSequence(PairedDGEIlluminaFASTQSequence&& paired_dge_seq, bool parse_compos_seq=false);

    CompositedDGEIlluminaFASTQSequence(const DGEIlluminaFASTQSequence& seq_1, const DGEIlluminaFASTQSequence& seq_2, bool parse_paired_seq=false, bool parse_compos_seq=false);

    CompositedDGEIlluminaFASTQSequence(DGEIlluminaFASTQSequence&& seq_1, DGEIlluminaFASTQSequence&& seq_2, bool parse_paired_seq=false, bool parse_compos_seq=false);

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
