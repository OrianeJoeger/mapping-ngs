#include <iostream>
#include <fstream>

#include "../include/Fasta.h"
#include "../include/FastQ.h"
#include "../include/FastX.h"

using namespace std;


int main(int argc, char **argv) {
	Fasta fasta1;
	filebuf fb;

	if (fb.open("./fastaH.fasta", ios::in)) {
		istream is(&fb);
		fasta1.fromStream(is);
	}
	cout << fasta1.getHeader() << endl;
	cout << fasta1.getSeqbio() << endl;
	cout << fasta1.getSeqComp() << endl;
	cout << fasta1.getSeqRev() << endl;
}


