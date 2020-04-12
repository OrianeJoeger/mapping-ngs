#include <iostream>
#include <string>

#include "../include/FastReader.h"
#include "../include/parser/FastParserA.h"
#include "../include/parser/FastParserQ.h"
#include "../include/FastX.h"
#include "../include/FastA.h"
#include "../include/FastQ.h"

using namespace std;

FastReader::FastReader(istream *file_ptr)
        : file_ptr(file_ptr), type(0) {
    char c;

    while (!this->file_ptr->eof() && (c = this->file_ptr->get()) > ' ') {
        if (c == ';' || c == '>') {
            this->parser = new FastParserA;
            this->type = FastReader::TYPE_FASTA;
        } else if (c == '@') {
            this->parser = new FastParserQ;
            this->type = FastReader::TYPE_FASTQ;
        }

        break;
    }

    if (this->type == 0) {
        throw "Error unknown format type";
    }

    // rewind ptr
    this->file_ptr->seekg(0);
}

FastX *FastReader::next() {
    return this->parser->extract(this->file_ptr);
}

string FastReader::getFormat() {
    switch (this->type) {
        case FastReader::TYPE_FASTA:
            return "FASTA";

        case FastReader::TYPE_FASTQ:
            return "FASTQ";
    }

    return NULL;
}
