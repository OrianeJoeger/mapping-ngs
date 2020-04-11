#include <iostream>
#include <string>
#include <fstream>

#ifndef __FASTX_H__
#define __FASTX_H__

// se renseigner sur cassert 

class FastX {
protected:
    std::string entete;
    std::string seqbio;
public:
    FastX(const std::string &entete = "", const std::string &seqbio = "");

    //Ajouter méthodes ici
    virtual std::string getType() = 0;

    virtual void fromStream(std::istream &is) = 0; //virtuel pur

    virtual void toStream(std::ostream &os);

    //virtual void lireFichier(std::ifstream &ifs) = 0; // = 0 interdit la construction de FastX
    virtual bool isNucl(char c);

    virtual bool isAA(char c);

    std::string getSeqbio();

    std::string getHeader();

    void setHeader(std::string header);

    size_t getSeqbioLength();

    std::string getSeqComp();

    std::string getSeqRev();

    std::string getSeqRevComp();
};

std::istream &operator>>(std::istream &is, FastX &f);

std::ostream &operator<<(std::ostream &os, const FastX &f);

#endif
