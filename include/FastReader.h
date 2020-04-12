#ifndef CPP_FASTREADER_H
#define CPP_FASTREADER_H

#include <iostream>
#include <string>

#include "FastX.h"

class FastReader {
protected:
    std::istream *file_ptr;

    static bool isNucleic(char c);

    static bool isAmino(char c);

public:
    static const int TYPE_FASTQ = 1;
    static const int TYPE_FASTA = 2;

    FastReader(std::istream *file_ptr);

    virtual FastX *next() = 0;

    virtual std::string getFormat() const = 0;
};

#endif //CPP_FASTREADER_H