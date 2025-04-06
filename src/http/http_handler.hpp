#ifndef HTTP_HANDLER_HPP_INCLUDE
#define HTTP_HANDLER_HPP_INCLUDE

#include <string>

#include "http/http_cache.hpp"

class HttpHandler
{
public:
    HttpHandler(std::string username, std::string password, std::string cache_directory_path);

    std::string GetPuzzleData(int level) const;
    void PostPuzzleSolution() const;

private:
    std::string base_url;
    HttpCache cache;

private:
    std::string ConstructBaseUrl(std::string username, std::string password);

    std::string GetWebsiteData(int level) const;
    std::string ExtractPuzzleData(std::string website_data, int level) const;

    // Necessary because of how CURL works.
    static size_t curl_write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
};

#endif // HTTP_HANDLER_HPP_INCLUDE