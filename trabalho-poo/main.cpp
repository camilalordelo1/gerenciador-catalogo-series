#include <iostream>
#include <vector>
#include <algorithm> 
#include "Serie.h"
#include "SerieDAO.h"
#include "Catalogo.h"
#include "PersistenciaBanco.h"

void exibirMenu() {
    std::cout << "Menu Principal:" << endl;
    std::cout << "1. Series" << endl;
    std::cout << "   a) Incluir um novo registro" << endl;
    std::cout << "   b) Recuperar um registro" << endl;
    std::cout << "   c) Editar um registro" << endl;
    std::cout << "   d) Excluir um registro" << endl;
    std::cout << "2. Relatorios" << endl;
    std::cout << "   a) Registros ordenados por título" << endl;
    std::cout << "   b) Registros ordenados por canal/streaming" << endl;
    std::cout << "   c) Registros ordenados por ano" << endl;
    std::cout << "   d) Registros ordenados por nota" << endl;
    std::cout << "3. Ajuda" << endl;
    std::cout << "4. Creditos" << endl;
    std::cout << "5. Sair" << endl;
}

void incluirSerie(PersistenciaBanco& persistencia) {
    int release_year, season, episode_count, rating;
    string series_name, main_actors, main_characters, network;

    std::cout << "Incluir Nova Serie:" << endl;
    std::cout << "Nome da Serie: ";
    cin.ignore();
    getline(cin, series_name);
    std::cout << "Ano de Lancamento: ";
    cin >> release_year;
    std::cout << "Temporada: ";
    cin >> season;
    std::cout << "Numero de Episodios: ";
    cin >> episode_count;
    std::cout << "Atores Principais: ";
    cin.ignore();
    getline(cin, main_actors);
    std::cout << "Personagens Principais: ";
    getline(cin, main_characters);
    std::cout << "Canal/Streaming: ";
    getline(cin, network);
    std::cout << "Nota: ";
    cin >> rating;

    Serie novaSerie(0, series_name, release_year, season, episode_count, main_actors, main_characters, network, rating);
    persistencia.salvarSerie(novaSerie);
}

void recuperarSerie(PersistenciaBanco& persistencia) {
    int internal_id;
    std::cout << "Recuperar Serie:" << endl;
    std::cout << "ID da Serie: ";
    cin >> internal_id;

    Serie* serie = persistencia.carregarSerie(internal_id);
    if (serie) {
        std::cout << "Serie carregada: " << serie->getSeriesName() << endl;
        std::cout << "Ano de lancamento: " << serie->getReleaseYear() << endl;
        std::cout << "Temporada: " << serie->getSeason() << endl;
        std::cout << "Numero de episodios: " << serie->getEpisodeCount() << endl;
        std::cout << "Atores principais: " << serie->getMainActors() << endl;
        std::cout << "Personagens principais: " << serie->getMainCharacters() << endl;
        std::cout << "Canal/Streaming: " << serie->getNetwork() << endl;
        std::cout << "Nota: " << serie->getRating() << endl;
    }
    else {
        std::cout << "Serie nao encontrada." << endl;
    }
}

void editarSerie(PersistenciaBanco& persistencia) {
    int internal_id;
    std::cout << "Editar Serie:" << endl;
    std::cout << "ID da Serie: ";
    cin >> internal_id;

    Serie* serie = persistencia.carregarSerie(internal_id);
    if (serie) {
        int release_year, season, episode_count, rating;
        string series_name, main_actors, main_characters, network;

        std::cout << "Novo Nome da Serie (atual: " << serie->getSeriesName() << "): ";
        cin.ignore();
        getline(cin, series_name);
        std::cout << "Novo Ano de Lancamento (atual: " << serie->getReleaseYear() << "): ";
        cin >> release_year;
        std::cout << "Nova Temporada (atual: " << serie->getSeason() << "): ";
        cin >> season;
        std::cout << "Novo Numero de Episodios (atual: " << serie->getEpisodeCount() << "): ";
        cin >> episode_count;
        std::cout << "Novos Atores Principais (atual: " << serie->getMainActors() << "): ";
        cin.ignore();
        getline(cin, main_actors);
        std::cout << "Novos Personagens Principais (atual: " << serie->getMainCharacters() << "): ";
        getline(cin, main_characters);
        std::cout << "Novo Canal/Streaming (atual: " << serie->getNetwork() << "): ";
        getline(cin, network);
        std::cout << "Nova Nota (atual: " << serie->getRating() << "): ";
        cin >> rating;

        serie->setSeriesName(series_name);
        serie->setReleaseYear(release_year);
        serie->setSeason(season);
        serie->setEpisodeCount(episode_count);
        serie->setMainActors(main_actors);
        serie->setMainCharacters(main_characters);
        serie->setNetwork(network);
        serie->setRating(rating);

        persistencia.salvarSerie(*serie);
    }
    else {
        std::cout << "Serie nao encontrada." << endl;
    }
}

void excluirSerie(SerieDAO& persistencia) {
    int internal_id;
    cout << "Excluir Série:" << endl;
    cout << "ID da Série: ";
    cin >> internal_id;
    persistencia.removerSerie(internal_id);
}

void relatorios(SerieDAO& persistencia, char opcao) {
    vector<Serie> series = persistencia.listarSeries();

    switch (opcao) {
    case 'a':
        sort(series.begin(), series.end(), [](const Serie& a, const Serie& b) {
            return a.getSeriesName() < b.getSeriesName();
            });
        break;
    case 'b':
        sort(series.begin(), series.end(), [](const Serie& a, const Serie& b) {
            return a.getNetwork() < b.getNetwork();
            });
        break;
    case 'c':
        sort(series.begin(), series.end(), [](const Serie& a, const Serie& b) {
            return a.getReleaseYear() < b.getReleaseYear();
            });
        break;
    case 'd':
        sort(series.begin(), series.end(), [](const Serie& a, const Serie& b) {
            return a.getRating() < b.getRating();
            });
        break;
    default:
        cout << "Opção inválida!" << endl;
        return;
    }

    for (const auto& serie : series) {
        cout << "ID: " << serie.getInternalId() << ", Nome: " << serie.getSeriesName() << ", Ano: " << serie.getReleaseYear() << ", Temporada: " << serie.getSeason() << ", Episódios: " << serie.getEpisodeCount() << ", Canal/Streaming: " << serie.getNetwork() << ", Nota: " << serie.getRating() << endl;
    }
}

int main() {
    //PersistenciaBanco persistencia;
    std::string host = "127.0.0.1:3306";
    std::string user = "root";
    std::string pass = "admin";
    std::string db = "catalogo";

    PersistenciaBanco persistencia(host, user, pass, db);

    char opcao;
    do {
        exibirMenu();
        std::cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case '1':
            char subOpcao;
            std::cout << "Escolha uma subopcao: ";
            cin >> subOpcao;
            switch (subOpcao) {
            case 'a':
                incluirSerie(persistencia);
                break;
            case 'b':
                recuperarSerie(persistencia);
                break;
            case 'c':
                editarSerie(persistencia);
                break;
            case 'd':
                excluirSerie(persistencia);
                break;
            default:
                std::cout << "Opcao invalida!" << endl;
                break;
            }
            break;
        case '2':
            std::cout << "Escolha uma subopcao: ";
            cin >> opcao;
            relatorios(persistencia, opcao);
            break;
        case '3':
            std::cout << "Ajuda: Utilize as opcões do menu para interagir com o sistema." << endl;
            break;
        case '4':
            std::cout << "Creditos: Desenvolvido por Heloisa, Camila, Geovanne, Thalita e Gaby." << endl;
            break;
        case '5':
            std::cout << "Saindo..." << endl;
            break;
        default:
            std::cout << "Opcao invalida!" << endl;
            break;
        }
    } while (opcao != '5');

    return 0;
}
