#include <iostream>
#include <curl/curl.h>
#include <fstream>

//Idea: This app is a price monitoring program. You feed it a list of links to websites that are supported and it keeps an eye on price changes
//  Can run at specified intervals and alerts to email given price increase/decrease
/*

    libcurl to download the html file
    libtidy to convert to valid xml
    libxml to parse/navigate the xml

*/

size_t write_data(char *ptr, size_t size, size_t nmemb, std::string *buf)
{
  if(buf == NULL)
    return 0;

  buf->append(ptr, size*nmemb);

  return size * nmemb;
}

int main(){
    const char* outfile = "out.html";
    bool success = true;
    std::string buffer;
    CURLcode res;

    std::cout << "Welome to my crappy webscraper" << std::endl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    if(!curl){
        success = false;
        goto global_cleanup; // Just go straight to global cleanup and be done
    }
    //Option setup
    //Target addr
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
    //Write function callback
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        success = false;
    }
    printf("String is len: %d: %s\n", (int)buffer.length(), buffer.c_str());

    //Tiered cleanup, goto these when appropriate
    //easy cleanup
    easy_cleanup:
    curl_easy_cleanup(curl);
    //Global Cleanup
    global_cleanup:
    curl_global_cleanup();
    return success ? 0 : -1;
}