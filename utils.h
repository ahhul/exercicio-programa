/* Criptografia e Segurança de Dados  */
/* Exercício-programa 2018 - K128     */
/* Ludmila Ferreira Vicente e Silva   */
#ifndef H_UTILS
#define H_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include "hexdump.h"

typedef unsigned int uint32;

/* blocos que serao usados na criptografia */
typedef struct{
  uint32 X, Y, W, Z;
} uint128;

/* vetores para guardas as sboxes */
uint32_t sbox_1[256], sbox_2[256], sbox_3[256], sbox_4[256];


/*------------------------ SENHA --------------------------*/

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

/* faz uma rotacao cirular de n bits */
uint32 circular_rotation (uint32 bin, byte_t n);


/*----------------- MANIPULACAO DE BLOCOS -----------------*/

/* cria um vetor de blocos de 128bits a partir de um vetor de bytes.
  A flag cripto setada em 1, significa que estamos criando blocos
  para criptografar um araquivo */
uint128* block_generation (long file_size, byte_t *file_bytes, long *number_blocks, int cripto);

/* faz o xor entre dois blocos de 128bits */
uint128 xor (uint128 x, uint128 y);

/* cria o primeiro bloco do cbc */
uint128 block_VI_cbc ();

/* cria um vetor de bytes a partir do vetor de blocos uint128 para ser printado
  no arquivo de saída */
byte_t* blocks_to_bytes (uint128 *blocks, int n_blocks);


/*------------------------ SBOXES -----------------------*/

/* le as sboxes */
void sbox_read (char *file, uint32 sbox[]);


#endif
