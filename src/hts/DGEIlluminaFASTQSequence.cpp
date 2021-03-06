//
//  DGEIlluminaFASTQSequence.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 5/4/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include "DGEIlluminaFASTQSequence.hpp"

namespace hts
{

DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence() {}

// parse_seq is defaulted to true for the parsing of IlluminaFASTQSequence.
DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(const FASTQSequenceLines& lines, bool parse_seq, bool parse_seq_id_level_1, bool parse_seq_id_level_2, bool flush_ostream) : IlluminaFASTQSequence(lines, parse_seq, parse_seq_id_level_1, parse_seq_id_level_2, flush_ostream)
{
    setGroupId();
    setBarcode();
}

// parse_seq is defaulted to true for the parsing of IlluminaFASTQSequence.
DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(FASTQSequenceLines&& lines, bool parse_seq, bool parse_seq_id_level_1, bool parse_seq_id_level_2, bool flush_ostream) : IlluminaFASTQSequence(std::move(lines), parse_seq, parse_seq_id_level_1, parse_seq_id_level_2, flush_ostream)
{
    setGroupId();
    setBarcode();
}

// parse_seq is defaulted to true for the parsing of IlluminaFASTQSequence.
DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(const std::string& line1, const std::string& line2, const std::string& line3, const std::string& line4, bool parse_seq, bool parse_seq_id_level_1, bool parse_seq_id_level_2, bool flush_ostream) : IlluminaFASTQSequence(line1, line2, line3, line4, parse_seq, parse_seq_id_level_1, parse_seq_id_level_2, flush_ostream)
{
    setGroupId();
    setBarcode();
}

// parse_seq is defaulted to true for the parsing of IlluminaFASTQSequence.
DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(std::string&& line1, std::string&& line2, std::string&& line3, std::string&& line4, bool parse_seq, bool parse_seq_id_level_1, bool parse_seq_id_level_2, bool flush_ostream) : IlluminaFASTQSequence(std::move(line1), std::move(line2), std::move(line3), std::move(line4), parse_seq, parse_seq_id_level_1, parse_seq_id_level_2, flush_ostream)
{
    setGroupId();
    setBarcode();
}

DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(const IlluminaFASTQSequence& seq) : IlluminaFASTQSequence(seq)
{
    setGroupId();
    setBarcode();
}

DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(IlluminaFASTQSequence&& seq) : IlluminaFASTQSequence(std::move(seq))
{
    setGroupId();
    setBarcode();
}

DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(const FASTQSequence& seq, bool parse_seq_id_level_1, bool parse_seq_id_level_2) : IlluminaFASTQSequence(seq, parse_seq_id_level_1, parse_seq_id_level_2)
{
    setGroupId();
    setBarcode();
}

DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(FASTQSequence&& seq, bool parse_seq_id_level_1, bool parse_seq_id_level_2) : IlluminaFASTQSequence(std::move(seq), parse_seq_id_level_1, parse_seq_id_level_2)
{
    setGroupId();
    setBarcode();
}

DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(const DGEIlluminaFASTQSequence& seq) : IlluminaFASTQSequence(seq), well_barcode{seq.well_barcode}, umi_barcode{seq.umi_barcode} {}

DGEIlluminaFASTQSequence::DGEIlluminaFASTQSequence(DGEIlluminaFASTQSequence&& seq) : IlluminaFASTQSequence(std::move(seq)), well_barcode{std::move(seq.well_barcode)}, umi_barcode{std::move(seq.umi_barcode)} {}

DGEIlluminaFASTQSequence::~DGEIlluminaFASTQSequence() noexcept {}

// Set the group ID of FASTQ sequence using sequence information.
void DGEIlluminaFASTQSequence::setGroupId()
{
    group_id = lines[Sequence].substr(well_barcode_beg_pos, well_barcode_end_pos-well_barcode_beg_pos+1);
}

DGEIlluminaFASTQSequence& DGEIlluminaFASTQSequence::operator=(const DGEIlluminaFASTQSequence& seq)
{
    if(this != &seq)
    {
        IlluminaFASTQSequence::operator=(seq);
        well_barcode = seq.well_barcode;
        umi_barcode = seq.umi_barcode;
    }
    return *this;
}

DGEIlluminaFASTQSequence& DGEIlluminaFASTQSequence::operator=(DGEIlluminaFASTQSequence&& seq)
{
    if(this != &seq)
    {
        IlluminaFASTQSequence::operator=(std::move(seq));
        well_barcode = std::move(seq.well_barcode);
        umi_barcode = std::move(seq.umi_barcode);
    }
    return *this;
}

}
