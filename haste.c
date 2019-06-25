#include <stdio.h>
#include <stdlib.h>
#include <json-c/json_tokener.h>
#include <json-c/json_object.h>
#include <curl/curl.h>

/*
 * Takes input from stdin and posts it to a specified hastebin.
 *
 * When run standalone, accepts input until the user sends an
 * EOF, then returns a url to the paste. Can also be piped into
 * like so:
 *
 * `cat filename.txt | haste`
 */

#define HASTEBIN_URL "https://haste.r3valkyrie.com"

uint8_t * dyn_mem_allocate(FILE * fp, size_t size)
{
    uint8_t * str;
    int64_t ch;
    size_t len = 0;

    str = realloc(NULL, sizeof(uint8_t) * size);

    if (!str) return str;

    while ((ch = fgetc(fp)) != EOF) {
        str[len++] = ch;

        if (len == size) {
            str = realloc(str, sizeof(uint8_t) * (size += 1024));

            if (!str) return str;
        }
    }

    str[len++] = '\0';

    return realloc(str, sizeof(uint8_t) * len);
}

size_t print_url(void * buffer, size_t size, size_t nmemb, void * userp)
{
    struct json_object * parsed_json;
    struct json_object * key;

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "key", & key);
    printf("\n" HASTEBIN_URL "/%s\n", json_object_get_string(key));
}

int64_t post_input(uint8_t * dat)
{
    uint8_t * url = HASTEBIN_URL "/documents";
    CURL * curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {
        struct curl_slist * headers = NULL;

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dat);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, print_url);

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}

int64_t main(void)
{
    uint8_t * dat;

    dat = dyn_mem_allocate(stdin, 1024);

    post_input(dat);
    free(dat);

    return 0;
}
