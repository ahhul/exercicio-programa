/* Criptografia e Segurança de Dados  */
/* Exercício-programa 2018 - K128     */
/* Ludmila Ferreira Vicente e Silva   */
#ifndef H_KEYS
#define H_KEYS

#include <math.h>
#include "utils.h"


#define ConstR 0x10011
#define ConstM 0xCB3725F7
#define K0Const 0x5A827999874AA67D657B7C8EBD070242


/*----------------------------- GERACAO DE CHAVES -----------------------------*/

/* gera a chave principal */
uint128 key_creation (char* password);

/* gera a chave intermediaria a partir das constantes */
uint128 intermediary_key (uint128 K_old, int iteration);

/* Gera as subchaves KR5 e KM32*/
void sub_keys (uint128 inter_key, byte_t KR5[], uint32 KM32[]);


/*--------------------------- FUNCOES DO ENUNCIADO ---------------------------*/

/* fucao f1 do enunciado */
uint32 f_1(uint32 X, byte_t KR5, uint32 KM32);

/* funcao f2 do enunciado */
uint32 f_2(uint32 X, byte_t KR5, uint32 KM32);

/* funcao f3 do enunciado */
uint32 f_3(uint32 X, byte_t KR5, uint32 KM32);


/*----------------------- ITERACOES DO ALGORITMO K128 ------------------------*/

/* faz uma interacao do algoritmo k128 */
uint128 one_iteration (int iteration, uint128 int_key, uint128 value);

/* faz o inverso de uma iteracao algoritmo k128 */
uint128 reverse_one_iteration (int iteration, uint128 int_key, uint128 value);


/*---------------------------- LEITURA DAS SBOXES ----------------------------*/

/* le as sboxes */
void sbox_read (char *file, uint32 sbox[]);


#endif
