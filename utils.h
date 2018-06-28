#ifndef H_UTILS
#define H_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include "hexdump.h"
typedef unsigned int uint32;

typedef struct{
  uint32 X, Y, Z, W;
} uint128;

/*-------------------- SENHA E CHAVE K --------------------*/

/* avalia se a senha digitada é válida */
int password_check (char *password);

/* concatena a senha com ela mesma até chegar em 16 bytes */
char* password_concat (char *password);


/*----------------- MANIPULACAO DE BYTES -----------------*/

/* converte um vetor de bytes em um inteiro de 32 bits */
uint32 byte_to_uint32 (byte_t bytes[]);

/* converte um inteiro de 32 bits em um vetor de bytes em */
byte_t* uint32_to_byte (uint32 num_int32);

/* pega os 5 bits da direita do valor */
byte_t five_bits_right (uint32 num_int32);

/* cria um vetor de blocos de 128bits a partir de um vetor de bytes */
uint128* block_generation (long file_size, byte_t *file_bytes);

#endif
