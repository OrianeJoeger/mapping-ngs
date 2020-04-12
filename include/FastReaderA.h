#ifndef CPP_FASTREADERA_H
#define CPP_FASTREADERA_H

#include <string>
#include "FastReader.h"
#include "SeqA.h"

using namespace std;

class FastReaderA : public FastReader {
public:

    FastReaderA(std::istream *file_ptr);

    virtual SeqA *next();

    virtual string getFormat() const;
};

#endif //CPP_FASTREADERA_H
