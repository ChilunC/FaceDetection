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

//string data; //will hold the url's contents

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);

int CommandIP(string ComCam, string User, string Psw, string IPAddr);

int PresetIP(string ComCam, string User, string Psw, string IPAddr);
