#include <cstdint>
#include <string>
#include <vector>

#include "../include/Seq.h"
#include "../include/EncodedSequence.h"

using namespace std;

Seq::Seq(const string &entete, const EncodedSequence &seq) :
        entete(entete),
        seq(seq) {
}

Seq::Seq(const string &entete, const string &seqbio) :
        entete(entete),
        seq(seqbio, &errors) {
}

string Seq::getSeqbio() {
    return this->seq.toString();
}

string Seq::getHeader() {
    return this->entete;
}

size_t Seq::getSeqbioLength() {
    return this->seq.size();
}

string Seq::getSeqComp() {
    size_t seqLength = this->seq.size();
    string seqComp;
    for (size_t i = 0; i < seqLength; i++) {
        switch (this->seq[i]) {
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
                seqComp.push_back(this->seq[i]);
                break;
        }
    }
    return seqComp;
}

string Seq::getSeqRev() {
    size_t seqLength = this->seq.size();
    string seqRev;
    for (size_t i = seqLength; i > 0; i--) {
        seqRev += this->seq[i - 1];
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

vector <string> *Seq::getErrors() {
    return &(this->errors);
}

string Seq::toString(bool display_comp, bool display_rev) {
    string str = "[HEADER:] " + this->entete +
                 +"\n[SEQUENCE:] " + this->seq.toString();
    if (display_comp)
        str += "\n[COMPLEMENTARY:] " + this->getSeqComp();

    if (display_rev)
        str += "\n[REVERSE:] " + this->getSeqRev();

    return str;
}

string Seq::toString() {
    return this->toString(false, false);
}