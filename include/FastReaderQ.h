#ifndef CPP_FASTREADERQ_H
#define CPP_FASTREADERQ_H

#include <string>
#include <istream>

#include "FastReader.h"
#include "SeqQ.h"

class FastReaderQ : public FastReader {
public:

    FastReaderQ(std::istream *file_ptr);

    virtual SeqQ *next();

    virtual std::string getFormat() const;
};


#endif //CPP_FASTREADERQ_H
