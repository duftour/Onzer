#include "parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>

void Parser::readJsonFile(const char* _file_path)
{
    std::ifstream inFile;
    inFile.open(_file_path); // open the input file
    if (!inFile.is_open())
    {
        std::cout << "Opening file " << _file_path << " failed." << std::endl;
        exit(1);
    }
    std::stringstream _file_content;
    _file_content << inFile.rdbuf();       // read the file
    std::string str = _file_content.str(); // str holds the content of the file

    file_content = str.c_str();
    recoverMusic();
    inFile.close();
}

bool Parser::ignoreField(const rapidjson::Value& _songs_array, int _index)
{
    if (!_songs_array[_index].HasMember("title") || !_songs_array[_index].HasMember("album")
        || !_songs_array[_index].HasMember("artist") || !_songs_array[_index].HasMember("duration"))
    {
        std::cout << "Missing field at index : " << _index << "." << std::endl;
        std::cout << "Ignoring music." << std::endl;
        return false;
    }
    if (strcmp(_songs_array[_index]["title"].GetString(), "") == 0)
    {
        std::cout << "Music tittle at index: " << _index << " is empty." << std::endl;
        std::cout << "Ignoring music." << std::endl;
        return false;
    }
    if (strcmp(_songs_array[_index]["album"].GetString(), "") == 0)
    {
        std::cout << "Album tittle at index: " << _index << " is empty." << std::endl;
        std::cout << "Ignoring music." << std::endl;
        return false;
    }
    if (strcmp(_songs_array[_index]["artist"].GetString(), "") == 0)
    {
        std::cout << "Artist tittle at index: " << _index << " is empty." << std::endl;
        std::cout << "Ignoring music." << std::endl;
        return false;
    }
    if (_songs_array[_index]["duration"].GetInt() <= 0)
    {
        std::cout << "Music duration at index; " << _index << " can't be 0 or lower." << std::endl;
        std::cout << "Ignoring music." << std::endl;
        return false;
    }
    return true;
}

void Parser::recoverMusic()
{
    rapidjson::Document document;
    std::vector<Music> tmp_playlist;
    Music tmp;
    rapidjson::ParseResult parse_error_handler = document.Parse(file_content);

    if (!parse_error_handler)
    {
        std::cout << "JSON parse error: " << GetParseError_En(parse_error_handler.Code())
                  << " at : " << parse_error_handler.Offset() << std::endl;
        exit(1);
    }
    if (!document.HasMember("songs"))
    {
        std::cout << "Invalid Json file." << std::endl;
        exit(1);
    }

    const rapidjson::Value& songs_array = document["songs"];
    assert(songs_array.IsArray());
    for (rapidjson::SizeType i = 0; i < songs_array.Size(); i++)
    {
        if (ignoreField(songs_array, i))
        {
            tmp.setTitle(songs_array[i]["title"].GetString());
            tmp.setAlbum(songs_array[i]["album"].GetString());
            tmp.setArtist(songs_array[i]["artist"].GetString());
            tmp.setDuration(std::chrono::seconds(songs_array[i]["duration"].GetInt()));
            tmp_playlist.push_back(tmp);
        }
    }
    if (tmp_playlist.empty())
    {
        std::cout << "No music find in json. Exit." << std::endl;
        exit(1);
    }
    music_database.setPlaylist(tmp_playlist);
    music_database.setPlaylistName("Default_playlist");
}

const Playlist& Parser::getRecoveredPlaylist() const
{
    return music_database;
}
