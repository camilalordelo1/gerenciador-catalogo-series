#include "Catalogo.h"

void Catalogo::adicionarSerie(const Serie& serie) {
    series.push_back(serie);
}

Serie* Catalogo::buscarSerie(int internal_id) {
    for (auto& serie : series) {
        if (serie.getInternalId() == internal_id) {
            return &serie;
        }
    }
    return nullptr;
}

void Catalogo::removerSerie(int internal_id) {
    series.erase(remove_if(series.begin(), series.end(), [internal_id](const Serie& serie) {
        return serie.getInternalId() == internal_id;
        }), series.end());
}
