#ifndef _SUDOKU_CLIENT_H_
#define _SUDOKU_CLIENT_H_

#include "client_message.h"
#include "instruction.h"
#include "client.h"

typedef struct sudoku_client {
    client_message_t client_msg;
    instruction_t instruction;
} sudoku_client_t;

//Inicia el juego en modo cliente
int sudoku_run_as_client(const char* host, const char* port);

#endif
