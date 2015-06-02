/*
 *  Copyright (C) Josef Gajdusek <atx@atx.name>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef __ENC_H__
#define __ENC_H__

#include "hal.h"

/* EIR bits */
#define ENC_PKTIF			0x40
#define ENC_DMAIF			0x20
#define ENC_LINKIF			0x10
#define ENC_TXIF			0x08
#define ENC_WOLIF			0x04
#define ENC_TXERIF			0x02
#define ENC_RXERIF			0x01
#define ENC_ALLIF			(ENC_PKTIF | ENC_DMAIF | ENC_LINKIF | ENC_TXIF | \
							 ENC_WOLIF | ENC_TXERIF | ENC_RXERIF)


struct enc {
	SPIDriver *driver;
	SPIConfig config;
	uint8_t bank;
	uint16_t ptr;
	uint8_t mac[];
};

void enc_reset(struct enc *enc);

void enc_packet_send(struct enc *enc, uint16_t hlen, uint8_t *hd,
		uint16_t len, uint8_t *data);
uint16_t enc_packet_receive(struct enc *enc, uint16_t len, uint8_t *data);
uint8_t enc_int_flags(struct enc *enc);
void enc_drop_packets(struct enc *enc);
void enc_int_clear(struct enc *enc, uint8_t mask);
void enc_init(struct enc *enc);

#endif
