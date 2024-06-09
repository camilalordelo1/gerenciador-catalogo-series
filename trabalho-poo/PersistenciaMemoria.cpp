#include "PersistenciaMemoria.h"

void PersistenciaMemoria::salvarSerie(const Serie& serie) {
    series.push_back(serie);
}

void PersistenciaMemoria::removerSerie(int internal_id) {
    series.erase(remove_if(series.begin(), series.end(), [internal_id](const Serie& serie) {
        return serie.getInternalId() == internal_id;
        }), series.end());
}

Serie* PersistenciaMemoria::carregarSerie(int internal_id) {
    for (auto& serie : series) {
        if (serie.getInternalId() == internal_id) {
            return &serie;
        }
    }
    return nullptr;
}

std::vector<Serie> PersistenciaMemoria::listarSeries() {
    return series;
}
