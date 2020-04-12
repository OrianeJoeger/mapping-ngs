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

vector <string> *Seq::getErrors() {
    return &(this->errors);
}

string Seq::toString(bool display_comp, bool display_rev) {
    string to_string = "[HEADER:] " + this->entete +
                       +"\n[SEQUENCE:] " + this->seqbio;
    if (display_comp)
        to_string += "\n[COMPLEMENTARY:] " + this->getSeqComp();

    if (display_rev)
        to_string += "\n[REVERSE:] " + this->getSeqRev();

    return to_string;
}

string Seq::toString() {
    return this->toString(false, false);
}