#include <iostream>
#include <string>

#ifndef __FASTPARSERX_H__
#define __FASTPARSERX_H__

#include "../FastX.h"

class FastParserX {
protected:
    static bool isNucleic(char c);

    static bool isAmino(char c);

public:
    virtual FastX *extract(std::istream *is) = 0;
};

#endif
