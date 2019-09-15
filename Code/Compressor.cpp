#include "Compressor.h"
#include "ProtectedQueue.h"
#include "CompressorThread.h"
#include <iostream>

/*--------------Public--------------*/
Compressor::Compressor(int num_thrds, size_t max_q_len, int block_len) {
    this->wtr_thread = new WriterThread(this->queues); //By Reference
    this->num_thrds = num_thrds;
    this->init_queues(max_q_len);
    this->init_threads(block_len);
}

void Compressor::set_input_file(const char* i_filename) {
    this->i_file.open(i_filename, std::ios::binary);
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads[i]->set_file(&this->i_file);
    }
}

void Compressor::set_output_file(const char* o_filename) {
    this->o_file.open(o_filename, std::ios::binary);
    this->wtr_thread->set_file(&this->o_file);
}

void Compressor::compress() {
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads[i]->run();
    }
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads[i]->join();
    }
    this->wtr_thread->run();
    this->wtr_thread->join();
    std::cerr << "Threads Closed" << '\n';
}

/*--------------Private-------------*/
void Compressor::init_threads(int block_len) {
    for (int i = 0; i < this->num_thrds; i++) {
        CompressorThread* cmp_thread = new CompressorThread(block_len, i, this->i_file_mtx);
        this->cmp_threads.push_back(cmp_thread); //By pointer
        this->cmp_threads[i]->set_queue(this->queues[i]); //By reference
    }
}

void Compressor::init_queues(size_t max_q_len) {
    for (int i = 0; i < this->num_thrds; i++) {
        ProtectedQueue* queue = new ProtectedQueue(max_q_len);
        this->queues.push_back(queue); //By pointer
    }
}

Compressor::~Compressor() {
    this->cmp_threads.clear();

    if (this->i_file.is_open()) {
        this->i_file.close();
    }
    if (this->o_file.is_open()) {
        printf("cerre\n");
        this->o_file.close();
    }

    //Destroy queues
    //Destroy threads
}
