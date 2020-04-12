#ifndef CPP_FASTREADERA_H
#define CPP_FASTREADERA_H

#include <string>
#include "Reader.h"
#include "SeqA.h"

using namespace std;

class ReaderA : public Reader {
public:

    ReaderA(std::istream *file_ptr);

    virtual SeqA *next();

    virtual string getFormat() const;
};

#endif //CPP_FASTREADERA_H
