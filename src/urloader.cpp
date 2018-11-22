#include "urloader.hpp"

namespace urloader
{
    Urloader::Urloader(){
        /* init libcurl */
        curl_global_init(CURL_GLOBAL_ALL);
        /* init the curl session */
        curl_handle = curl_easy_init();
    }

    Urloader::~Urloader(){
    /* cleanup curl stuff */
        curl_easy_cleanup(curl_handle);
    /* we're done with libcurl, so clean it up */
        curl_global_cleanup();
    }

    size_t Urloader::WriteCallback(void *ptr, size_t size, size_t nmemb, void *data)
    {
        (void)ptr;  /* unused */
        (void)data; /* unused */
        return (size_t)(size * nmemb);
    }

    /* Convert std::string to char*. Create vector<char> c_url. And will use it as &c_url[0]*/
    std::vector<char> Urloader::FillUrlfromString(std::string& url_of_file){
        //std::vector<char> c_url;
        std::vector<char> c_url(url_of_file.begin(), url_of_file.end());
        //c_url = (url_of_file.begin(), url_of_file.end());
        c_url.push_back('\0');
        return c_url;
    }

    /* Get vector of string in RAM from URL; Input: HTTP URL of file; Output: file in buffer as a vector of string */
    bool Urloader::GetFileByUrl(std::string& url_of_file, std::string& s_buffer){
        bool bResult = true;
        std::vector<char> c_url = FillUrlfromString(url_of_file);

        /* specify URL to get */
        curl_easy_setopt(curl_handle, CURLOPT_URL, &c_url[0]);

        /* send all data to this function  */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, Urloader::WriteCallback);

        /* save data to this buffer */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &s_buffer);

        /* get it! */
        curl_res = curl_easy_perform(curl_handle);
        curl_easy_reset(curl_handle);
        return bResult;
    }

    /* Return True if remote resource exist and accessible */
    bool Urloader::IsUrlAccessible(std::string& url_of_file){
        std::vector<char> c_url = FillUrlfromString(url_of_file);
        curl_easy_setopt(curl_handle, CURLOPT_URL, &c_url[0]);
        /* Now specify the HEAD method */
        curl_easy_setopt(curl_handle, CURLOPT_NOBODY, 1L);
        /* Perform the request, res will get the return code */
        curl_res = curl_easy_perform(curl_handle);
        curl_easy_reset(curl_handle);
        /* Check for errors */
        if(curl_res != CURLE_OK){
            return false;
        }else{
            return true;
        }
    }
}
