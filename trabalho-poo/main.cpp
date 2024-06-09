#include <iostream>
#include <vector>
#include <algorithm> 
#include "Serie.h"
#include "SerieDAO.h"
#include "Catalogo.h"
#include "PersistenciaBanco.h"

void exibirMenu() {
    cout << " --------------------------------------------------------------------" << endl;
    cout << "|                           MENU PRINCIPAL                           |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "|                                                                    |" << endl;
    cout << "|  (1) SERIES                                                        |" << endl;
    cout << "|      a) Incluir um novo registro                                   |" << endl;
    cout << "|      b) Recuperar um registro                                      |" << endl;
    cout << "|      c) Editar um registro                                         |" << endl;
    cout << "|      d) Excluir um registro                                        |" << endl;
    cout << "|                                                                    |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "|                                                                    |" << endl;
    cout << "|  (2) RELATORIOS                                                    |" << endl;
    cout << "|      a) Registros ordenados por titulo                             |" << endl;
    cout << "|      b) Registros ordenados por canal/streaming                    |" << endl;
    cout << "|      C) Registros ordenados por ano                                |" << endl;
    cout << "|      d) Registros ordenados por nota                               |" << endl;
    cout << "|                                                                    |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "|                                                                    |" << endl;
    cout << "|  (3) AJUDA                                                         |" << endl;
    cout << "|  (4) CREDITOS                                                      |" << endl;
    cout << "|  (5) SAIR                                                          |" << endl;
    cout << "|                                                                    |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
}

void incluirSerie(PersistenciaBanco& persistencia) {
    int release_year, season, episode_count, rating;
    string series_name, main_actors, main_characters, network;

    cout << " --------------------------------------------------------------------" << endl;
    cout << "|                        INCLUIR NOVA SERIE                          |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "- Nome da Serie: ";
    cin.ignore();
    getline(cin, series_name);
    cout << "- Ano de Lancamento: ";
    cin >> release_year;
    cout << "- Temporada: ";
    cin >> season;
    cout << "- Numero de episodios: ";
    cin >> episode_count;
    cout << "- Atores principais: ";
    cin.ignore();
    getline(cin, main_actors);
    cout << "- Personagens principais: ";
    getline(cin, main_characters);
    cout << "- Canal/Streaming: ";
    getline(cin, network);
    cout << "- Nota: ";
    cin >> rating;

    Serie novaSerie(0, series_name, release_year, season, episode_count, main_actors, main_characters, network, rating);
    persistencia.salvarSerie(novaSerie);
}

void recuperarSerie(PersistenciaBanco& persistencia) {
    int internal_id;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "|                         RECUPERAR SERIE                            |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "- ID da Serie: ";
    cin >> internal_id;

    Serie* serie = persistencia.carregarSerie(internal_id);
    if (serie) {
        cout << " --------------------------------------------------------------------" << endl;
        cout << "****** SERIE " << internal_id << " *******" << endl;
        cout << "Serie carregada: " << serie->getSeriesName() << endl;
        cout << "Ano de lancamento: " << serie->getReleaseYear() << endl;
        cout << "Temporada: " << serie->getSeason() << endl;
        cout << "Numero de episodios: " << serie->getEpisodeCount() << endl;
        cout << "Atores principais: " << serie->getMainActors() << endl;
        cout << "Personagens principais: " << serie->getMainCharacters() << endl;
        cout << "Canal/streaming: " << serie->getNetwork() << endl;
        cout << "Nota: " << serie->getRating() << endl;
        cout << "\n\n";
    }
    else {
        cout << "Serie nao encontrada." << endl;
    }
}

void editarSerie(PersistenciaBanco& persistencia) {
    int internal_id;
    cout << "Editar Serie:" << endl;
    cout << "ID da Serie: ";
    cin >> internal_id;

    Serie* serie = persistencia.carregarSerie(internal_id);
    if (serie) {
        int release_year, season, episode_count, rating;
        string series_name, main_actors, main_characters, network;

        cout << "Novo Nome da Serie (atual: " << serie->getSeriesName() << "): ";
        cin.ignore();
        getline(cin, series_name);
        cout << "Novo Ano de Lancamento (atual: " << serie->getReleaseYear() << "): ";
        cin >> release_year;
        cout << "Nova Temporada (atual: " << serie->getSeason() << "): ";
        cin >> season;
        cout << "Novo Numero de Episodios (atual: " << serie->getEpisodeCount() << "): ";
        cin >> episode_count;
        cout << "Novos Atores Principais (atual: " << serie->getMainActors() << "): ";
        cin.ignore();
        getline(cin, main_actors);
        cout << "Novos Personagens Principais (atual: " << serie->getMainCharacters() << "): ";
        getline(cin, main_characters);
        cout << "Novo Canal/Streaming (atual: " << serie->getNetwork() << "): ";
        getline(cin, network);
        cout << "Nova Nota (atual: " << serie->getRating() << "): ";
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
        cout << "Serie nao encontrada." << endl;
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

    cout << " --------------------------------------------------------------------" << endl;
    cout << "|                        CATALOGO DE SERIES                          |" << endl;
    cout << " --------------------------------------------------------------------" << endl;

    for (const auto& serie : series) {
        cout << "ID: " << serie.getInternalId() << ", Nome: " << serie.getSeriesName() << ", Ano: " << serie.getReleaseYear() << ", Temporada: " << serie.getSeason() << ", Episodios: " << serie.getEpisodeCount() << ", Canal/Streaming: " << serie.getNetwork() << ", Nota: " << serie.getRating() << endl;
    }

    cout << "\n\n" << endl;
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
        cout << "\nEscolha uma opcao (1-5): ";
        cin >> opcao;

        switch (opcao) {
        case '1':
            char subOpcao;
            cout << "Escolha uma sub-opcao (a-d): ";
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
                cout << "Opcao invalida!" << endl;
                break;
            }
            break;
        case '2':
            cout << "Escolha uma sub-opcao: ";
            cin >> opcao;
            relatorios(persistencia, opcao);
            break;
        case '3':
            cout << "Ajuda: Utilize as opcoes do menu para interagir com o sistema." << endl;
            break;
        case '4':
            cout << "Creditos: Desenvolvido por Heloisa, Camila, Geovanne, Thalita e Gaby." << endl;
            break;
        case '5':
            cout << "Saindo..." << endl;
            break;
        default:
            cout << "Opcao invalida!" << endl;
            break;
        }
    } while (opcao != '5');

    return 0;
}
