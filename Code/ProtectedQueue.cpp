#include "ProtectedQueue.h"
#include "Block.h"
#include "Lock.h"
#include <cstdbool>
#include <iostream>
#include <mutex>

/*--------------Public--------------*/
ProtectedQueue::ProtectedQueue(size_t max_q_len) {
    this->max_q_len = max_q_len;
    this->q_closed = false;

    this->pushed = 0;
    this->poped = 0;
}

void ProtectedQueue::push(Block* block) {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    while (this->queue.size() >= this->max_q_len) {
        this->cv.wait(lock);
    }

    this->queue.push(block);
    this->pushed++;

    //Now a thread can pop
    this->cv.notify_all();
}

Block* ProtectedQueue::pop() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    while (!this->q_closed && this->queue.empty()) {
        this->cv.wait(lock);
    }
    Block* block = this->queue.front();
    this->queue.pop();
    this->poped++;

    //Now a thread can push
    this->cv.notify_all();

    return block;
}

bool ProtectedQueue::empty() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    return this->queue.empty();
}

void ProtectedQueue::close() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    this->q_closed = true;
    //Notify free pass to take!
    this->cv.notify_all();
}

bool ProtectedQueue::closed() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    return this->q_closed;
}

int ProtectedQueue::get_pop() {
    return this->poped;
}

int ProtectedQueue::get_push() {
    return this->pushed;
}

/*--------------Private--------------*/
ProtectedQueue::~ProtectedQueue() {}
