/**
 * @file ft_checksum.c
 * @brief Compute a packet checksum
 *
 */

#include <stddef.h>
#include <stdint.h>

#include "ft_utils.h"

/**
 * @fn uint_least16_t ft_checksum(void *data, size_t size)
 *
 * @param data: buffer containing the data
 * @param size: size of the memory buffer as uint8
 *
 * @return the computed checksum
 *
 * @brief compute the checksum
 *
 * The checksum is the 16-bit ones's complement of the one's complement sum of
 * the ICMP message starting with the ICMP Type.  For computing the checksum ,
 * the checksum field should be zero.  If the total length is odd, the received
 * data is padded with one octet of zeros for computing the checksum.
 */
uint_least16_t ft_checksum(void *data, size_t size)
{
	uint64_t		checksum = 0;
	const uint16_t	*buffer = data;

	if (size & 0x1)
	{
		checksum += buffer[size >> 1] & 0xff;
		size--;
	}
	size = size >> 1;
	for (size_t i = 0; i < size; i++)
		checksum += buffer[i];
	while (checksum != (checksum & 0xffffLL))
		checksum = (checksum & 0xffffLL) + (checksum >> 16);
	return ((uint_least16_t)checksum);
}
