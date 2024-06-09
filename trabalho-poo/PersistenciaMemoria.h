#ifndef PERSISTENCIAMEMORIA_H
#define PERSISTENCIAMEMORIA_H

#include "SerieDAO.h"
#include <vector>

class PersistenciaMemoria : public SerieDAO {
private:
    std::vector<Serie> series;

public:
    void salvarSerie(const Serie& serie) override;
    void removerSerie(int internal_id) override;
    Serie* carregarSerie(int internal_id) override;
    std::vector<Serie> listarSeries() override;
};

#endif // PERSISTENCIAMEMORIA_H
