#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#include <unistd.h>

#define USAGE "USAGE: ./test_c [URI] [REGEX]\n"

struct string {
  char *ptr;
  size_t len;
};

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *data)
{
	size_t new_len;
	
	new_len = data->len + size * nmemb;
	data->ptr = realloc(data->ptr, new_len + 1);
	if (!data->ptr) return 0;
	memcpy(data->ptr + data->len, ptr, size * nmemb);
	data->ptr[new_len] = 0;
	data->len = new_len;
	return size * nmemb;
}

int main(int argc, char **argv)
{
	CURL			*curl;
	CURLcode		res;
	struct string	body;
	struct string	header;
	regex_t			preg;
	regmatch_t		pmatch[2];

	if (argc < 3)
	{
		dprintf(2, USAGE);
		return EXIT_FAILURE;
	}
	if (regcomp(&preg, argv[2], REG_EXTENDED) != 0)
	{
		dprintf(2, "Invalid Regex\n");
		return EXIT_FAILURE;
	}
	curl_global_init(CURL_GLOBAL_DEFAULT);
	bzero(&body, sizeof(body));
	bzero(&header, sizeof(header));

	if (!(curl = curl_easy_init()))
		return EXIT_FAILURE;
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body);
	if ((res = curl_easy_perform(curl)) != CURLE_OK)
		return EXIT_FAILURE;
	curl_easy_cleanup(curl);
	curl_global_cleanup();
	//printf("header: %s\n", header.ptr);
	//printf("body: %s\n", body.ptr);
	regexec(&preg, body.ptr, 2, pmatch, 0);
	write(1, body.ptr + pmatch[1].rm_so, pmatch[1].rm_eo - pmatch[1].rm_so);
	write(1, "\n", 1);
	return EXIT_SUCCESS;
}
