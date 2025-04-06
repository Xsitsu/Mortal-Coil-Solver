#include "http_handler.hpp"

#include <curl/curl.h>
#include <regex>
#include <format>
#include <filesystem>
#include <fstream>

#include <iostream>

HttpHandler::HttpHandler(std::string username, std::string password, std::string cache_directory_path) : cache(HttpCache(cache_directory_path))
{
    this->base_url = this->ConstructBaseUrl(username, password);
}

std::string HttpHandler::GetPuzzleData(int level) const
{
    if (this->cache.HasLevelInCache(level))
        return this->cache.ReadPuzzleDataFromCache(level);

    std::string website_data = this->GetWebsiteData(level);
    std::string puzzle_data = this->ExtractPuzzleData(website_data, level);

    if (puzzle_data == "")
    {
        std::cout <<  website_data << std::endl;
        throw "level not found :(";
    }

    std::string results = puzzle_data;
    this->cache.WritePuzzleDataToCache(level, puzzle_data);

    return results;
}

std::string HttpHandler::GetWebsiteData(int level) const
{
    CURL *curl = curl_easy_init();
    if (curl == nullptr)
        throw "Curl failed!";

    std::string readbuffer;

    std::string url = this->base_url + "&gotolevel=" + std::to_string(level) + "&go=Go+To+Level";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &(this->curl_write_callback));
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readbuffer);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
        throw curl_easy_strerror(res);

    curl_easy_cleanup(curl);

    return readbuffer;
}

std::string HttpHandler::ExtractPuzzleData(std::string website_data, int level) const
{
    std::string pattern = std::format("<script>var curLevel = {}.*;</script>", level);
    std::regex puzzle_pattern(pattern);
    std::smatch matches;
    std::regex_search(website_data, matches, puzzle_pattern);

    std::string results;
    for (auto match : matches)
    {
        results += match;
        results += "\n";
    }

    return results;
}

void HttpHandler::PostPuzzleSolution() const
{

}

std::string HttpHandler::ConstructBaseUrl(std::string username, std::string password)
{
    std::string base_url = "https://www.hacker.org/coil/index.php";
    std::string creds = "?name=" + username + "&password=" + password;
    std::string url = base_url + creds;
    return url;
}

size_t HttpHandler::curl_write_callback(char *contents, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    static_cast<std::string*>(userdata)->append(contents, realsize);
    return realsize;
}