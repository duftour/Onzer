#include "music.h"
#include "playlist.h"
#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/error/en.h"
#include <vector>

class Parser
{
public:
    Parser(){};
    ~Parser(){};

    void recoverMusic();
    void readJsonFile(const char* _file_path);
    const Playlist& getRecoveredPlaylist() const;
    bool ignoreField(const rapidjson::Value& _songs_array, int _index);

private:
    Playlist music_database;
    const char* file_content;
};
