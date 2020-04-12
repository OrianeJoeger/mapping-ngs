#ifndef CPP_FASTFILE_H
#define CPP_FASTFILE_H

#include <vector>

#include "FastReader.h"
#include "FastX.h"

using namespace std;

class FastFile {

private:
    vector<FastX *> data;
    string format;

protected:
    static FastReader *getReader(istream *is);

public:
    FastFile(char *file);

    void printFormat();

    void printDataSize();

    void printData(bool, bool, bool);

    void printErrors();

    vector<FastX *> getData();
};

#endif //CPP_FASTFILE_H