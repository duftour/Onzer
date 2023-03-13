#include "music.h"

void Music::setTitle(const std::string& _title)
{
    title = _title;
}

void Music::setArtist(const std::string& _artist)
{
    artist = _artist;
}

void Music::setAlbum(const std::string& _album)
{
    album = _album;
}

void Music::setDuration(const std::chrono::duration<int>& _duration)
{
    duration = _duration;
}

const std::string& Music::geTitle() const
{
    return title;
}

const std::string& Music::getArtist() const
{
    return artist;
}

const std::string& Music::getAlbum() const
{
    return album;
}

const std::chrono::duration<int>& Music::getDuration() const
{
    return duration;
}

bool Music::operator==(std::string const& _title) const
{
    return this->title == _title;
}

void Music::clear()
{
    title = "";
    artist = "";
    album = "";
    duration = std::chrono::duration<int>(0);
}
