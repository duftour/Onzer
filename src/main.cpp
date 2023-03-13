#include "prompter_eval.h"
#include <chrono>
#include <future>
#include <iostream>

#include <string>

std::string GetLineFromCin()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int main(int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cout << "Please specifiy a music.json file." << std::endl
                  << "Usage: ./Onzer {file_path}." << std::endl;
        exit(1);
    }
    PrompterEval prompter_eval;
    Player player(argv[1]);
    auto future = std::async(std::launch::async, GetLineFromCin);

    std::cout << ">>>";
    while (true)
    {
        if (future.wait_for(std::chrono::milliseconds(1)) == std::future_status::ready)
        {

            auto prompt = future.get();

            future = std::async(std::launch::async, GetLineFromCin);
            if (prompt != "")
            {
                prompter_eval.splitPrompt(prompt, '\"');
                prompter_eval.evaluatePrompt(player);
            }

            std::cout << ">>>";
        }
        player.run();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
