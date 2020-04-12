#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "include/FastFile.h"
#include "include/FastX.h"
#include "include/FastQ.h"

void help() {
    cout << "Fast[A-Q] parser : " << endl;
    cout << "usage prog_exec <file_name>" << endl;
    cout << "    options:" << endl;
    cout << "    --help : display this message" << endl;
    cout << "    --count : only count sequence in file" << endl;
    cout << "    --only-errors : display only sequence with errors" << endl;
    cout << "    --display-errors : display errors" << endl;
    cout << "    --comp : display sequence complementary" << endl;
    cout << "    --rev : display rev sequence" << endl;
}

int main(int argc, char **argv) {
    int i = 1;
    bool display_error = false;
    bool only_seq_with_error = false;
    bool count_only = false;
    bool comp = false;
    bool rev = false;

    char *file;

    std::string arg;

    while (i < argc) {
        arg = argv[i];

        if (arg == "--help") {
            help();
            return 0;
        } else if (arg == "--display-errors") {
            display_error = true;
        } else if (arg == "--only-errors") {
            only_seq_with_error = true;
        } else if (arg == "--count") {
            count_only = true;
        } else if (arg == "--comp") {
            comp = true;
        } else if (arg == "--rev") {
            rev = true;
        } else if (arg.rfind("--", 0) == 0 || arg.rfind("-", 0) == 0) {
            cerr << "Unknown option : " << arg << endl;
            return 1;
        } else {
            file = argv[i];
        }

        i++;
    }

    try {
        FastFile fast_file(file);

        cout << "[F:] " << fast_file.getFormat() << endl;
        cout << "[N:] " << fast_file.getData().size() << endl;

        if (!count_only) {
            for (FastX *seq : fast_file.getData()) {
                if (only_seq_with_error) {
                    if (seq->hasErrors()) {
                        cout << endl;

                        cout << "[H:] " << seq->getHeader() << endl;
                        cout << "[S:] " << seq->getSeqbio() << endl;
                        if (comp) cout << "[C:] " << seq->getSeqComp() << endl;
                        if (rev) cout << "[R:] " << seq->getSeqRev() << endl;
                        if (fast_file.getFormat() == "FASTQ") {
                            cout << "[Q:] " << ((FastQ *) seq)->getQualite() << endl;
                        }
                        cout << "[E:] " << seq->countErrors() << endl;

                        if (display_error) {
                            for (string error : seq->getErrors()) {
                                cout << "    - " << error << endl;
                            }
                        }
                    }
                } else {
                    cout << endl;

                    cout << "[H:] " << seq->getHeader() << endl;
                    cout << "[S:] " << seq->getSeqbio() << endl;
                    if (comp) cout << "[C:] " << seq->getSeqComp() << endl;
                    if (rev) cout << "[R:] " << seq->getSeqRev() << endl;
                    if (fast_file.getFormat() == "FASTQ") {
                        cout << "[Q:] " << ((FastQ *) seq)->getQualite() << endl;
                    }
                    if (seq->hasErrors()) cout << "[E:] " << seq->countErrors() << endl;

                    if (display_error) {
                        for (string error : seq->getErrors()) {
                            cout << "    - " << error << endl;
                        }
                    }
                }
            }
        }
    } catch (const char *error) {
        cerr << error << endl;
    } catch (...) {
        cerr << "Fatal error" << endl;
    }
}
