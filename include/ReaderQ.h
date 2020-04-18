#ifndef CPP_FASTREADERQ_H
#define CPP_FASTREADERQ_H

#include <string>
#include <istream>

#include "Reader.h"
#include "SeqQ.h"

class ReaderQ : public Reader {
public:

    ReaderQ(std::istream *is);

    virtual SeqQ *next();

    virtual std::string getFormat() const;
};


#endif //CPP_FASTREADERQ_H
