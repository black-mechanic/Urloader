#include "urloader.hpp"
#include <fstream>
#include <curl/curl.h>

namespace urloader
{
    struct Urloader::Impl{
  /* Convert std::string to char*. Create vector<char> c_url. And will use it as &c_url[0]*/
        std::vector<char> FillUrlfromString(const std::string& url_of_file){
            std::vector<char> c_url(url_of_file.begin(), url_of_file.end());
            c_url.push_back('\0');
            return c_url;
        }
    // -----------* Callbacks *----------------------------------------
        static size_t WriteToRAMCallback(char* current_chunk_of_data, size_t multiplier_size,
                                            size_t chunk_size, std::vector<uint8_t>* big_storage) {
            int bytes_in_chunk = multiplier_size * chunk_size;
            if(big_storage == NULL){
                return 0;
            }
            for(int i = 0; i< bytes_in_chunk; i++){
                big_storage->push_back(current_chunk_of_data[i]);
            }
            return bytes_in_chunk;
        }

        static size_t WriteToFileCallback(char* current_chunk_of_data, size_t multiplier_size,
                                            size_t chunk_size, std::fstream* big_storage) {
            if(big_storage == NULL){
                return 0;
            }
            big_storage->write(current_chunk_of_data, multiplier_size * chunk_size);
            //big_storage->append(current_chunk_of_data, (multiplier_size * chunk_size));
            return multiplier_size*chunk_size;
        }

        CURL *curl_handler;
        CURLcode curl_res;
        uint32_t size_of_manifest;

    };


    Urloader::Urloader() : mImpl(new Impl){
        /* init libcurl */
        curl_global_init(CURL_GLOBAL_ALL);
        /* init the curl session */
        mImpl->curl_handler = curl_easy_init();
        mImpl->size_of_manifest = 0;
        progress_indicator.is_download_completed = true;
        progress_indicator.pProgressCallback = nullptr;
    }

    Urloader::~Urloader(){
    /* cleanup curl stuff */
        curl_easy_cleanup(mImpl->curl_handler);
    /* we're done with libcurl, so clean it up */
        curl_global_cleanup();
    }

    /* Return True if remote resource exist and accessible */
    bool Urloader::IsUrlAccessible(const std::string& url_of_file){
        std::vector<char> c_url = mImpl->FillUrlfromString(url_of_file);
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_URL, &c_url[0]);
        /* Now specify the HEAD method */
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_NOBODY, 1L);
        /* Perform the request, res will get the return code */
        mImpl->curl_res = curl_easy_perform(mImpl->curl_handler);
 // Get size of remote file
        curl_off_t content_length;
        mImpl->curl_res = curl_easy_getinfo(mImpl->curl_handler, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &content_length);
        if(content_length != 0){
            mImpl->size_of_manifest = static_cast<uint32_t>(content_length);
        }

        curl_easy_reset(mImpl->curl_handler);
        /* Check for errors */
        if(mImpl->curl_res != CURLE_OK){
            return false;
        }else{
            return true;
        }
    }

    /* Get string in RAM from URL; Input: HTTP URL of file; Output: file in buffer as a string */
    bool Urloader::GetManifestByUrl(const std::string& url_of_file,
                                    std::vector<uint8_t>& buffer){

        std::vector<char> c_url = mImpl->FillUrlfromString(url_of_file);

        /* specify URL to get */
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_URL, &c_url[0]);

        /* save data to this buffer */
        if(mImpl->size_of_manifest != 0){
            buffer.resize(mImpl->size_of_manifest + 128);
        }
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_WRITEDATA, &buffer);

        /* send all data to this function  */
        //curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, Urloader::WriteToRAMCallback);
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_WRITEFUNCTION, mImpl->WriteToRAMCallback);

        /* some servers don't like requests that are made without a user-agent
             field, so we provide one */
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        if(progress_indicator.pProgressCallback != nullptr){
            progress_indicator.is_download_completed = false;
            progress_indicator.received_file_size = 0;
        }

        /* get it! */
        mImpl->curl_res = curl_easy_perform(mImpl->curl_handler);
        /* transmission done */
        curl_easy_reset(mImpl->curl_handler);

        if(progress_indicator.pProgressCallback != nullptr){
            progress_indicator.is_download_completed = true;
            (void*)progress_indicator.pProgressCallback();
        }

        if(mImpl->curl_res != CURLE_OK){
            return false;
        }else{
            return true;
        }
    }

    bool Urloader::GetFileByUrl(const std::string& url_of_file, const std::string& path_to_file){

        std::vector<char> c_url = mImpl->FillUrlfromString(url_of_file);

        /* specify URL to get */
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_URL, &c_url[0]);

        std::fstream file_handler;
        file_handler.open(path_to_file, std::fstream::out       |
                                        std::fstream::binary    |
                                        std::fstream::trunc);

        curl_easy_setopt(mImpl->curl_handler, CURLOPT_WRITEDATA, &file_handler);

        /* send all data to this function  */
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_WRITEFUNCTION, mImpl->WriteToFileCallback);

        /* some servers don't like requests that are made without a user-agent
             field, so we provide one */
        curl_easy_setopt(mImpl->curl_handler, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        mImpl->curl_res = curl_easy_perform(mImpl->curl_handler);
        file_handler.close();
        /* transmission done */
        curl_easy_reset(mImpl->curl_handler);
        if(mImpl->curl_res != CURLE_OK){
            return false;
        }else{
            return true;
        }
    }

    uint32_t Urloader::GetLastResultCode(){
        return static_cast<uint32_t>(mImpl->curl_res);
    }


}
