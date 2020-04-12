#include <iostream>
#include <string>

#ifndef __FASTPARSERA_H__
#define __FASTPARSERA_H__

#include "FastParserX.h"
#include "../FastA.h"

class FastParserA : public FastParserX {
public:
    virtual FastA *extract(std::istream *is);
};

#endif
