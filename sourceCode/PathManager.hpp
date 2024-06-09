#ifndef PATHMANAGER
#define PATHMANAGER

#include <filesystem>
#include <string>

class PathManager{
    private:
        std::string m_pathToCacheRoot;
        bool m_isValid;
        int m_numberOfGameCounter;

        void getNextValidGameIndice();

    public:
        PathManager(std::string pathToCacheRoot);

        std::string getPathToGamesFolder() const;
        std::string getNextValidGameFolder();
        bool isValid() const;
};

extern PathManager globalPathManager;

#endif