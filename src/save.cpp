#include "../includes/include.h"

int load_best_score()
{
    std::string appData = getenv("APPDATA");
    std::string folderPath = appData + "\\snake only on cpp";
    std::string filePath = folderPath + "\\best_score.txt";

    CreateDirectory(folderPath.c_str(), NULL);

    int best_score = 0;
    std::ifstream input_file(filePath, std::ios::in | std::ios::binary);
    if (input_file.is_open())
    {
        input_file.read(reinterpret_cast<char *>(&best_score), sizeof(best_score));
        input_file.close();
    }
    return best_score;
}

void save_best_score(int best_score)
{
    std::string appData = getenv("APPDATA");
    std::string folderPath = appData + "\\snake only on cpp";
    std::string filePath = folderPath + "\\best_score.txt";

    CreateDirectory(folderPath.c_str(), NULL);

    std::ofstream output_file(filePath, std::ios::out | std::ios::binary);
    if (output_file.is_open())
    {
        output_file.write(reinterpret_cast<char *>(&best_score), sizeof(best_score));
        output_file.close();
    }
}