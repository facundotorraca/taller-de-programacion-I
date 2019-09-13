#include "Compressor.h"
#include <iostream>
#include <cstring>
#include <sstream>

#define SUCCESS 0
#define NO_FILE "-"

int main (int argc, char *argv[]) {
    int block_len = atoi(argv[1]);
    int max_q_len = atol(argv[2]);
    int num_thrds = atoi(argv[3]);

    char* i_filename = argv[4];
    char* o_filename = argv[5];

    Compressor compressor(num_thrds, max_q_len, block_len);

    if (strncmp(NO_FILE, i_filename, 1) != 0) {
        compressor.set_input_file(i_filename);
    }
    if (strncmp(NO_FILE, o_filename, 1) != 0) {
        compressor.set_output_file(o_filename);
    }

    compressor.compress();
    return SUCCESS;
}