#ifndef URLOADER_HPP
#define URLOADER_HPP

#include <string>
#include <vector>
#include <memory>

namespace urloader
{
    struct IndicatorLoadingProgress_t{
        int* pProgressCallback;
        size_t whole_file_size;
        size_t received_file_size;
        bool is_download_completed;
    };


    class Urloader
    {
    public:
        Urloader();
        ~Urloader();

        bool IsUrlAccessible(const std::string& url_of_file);
        bool GetManifestByUrl(const std::string& url_of_file, std::vector<uint8_t>& buffer);
        bool GetFileByUrl(const std::string& url_of_file, const std::string& path_to_file);
        uint32_t GetLastResultCode(void);

        IndicatorLoadingProgress_t progress_indicator;


    private:
        struct Impl;
        std::unique_ptr<Impl> mImpl;
    };
}
#endif // URLOADER_HPP
