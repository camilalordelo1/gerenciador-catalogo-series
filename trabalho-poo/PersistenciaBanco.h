#ifndef PERSISTENCIABANCO_H
#define PERSISTENCIABANCO_H

#include "SerieDAO.h"
#include <mariadb/conncpp.hpp>
#include <vector>

using namespace std;

class PersistenciaBanco : public SerieDAO {
private:
    sql::Driver* driver;
    unique_ptr<sql::Connection> conn;

public:
    PersistenciaBanco(const string& host, const string& user, const string& pass, const string& db);
    ~PersistenciaBanco();

    void salvarSerie(const Serie& serie) override;
    void removerSerie(int internal_id) override;
    Serie* carregarSerie(int internal_id) override;
    void atualizarSerie(const Serie& serie);
    vector<Serie> listarSeries() override;
};

#endif // PERSISTENCIABANCO_H
