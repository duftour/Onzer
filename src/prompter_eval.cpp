#include "prompter_eval.h"
#include <iostream>
#include <ostream>
#include <sstream>

void PrompterEval::splitPrompt(const std::string& _str, char _delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(_str);
    std::string item;

    while (getline(ss, item, _delimiter))
    {
        if (item.starts_with(" "))
            item.erase(0, 1);
        if (item.ends_with(" "))
            item.erase(item.size() - 1);
        if (item != "")
            result.push_back(item);
    }
    splited = result;
}

void PrompterEval::evaluatePrompt(Player& _player) const
{
    if (splited[0] == "play")
    {
        _player.setPlayStatus();
    }
    else if (splited[0] == "pause")
    {
        _player.setPauseStatus();
    }
    else if (splited[0] == "exit")
    {
        exit(0);
    }
    else if (splited[0] == "next")
    {
        _player.nextSong();
    }
    else if (splited[0] == "previous")
    {
        _player.previousSong();
    }
    else if (splited[0] == "np")
    {
        _player.displayNowPlaying();
    }
    else if (splited[0] == "np_playlist")
    {
        _player.displayNowPlayingPlaylist();
    }
    else if (splited[0] == "playlist_list")
    {
        _player.displayPlaylistList();
    }
    else if (splited[0] == "repeat")
    {
        _player.updateRepeat();
    }
    else if (splited[0] == "random")
    {
        _player.shufflePlaylist();
    }
    else if (splited[0] == "help")
    {
        _player.displayHelp();
    }
    else if (splited[0] == "create_playlist")
    {
        if (splited.size() <= 1)
        {
            std::cout << "Please specify a playlist name." << std::endl;
        }
        else
        {
            _player.createPlaylist(splited[1]);
        }
    }
    else if (splited[0] == "delete_playlist")
    {
        if (splited.size() <= 1)
        {
            std::cout << "Please specify a playlist name." << std::endl;
        }
        else
        {
            _player.deletePlaylist(splited[1]);
        }
    }
    else if (splited[0] == "play_playlist")
    {
        if (splited.size() <= 1)
        {
            std::cout << "Please specify a playlist name." << std::endl;
        }
        else
        {
            _player.setPlayingPlaylist(splited[1]);
        }
    }
    else if (splited[0] == "add")
    {
        if (splited.size() <= 1)
        {
            std::cout << "Please specify a playlist name." << std::endl;
        }
        else if (splited.size() <= 2)
        {
            std::cout << "Please enter a music name" << std::endl;
        }
        else
        {
            _player.addMusicToPlaylist(splited[1], splited[2]);
        }
    }
    else if (splited[0] == "delete")
    {
        if (splited.size() <= 1)
        {
            std::cout << "Please specify a playlist name." << std::endl;
        }
        else if (splited.size() <= 2)
        {
            std::cout << "Please enter a music name" << std::endl;
        }
        else
        {
            _player.deleteMusicToPlaylist(splited[1], splited[2]);
        }
    }
    else
    {
        std::cout << "Unrecognize command : " << splited[0] << std::endl;
    }
}
