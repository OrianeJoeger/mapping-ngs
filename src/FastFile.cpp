#include <vector>

#include "../include/FastFile.h"
#include "../include/Reader.h"
#include "../include/ReaderA.h"
#include "../include/ReaderQ.h"
#include "../include/Seq.h"
#include "../include/SeqQ.h"

using namespace std;

FastFile::FastFile(char *file) {
    filebuf fb;

    if (!fb.open(file, ios::in)) {
        throw "Invalid file";
    }

    istream is(&fb);

    try {
        Reader *reader = FastFile::getReader(&is);

        this->format = reader->getFormat();

        Seq *fast;
        while ((fast = reader->next()) != NULL) {
            this->data.push_back(fast);
        }
        fb.close();
    } catch (const char *e) {
        fb.close();
        throw e;
    }
}

Reader *FastFile::getReader(istream *is) {
    char c;

    while (!is->eof() && (c = is->get()) < ' ') {
        // do nothing
    }

    // rewind ptr
    is->seekg(0);

    if (c == ';' || c == '>') {
        return new ReaderA(is);
    } else if (c == '@') {
        return new ReaderQ(is);
    }

    throw "Error unknown format type";
}

vector<Seq *> FastFile::getData() {
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
    Seq *seq;

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
            if (this->format == "SeqQ")
                cout << "[QUALITY:] " << ((SeqQ *) seq)->getQualite() << endl;
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

    Seq *seq;
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

