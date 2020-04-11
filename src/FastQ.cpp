#include <iostream>
#include <string>

#include "../include/FastQ.h"

using namespace std;

FastQ::FastQ(const string &entete, const string &seqbio, const string &qualite) :
        FastX(entete, seqbio),
        qualite(qualite) {

}
