#ifndef SERIEDAO_H
#define SERIEDAO_H

#include "Serie.h"
#include <vector>

class SerieDAO {
public:
    virtual void salvarSerie(const Serie& serie) = 0;
    virtual void removerSerie(int internal_id) = 0;
    virtual Serie* carregarSerie(int internal_id) = 0;
    virtual std::vector<Serie> listarSeries() = 0;
};

#endif // SERIEDAO_H
