//
//  FASTQSequence.cpp
//  FASTQ-Sequence-Parser
//
//  Created by Yuguang Xiong on 5/2/17.
//  Copyright © 2017 Yuguang Xiong. All rights reserved.
//

#include <stdexcept>
#include "FASTQSequence.hpp"

namespace hts
{

FASTQSequence::FASTQSequence() {}

FASTQSequence::FASTQSequence(const FASTQSequenceLines& lines, bool parse_seq) : lines{lines}, parse_seq{parse_seq}
{
    if(parse_seq) parse();
}

FASTQSequence::FASTQSequence(FASTQSequenceLines&& lines, bool parse_seq) : lines{std::move(lines)}, parse_seq{parse_seq}
{
    if(parse_seq) parse();
}

FASTQSequence::FASTQSequence(const std::string& line1, const std::string& line2, const std::string& line3, const std::string& line4, bool parse_seq) : lines{{line1, line2, line3, line4}}, parse_seq{parse_seq}
{
    if(parse_seq) parse();
}

FASTQSequence::FASTQSequence(std::string&& line1, std::string&& line2, std::string&& line3, std::string&& line4, bool parse_seq) : lines{{std::move(line1), std::move(line2), std::move(line3), std::move(line4)}}, parse_seq{parse_seq}
{
    if(parse_seq) parse();
}

FASTQSequence::FASTQSequence(const FASTQSequence& seq) : lines{seq.lines}, read_length{seq.read_length}, parse_seq{seq.parse_seq} {}

FASTQSequence::FASTQSequence(FASTQSequence&& seq) : lines{std::move(seq.lines)}, read_length{seq.read_length}, parse_seq{seq.parse_seq} {}

FASTQSequence::~FASTQSequence() noexcept {}

FASTQSequence& FASTQSequence::operator=(const FASTQSequence& seq)
{
    if(this != &seq)
    {
        lines = seq.lines;
        read_length = seq.read_length;
        group_id = seq.group_id;
        parse_seq = seq.parse_seq;
    }
    return *this;
}

FASTQSequence& FASTQSequence::operator=(FASTQSequence&& seq)
{
    if(this != &seq)
    {
        lines = std::move(seq.lines);
        read_length = seq.read_length;
        group_id = std::move(seq.group_id);
        parse_seq = seq.parse_seq;
        seq.read_length = 0;
        seq.group_id.clear();
        seq.parse_seq = false;
    }
    return *this;
}

bool FASTQSequence::empty() const
{
    bool result = true;
    for(const auto& line : lines)
    {
        if(!line.empty())
        {
            result = false;
            break;
        }
    }
    return result;
}

// Validates sequence format.
void FASTQSequence::parse()
{
    // Identifier line must start with @
    if(lines[Identifier].c_str()[0] != '@') throw std::logic_error("Identifier line doesn't start with @");
    
    // Option line must start with +
    if(lines[Option].c_str()[0] != '+') throw std::logic_error("Option line doesn't start with +");
    
    // Sequence line and Quality line must have an equal read length.
    auto seq_length = lines[Sequence].length();
    auto qual_length = lines[Quality].length();
    if(seq_length == qual_length) read_length = seq_length;
    else throw std::logic_error("The lengths of sequence line and quality line are not equal");
    read_length = seq_length;
}

// Output of FASTQ sequence.
std::ostream& operator<<(std::ostream& os, const FASTQSequence& seq)
{
    os << seq[FASTQSequence::Identifier] << '\n';
    os << seq[FASTQSequence::Sequence] << '\n';
    os << seq[FASTQSequence::Option] << '\n';
    // Flush sequence lines to output stream in the end.
    os << seq[FASTQSequence::Quality] << '\n';
    return os;
}

}
