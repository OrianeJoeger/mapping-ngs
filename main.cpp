#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "include/FastFile.h"
#include "include/FastX.h"

void help() {
    cout << "Fast[A-Q] parser : " << endl;
    cout << "usage prog_exec <file_name>" << endl;
    cout << "    options:" << endl;
    cout << "    --help : display this message" << endl;
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

    FastFile fast_file(file);
    cout << "-- Format [" << fast_file.getFormat() << "]" << endl;

    cout << "-- Size [" << fast_file.getData().size() << "]" << endl;

}
