#include <string>
#include <algorithm>
#include <list>
#include <vector>

#include "../include/Seq.h"

using namespace std;

Seq::Seq(const vector <string> errors, const string &entete, const string &seqbio) :
        errors(errors),
        entete(entete),
        seqbio(seqbio) {

}

string Seq::getSeqbio() {
    return seqbio;
}

string Seq::getHeader() {
    return entete;
}

void Seq::setHeader(string header) {
    entete = header;
}

size_t Seq::getSeqbioLength() {
    return seqbio.length();
}

string Seq::getSeqComp() {
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

string Seq::getSeqRev() {
    size_t seqLength = this->seqbio.size();
    string seqRev;
    for (size_t i = seqLength; i > 0; i--) {
        seqRev += seqbio[i - 1];
    }
    return seqRev;
}

string Seq::getSeqRevComp() {
    return "";
}

bool Seq::hasErrors() const {
    if (this->errors.size()) {
        return true;
    }

    return false;
}

int Seq::countErrors() const {
    return this->errors.size();
}

vector <std::string> Seq::getErrors() const {
    return this->errors;
}