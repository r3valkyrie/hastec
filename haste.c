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

#define HASTEBIN_URL "https://haste.r3valkyrie.com" 				/* Hastebin URL */

char * dyn_mem_allocate(FILE * fp, size_t size)					/* Dynamically allocate enough memory for the user input */
{
    char * str;
    int ch;
    size_t len = 0;

    str = realloc(NULL, sizeof(char) * size);

    if (!str) return str;

    while ((ch = fgetc(fp)) != EOF) {
        str[len++] = ch;
        if (len == size) {
            str = realloc(str, sizeof(char) * (size += 1024));
            if (!str) return str;
        }
    }

    str[len++] = '\0';

    return realloc(str, sizeof(char) * len);
}

size_t print_url(void * buffer, size_t size, size_t nmemb, void * userp) 	/* libcurl callback function, prints hastebin URL */
{
    struct json_object * parsed_json;
    struct json_object * key;

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "key", & key);
    printf("\n"
        HASTEBIN_URL "/%s\n", json_object_get_string(key));
}

int post_input(char * dat)
{
    char * url = HASTEBIN_URL "/documents"; 					/* The URL we are sending the POST request to */

    CURL * curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {
        struct curl_slist * headers = NULL;

        curl_easy_setopt(curl, CURLOPT_URL, url); 				/* The URL */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dat); 			/* The data being pasted */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, print_url);		/* Write to callback function */

        res = curl_easy_perform(curl); 						/* Perform the request */

        curl_easy_cleanup(curl); 						/* Cleanup */
    }
    curl_global_cleanup();
    return 0;
}

int main(void)
{
    char * dat;
    dat = dyn_mem_allocate(stdin, 1024);

    post_input(dat);

    free(dat);
    return 0;

}
