#ifndef CPP_FASTFILE_H
#define CPP_FASTFILE_H

#include <vector>

#include "FastX.h"

using namespace std;

class FastFile {

private:
	vector<FastX*>	data;
	string			format;

public:
	FastFile(char *file);

	string			getFormat();
	vector<FastX*>	getData();
};

#endif //CPP_FASTFILE_H