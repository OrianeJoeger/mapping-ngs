#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "include/FastA.h"
#include "include/FastQ.h"
#include "include/FastX.h"

void help() {
    cout << "Fast[A-Q] parser : " << endl;
    cout << "usage prog_exec <file_name>" << endl;
    cout << "    options:" << endl;
    cout << "    --help : display this message" << endl;
}

FastX *detect(istream &is) {
    char c;

    while (!is.eof() && (c = is.get()) > ' ') {
        if (c == ';' || c == '>') {
            return new FastA;
        } else if (c == '@') {
            return new FastQ;
        } else {
            break;
        }
    }

    throw "Error unknown format type";
}

FastX *parse(filebuf &file) {
    istream is(&file);

    FastX *fast(NULL);

    fast = detect(is);

    fast->fromStream(is);

    return fast;
}

int main(int argc, char **argv) {
    char *file;

    int i = 1;
    std::string arg;

    while (i < argc) {
        arg = argv[i];
        if (arg == "--help") {
            help();
            return 0;
        }
        if (arg.rfind("--", 0) == 0 || arg.rfind("-", 0) == 0) {
            cerr << "Unknown option : " << arg << endl;
            return 1;
        }

        file = argv[i];
        i++;
    }

    filebuf fb;
    if (!fb.open(file, ios::in)) {
        cerr << "Invalid file : " << file << endl;
        return 1;
    }

    FastX *fast = parse(fb);

    cout << "-- Format [" << fast->getType() << "]" << endl;

    cout << "--- Header" << endl;
    cout << fast->getHeader() << endl << endl;
    cout << "--- Seqbio" << endl;
    cout << fast->getSeqbio() << endl << endl;
    cout << "--- SeqComp" << endl;
    cout << fast->getSeqComp() << endl << endl;
    cout << "--- Seqrev" << endl;
    cout << fast->getSeqRev() << endl << endl;

    fb.close();

    return 0;
}
