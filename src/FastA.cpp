#include <iostream>
#include <string>

#include "../include/FastA.h"

using namespace std;

FastA::FastA(const std::vector <std::string> errors, const string &entete, const string &seqbio) :
        FastX(errors, entete, seqbio) {

}
