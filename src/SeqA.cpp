#include <string>

#include "../include/SeqA.h"

using namespace std;

SeqA::SeqA(const string &entete, const EncodedSequence &seqbio) :
        Seq(entete, seqbio) {

}

SeqA::SeqA(const string &entete, const string &seqbio) :
        Seq(entete, seqbio) {

}
