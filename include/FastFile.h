#ifndef CPP_FASTFILE_H
#define CPP_FASTFILE_H

#include <vector>

#include "FastReader.h"
#include "Seq.h"

using namespace std;

class FastFile {

private:
    vector<Seq *> data;
    string format;

protected:
    static FastReader *getReader(istream *is);

public:
    FastFile(char *file);

    void printFormat();

    void printDataSize();

    void printData(bool, bool, bool);

    void printErrors();

    vector<Seq *> getData();
};

#endif //CPP_FASTFILE_H