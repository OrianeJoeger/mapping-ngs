#include <string>
#include <algorithm>
#include <list>
#include <vector>

#include "../include/FastX.h"

using namespace std;

FastX::FastX(const vector <string> errors, const string &entete, const string &seqbio) :
        errors(errors),
        entete(entete),
        seqbio(seqbio) {

}

string FastX::getSeqbio() {
    return seqbio;
}

string FastX::getHeader() {
    return entete;
}

void FastX::setHeader(string header) {
    entete = header;
}

size_t FastX::getSeqbioLength() {
    return seqbio.length();
}

string FastX::getSeqComp() {
    size_t seqLength = this->seqbio.size();
    string seqComp;
    for (size_t i = 0; i < seqLength; i++) {
        switch (this->seqbio[i]) {
            case 'A':
                seqComp.push_back('T');   //pushback append
                break;
            case 'C':
                seqComp.push_back('G');
                break;
            case 'G':
                seqComp.push_back('C');
                break;
            case 'T':
                seqComp.push_back('A');
                break;
            default:
                seqComp.push_back(seqbio[i]);
                break;
        }
    }
    return seqComp;
}

string FastX::getSeqRev() {
    size_t seqLength = this->seqbio.size();
    string seqRev;
    for (size_t i = seqLength; i > 0; i--) {
        seqRev += seqbio[i - 1];
    }
    return seqRev;
}

string FastX::getSeqRevComp() {
    return "";
}

bool FastX::hasErrors() const {
    if (this->errors.size()) {
        return true;
    }

    return false;
}

int FastX::countErrors() const {
    return this->errors.size();
}

vector <std::string> FastX::getErrors() const {
    return this->errors;
}