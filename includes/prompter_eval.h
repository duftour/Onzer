#include "player.h"
#include <map>

class PrompterEval
{
public:
    PrompterEval() = default;
    ~PrompterEval() = default;
    void evaluatePrompt(Player& _player) const;
    void splitPrompt(const std::string& _str, char _delimiter);

private:
    std::vector<std::string> splited;
};
