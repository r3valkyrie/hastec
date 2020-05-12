#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "vector.h"

#define HASTEBIN_URL "https://haste.r3valkyrie.com"

/*
 * Takes input from stdin and posts it to a specified hastebin.
 *
 * When run standalone, accepts input until the user sends an
 * EOF, then returns a url to the paste. Can also be piped into
 * like so:
 *
 * `cat filename.txt | haste`
 */


char print_url(char *res)
{
    int start = 8;
    int len = 10;
    printf(HASTEBIN_URL "/%.*s\n", len, res + start);
    return 0;
}

CURLcode post_paste(char * data)
{
    char * url = HASTEBIN_URL "/documents";
    CURL * curl;

    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, print_url);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return 0;
}

int main()
{
    Vector paste;
    char c;

    initVector(&paste);
    while((c = fgetc(stdin)) != EOF)
    {
        appendVector(&paste, c);
    }

    if(paste.array[paste.used-1] == '\n')
    {
        paste.array[paste.used-1] = 0;
    }

    post_paste(paste.array);

    free(paste.array);
    paste.array = NULL;
    paste.used = 0;
    paste.size = 0;
    return 0;
}