#ifndef SERIE_H
#define SERIE_H

#include <string>

using namespace std;

class Serie {
private:
    int internal_id;
    string series_name;
    int release_year;
    int season;
    int episode_count;
    string main_actors;
    string main_characters;
    string network;
    int rating;

public:
    Serie() = default;

    Serie(int internal_id, const string& series_name, int release_year, int season, int episode_count,
        const string& main_actors, const string& main_characters, const string& network, int rating);

    int getInternalId() const;
    string getSeriesName() const;
    int getReleaseYear() const;
    int getSeason() const;
    int getEpisodeCount() const;
    string getMainActors() const;
    string getMainCharacters() const;
    string getNetwork() const;
    int getRating() const;

    void setSeriesName(const string& series_name);
    void setReleaseYear(int release_year);
    void setSeason(int season);
    void setEpisodeCount(int episode_count);
    void setMainActors(const string& main_actors);
    void setMainCharacters(const string& main_characters);
    void setNetwork(const string& network);
    void setRating(int rating);
};

#endif // SERIE_H
