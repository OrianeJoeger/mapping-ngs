#include <iostream>
#include <string>

#ifndef __FASTPARSERQ_H__
#define __FASTPARSERQ_H__

#include "FastParserX.h"
#include "../FastQ.h"

class FastParserQ : public FastParserX {
public:
    virtual FastQ *extract(std::istream *is);
};

#endif
