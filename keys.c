/* Criptografia e Segurança de Dados  */
/* Exercício-programa 2018 - K128     */
/* Ludmila Ferreira Vicente e Silva   */
#include "keys.h"

/* gera a chave principal */
uint128 key_creation (char* password) {
  byte_t bytes[4];
  uint32 blocks[4];
  uint128 key;
  int i, j = 0, k = 0;

  for(i = 0; i < 16; i++){
    bytes[j++] = password[i];
    if( j == 4){
      blocks[k++] = byte_to_uint32 (bytes);
      j = 0;
    }
  }
  key.X = blocks[0];
  key.Y = blocks[1];
  key.W = blocks[2];
  key.Z = blocks[3];
  return key;
}

/* gera a chave intermediaria a partir das constantes */
uint128 intermediary_key (uint128 K_old, int iteration) {
	uint128 inter_key, constant;
	uint32 X, Y, W, Z;
	X = K_old.X;
	Y = K_old.Y;
	W = K_old.W;
	Z = K_old.Z;

	if (iteration == 0) {
    /* constante retirada do enunciado*/
		constant.X = 0x5A827999;
		constant.Y = 0x874AA67D;
		constant.W = 0x657B7C8E;
		constant.Z = 0xBD070242;
		inter_key.X = X ^ constant.X;
		inter_key.Y = Y ^ constant.Y;
		inter_key.W = W ^ constant.W;
		inter_key.Z = Z ^ constant.Z;
	} else {
		K_old.Z ^= f_2(K_old.X, circular_rotation (ConstR, fmod(pow(iteration + 2, 2), 3)), circular_rotation (ConstM, fmod(pow(iteration + 3, 2), 7)));
		K_old.W ^= f_2(K_old.Z, circular_rotation (ConstR, fmod(iteration + 2, 3)), circular_rotation (ConstM, fmod(iteration + 3, 7)));
		K_old.Y ^= f_2(K_old.W, circular_rotation (ConstR, fmod(pow(iteration + 2, 3), 3)), circular_rotation (ConstM, fmod(pow(iteration + 3, 3), 7)));
		K_old.X ^= f_2(K_old.Y, circular_rotation (ConstR, fmod(pow(iteration + 2, 2), 3)), circular_rotation (ConstM, fmod(pow(iteration + 3, 2), 7)));
		inter_key.X = K_old.Z;
		inter_key.Y = K_old.W;
		inter_key.W = K_old.Y;
		inter_key.Z = K_old.X;
	}

	return inter_key;
}

void sub_keys (uint128 inter_key, byte_t KR5[], uint32 KM32[]) {
	uint32 X, Y, W, Z;
	X = inter_key.X;
	Y = inter_key.Y;
	W = inter_key.W;
	Z = inter_key.Z;

	KR5[0] = five_bits_right (X);
	KR5[1] = five_bits_right (Y);
	KR5[2] = five_bits_right (W);
	KR5[3] = five_bits_right (Z);

	KM32[0] = Z;
	KM32[1] = W;
	KM32[2] = Y;
	KM32[3] = X;
}

uint32 f_1 (uint32 X, byte_t KR5, uint32 KM32) {
  uint32 i, Y;
	byte_t *bytes;
	i = circular_rotation ((X ^ KM32), KR5);
  bytes = uint32_to_byte (i);
  Y = ((sbox_1[bytes[0]] + sbox_2[bytes[1]]) - sbox_3[bytes[2]]);
  Y ^= sbox_4[bytes[3]];
  return Y;
}

uint32 f_2 (uint32 X, byte_t KR5, uint32 KM32) {
  uint32 i, Y;
	byte_t *bytes;
	i = circular_rotation ((X ^ KM32), KR5);
  bytes = uint32_to_byte (i);
  Y = ((sbox_1[bytes[0]] - sbox_2[bytes[1]]) ^ sbox_3[bytes[2]]);
  Y += sbox_4[bytes[3]];
  return Y;
}

uint32 f_3 (uint32 X, byte_t KR5, uint32 KM32) {
  uint32 i, Y;
	byte_t *bytes;
	i = circular_rotation ((X ^ KM32), KR5);
  bytes = uint32_to_byte (i);
  Y = ((sbox_1[bytes[0]] ^ sbox_2[bytes[1]]) + sbox_3[bytes[2]]);
  Y -= sbox_4[bytes[3]];
  return Y;
}


/* faz uma interacao do algoritmo k128 */
uint128 one_iteration (int iteration, uint128 int_key, uint128 value) {
  uint128 block;
	uint32 X, Y, W, Z;
	uint32 KM32[4];
  byte_t KR5[4];

	X = value.X;
  Y = value.Y;
  W = value.W;
  Z = value.Z;

	sub_keys (int_key, KR5, KM32);
  W ^= f_2 (Z, KR5[0], KM32[0]);
  Y ^= f_1 (W, KR5[1], KM32[1]);
  X ^= f_3 (Y, KR5[2], KM32[2]);
  Z ^= f_2 (X, KR5[3], KM32[3]);

  block.X = W;
  block.Y = Y;
  block.W = X;
  block.Z = Z;

  return block;
}

/* faz o inverso de uma iteracao algoritmo k128 */
uint128 reverse_one_iteration (int iteration, uint128 int_key, uint128 value) {
  uint128 block;
	uint32 X, Y, W, Z;
	uint32 KM32[4];
  byte_t KR5[4];

  X = value.W;
  Y = value.Y;
  W = value.X;
  Z = value.Z;

  sub_keys (int_key, KR5, KM32);

  Z ^= f_2 (X, KR5[3], KM32[3]);
  X ^= f_3 (Y, KR5[2], KM32[2]);
  Y ^= f_1 (W, KR5[1], KM32[1]);
  W ^= f_2 (Z, KR5[0], KM32[0]);

  block.X = X;
  block.Y = Y;
  block.W = W;
  block.Z = Z;

  return block;
}
