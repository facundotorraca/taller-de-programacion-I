#include "BlockBuffer.h"
#include "Block.h"
#include <cstdint>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

/*--------------Public--------------*/
BlockBuffer::BlockBuffer(int block_len) {
    this->buffer = new uint32_t[block_len];
    this->buff_len = block_len;
    this->clear(); //Init the buffer
}

void BlockBuffer::add_number(char* str_number) {
    uint32_t number;
    memcpy(&number, str_number, 4);

    this->buffer[this->curr_pos] = ntohl(number);
    this->curr_pos++;
}

Block* BlockBuffer::create_compressed_block() {
    Block* block;
    if (curr_pos == 1) { //Zero brick case
        block = new Block(buffer, 1);
    } else {
        this->complete_buffer();
        block = new Block(buffer, this->buff_len);
    }
    this->clear(); //Restart the buffer
    block->compress();
    return block;
}

/*--------------Private--------------*/
void BlockBuffer::clear() {
    memset(this->buffer, 0, this->buff_len * sizeof(uint32_t));
    this->curr_pos = 0;
}

void BlockBuffer::complete_buffer() {
    if (this->curr_pos < this->buff_len) {
        int pos_last = this->curr_pos - 1;
        while (this->curr_pos < this->buff_len) {
            this->buffer[this->curr_pos] = this->buffer[pos_last];
            this->curr_pos++;
        }
    }
}

BlockBuffer::~BlockBuffer() {
    delete [] buffer;
}
