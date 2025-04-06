#include "http_cache.hpp"

#include <filesystem>
#include <fstream>

HttpCache::HttpCache(std::string cache_directory_path)
{
    this->cache_directory_path = cache_directory_path;
    this->SetupCache();
}

void HttpCache::SetupCache()
{
    if (this->CacheExists())
    {
        this->using_cache = this->CanUseCache();
    }
    else
    {
        this->CreateCache();
        this->using_cache = true;
    }
}

bool HttpCache::CacheExists() const
{
    return std::filesystem::exists(this->cache_directory_path);
}

void HttpCache::CreateCache() const
{
    std::filesystem::create_directory(this->cache_directory_path);
}

bool HttpCache::CanUseCache() const
{
    return std::filesystem::is_directory(this->cache_directory_path);
}

std::string HttpCache::GetCacheFilePathForLevel(int level) const
{
    return this->cache_directory_path + "/" + std::to_string(level) + ".txt";
}

bool HttpCache::HasLevelInCache(int level) const
{
    std::fstream fs(this->GetCacheFilePathForLevel(level), std::ios_base::in);
    return (fs.fail() == false);
}

std::string HttpCache::ReadPuzzleDataFromCache(int level) const
{
    std::ifstream in(this->GetCacheFilePathForLevel(level), std::ios_base::in);
    std::string result;
    std::getline(in, result);
    return result;
}

void HttpCache::WritePuzzleDataToCache(int level, std::string puzzle_data) const
{
    std::ofstream fs(this->GetCacheFilePathForLevel(level), std::ios_base::out);
    if (!fs.fail())
        fs << puzzle_data;
}