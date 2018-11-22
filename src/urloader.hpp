#ifndef URLOADER_HPP
#define URLOADER_HPP

#include <curl/curl.h>
#include <string>
#include <vector>

namespace urloader
{
    class Urloader
    {
    public:
        Urloader();
        ~Urloader();

        bool GetFileByUrl(std::string& url_of_file, std::string& s_buffer);
        bool IsUrlAccessible(std::string& url_of_file);

        CURLcode curl_res;


    private:
        std::vector<char> FillUrlfromString(std::string& url_of_file);
        static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *data);

        CURL *curl_handle;

    };
}
#endif // URLOADER_HPP
