// made by CocoKitty on 2020-07-11
#include <inttypes.h>

typedef struct ParsedOutput {
	char byte;
	uint8_t amount;
	ParsedOutput* next;
} ParsedOutput;

int parseFile(FILE* input, ParsedOutput* output);
