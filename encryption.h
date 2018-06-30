/* Criptografia e Segurança de Dados  */
/* Exercício-programa 2018 - K128     */
/* Ludmila Ferreira Vicente e Silva   */
#ifndef H_ENCRYPTION
#define H_ENCRYPTION

#include "utils.h"
#include "keys.h"

/*------------------------ CRIPTOGRAFIA E DECRIPTOGRAFIA ------------------------*/
/* encripta um bloco uint128 */
uint128 block_encrypt_k128 (uint128 block, uint128 key);


/* decripta um bloco uint128 */
uint128 block_decrypt_k128 (uint128 block, uint128 key);

/* faz a encriptacao do arquivo de entrada */
void encryption (long file_size, byte_t *file_bytes, char* password, char* output);

void decryption (long file_size, byte_t *file_bytes, char* password, char* output);


#endif
