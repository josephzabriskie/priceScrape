#include <iostream>
#include <curl/curl.h>

//Idea: This app is a price monitoring program. You feed it a list of links to websites that are supported and it keeps an eye on price changes
//  Can run at specified intervals and alerts to email given price increase/decrease

int callcount = 0;
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    return size;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int main(){
    std::cout << "Welome to my crappy webscraper" << std::endl;
    bool success = true;
    CURLcode res;
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
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    res = curl_easy_perform(curl);
    if(res != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        success = false;
    }

    //easy cleanup
    curl_easy_cleanup(curl);

    //Global Cleanup
    global_cleanup:
    curl_global_cleanup();
    return success ? 0 : -1;
}