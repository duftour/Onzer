#pragma once
#include "music.h"

#include <vector>

class Playlist
{
public:
    Playlist() = default;
    ~Playlist() = default;

    const std::string& getPlaylistName() const;
    const std::vector<Music>& getPlaylist() const;
    void setPlaylistName(const std::string& _name);
    void setPlaylist(std::vector<Music> _playlist);
    void addMusic(const Music& _music);
    void deleteMusic(std::string _title);
    bool operator==(std::string const& _name) const;

private:
    std::string playlist_name;
    std::vector<Music> playlist;
};
