#include <iostream>
#include <string>

#include "../include/FastQ.h"

using namespace std;

FastQ::FastQ(const vector <string> errors, const string &entete, const string &seqbio, const string &qualite) :
        FastX(errors, entete, seqbio),
        qualite(qualite) {

}

string FastQ::getQualite() {
    return this->qualite;
}