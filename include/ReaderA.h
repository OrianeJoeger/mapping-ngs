#ifndef CPP_FASTREADERA_H
#define CPP_FASTREADERA_H

#include <string>
#include <istream>

#include "Reader.h"
#include "SeqA.h"

using namespace std;

class ReaderA : public Reader {
public:

    ReaderA(std::istream *is);

    virtual SeqA *next();

    virtual string getFormat() const;
};

#endif //CPP_FASTREADERA_H
