#include "../inc/libmx.h"

char **mx_strsplit(const char *s, char c) {
	char **news = NULL;
	int i = 0;
	int k = 0;
	int start;
	int end;

	if (s == NULL)
		return NULL;
	news = (char **)malloc(sizeof(char **) * mx_count_words(s, c) + 1);
	news[mx_count_words(s, c)] = NULL;
	while (s[i]) {
		while (s[i] == c && s[i] != '\0')
			i++;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		end = i;
		if (start != end) {
			news[k] = mx_str_size_dup(s, start, end);
			k++;
		}
	}
	return news;
}
