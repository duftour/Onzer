#include "playlist.h"
#include <algorithm>
#include <iostream>

void Playlist::addMusic(const Music& _music)
{
    if (std::find(playlist.begin(), playlist.end(), _music.geTitle()) == playlist.end())
    {
        std::cout << "Add music : " << _music.geTitle() << " to playlist : " << playlist_name
                  << std::endl;
        playlist.push_back(_music);
    }
    else
        std::cout << "Music : " << _music.geTitle() << " already in playlist : " << playlist_name
                  << std::endl;
}

void Playlist::deleteMusic(std::string _title)
{
    std::vector<Music>::iterator it;

    it = std::find(playlist.begin(), playlist.end(), _title);
    if (it == playlist.end())
        std::cout << "Music : " << _title << " not found in playlist : " << playlist_name
                  << std::endl;
    else
    {
        playlist.erase(it);
        std::cout << "Deleting : " << _title << " from playlist : " << playlist_name << std::endl;
    }
}

void Playlist::setPlaylistName(const std::string& _name)
{
    playlist_name = _name;
}

void Playlist::setPlaylist(std::vector<Music> _playlist)
{
    playlist = _playlist;
}

const std::string& Playlist::getPlaylistName() const
{
    return playlist_name;
}

const std::vector<Music>& Playlist::getPlaylist() const
{
    return playlist;
}

bool Playlist::operator==(std::string const& _name) const
{
    return this->playlist_name == _name;
}
