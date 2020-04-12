#ifndef CPP_FASTREADER_H
#define CPP_FASTREADER_H

#include <iostream>
#include <string>

#include "Seq.h"

class FastReader {
protected:
    std::istream *file_ptr;

    static bool isNucleic(char c);

    static bool isAmino(char c);

public:
    FastReader(std::istream *file_ptr);

    virtual Seq *next() = 0;

    virtual std::string getFormat() const = 0;
};

#endif //CPP_FASTREADER_H