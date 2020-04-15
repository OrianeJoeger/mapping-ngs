
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cassert>
#include "../include/EncodedSequence.h"
#include "../include/Reader.h"


using namespace std;

const size_t EncodedSequence::endpos = (size_t) - 1;

EncodedSequence::EncodedSequence(const char *seq, std::vector <std::string> *errors)
        : tab(NULL), n(0), N(0) {
    size_t i = 0;
    while (seq && (seq[i] != '\0')) {
        if (seq[i] > ' ') {
            if (Reader::isNucleic(seq[i])) {
                ++n;
            } else {
                errors->push_back("Warn : bad character at pos " + to_string(i));
            }
        }
        ++i;
    }
    reserve(n);
    n = i = 0;
    while (seq && (seq[i] != '\0')) {
        if (Reader::isNucleic(seq[i])) {
            push_back(seq[i]);
        }
        ++i;
    }
}

EncodedSequence::EncodedSequence(const std::string seqbio, std::vector <std::string> *errors)
        : tab(NULL), n(0), N(0) {
    const char * seq = seqbio.c_str();
    size_t i = 0;
    while (seq && (seq[i] != '\0')) {
        if (seq[i] > ' ') {
            if (Reader::isNucleic(seq[i])) {
                ++n;
            } else {
                errors->push_back("Warn : bad character at pos " + to_string(i));
            }
        }
        ++i;
    }
    reserve(n);
    n = i = 0;
    while (seq && (seq[i] != '\0')) {
        if (Reader::isNucleic(seq[i])) {
            push_back(seq[i]);
        }
        ++i;
    }
}


EncodedSequence::EncodedSequence(const EncodedSequence &seq) : tab(NULL), n(seq.n), N(seq.N) {
    if (N) {
        tab = new uint8_t[N];
        for (size_t i = 0; i < N; ++i) {
            tab[i] = seq.tab[i];
        }
    }
}

EncodedSequence::~EncodedSequence() {
    if (N) {
        delete[] tab;
    }
}

EncodedSequence &EncodedSequence::operator=(const EncodedSequence &seq) {
    if (this != &seq) {
        if (N != seq.N) {
            if (N) {
                delete[] tab;
            }
            N = seq.N;
            if (N) {
                tab = new uint8_t[N];
            }
        }
        n = seq.n;
        if (N) {
            for (size_t i = 0; i < N; ++i) {
                tab[i] = seq.tab[i];
            }
        }
    }
    return *this;
}

char EncodedSequence::at(size_t i) const {
    if (i >= n) {
        throw std::out_of_range("Out of EncodedSequence bounds");
    }
    return operator[](i);
}

static size_t getByte(size_t i) {
    return i >> 2; /* même chose que (i / 4) mais plus rapide */
}

size_t getByteShift(size_t i) {
    return (3 - (i & 3)) << 1; /* même chose que 2 * (3 - (i % 4)) mais plus rapide */
}

uint8_t encode(char c) {
    return ((c == 'a') || (c == 'A')
            ? 0
            : ((c == 'c') || (c == 'C')
               ? 1
               : ((c == 'g') || (c == 'G')
                  ? 2
                  : ((c == 't') || (c == 'T')
                     || (c == 'u') || (c == 'U')
                     ? 3
                     : (rand() & 3)))));
}

char decode(uint8_t v) {
    return (v == 0
            ? 'A'
            : (v == 1
               ? 'C'
               : (v == 2
                  ? 'G'
                  : (v == 3
                     ? 'T'
                     : 'N'))));
}

char EncodedSequence::operator[](size_t i) const {
    return decode((tab[getByte(i)] >> getByteShift(i)) & 3);
}

void EncodedSequence::set(size_t i, char c) {
    uint8_t v = tab[getByte(i)] & (~(3 << getByteShift(i)));
    tab[getByte(i)] = v | (encode(c) << getByteShift(i));
}

void EncodedSequence::push_back(char c) {
    reserve(n + 1);
    set(n++, c);
}

EncodedSequence EncodedSequence::substr(size_t i, size_t len) const {
    size_t max_i = (len == endpos
                    ? n
                    : i + len > n
                      ? n
                      : i + len);
    EncodedSequence res;
    res.reserve(max_i - i);
    for (size_t j = i; j < max_i; ++j) {
        res.push_back(operator[](j));
    }
    return res;
}

void EncodedSequence::reserve(size_t len) {
    if (len) {
        size_t min_N = getByte(len - 1) + 1;
        if (min_N > N) {
            uint8_t *aux = new uint8_t[min_N];
            for (size_t i = 0; i < N; ++i) {
                aux[i] = tab[i];
            }
            delete[] tab;
            tab = aux;
            N = min_N;
        }
    }
}

string EncodedSequence::toString() const {
    string str = "";
    for (size_t i = 0; i < this->n; ++i) {
        str += this->operator[](i);
    }
    return str;
}

ostream &operator<<(ostream &os, const EncodedSequence &seq) {
    for (size_t i = 0; i < seq.size(); ++i) {
        os << seq[i];
    }
    return os;
}
