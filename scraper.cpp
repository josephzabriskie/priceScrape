#include <iostream>
#include <curl/curl.h>

//Idea: This app is a price monitoring program. You feed it a list of links to websites that are supported and it keeps an eye on price changes
//  Can run at specified intervals and alerts to email given price increase/decrease
using namespace std;

int main(){
    cout << "Welome to my crappy webscraper" << endl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    auto curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        //Final cleanup
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}