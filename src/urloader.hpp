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

        bool IsUrlAccessible(std::string& url_of_file);
        bool GetManifestByUrl(std::string& url_of_file, std::string& buffer);
        bool GetFileByUrl(std::string& url_of_file, std::string& s_buffer);

        CURLcode curl_res;


    private:
        std::vector<char> FillUrlfromString(std::string& url_of_file);
        static size_t WriteToRAMCallback(char *current_chunk_of_data, size_t multiplier_size,
                                         size_t chunk_size, std::string* big_storage);

        CURL *curl_handle;

    };
}
#endif // URLOADER_HPP
