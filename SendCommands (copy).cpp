/* 
 * File:   webClient.c
 * Author: Adam
 *
 * Created on November 3, 2011, 1:26 AM
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
//#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <curlpp/cURLpp.hpp>
//#include <curlpp/Options.hpp>
//#include <curl/curl.h>
#define BUFFSIZE 32 

//#include <iostream>
#include <string>
#include <curl/curl.h> //your directory may be different
using namespace std;

string data; //will hold the url's contents

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}

int main()
{
    CURL* curl; //our curl object
    
   //char requestURL[70];
   //char referer[100];
   struct curl_slist *headers=NULL;

   

    const std::string CommandStringRight = "http://admin:123456@192.168.2.7/hy-cgi/ptz.cgi?user=admin&pwd=123456&cmd=ptzctrl&act=hscan";
    const std::string UserPsw = "admin:123456";
    const std::string strArguments = "cmd=ptzctrl&act=right";

    //strcpy(requestURL , CommandStringRight.c_str());
   //strcat(requestURL, CAM_SESSION_CONTINUE);

   //strcpy(referer , "Accept: */*");
   //strcat(referer , "Accept-Encoding: gzip, deflate, sdch");
   //strcat(referer , "Authorization: Digest username="admin");
   //strcat(referer , "Referer: http://192.168.2.11/main.html?id=1&playtype=fv");
   //strcat(referer , CAM_MONITOR);

   headers = curl_slist_append(headers, "Accept: */*");
   headers = curl_slist_append(headers, "Accept-Encoding: gzip, deflate, sdch");
   headers = curl_slist_append(headers, "Accept-Language: en-US,en;q=0.8");
   //headers = curl_slist_append(headers, "Authorization: Digest username='admin', realm='IPCamera Login', nonce ='242d19fa471dfee9791075cf0db01d8e', uri='/hy-cgi/user.cgi?cmd=checkuserinfo', response='0ce9dbe9c61ea5a9a3964d53e7a620f0', qop=auth, nc=00000055, cnonce='e16ce184d007e0c6'");
   headers = curl_slist_append(headers, "Connection:keep-alive");
   headers = curl_slist_append(headers, "Cookie: language=english");
   headers = curl_slist_append(headers, "Host: 192.168.2.7");
   headers = curl_slist_append(headers, "Referer: http://192.168.2.7/main.html?id=1&playtype=fv");
   headers = curl_slist_append(headers, "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36");
   //headers = curl_slist_append(headers, camCookie);


    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();
    curl_easy_reset(curl);

    //curl_easy_setopt(curl, CURLOPT_URL, CommandStringRight.c_str());
    //curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
    //curl_easy_setopt(curl, CURLOPT_USERPWD, UserPsw.c_str());    // set user name and password for the authentication
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strArguments.c_str());
    curl_easy_setopt( curl , CURLOPT_URL        , CommandStringRight.c_str()                        );
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(strArguments.c_str()));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); //tell curl to output its progress
    
    
    curl_easy_setopt( curl , CURLOPT_HTTPHEADER , headers);//"Referer: http://192.168.2.11/main.html?id=1&playtype=fv"                           );
    curl_easy_setopt( curl , CURLOPT_HTTPGET    , 1                                 );
    curl_easy_setopt( curl , CURLOPT_USERNAME   , "admin"                            );
    curl_easy_setopt( curl , CURLOPT_PASSWORD   , "123456"                        );
    curl_easy_setopt( curl , CURLOPT_HTTPAUTH   , (long)CURLAUTH_ANY  );
    //curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); //tell curl to output its progress
    curl_easy_setopt(curl, CURLOPT_PORT, 80);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie.txt");
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.txt");
    CURLcode res = curl_easy_perform(curl);

    //res = curl_easy_perform(curl);
    
    if (res != CURLE_OK)
    {
       cout << "Curl call to server failed";
       return false;
    }


    cout << endl << data << endl;
    cin.get();

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}
