#ifndef __FASTA_H__
#define __FASTA_H__

#include "FastX.h"
#include <string>


class Fasta : public FastX {
	public:
		Fasta(const std::string &entete = "", const std::string &seqbio= "");
		virtual void fromStream (std::istream &is);
};

#endif