#ifndef CRC_H
#define CRC_H

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

int crc32_check(const uint8_t *buf, int size);

uint32_t crc32(uint32_t crc, const uint8_t *buf, uint32_t size);

uint16_t crc16(unsigned char *puchMsg, uint32_t usDataLen);

#ifdef  __cplusplus
}
#endif

#endif // CRC_H
