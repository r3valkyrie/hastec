#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json_tokener.h>
#include <json-c/json_object.h>
#include <curl/curl.h>

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


char * auto_realloc(FILE * fp, size_t size)
{
        char * str;
        int ch;
        size_t len = 0;

        str = realloc(NULL, sizeof(int) * size);

        if (!str) return str;

        while ((ch = fgetc(fp)) != EOF) {
                str[len++] = ch;

                if (len == size) {
                        str = realloc(str, sizeof(int) * (size += 1024));

                        if (!str) return str;
                }
        }

        len = strlen(str);
        if (str[len-1] == '\n'){
            str[len-1] = 0;
        }

        return realloc(str, sizeof(int) * len);
}


size_t return_url(void * buffer, size_t size, size_t nmemb, void * userp)
{
        struct json_object * parsed_json;
        struct json_object * key;

        parsed_json = json_tokener_parse(buffer);

        json_object_object_get_ex(parsed_json, "key", & key);
        printf(HASTEBIN_URL "/%s\n", json_object_get_string(key));

        return 0;
}


int64_t post_input(char * dat)
{
        char * url = HASTEBIN_URL "/documents";
        CURL * curl;
        CURLcode res;

        curl = curl_easy_init();

        if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dat);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, return_url);

                res = curl_easy_perform(curl);

                curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        return 0;
}


int main(void)
{
        char * dat;

        dat = auto_realloc(stdin, 1024);

        post_input(dat);
        free(dat);

        return 0;
}
