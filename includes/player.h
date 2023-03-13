#include "display.h"
#include "parser.h"
#include "playlist.h"
#include <memory>

enum playingStatus
{
    UNKNOWN = -1,
    PLAY,
    PAUSE
};

class Player
{
public:
    Player(const char* file_path);
    ~Player() = default;

    void run();
    void resetTimer();
    void updateRepeat();
    void createPlaylist(const std::string& _name);
    void deletePlaylist(const std::string& _name);
    void setPlayStatus();
    void setPauseStatus();
    void nextSong();
    void shufflePlaylist();
    void previousSong();
    void displayNowPlaying();
    void displayNowPlayingPlaylist();
    void displayPlaylistList();
    void displayHelp();
    void setPlayingPlaylist(const std::string& _name);
    void addMusicToPlaylist(const std::string& _name, const std::string& _playlist);
    void deleteMusicToPlaylist(const std::string& _name, const std::string& _playlist);
    std::vector<Music>::const_iterator findMusic(const Playlist& _playlist,
                                                 const std::string& _music);
    std::vector<Playlist>::iterator findPlaylist(const std::string& _playlist_name);

private:
    Playlist default_playlist;
    Playlist& selected_playlist;
    Playlist shuffle_playlist;
    std::vector<Music>::const_iterator now_playing;
    std::vector<Playlist> playlist_list;
    Parser config_parser;
    playingStatus playing_status;
    std::chrono::system_clock::time_point start_time;
    std::chrono::duration<int> elapsed_time;
    Display displayer;
    bool repeat;
    bool random_read;
    std::string playlist_name_save;
};
