#ifndef CPP_FASTREADER_H
#define CPP_FASTREADER_H

#include <iostream>
#include <string>

#include "Seq.h"

class Reader {
protected:
    std::istream *file_ptr;

public:
    static bool isNucleic(char c);

    static bool isAmino(char c);

    Reader(std::istream *file_ptr);

    virtual Seq *next() = 0;

    virtual std::string getFormat() const = 0;
};

#endif //CPP_FASTREADER_H