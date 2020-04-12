#include <iostream>
#include <string>

#include "../include/SeqQ.h"

using namespace std;

SeqQ::SeqQ(const vector <string> errors, const string &entete, const string &seqbio, const string &qualite) :
        Seq(errors, entete, seqbio),
        qualite(qualite) {

}

string SeqQ::getQualite() {
    return this->qualite;
}