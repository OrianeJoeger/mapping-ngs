#ifndef CPP_FASTFILE_H
#define CPP_FASTFILE_H

#include <vector>

#include "Reader.h"
#include "Seq.h"

using namespace std;

class FastFile {

private:
    vector<Seq *> data;
    string format;

protected:
    static Reader *getReader(istream *is);

public:
    FastFile(char *file);

    void printFormat();

    void printDataSize();

    void printData(bool, bool, bool);

    void printErrors();

    vector<Seq *> getData();
};

#endif //CPP_FASTFILE_H