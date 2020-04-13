#ifndef __ENCODEDSEQUENCE_H__
#define __ENCODEDSEQUENCE_H__

// doxygen peut reconnaître les commentaires /** */ (qui commencent par /** au lieu de /*)
// pour automatiser la création de documentations

#include <stdint.h>
#include <iostream>
#include <string>

class EncodedSequence {
    friend void test_EncodedSequence();

private:
    uint8_t *tab;
    size_t n;
    size_t N;

public:
    EncodedSequence(const char *seq = NULL);

    EncodedSequence(const std::string seq);

    EncodedSequence(const EncodedSequence &seq);

    ~EncodedSequence();

    EncodedSequence &operator=(const EncodedSequence &seq);

    inline size_t size() const {
        return n;
    }

    inline bool empty() const {
        return !n;
    }

    char at(size_t i) const;

    char operator[](size_t i) const;

    void set(size_t i, char c);

    void push_back(char c);

    EncodedSequence substr(size_t i, size_t len = endpos) const;

    void reserve(size_t len); // allouer len octets -> stocker 4*len nucléotides

    std::string toString() const;

    static const size_t endpos;
};

std::ostream &operator<<(std::ostream &os, const EncodedSequence &seq);

#endif

