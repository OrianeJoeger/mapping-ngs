#include <vector>

#include "../include/FastFile.h"
#include "../include/FastReader.h"
#include "../include/FastX.h"

using namespace std;

FastFile::FastFile(char *file) {
    filebuf fb;

    if (!fb.open(file, ios::in)) {
        throw "Invalid file";
    }

    istream is(&fb);
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

string FastFile::getFormat() {
    return this->format;
}

vector<FastX *> FastFile::getData() {
    return this->data;
}

void    FastFile::printFormat() {
    cout << "[FORMAT:] " << this->getFormat() << endl;
}

void    FastFile::printDataSize() {
    cout << "[SIZE:] " << this->getData().size() << endl;
}

void    FastFile::printData(bool only_seq_with_error, bool comp, bool rev) {
    int i = 1;
    for (FastX *seq : this->getData()) {
        if (seq->hasErrors() && only_seq_with_error) {
            cout << "N°" << i << " ------------------------------" << endl;
            cout << "[HEADER:] " << seq->getHeader() << endl;
            cout << "[SEQUENCE:] " << seq->getSeqbio() << endl;
            if (comp)
                cout << "[COMPLEMENTARY:] " << seq->getSeqComp() << endl;
            if (rev)
                cout << "[REVERSE:] " << seq->getSeqRev() << endl;
            if (this->getFormat() == "FASTQ")
                cout << "[QUALITY:] " << ((FastQ *) seq)->getQualite() << endl;
        }
        i++;
    }
}

void    FastFile::printErrors(bool display_error) {
    if (display_error) {
        int i = 1;
        for (FastX *seq : this->getData()) {
            if (seq->hasErrors()) {
                cout << "[ERRORS:] " << seq->countErrors() << endl;
                for (string error : seq->getErrors()) {
                    cout << "SEQUENCE N°" << i << "    - " << error << endl;
                }
            }
            i++;
        }
    }
}

