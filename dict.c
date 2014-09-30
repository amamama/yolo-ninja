#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <oauth.h>
#include <curl/curl.h>

inline static int amp_count(char const *str) {
	int cnt = 1;
	for (char const *p; (p = strchr(str, '&')); cnt++) {
		str = p + 1;
	}
	return cnt;
}

char **parse_qstr(int const qstrc, char *qstrv[qstrc], char *qstr) {
	int i = 0;
	char *tmp = strtok(qstr, "&");
	do {
		qstrv[i] = tmp;
		i++;
		tmp = strtok(NULL, "&");
	} while (i < qstrc);
	return qstrv;
}

int print_qstr(int const qstrc, char *qstrv[qstrc]) {
	for (int i = 0; i < qstrc; i++) {
		printf("%d:%s\n", i, qstrv[i]);
	}
	return 0;
}

int main (int argc, char *argv[]) {

	puts("Content-type: text/html; Charset=UTF-8");

	char const * qstr = getenv("QUERY_STRING");
	if (!qstr) {
		puts("No argments");
		return 0;
	}

	char * const qstr_body = oauth_url_unescape(qstr, NULL);
	if (qstr_body[0] == '\0') {
		free(qstr_body);
		puts("No argments");
		return 0;
	}

	int const qstrc = amp_count(qstr_body);
	char *qstrv[qstrc];
	parse_qstr(qstrc, qstrv, qstr_body);

#define weblio "http://ejje.weblio.jp/content/"
	char request[strlen(weblio) + strlen(qstrv[0]) + 1];
	memset(request, 0, sizeof(request));
   	strncat(request, weblio, sizeof(request));
	strncat(request, qstrv[0], sizeof(request));

	CURL *curl;
	CURLcode ret;
	curl = curl_easy_init();
	if (!curl) {
		fprintf(stderr, "failed to initialize curl\n");
	}
	curl_easy_setopt (curl, CURLOPT_URL, request);
	ret = curl_easy_perform (curl);
	if (ret != CURLE_OK) {
		fprintf (stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror (ret));
	}
	curl_easy_cleanup(curl);

	free(qstr_body);
	return 0;
}
