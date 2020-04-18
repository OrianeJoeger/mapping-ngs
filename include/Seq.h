#ifndef __SEQ_H__
#define __SEQ_H__

#include <cstdint>
#include <string>
#include <vector>

#include "EncodedSequence.h"

class Seq {
protected:
    /**
     * Entete de la sequence
     *
     * @property
     */
    std::string entete;
    /**
     * Sequence biologique encodé
     *
     * @property
     */
    EncodedSequence seq;
    /**
     * Erreurs detecté
     *
     * @property
     */
    std::vector <std::string> errors;
public:
    /**
     * @constructor
     * @param string entete Entete de la sequence
     * @param EncodeSequence seq Sequence biologique encodé
     */
    Seq(
            const std::string &entete,
            const EncodedSequence &seq
    );

    /**
     * @constructor
     * @param string entete Entete de la sequence
     * @param string seq Sequence biologique au format string
     */
    Seq(
            const std::string &entete = "",
            const std::string &seqbio = ""
    );

    /**
     * Retourne la sequence biologique
     *
     * @return string
     */
    std::string getSeqbio();

    /**
     * Retourne l'entete de la sequence
     *
     * @return string
     */
    std::string getHeader();

    /**
     * Retourne la longueur de la sequence biologique
     *
     * @return int
     */
    size_t getSeqbioLength();

    /**
     * Retourne le complement de la sequence
     *
     * @return string
     */
    std::string getSeqComp();

    /**
     * Retourne le reverse de la sequence
     *
     * @return string
     */
    std::string getSeqRev();

    /**
     * Retourne le complement reverse de la sequence
     *
     * @return string
     */
    std::string getSeqRevComp();

    /**
     * Retourne si la sequence a des erreurs
     *
     * @return bool
     */
    bool hasErrors() const;

    /**
     * Retourne le nombre d'erreur
     *
     * @return bool
     */
    int countErrors() const;

    /**
     * Retourne les erreurs
     *
     * @return vector<string>
     */
    std::vector <std::string> *getErrors();

    /**
     * Retourne la sequence au format string avec l'entete
     *
     * @param display_comp Affiche le complement de la sequence
     * @param display_rev  Affiche le reverse de la sequence
     * @return string
     */
    virtual std::string toString(bool display_comp, bool display_rev);

    /**
     * Retourne la sequence au format string avec l'entete
     *
     * @return string
     */
    virtual std::string toString();
};

#endif