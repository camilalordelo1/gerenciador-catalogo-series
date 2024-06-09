#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "Serie.h"
#include <vector>

class Persistencia {
public:
    virtual void salvarSerie(const Serie& serie) = 0;
    virtual void removerSerie(int internal_id) = 0;
    virtual Serie* carregarSerie(int internal_id) = 0;
    virtual std::vector<Serie> listarSeries() = 0;
};

#endif // PERSISTENCIA_H
