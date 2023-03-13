#include "display.h"
#include <iostream>
#include <sstream>

std::string Display::recordBar(const int _total_time, const int _elapsed_time)
{
    std::string str;
    std::stringstream ss;

    const int ratio = (100 * _elapsed_time) / _total_time;
    for (int i = 0; i < 50; i++)
    {

        if (i == ratio / 2)
            ss << "o";
        else
            ss << "-";
    }
    str = ss.str();
    return str;
}

void Display::displayNowPlaying(const Music& _music,
                                const std::chrono::duration<int>& _elapsed_time)
{
    std::stringstream ss;
    auto minutes_elapsed = std::chrono::duration_cast<std::chrono::minutes>(_elapsed_time);
    auto seconds_elapsed
      = std::chrono::duration_cast<std::chrono::seconds>(_elapsed_time - minutes_elapsed);

    auto minutes_total = std::chrono::duration_cast<std::chrono::minutes>(_music.getDuration());
    auto seconds_total
      = std::chrono::duration_cast<std::chrono::seconds>(_music.getDuration() - minutes_total);

    ss << "Now playing : " << _music.geTitle() << " by : " << _music.getArtist() << std::endl;

    if (seconds_elapsed < std::chrono::duration<int>(10))
    {
        ss << minutes_elapsed.count() << ":0" << seconds_elapsed.count() << " ";
        ss << recordBar(_music.getDuration().count(), _elapsed_time.count());
        ss << " " << minutes_total.count();
        if (seconds_total < std::chrono::duration<int>(10))
            ss << ":0" << seconds_total.count() << std::endl;
        else
            ss << ":" << seconds_total.count() << std::endl;
    }
    else
    {
        ss << minutes_elapsed.count() << ":" << seconds_elapsed.count() << " ";
        ss << recordBar(_music.getDuration().count(), _elapsed_time.count());
        ss << " " << minutes_total.count();

        if (seconds_total < std::chrono::duration<int>(10))
            ss << ":0" << seconds_total.count() << std::endl;
        else
            ss << ":" << seconds_total.count() << std::endl;
    }
    std::cout << ss.str();
}

void Display::displayPlayingPlaylist(const Playlist& _playlist) const
{
    std::cout << "Now playing playlist : " << _playlist.getPlaylistName() << std::endl;
    int song_order = 1;
    for (const auto& p : _playlist.getPlaylist())
    {
        std::cout << song_order << " : " << p.geTitle() << " by " << p.getArtist() << " ("
                  << p.getAlbum() << ")" << std::endl;
        song_order++;
    }
}

void Display::displayPlaylistList(const std::vector<Playlist>& _playlist_list) const
{
    std::cout << "Playlist list:" << std::endl;
    for (const auto& p : _playlist_list)
    {
        std::cout << p.getPlaylistName() << std::endl;
    }
}

void Display::displayHelp() const
{
    std::stringstream ss;
    ss << "Onzer manual:" << std::endl;
    ss << "  Usage: ./Onzer {json file path}" << std::endl;
    ss << "  Commands:" << std::endl;
    ss << "     play: Start playing music" << std::endl;
    ss << "     np: Show now playing song" << std::endl;
    ss << "     pause: Pause song" << std::endl;
    ss << "     next: Start playing next song" << std::endl;
    ss << "     repeat: Play music in repeat" << std::endl;
    ss << "     random: Play music in random" << std::endl;
    ss << "     previous: Start playing previous song (If you are above 5s of listening resume to "
          "the beginning "
       << std::endl;
    ss << "     create_playlist \"playlist name\": Create a playlist" << std::endl;
    ss << "     delete_playlist \"playlist name\": Delete playlist" << std::endl;
    ss << "     play_playlist \"playlist name\": Start playing playlist" << std::endl;
    ss << "     add \"music name\" \"playlist name\": Add music to playlist" << std::endl;
    ss << "     delete \"music name\" \"playlist name\": Delete music from playlist" << std::endl;
    ss << "     np_playlist: Show currently playing playlist" << std::endl;
    ss << "     playlist_list: Show playlist list" << std::endl << std::endl;
    ss << "HINT: Don't forget to use \"\" for multiple arguments." << std::endl;
    std::cout << ss.str();
}
