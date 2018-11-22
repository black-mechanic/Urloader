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
    string mnf_url = "http://www.olinchuk.ru/manifest/manifest_clarion.json";
//"file_1M.bin";
    string ota_url = "http://www.olinchuk.ru";
    Urloader myUrldr;
    cout << "-------------------------------------------------" << endl;

    /* print localtime */
    time_t t = time(NULL);
    cout << "Start time: " << ctime(&t) << endl;

    if(myUrldr.IsUrlAccessible(ota_url)){
        //myUrldr
        cout << " URL Exist! " << endl;
    }else{
        cout << " Can't connect to URL! " << endl;
    }

    t = time(NULL);
    cout << endl << "End time: " << ctime(&t) << endl;


  return 0;
}
