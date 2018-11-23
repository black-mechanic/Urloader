#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <stdio.h>
#include "urloader.hpp"

using namespace std;
using namespace urloader;

#define FIRMWARE_UPGRADE "1.1"


int main(void)
{
    string manifest_url = "http://www.olinchuk.ru/manifest/upgrade.json";
    string buffer_for_manifest;
    Urloader myUrldr;
    cout << "-------------------------------------------------" << endl;

    /* print localtime */
    time_t t = time(NULL);
    cout << "Start time: " << ctime(&t) << endl;

    /* Check URL accessibility */
    if(myUrldr.IsUrlAccessible(manifest_url)){
        //myUrldr
        cout << " URL Exist! " << endl;
        /* Get manifest as a std::string */
        myUrldr.GetManifestByUrl(manifest_url, buffer_for_manifest);
        cout << buffer_for_manifest << endl;
        /* Parse manifest and get URL for firmware file. Not implemented. */
        string firmware_url = "http://www.olinchuk.ru/firmware/upgrade.bin";


    }else{
        cout << " Can't connect to URL! " << endl;
    }

    t = time(NULL);
    cout << endl << "End time: " << ctime(&t) << endl;


  return 0;
}
