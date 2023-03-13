#pragma once

#include <chrono>
#include <string>

class Music
{
public:
    Music() = default;
    ~Music() = default;

    void setTitle(const std::string& _title);

    void setArtist(const std::string& _artist);

    void setAlbum(const std::string& _album);

    void setDuration(const std::chrono::duration<int>& _duration);

    const std::string& geTitle() const;

    const std::string& getArtist() const;

    const std::string& getAlbum() const;

    const std::chrono::duration<int>& getDuration() const;

    void clear();

    bool operator==(std::string const& _title) const;

private:
    //    int id;
    std::string title;
    std::string artist;
    std::string album;
    std::chrono::duration<int> duration;
};
