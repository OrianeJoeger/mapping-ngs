#include <vector>

#include "../include/FastFile.h"
#include "../include/FastReader.h"
#include "../include/FastReaderA.h"
#include "../include/FastReaderQ.h"
#include "../include/FastX.h"

using namespace std;

FastFile::FastFile(char *file) {
    filebuf fb;

    if (!fb.open(file, ios::in)) {
        throw "Invalid file";
    }

    istream is(&fb);

    FastReader *reader = FastFile::getReader(&is);

    this->format = reader->getFormat();

    FastX *fast;
    try {
        while ((fast = reader->next()) != NULL) {
            this->data.push_back(fast);
        }
        fb.close();
    } catch (const char *e) {
        fb.close();
        throw e;
    }
}

FastReader *FastFile::getReader(istream *is) {
    char c;

    while (!is->eof() && (c = is->get()) < ' ') {
        // do nothing
    }

    // rewind ptr
    is->seekg(0);

    if (c == ';' || c == '>') {
        return new FastReaderA(is);
    } else if (c == '@') {
        return new FastReaderQ(is);
    }

    throw "Error unknown format type";
}

vector<FastX *> FastFile::getData() {
    return this->data;
}

void FastFile::printFormat() {
    cout << "[FORMAT:] " << this->format << endl;
}

void FastFile::printDataSize() {
    cout << "[SIZE:] " << this->getData().size() << endl;
}

void FastFile::printData(bool only_seq_with_error, bool comp, bool rev) {
    unsigned int i = 0;
    unsigned int l = this->getData().size();
    FastX *seq;

    for (; i < l; i++) {
        seq = this->getData()[i];
        if (only_seq_with_error ? seq->hasErrors() : true) {
            cout << "N°" << (i + 1) << " ------------------------------" << endl;
            cout << "[HEADER:] " << seq->getHeader() << endl;
            cout << "[SEQUENCE:] " << seq->getSeqbio() << endl;
            if (comp)
                cout << "[COMPLEMENTARY:] " << seq->getSeqComp() << endl;
            if (rev)
                cout << "[REVERSE:] " << seq->getSeqRev() << endl;
            if (this->format == "FASTQ")
                cout << "[QUALITY:] " << ((FastQ *) seq)->getQualite() << endl;
        }
    }

    cout << endl;
}

void FastFile::printErrors() {
    unsigned int
            i = 0,
            l = this->getData().size(),
            j,
            m;

    FastX *seq;
    string error;

    for (; i < l; i++) {
        seq = this->getData()[i];

        if (seq->hasErrors()) {
            cout << "[ERRORS:] SEQUENCE N°" << (i + 1) << endl;
            for (j = 0, m = seq->countErrors(); j < m; j++) {
                cout << "    - " << seq->getErrors()[j] << endl;
            }
        }
    }
}

