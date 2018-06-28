#ifndef H_ENCRYPTION
#define H_ENCRYPTION

#include "utils.h"
#include "keys.h"

/* faz a criptografia do arquivo de entrada */
void encryption (long file_size, byte_t *file_bytes, uint128 *in_blocks, char* password);

#endif
