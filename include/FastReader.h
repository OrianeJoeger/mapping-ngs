#ifndef CPP_FASTREADER_H
#define CPP_FASTREADER_H

#include <iostream>
#include <string>

#include "FastX.h"
#include "FastA.h"
#include "FastQ.h"

class FastReader {
private:
    std::istream *file_ptr;
    int type;

    static bool isNucleic(char c);

    static bool isAmino(char c);

    FastA *extractFastA();

    FastQ *extractFastQ();
public:
    static const int TYPE_FASTQ = 1;
    static const int TYPE_FASTA = 2;

    FastReader(std::istream *file_ptr);

    FastX *next();

    std::string getFormat();
};

#endif //CPP_FASTREADER_H
