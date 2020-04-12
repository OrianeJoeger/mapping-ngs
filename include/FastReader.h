#ifndef CPP_FASTREADER_H
#define CPP_FASTREADER_H

#include <iostream>
#include <string>

#include "parser/FastParserX.h"
#include "FastX.h"
#include "FastA.h"
#include "FastQ.h"

class FastReader {
private:
    std::istream *file_ptr;
    FastParserX *parser;
    int type;

public:
    static const int TYPE_FASTQ = 1;
    static const int TYPE_FASTA = 2;

    FastReader(std::istream *file_ptr);

    FastX *next();

    std::string getFormat();
};

#endif //CPP_FASTREADER_H