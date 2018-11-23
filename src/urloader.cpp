#include "urloader.hpp"
//#include <fstream>

namespace urloader
{
    Urloader::Urloader(){
        /* init libcurl */
        curl_global_init(CURL_GLOBAL_ALL);
        /* init the curl session */
        curl_handler = curl_easy_init();
    }

    Urloader::~Urloader(){
    /* cleanup curl stuff */
        curl_easy_cleanup(curl_handler);
    /* we're done with libcurl, so clean it up */
        curl_global_cleanup();
    }
// -----------* Callbacks *----------------------------------------
    size_t Urloader::WriteToRAMCallback(char* current_chunk_of_data, size_t multiplier_size,
                                        size_t chunk_size, std::string* big_storage) {
        if(big_storage == NULL){
            return 0;
        }
        big_storage->append(current_chunk_of_data, (multiplier_size * chunk_size));
        return multiplier_size*chunk_size;
    }

    size_t Urloader::WriteToFileCallback(char* current_chunk_of_data, size_t multiplier_size,
                                        size_t chunk_size, std::fstream* big_storage) {
        if(big_storage == NULL){
            return 0;
        }
        big_storage->write(current_chunk_of_data, multiplier_size * chunk_size);
        //big_storage->append(current_chunk_of_data, (multiplier_size * chunk_size));
        return multiplier_size*chunk_size;
    }
// -----------* Helpers *------------------------------------------
    /* Convert std::string to char*. Create vector<char> c_url. And will use it as &c_url[0]*/
    std::vector<char> Urloader::FillUrlfromString(std::string& url_of_file){
        //std::vector<char> c_url;
        std::vector<char> c_url(url_of_file.begin(), url_of_file.end());
        //c_url = (url_of_file.begin(), url_of_file.end());
        c_url.push_back('\0');
        return c_url;
    }
// -----------* Main functions *------------------------------------
    /* Return True if remote resource exist and accessible */
    bool Urloader::IsUrlAccessible(std::string& url_of_file){
        std::vector<char> c_url = FillUrlfromString(url_of_file);
        curl_easy_setopt(curl_handler, CURLOPT_URL, &c_url[0]);
        /* Now specify the HEAD method */
        curl_easy_setopt(curl_handler, CURLOPT_NOBODY, 1L);
        /* Perform the request, res will get the return code */
        curl_res = curl_easy_perform(curl_handler);
        curl_easy_reset(curl_handler);
        /* Check for errors */
        if(curl_res != CURLE_OK){
            return false;
        }else{
            return true;
        }
    }

    /* Get string in RAM from URL; Input: HTTP URL of file; Output: file in buffer as a string */
    bool Urloader::GetManifestByUrl(std::string& url_of_file, std::string& buffer){

        std::vector<char> c_url = FillUrlfromString(url_of_file);

        /* specify URL to get */
        curl_easy_setopt(curl_handler, CURLOPT_URL, &c_url[0]);

        /* save data to this buffer */
        curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, &buffer);

        /* send all data to this function  */
        curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, Urloader::WriteToRAMCallback);

        /* some servers don't like requests that are made without a user-agent
             field, so we provide one */
        curl_easy_setopt(curl_handler, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        /* get it! */
        curl_res = curl_easy_perform(curl_handler);
        /* transmission done */
        curl_easy_reset(curl_handler);
        if(curl_res != CURLE_OK){
            return false;
        }else{
            return true;
        }
    }

    bool Urloader::GetFileByUrl(std::string& url_of_file, std::string& path_to_file){

        std::vector<char> c_url = FillUrlfromString(url_of_file);

        /* specify URL to get */
        curl_easy_setopt(curl_handler, CURLOPT_URL, &c_url[0]);

        std::fstream file_handler;
        file_handler.open(path_to_file, std::fstream::out       |
                                        std::fstream::binary    |
                                        std::fstream::trunc);

        curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, &file_handler);

        /* send all data to this function  */
        curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, Urloader::WriteToFileCallback);

        /* some servers don't like requests that are made without a user-agent
             field, so we provide one */
        curl_easy_setopt(curl_handler, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        curl_res = curl_easy_perform(curl_handler);
        file_handler.close();
        /* transmission done */
        curl_easy_reset(curl_handler);
        if(curl_res != CURLE_OK){
            return false;
        }else{
            return true;
        }
    }


}
