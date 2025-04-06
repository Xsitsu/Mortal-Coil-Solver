#ifndef HTTP_CACHE_HPP_INCLUDE
#define HTTP_CACHE_HPP_INCLUDE

#include <string>

class HttpCache
{
public:
    HttpCache(std::string cache_directory_path);

    bool HasLevelInCache(int level) const;
    std::string ReadPuzzleDataFromCache(int level) const;
    void WritePuzzleDataToCache(int level, std::string puzzle_data) const;

private:
    std::string cache_directory_path;
    bool using_cache;

private:
    void SetupCache();
    bool CacheExists() const;
    void CreateCache() const;
    bool CanUseCache() const;
    std::string GetCacheFilePathForLevel(int level) const;
};

#endif // HTTP_CACHE_HPP_INCLUDE