#include "stdafx.h"

static bool
hasDashes(const char *key)
{
	return (key[5] == '-' && key[11] == '-' && key[17] == '-' && key[23] == '-');
}

static bool
hasValidFormat(const char *key)
{
	return (strlen(key) == 29U && hasDashes(key));
}

bool
isValidKey(const char *key)
{
	char c;
	unsigned int sum = 0;

	if (!hasValidFormat(key))
		return false;

	while ((c = *key++) != '\0') {
		if (c == '-')
			continue;
		if (c < 'A' || c > 'Z')
			return false;
		sum += c - 'A';
	}

	return (sum % 7 == 0);
}

int
main(int argc, char **argv)
{
#if 1
	if (argc < 2) {
		fprintf(stderr, "Usage: %s key\n"
		"This program will print \"PASS\" if the key is valid.\n", argv[0]);
		return EXIT_FAILURE;
	}

	if (isValidKey(argv[1])) {
		puts("PASS");
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
#else
	/* NZGBY-FXUOL-LAQLI-YTCXY-QXWMS */
	char key[30];
	size_t i;

	srand(time(NULL));
	key[29] = '\0';

	do {
		for (i = 0; i < 29; ++i) {
			/* This has HORRIBLE modulo bias. */
			key[i] = 'A' + (rand() % 26);
		}

		key[5] = key[11] = key[17] = key[23] = '-';
	} while (!isValidKey(key));

	std::cout << key << std::endl;

	return EXIT_SUCCESS;
#endif
}
