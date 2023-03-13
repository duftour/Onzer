#include "music.h"
#include "playlist.h"
#include <chrono>

class Display
{
public:
    Display() = default;
    ~Display() = default;

    void displayNowPlaying(const Music& _music, const std::chrono::duration<int>& _elapsed_time);
    void displayPlayingPlaylist(const Playlist& _playlist) const;
    void displayPlaylistList(const std::vector<Playlist>& _playlist_list) const;
    void displayHelp() const;
    std::string recordBar(const int _total_time, const int _elapsed_time);

private:
};
