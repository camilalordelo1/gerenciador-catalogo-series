#include "Serie.h"

Serie::Serie(int internal_id, const string& series_name, int release_year, int season, int episode_count,
    const string& main_actors, const string& main_characters, const string& network, int rating)
    : internal_id(internal_id), series_name(series_name), release_year(release_year), season(season),
    episode_count(episode_count), main_actors(main_actors), main_characters(main_characters), network(network), rating(rating) {}

int Serie::getInternalId() const {
    return internal_id;
}

string Serie::getSeriesName() const {
    return series_name;
}

int Serie::getReleaseYear() const {
    return release_year;
}

int Serie::getSeason() const {
    return season;
}

int Serie::getEpisodeCount() const {
    return episode_count;
}

string Serie::getMainActors() const {
    return main_actors;
}

string Serie::getMainCharacters() const {
    return main_characters;
}

string Serie::getNetwork() const {
    return network;
}

int Serie::getRating() const {
    return rating;
}

void Serie::setSeriesName(const string& series_name) {
    this->series_name = series_name;
}

void Serie::setReleaseYear(int release_year) {
    this->release_year = release_year;
}

void Serie::setSeason(int season) {
    this->season = season;
}

void Serie::setEpisodeCount(int episode_count) {
    this->episode_count = episode_count;
}

void Serie::setMainActors(const string& main_actors) {
    this->main_actors = main_actors;
}

void Serie::setMainCharacters(const string& main_characters) {
    this->main_characters = main_characters;
}

void Serie::setNetwork(const string& network) {
    this->network = network;
}

void Serie::setRating(int rating) {
    this->rating = rating;
}
