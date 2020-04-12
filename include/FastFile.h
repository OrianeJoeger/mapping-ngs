#ifndef CPP_FASTFILE_H
#define CPP_FASTFILE_H

#include <vector>

#include "FastX.h"

using namespace std;

class FastFile {

private:
    vector<FastX *> data;
    string format;

    string getFormat();

public:
    FastFile(char *file);
    void	printFormat();
    void	printDataSize();
    void	printData(bool, bool, bool);
    void	printErrors(bool);
    vector<FastX *> getData();
};

#endif //CPP_FASTFILE_H