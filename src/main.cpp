#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <stdio.h>
#include "urloader.hpp"

using namespace std;
using namespace urloader;




int main(void)
{
    string manifest_url = "http://www.olinchuk.ru/manifest/upgrade.json";
    vector<uint8_t> buffer_for_manifest;
    Urloader myUrldr;
    cout << "-------------------------------------------------" << endl;

    /* print localtime */
    time_t t = time(NULL);
    cout << "Start time: " << ctime(&t) << endl;

    /* Check URL accessibility */
    if(myUrldr.IsUrlAccessible(manifest_url)){

        cout << " URL Exist! " << endl;
        /* Get manifest as a std::string */
        myUrldr.GetManifestByUrl(manifest_url, buffer_for_manifest);
        for(auto ch: buffer_for_manifest){
            cout << ch;
        }
        cout << endl;

        /* Parse manifest and get URL for firmware file. Not implemented. */
        string firmware_url = "http://www.olinchuk.ru/firmware/upgrade.bin";
        string path_to_file = "d_upgrade.bin";
        /* Download file from firmware_url and save it to path_to_file */
        myUrldr.GetFileByUrl(firmware_url, path_to_file);
    }else{
        cout << " Can't connect to URL! " << endl;
    }

    t = time(NULL);
    cout << endl << "End time: " << ctime(&t) << endl;


  return 0;
}
