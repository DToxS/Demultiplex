//
//  CompositedDGEIlluminaFASTQSequence.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 8/7/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include "CompositedDGEIlluminaFASTQSequence.hpp"

namespace hts
{

CompositedDGEIlluminaFASTQSequence::CompositedDGEIlluminaFASTQSequence(const PairedDGEIlluminaFASTQSequence& paired_dge_seq, bool parse_dge_seq)
{
    // Fill in FASTQSequenceLines.
    const DGEIlluminaFASTQSequence& dge_seq1 = paired_dge_seq.getSequence1();
    const DGEIlluminaFASTQSequence& dge_seq2 = paired_dge_seq.getSequence2();
    // The Identifier line is concatenated from the first part of
    // sequence identifier, the well barcode, and the UMI barcode
    // of the first read of DGE sequence pair.
    lines[0] = dge_seq1.getSequenceIdentifierPart1() + ":" + dge_seq1.getWellBarcode() + dge_seq1.getUMIBarcode();
    // The Sequence line is the that of the second read of DGE
    // sequence pair.
    lines[1] = dge_seq2.getSequenceLine();
    lines[2] = "+";
    // The Quality line is the that of the second read of DGE sequence
    // pair.
    lines[3] = dge_seq2.getQualityLine();

    // Parse the composite FASTQ sequence.
    parse_seq = parse_dge_seq;
    if(parse_seq) parse();

    // Fill in sequence Identifier info.
    instrument_id = dge_seq1.getInstrumentId();
    run_number = dge_seq1.getRunNumber();
    flowcell_id = dge_seq1.getFlowcellId();
    lane_number = dge_seq1.getLaneNumber();
    tile_number = dge_seq1.getTileNumber();
    x_pos = dge_seq1.getXPos();
    y_pos = dge_seq1.getYPos();
    // Set well and UMI barcodes using the read 1 of paired DGE FASTQ sequence.
    well_barcode = dge_seq1.getWellBarcode();
    umi_barcode = dge_seq1.getUMIBarcode();

    // Fill in group ID.
    setGroupId();
}

CompositedDGEIlluminaFASTQSequence::CompositedDGEIlluminaFASTQSequence(PairedDGEIlluminaFASTQSequence&& paired_dge_seq, bool parse_dge_seq)
{
    DGEIlluminaFASTQSequence& dge_seq1 = paired_dge_seq.getSequence1();
    DGEIlluminaFASTQSequence& dge_seq2 = paired_dge_seq.getSequence2();
    // The Identifier line is concatenated from the first part of
    // sequence identifier, the well barcode, and the UMI barcode
    // of the first read of DGE sequence pair.
    lines[0] = std::move(dge_seq1.getSequenceIdentifierPart1()) + ":" + std::move(dge_seq1.getWellBarcode()) + std::move(dge_seq1.getUMIBarcode());
    // The Sequence line is the that of the second read of DGE
    // sequence pair.
    lines[1] = std::move(dge_seq2.getSequenceLine());
    lines[2] = "+";
    // The Quality line is the that of the second read of DGE sequence
    // pair.
    lines[3] = std::move(dge_seq2.getQualityLine());

    // Parse the composite FASTQ sequence.
    parse_seq = parse_dge_seq;
    if(parse_seq) parse();

    // Fill in sequence Identifier info.
    instrument_id = std::move(dge_seq1.getInstrumentId());
    run_number = dge_seq1.getRunNumber();
    flowcell_id = std::move(dge_seq1.getFlowcellId());
    lane_number = dge_seq1.getLaneNumber();
    tile_number = dge_seq1.getTileNumber();
    x_pos = dge_seq1.getXPos();
    y_pos = dge_seq1.getYPos();
    well_barcode = std::move(dge_seq1.getWellBarcode());
    umi_barcode = std::move(dge_seq1.getUMIBarcode());

    // Fill in group ID.
    setGroupId();
}

}
