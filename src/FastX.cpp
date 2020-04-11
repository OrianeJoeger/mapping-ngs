#include <string>
#include <algorithm>
#include <list>

#include "../include/FastX.h"

using namespace std;

FastX::FastX(const string &entete, const string &seqbio) :
        entete(entete),
        seqbio(seqbio) {

}

void FastX::toStream(ostream &os) {  // os parametre pour afficher (tostring)
    os << "entete = '" << this->entete << "'" << endl // attribut entete et seqbio
       << "sequence = '" << this->seqbio << "'" << endl;
}

istream &operator>>(istream &is, FastX &f) {
    f.fromStream(is);
    return is;
}

ostream &operator<<(ostream &os, FastX &f) {
    f.toStream(os);
    return os;
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

bool FastX::isNucl(char c) {
    return (c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'U' || c == 'R' || c == 'Y' || c == 'S' || c == 'W' ||
            c == 'K' || c == 'M' || c == 'B' || c == 'D' || c == 'H' || c == 'V' || c == 'N' || c == '.' || c == '-');
}

bool FastX::isAA(char c) {
    return (c == 'A' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' || c == 'H' || c == 'I' || c == 'J' ||
            c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' ||
            c == 'V' || c == 'W' || c == 'Y');
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
