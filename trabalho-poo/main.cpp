#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>
#include <cctype>

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

    cout << "\n\n --------------------------------------------------------------------" << endl;
    cout << "|                        INCLUIR NOVA SERIE                          |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "- NOME: ";
    cin.ignore();
    getline(cin, series_name);
    cout << "- ANO DE LANCAMENTO (XXXX): ";
    cin >> release_year;
    cout << "- TEMPORADA: ";
    cin >> season;
    cout << "- Nº DE EPISODIOS: ";
    cin >> episode_count;
    cout << "- ATORES PRINCIPAIS: ";
    cin.ignore();
    getline(cin, main_actors);
    cout << "- PERSONAGENS PRINCIPAIS: ";
    getline(cin, main_characters);
    cout << "- CANAL/STREAMING: ";
    getline(cin, network);
    cout << "- NOTA (1-10): ";
    cin >> rating;

    Serie novaSerie(0, series_name, release_year, season, episode_count, main_actors, main_characters, network, rating);
    persistencia.salvarSerie(novaSerie);
}

void recuperarSerie(PersistenciaBanco& persistencia) {
    int internal_id;

    cout << "\n\n --------------------------------------------------------------------" << endl;
    cout << "|                         RECUPERAR SERIE                            |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "- Digite o ID da Serie: ";
    cin >> internal_id;

    Serie* serie = persistencia.carregarSerie(internal_id);

    if (serie) {
        cout << " --------------------------------------------------------------------" << endl;
        cout << "****** SERIE " << internal_id << " *******" << endl;
        cout << "- NOME: " << serie->getSeriesName() << endl;
        cout << "- ANO DE LANCAMENTO: " << serie->getReleaseYear() << endl;
        cout << "- TEMPORADA: " << serie->getSeason() << endl;
        cout << "- Nº DE EPISODIOS: " << serie->getEpisodeCount() << endl;
        cout << "- ATORES PRINCIPAIS: " << serie->getMainActors() << endl;
        cout << "- PERSONAGENS PRINCIPAIS: " << serie->getMainCharacters() << endl;
        cout << "- CANAL/STREAMING: " << serie->getNetwork() << endl;
        cout << "- NOTA (1-10): " << serie->getRating() << endl;
        cout << "\n\n";
    }
    else {
        cout << "Serie nao encontrada.\n" << endl;
    }
}

void editarSerie(PersistenciaBanco& persistencia) {
    int internal_id;
    cout << "\n\n --------------------------------------------------------------------" << endl;
    cout << "|                           EDITAR SERIE                             |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "Digite o ID da Serie: ";
    cin >> internal_id;

    Serie* serie = persistencia.carregarSerie(internal_id);
    if (serie) {
        int campo;
        cout << "  (1) NOME DA SERIE (ATUAL: " << serie->getSeriesName() << ")" << endl;
        cout << "  (2) ANO DE LANCAMENTO (ATUAL: " << serie->getReleaseYear() << ")" << endl;
        cout << "  (3) TEMPORADA (ATUAL: " << serie->getSeason() << ")" << endl;
        cout << "  (4) NUMERO DE EPISODIOS (ATUAL: " << serie->getEpisodeCount() << ")" << endl;
        cout << "  (5) ATORES PRINCIPAIS (ATUAL: " << serie->getMainActors() << ")" << endl;
        cout << "  (6) PERSONAGENS PRINCIPAIS (ATUAL: " << serie->getMainCharacters() << ")" << endl;
        cout << "  (7) CANAL/STREAMING (ATUAL: " << serie->getNetwork() << ")" << endl;
        cout << "  (8) NOTA (ATUAL: " << serie->getRating() << ")" << endl;
        cout << "\nEscolha o campo para editar:  ";
        cin >> campo;

        cin.ignore(); 

        switch (campo) {
        case 1: {
            string series_name;
            cout << "NOVO NOME DA SERIE: ";
            getline(cin, series_name);
            serie->setSeriesName(series_name);
            break;
        }
        case 2: {
            int release_year;
            cout << "NOVO ANO DE LANCAMENTO: ";
            cin >> release_year;
            serie->setReleaseYear(release_year);
            break;
        }
        case 3: {
            int season;
            cout << "NOVA TEMPORADA: ";
            cin >> season;
            serie->setSeason(season);
            break;
        }
        case 4: {
            int episode_count;
            cout << "NOVO NUMERO DE EPISODIOS: ";
            cin >> episode_count;
            serie->setEpisodeCount(episode_count);
            break;
        }
        case 5: {
            string main_actors;
            cout << "NOVOS ATORES PRINCIPAIS: ";
            getline(cin, main_actors);
            serie->setMainActors(main_actors);
            break;
        }
        case 6: {
            string main_characters;
            cout << "NOVOS PERSONAGENS PRINCIPAIS: ";
            getline(cin, main_characters);
            serie->setMainCharacters(main_characters);
            break;
        }
        case 7: {
            string network;
            cout << "NOVO CANAL/STREAMING: ";
            getline(cin, network);
            serie->setNetwork(network);
            break;
        }
        case 8: {
            int rating;
            cout << "NOVA NOTA: ";
            cin >> rating;
            serie->setRating(rating);
            break;
        }
        default:
            cout << "OPÇÃO INVÁLIDA!" << endl;
            return;
        }

        persistencia.atualizarSerie(*serie);
        cout << "\nSerie atualizada!! " << endl;
    }
    else {
        cout << "Serie nao encontrada :(" << endl;
    }
}

void excluirSerie(SerieDAO& persistencia) {
    int internal_id;
    cout << "\n\n --------------------------------------------------------------------" << endl;
    cout << "|                           EXCLUIR SERIE                            |" << endl;
    cout << " --------------------------------------------------------------------" << endl;
    cout << "Digite o ID da serie: ";
    cin >> internal_id;
    persistencia.removerSerie(internal_id);
    cout << "\nSerie excluida!! " << endl;
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
        cout << "Opção invalida!" << endl;
        return;
    }

    cout << " --------------------------------------------------------------------" << endl;
    cout << "|                        CATALOGO DE SERIES                          |" << endl;
    cout << " --------------------------------------------------------------------" << endl;

    for (const auto& serie : series) {
        cout << "ID: " << serie.getInternalId() << endl;
        cout << "-------------" << endl;
        cout << "Nome: " << serie.getSeriesName() << endl;
        cout << "Ano: " << serie.getReleaseYear() << endl;
        cout << "Temporada: " << serie.getSeason() << endl;
        cout << "Episodios: " << serie.getEpisodeCount() << endl;
        cout << "Canal / Streaming: " << serie.getNetwork() << endl;
        cout << "Nota: " << serie.getRating() << endl;
        cout << "\n\n";
    }

    cout << "\n\n" << endl;
}

int main() {
    string host = "127.0.0.1:3306";
    string user = "root";
    string pass = "admin";
    string db = "catalogo";

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
            subOpcao = tolower(subOpcao);
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
            cout << "Creditos: Desenvolvido por Heloisa, Camila, Geovanne, Thalita e Gabriela." << endl;
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
