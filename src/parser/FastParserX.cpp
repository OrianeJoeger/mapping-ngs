#include <iostream>
#include <string>

#include "../../include/parser/FastParserX.h"

using namespace std;

bool FastParserX::isNucleic(char c) {
    return c == 'A' || c == 'C' || c == 'G' || c == 'T' || c == 'U' || c == 'R' || c == 'Y' || c == 'S' || c == 'W' ||
           c == 'K' || c == 'M' || c == 'B' || c == 'D' || c == 'H' || c == 'V' || c == 'N' || c == '.' || c == '-';
}

bool FastParserX::isAmino(char c) {
    return c == 'A' || c == 'C' || c == 'D' || c == 'E' || c == 'F' || c == 'G' || c == 'H' || c == 'I' || c == 'J' ||
           c == 'K' || c == 'L' || c == 'M' || c == 'N' || c == 'P' || c == 'Q' || c == 'R' || c == 'S' || c == 'T' ||
           c == 'V' || c == 'W' || c == 'Y';
}
