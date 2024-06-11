#include "PathManager.hpp"

PathManager::PathManager(std::string nameOfCache){

    char* pathToHome = std::getenv("HOME");
    if (pathToHome==NULL){
        pathToHome = std::getenv("HOMEPATH");
    }
    if (pathToHome==NULL){
        m_isValid = false;
        m_numberOfGameCounter = 0;
        m_pathToCacheRoot = "";
        return;
    }
    m_pathToCacheRoot =  std::string(pathToHome) + "/" + nameOfCache;

    if (std::filesystem::exists(m_pathToCacheRoot)){
        if (std::filesystem::exists(m_pathToCacheRoot + "/.chess")){
            m_isValid = true;
            m_numberOfGameCounter = 0;
            this->getNextValidGameIndice();
        }
        else{
            m_isValid = false;
        }
    }
    else{
        m_isValid = std::filesystem::create_directories(m_pathToCacheRoot);
        if (m_isValid){
            std::filesystem::create_directory(m_pathToCacheRoot + "/.chess");
            std::filesystem::create_directories(this->getPathToGamesFolder());
            m_numberOfGameCounter = 0;
        }
    }
}

std::string PathManager::getPathToGamesFolder() const{
    return m_pathToCacheRoot + "/Games";
}

bool PathManager::isValid() const{
    return m_isValid;
}

void PathManager::getNextValidGameIndice(){
    while(std::filesystem::exists(this->getPathToGamesFolder() + "/Game_" + std::to_string(m_numberOfGameCounter))){
        m_numberOfGameCounter += 1;
    }
}

std::string PathManager::getNextValidGameFolder(){
    std::string res = this->getPathToGamesFolder() + "/Game_" + std::to_string(m_numberOfGameCounter);
    std::filesystem::create_directories(res);
    this->getNextValidGameIndice();
    return res;
}