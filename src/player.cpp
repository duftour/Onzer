#include "player.h"
#include <algorithm>
#include <iostream>
#include <random>

Player::Player(const char* file_path)
  : selected_playlist(default_playlist)
{
    config_parser.readJsonFile(file_path);
    playing_status = playingStatus::UNKNOWN;
    selected_playlist = config_parser.getRecoveredPlaylist();
    now_playing = selected_playlist.getPlaylist().begin();
    elapsed_time = std::chrono::duration<int>(0);
    repeat = false;
    random_read = false;
}

void Player::run()
{
    if (playing_status == playingStatus::UNKNOWN || playing_status == playingStatus::PAUSE)
    {
        start_time = std::chrono::system_clock::now() - elapsed_time;
    }
    else if (playing_status == playingStatus::PLAY)
    {
        elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(
          std::chrono::system_clock::now() - start_time);
    }
    if (elapsed_time > now_playing->getDuration() && playing_status == playingStatus::PLAY)
    {
        if (repeat)
        {
            resetTimer();
        }
        else
        {
            nextSong();
        }
    }
}

void Player::createPlaylist(const std::string& _name)
{
    std::vector<Playlist>::iterator it = findPlaylist(_name);
    if (it == playlist_list.end())
    {
        Playlist _playlist;
        _playlist.setPlaylistName(_name);
        playlist_list.push_back(_playlist);
        std::cout << "Create " << _name << " playlist" << std::endl;
    }
    else
    {

        std::cout << "Playlist " << _name << " already exist." << std::endl;
    }
}

void Player::deletePlaylist(const std::string& _name)
{
    std::vector<Playlist>::iterator it = findPlaylist(_name);
    if (it == playlist_list.end())
    {
        std::cout << "Can't find " << _name << " in created Playlist" << std::endl;
    }
    else
    {
        std::cout << "Deleting " << _name << " in created Playlist" << std::endl;
        playlist_list.erase(it);
    }

    // If there is no more playlist we play the database
    if (playlist_list.empty())
    {
        selected_playlist = config_parser.getRecoveredPlaylist();
        now_playing = config_parser.getRecoveredPlaylist().getPlaylist().begin();
        resetTimer();
    }
}

void Player::setPlayingPlaylist(const std::string& _name)
{
    std::vector<Playlist>::iterator it = findPlaylist(_name);
    if (it == playlist_list.end())
    {
        std::cout << "Can't find " << _name << " in created Playlist" << std::endl;
    }
    else if (it->getPlaylist().empty())
    {
        std::cout << "Can't play " << _name << " in created Playlist, playlist is empty."
                  << std::endl;
    }
    else
    {
        std::cout << "Now playing playlist : " << _name << std::endl;
        selected_playlist = *it;
        now_playing = selected_playlist.getPlaylist().begin();
        resetTimer();
    }
}

void Player::setPlayStatus()
{
    if (playing_status == playingStatus::UNKNOWN)
    {
        resetTimer();
    }
    playing_status = playingStatus::PLAY;
}

void Player::setPauseStatus()
{
    playing_status = playingStatus::PAUSE;
}

void Player::nextSong()
{
    // if we reach the end of the playlist we start at the begining.
    if (now_playing + 1 != selected_playlist.getPlaylist().end())
        now_playing++;
    else
        now_playing = selected_playlist.getPlaylist().begin();

    resetTimer();
}

void Player::previousSong()
{
    // if we are above 5 seconds previous just restart the current song.
    if (elapsed_time <= std::chrono::duration<int>(5)
        && now_playing != selected_playlist.getPlaylist().begin())
    {
        now_playing--;
        resetTimer();
    }
    else
    {
        resetTimer();
    }
}

std::vector<Music>::const_iterator Player::findMusic(const Playlist& _playlist,
                                                     const std::string& _music)
{
    std::vector<Music>::const_iterator it;
    it = std::find(_playlist.getPlaylist().begin(), _playlist.getPlaylist().end(), _music);

    return it;
}

std::vector<Playlist>::iterator Player::findPlaylist(const std::string& _playlist_name)
{
    std::vector<Playlist>::iterator it;
    it = std::find(playlist_list.begin(), playlist_list.end(), _playlist_name);

    return it;
}

void Player::addMusicToPlaylist(const std::string& _name, const std::string& _playlist)
{

    std::vector<Music>::const_iterator it
      = findMusic(config_parser.getRecoveredPlaylist(), _name); // search database
    if (it == config_parser.getRecoveredPlaylist().getPlaylist().end())
    {
        std::cout << "Can't find music : " << _name << " in database" << std::endl;
    }
    else
    {
        std::vector<Playlist>::iterator it_playlist;
        it_playlist = findPlaylist(_playlist); // search playlist existantes
        if (it_playlist == playlist_list.end())
        {
            std::cout << "Can't find playlist : " << _playlist << " in playlist list" << std::endl;
        }
        else
        {
            it_playlist->addMusic(*it);
        }
    }
}

void Player::deleteMusicToPlaylist(const std::string& _name, const std::string& _playlist)
{

    std::vector<Playlist>::iterator it = findPlaylist(_playlist);
    if (it == playlist_list.end())
    {
        std::cout << "Can't find playlist : " << _playlist << " in playlist list" << std::endl;
    }
    else
    {
        it->deleteMusic(_name);
        if (it->getPlaylist().empty())
            selected_playlist = default_playlist;
        else
            selected_playlist = *it;
    }
}

void Player::displayNowPlaying()
{
    displayer.displayNowPlaying(*now_playing, elapsed_time);
}

void Player::displayNowPlayingPlaylist()
{
    displayer.displayPlayingPlaylist(selected_playlist);
}

void Player::displayPlaylistList()
{
    displayer.displayPlaylistList(playlist_list);
}

void Player::displayHelp()
{
    displayer.displayHelp();
}

void Player::resetTimer()
{
    start_time = std::chrono::system_clock::now();
    elapsed_time = std::chrono::duration<int>(0);
}

void Player::updateRepeat()
{
    if (repeat)
        std::cout << "Disable repeat." << std::endl;
    else
        std::cout << "Enable repeat." << std::endl;
    repeat = !repeat;
}

void Player::shufflePlaylist()
{
    random_read = !random_read;
    if (random_read)
    {
        auto rng = std::default_random_engine{};
        std::vector<Music> music_list;

        music_list = selected_playlist.getPlaylist();

        std::shuffle(std::begin(music_list), std::end(music_list), rng);

        shuffle_playlist.setPlaylist(music_list);
        shuffle_playlist.setPlaylistName(selected_playlist.getPlaylistName());
        selected_playlist = shuffle_playlist;

        playlist_name_save = selected_playlist.getPlaylistName();
        std::cout << "Now playing in random." << std::endl;
    }
    else
    {
        std::vector<Playlist>::iterator it = findPlaylist(playlist_name_save);
        if (it == playlist_list.end())
            selected_playlist = default_playlist;
        else
            setPlayingPlaylist(playlist_name_save);
        std::cout << "Disable random mode." << std::endl;
    }
}
