#include "PersistenciaBanco.h"
#include <iostream>

PersistenciaBanco::PersistenciaBanco(const string& host, const string& user, const string& pass, const string& db) {
    driver = sql::mariadb::get_driver_instance();
    conn = unique_ptr<sql::Connection>(driver->connect("jdbc:mariadb://" + host + "/" + db, user, pass));
}

PersistenciaBanco::~PersistenciaBanco() {
    conn->close();
}

void PersistenciaBanco::salvarSerie(const Serie& serie) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO series (series_name, release_year, season, episode_count, main_actors, main_characters, network, rating) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"));
        pstmt->setString(1, serie.getSeriesName());
        pstmt->setInt(2, serie.getReleaseYear());
        pstmt->setInt(3, serie.getSeason());
        pstmt->setInt(4, serie.getEpisodeCount());
        pstmt->setString(5, serie.getMainActors());
        pstmt->setString(6, serie.getMainCharacters());
        pstmt->setString(7, serie.getNetwork());
        pstmt->setInt(8, serie.getRating());
        pstmt->execute();
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

void PersistenciaBanco::atualizarSerie(const Serie& serie) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "UPDATE series SET series_name = ?, release_year = ?, season = ?, episode_count = ?, main_actors = ?, main_characters = ?, network = ?, rating = ? "
            "WHERE internal_id = ?"));
        pstmt->setString(1, serie.getSeriesName());
        pstmt->setInt(2, serie.getReleaseYear());
        pstmt->setInt(3, serie.getSeason());
        pstmt->setInt(4, serie.getEpisodeCount());
        pstmt->setString(5, serie.getMainActors());
        pstmt->setString(6, serie.getMainCharacters());
        pstmt->setString(7, serie.getNetwork());
        pstmt->setInt(8, serie.getRating());
        pstmt->setInt(9, serie.getInternalId());
        pstmt->execute();
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}


void PersistenciaBanco::removerSerie(int internal_id) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("DELETE FROM series WHERE internal_id = ?"));
        pstmt->setInt(1, internal_id);
        pstmt->execute();
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
}

Serie* PersistenciaBanco::carregarSerie(int internal_id) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM series WHERE internal_id = ?"));
        pstmt->setInt(1, internal_id);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            string series_name = res->getString("series_name").c_str();
            int release_year = res->getInt("release_year");
            int season = res->getInt("season");
            int episode_count = res->getInt("episode_count");
            string main_actors = res->getString("main_actors").c_str();
            string main_characters = res->getString("main_characters").c_str();
            string network = res->getString("network").c_str();
            int rating = res->getInt("rating");

            return new Serie(internal_id, series_name, release_year, season, episode_count, main_actors, main_characters, network, rating);
        }
        else {
            return nullptr;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
        return nullptr;
    }
}

vector<Serie> PersistenciaBanco::listarSeries() {
    vector<Serie> series;
    try {
        unique_ptr<sql::Statement> stmt(conn->createStatement());
        unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM series"));

        while (res->next()) {
            int internal_id = res->getInt("internal_id");
            string series_name = res->getString("series_name").c_str();
            int release_year = res->getInt("release_year");
            int season = res->getInt("season");
            int episode_count = res->getInt("episode_count");
            string main_actors = res->getString("main_actors").c_str();
            string main_characters = res->getString("main_characters").c_str();
            string network = res->getString("network").c_str();
            int rating = res->getInt("rating");

            series.push_back(Serie(internal_id, series_name, release_year, season, episode_count, main_actors, main_characters, network, rating));
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what() << std::endl;
    }
    return series;
}
