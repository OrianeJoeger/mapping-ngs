#include <string>

#include "../include/SeqQ.h"

using namespace std;

SeqQ::SeqQ(const string &entete, const EncodedSequence &seqbio, const string &qualite) :
        Seq(entete, seqbio),
        qualite(qualite) {

}

SeqQ::SeqQ(const string &entete, const string &seqbio, const string &qualite) :
        Seq(entete, seqbio),
        qualite(qualite) {

}

string SeqQ::getQualite() {
    return this->qualite;
}

string SeqQ::toString(bool display_comp, bool display_rev) {
    return Seq::toString(display_comp, display_rev)
           + "\n[QUALITY:] " + this->qualite;
}