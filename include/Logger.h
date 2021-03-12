
#include <string>

class Logger
{
public:
    Logger(std::string path);

    void log(std::string message);

private:
    std::string path;
};
