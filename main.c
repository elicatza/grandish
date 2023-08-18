#include <stdlib.h>
#include <assert.h>
#include <sys/random.h>

#define RH_IMPLEMENTATION
#include "rainbow-hig.h"

static char *char_sets[] = {
     "abcdefghijklmnopqrstuvwxyz",
     "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
     "0123456789",
    "!\"#$%&'()*+,-",
};

#define CHAR_SETS_LEN sizeof(char_sets) / sizeof(*char_sets)


void compose_char_set(size_t char_set, char *buf, size_t sz)
{
    size_t i;
    for (i = 0; i < CHAR_SETS_LEN; ++i) {
        if (char_set & 1<<i) {
            assert(strlen(buf) + strlen(char_sets[i]) + 1 <= sz);
            strcat(buf, char_sets[i]);
        }
    }
}


char pick_random_char(char *char_set, size_t len)
{
    assert(len > 0);
    size_t rand_id = rand() % len;
    return char_set[rand_id];
}


int main(int argc, char **argv)
{
    // Set default flag values
    size_t char_amount = 16;

    size_t range = 0;
    size_t i;
    // Parse command line arguments 
    {
        bool set_opts[CHAR_SETS_LEN];
        memset(set_opts, 0, sizeof set_opts);

        RHArg args[] = {
            { RHARG_HELP },
            { "lower", 'l', "", rh_parser_bool, (void *) &set_opts[0], "Enable lower case letters" },
            { "upper", 'u', "", rh_parser_bool, (void *) &set_opts[1], "Enable upper case letters" },
            { "number", 'n', "", rh_parser_bool, (void *) &set_opts[2], "Enable numeric values" },
            { "sym", 's', "", rh_parser_bool, (void *) &set_opts[3], "Enable symbols" },
            { "amount", 'a', "UINT", rh_parser_uint, (void *) &char_amount, "Amount of characetrs to generate. Default 16" },
            { RHARG_NULL },
        };

        RHInfo info = rh_info_constructor("Gen randstr", "Me", "0.1.0", argv[0]);
        rh_args_parse(argc, argv, args, &info);
        if (argc == 1) {
            printf("%s\n", info.usage);
            printf("This program requires flags see `%s --help` for more details.\n", argv[0]);
            return 0;
        }

        for (i = 0; i < CHAR_SETS_LEN; ++i) {
            range |= set_opts[i] * 1<<i;
        }
    }

    char char_set[1<<7];
    compose_char_set(range, char_set, 1<<7);
    size_t char_set_len = strlen(char_set);

    int seed;
    getentropy(&seed, sizeof seed);
    srand(seed);

    for (i = 0; i < char_amount; ++i) {
        putchar(pick_random_char(char_set, char_set_len));
    }
    putchar('\n');
    return 0;
}
