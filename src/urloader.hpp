#ifndef URLOADER_HPP
#define URLOADER_HPP

#include <curl/curl.h>
#include <string>
#include <vector>
#include <fstream>

namespace urloader
{
    class Urloader
    {
    public:
        Urloader();
        ~Urloader();

        bool IsUrlAccessible(const std::string& url_of_file);
        bool GetManifestByUrl(const std::string& url_of_file, std::vector<uint8_t>& buffer  );
        bool GetFileByUrl(const std::string& url_of_file, const std::string& path_to_file);

        CURLcode curl_res;


    private:
        std::vector<char> FillUrlfromString(const std::string& url_of_file);
        static size_t WriteToRAMCallback(char *current_chunk_of_data, size_t multiplier_size,
                                         size_t chunk_size, std::vector<uint8_t>* big_storage);
        static size_t WriteToFileCallback(char* current_chunk_of_data, size_t multiplier_size,
                                                    size_t chunk_size, std::fstream* big_file);

        CURL *curl_handler;

    };
}
#endif // URLOADER_HPP
