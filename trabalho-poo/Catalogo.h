#ifndef CATALOGO_H
#define CATALOGO_H

#include <vector>
#include "Serie.h"

class Catalogo {
private:
    vector<Serie> series;

public:
    void adicionarSerie(const Serie& serie);
    Serie* buscarSerie(int internal_id);
    void removerSerie(int internal_id);
};

#endif // CATALOGO_H
