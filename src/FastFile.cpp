#include <vector>

#include "../include/FastFile.h"
#include "../include/FastReader.h"
#include "../include/FastX.h"

using namespace std;

FastFile::FastFile(char *file) {
	filebuf	fb;

	if (!fb.open(file, ios::in)) {
		throw "Invalid file";
	}

	istream	is(&fb);
	FastReader reader(&is);
	this->format = reader.getFormat();

	FastX *fast;
	try {
	    while ((fast = reader.next()) != NULL) {
	    	this->data.push_back(fast);
	    }
		fb.close();
	} catch (const char *e) {
        fb.close();
        throw e;
    }
}

string			FastFile::getFormat() {
	return this->format;
}

vector<FastX*> 	FastFile::getData() {
	return this->data;
}

