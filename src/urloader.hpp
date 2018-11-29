#ifndef URLOADER_HPP
#define URLOADER_HPP

#include <string>
#include <vector>
#include <memory>

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
        uint32_t GetLastResultCode(void);

    private:
        struct Impl;
        std::unique_ptr<Impl> mImpl;
    };
}
#endif // URLOADER_HPP
