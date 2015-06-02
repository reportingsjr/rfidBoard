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
 *
 *  Loosely based on the ENC28J60 driver by Pascal Stang from the
 *  avr-uip library
 */

#include "hal.h"
#include "enc.h"

#define BANK(x)		((x) << 5)
#define BANK_NUM(x)	(((x) >> 5) & 0b11)
#define BANK0		BANK(0)
#define BANK1		BANK(1)
#define BANK2		BANK(2)
#define BANK3		BANK(3)

#define NEEDS_DUMMY(x) !!((x) & 0x80)

/* Common registers */
#define EIE					0x1B
#define EIR					0x1C
#define ESTAT				0x1D
#define ECON2				0x1E
#define ECON1				0x1F
/* Bank 0 */
#define ERDPTL				(0x00|BANK0)
#define ERDPTH				(0x01|BANK0)
#define EWRPTL				(0x02|BANK0)
#define EWRPTH				(0x03|BANK0)
#define ETXSTL				(0x04|BANK0)
#define ETXSTH				(0x05|BANK0)
#define ETXNDL				(0x06|BANK0)
#define ETXNDH				(0x07|BANK0)
#define ERXSTL				(0x08|BANK0)
#define ERXSTH				(0x09|BANK0)
#define ERXNDL				(0x0A|BANK0)
#define ERXNDH				(0x0B|BANK0)
#define ERXRDPTL			(0x0C|BANK0)
#define ERXRDPTH			(0x0D|BANK0)
#define ERXWRPTL			(0x0E|BANK0)
#define ERXWRPTH			(0x0F|BANK0)
#define EDMASTL				(0x10|BANK0)
#define EDMASTH				(0x11|BANK0)
#define EDMANDL				(0x12|BANK0)
#define EDMANDH				(0x13|BANK0)
#define EDMADSTL			(0x14|BANK0)
#define EDMADSTH			(0x15|BANK0)
#define EDMACSL				(0x16|BANK0)
#define EDMACSH				(0x17|BANK0)
/* Bank 1 */
#define EHT0				(0x00|BANK1)
#define EHT1				(0x01|BANK1)
#define EHT2				(0x02|BANK1)
#define EHT3				(0x03|BANK1)
#define EHT4				(0x04|BANK1)
#define EHT5				(0x05|BANK1)
#define EHT6				(0x06|BANK1)
#define EHT7				(0x07|BANK1)
#define EPMM0				(0x08|BANK1)
#define EPMM1				(0x09|BANK1)
#define EPMM2				(0x0A|BANK1)
#define EPMM3				(0x0B|BANK1)
#define EPMM4				(0x0C|BANK1)
#define EPMM5				(0x0D|BANK1)
#define EPMM6				(0x0E|BANK1)
#define EPMM7				(0x0F|BANK1)
#define EPMCSL				(0x10|BANK1)
#define EPMCSH				(0x11|BANK1)
#define EPMOL				(0x14|BANK1)
#define EPMOH				(0x15|BANK1)
#define EWOLIE				(0x16|BANK1)
#define EWOLIR				(0x17|BANK1)
#define ERXFCON				(0x18|BANK1)
#define EPKTCNT				(0x19|BANK1)
/* Bank 2 */
#define MACON1				(0x00|BANK2|0x80)
#define MACON2				(0x01|BANK2|0x80)
#define MACON3				(0x02|BANK2|0x80)
#define MACON4				(0x03|BANK2|0x80)
#define MABBIPG				(0x04|BANK2|0x80)
#define MAIPGL				(0x06|BANK2|0x80)
#define MAIPGH				(0x07|BANK2|0x80)
#define MACLCON1			(0x08|BANK2|0x80)
#define MACLCON2			(0x09|BANK2|0x80)
#define MAMXFLL				(0x0A|BANK2|0x80)
#define MAMXFLH				(0x0B|BANK2|0x80)
#define MAPHSUP				(0x0D|BANK2|0x80)
#define MICON				(0x11|BANK2|0x80)
#define MICMD				(0x12|BANK2|0x80)
#define MIREGADR			(0x14|BANK2|0x80)
#define MIWRL				(0x16|BANK2|0x80)
#define MIWRH				(0x17|BANK2|0x80)
#define MIRDL				(0x18|BANK2|0x80)
#define MIRDH				(0x19|BANK2|0x80)
/* Bank 3 */
#define MAADR1				(0x00|BANK3|0x80)
#define MAADR0				(0x01|BANK3|0x80)
#define MAADR3				(0x02|BANK3|0x80)
#define MAADR2				(0x03|BANK3|0x80)
#define MAADR5				(0x04|BANK3|0x80)
#define MAADR4				(0x05|BANK3|0x80)
#define EBSTSD				(0x06|BANK3)
#define EBSTCON				(0x07|BANK3)
#define EBSTCSL				(0x08|BANK3)
#define EBSTCSH				(0x09|BANK3)
#define MISTAT				(0x0A|BANK3|0x80)
#define EREVID				(0x12|BANK3)
#define ECOCON				(0x15|BANK3)
#define EFLOCON				(0x17|BANK3)
#define EPAUSL				(0x18|BANK3)
#define EPAUSH				(0x19|BANK3)
/* PHY */
#define PHCON1				0x00
#define PHSTAT1				0x01
#define PHHID1				0x02
#define PHHID2				0x03
#define PHCON2				0x10
#define PHSTAT2				0x11
#define PHIE				0x12
#define PHIR				0x13
#define PHLCON				0x14

/* ERXFCON bits */
#define ERXFCON_UCEN		0x80
#define ERXFCON_ANDOR		0x40
#define ERXFCON_CRCEN		0x20
#define ERXFCON_PMEN		0x10
#define ERXFCON_MPEN		0x08
#define ERXFCON_HTEN		0x04
#define ERXFCON_MCEN		0x02
#define ERXFCON_BCEN		0x01
/* EIE bits */
#define EIE_INTIE			0x80
#define EIE_PKTIE			0x40
#define EIE_DMAIE			0x20
#define EIE_LINKIE			0x10
#define EIE_TXIE			0x08
#define EIE_WOLIE			0x04
#define EIE_TXERIE			0x02
#define EIE_RXERIE			0x01
/* EIR bits */
#define EIR_PKTIF			0x40
#define EIR_DMAIF			0x20
#define EIR_LINKIF			0x10
#define EIR_TXIF			0x08
#define EIR_WOLIF			0x04
#define EIR_TXERIF			0x02
#define EIR_RXERIF			0x01
/* ESTAT bits */
#define ESTAT_INT			0x80
#define ESTAT_LATECOL		0x10
#define ESTAT_RXBUSY		0x04
#define ESTAT_TXABRT		0x02
#define ESTAT_CLKRDY		0x01
/* ECON2 bits */
#define ECON2_AUTOINC		0x80
#define ECON2_PKTDEC		0x40
#define ECON2_PWRSV			0x20
#define ECON2_VRPS			0x08
/* ECON1 bits */
#define ECON1_TXRST			0x80
#define ECON1_RXRST			0x40
#define ECON1_DMAST			0x20
#define ECON1_CSUMEN		0x10
#define ECON1_TXRTS			0x08
#define ECON1_RXEN			0x04
#define ECON1_BSEL1			0x02
#define ECON1_BSEL0			0x01
/* MACON1 bits */
#define MACON1_LOOPBK		0x10
#define MACON1_TXPAUS		0x08
#define MACON1_RXPAUS		0x04
#define MACON1_PASSALL		0x02
#define MACON1_MARXEN		0x01
/* MACON2 bits */
#define MACON2_MARST		0x80
#define MACON2_RNDRST		0x40
#define MACON2_MARXRST		0x08
#define MACON2_RFUNRST		0x04
#define MACON2_MATXRST		0x02
#define MACON2_TFUNRST		0x01
/* MACON3 bits */
#define MACON3_PADCFG2		0x80
#define MACON3_PADCFG1		0x40
#define MACON3_PADCFG0		0x20
#define MACON3_TXCRCEN		0x10
#define MACON3_PHDRLEN		0x08
#define MACON3_HFRMLEN		0x04
#define MACON3_FRMLNEN		0x02
#define MACON3_FULDPX		0x01
/* MICMD bits */
#define MICMD_MIISCAN		0x02
#define MICMD_MIIRD			0x01
/* MISTAT bits */
#define MISTAT_NVALID		0x04
#define MISTAT_SCAN			0x02
#define MISTAT_BUSY			0x01
/* PHY PHCON1 bits */
#define PHCON1_PRST			0x8000
#define PHCON1_PLOOPBK		0x4000
#define PHCON1_PPWRSV		0x0800
#define PHCON1_PDPXMD		0x0100
/* PHY PHSTAT1 bits */
#define PHSTAT1_PFDPX		0x1000
#define PHSTAT1_PHDPX		0x0800
#define PHSTAT1_LLSTAT		0x0004
#define PHSTAT1_JBSTAT		0x0002
/* PHY PHCON2 bits */
#define PHCON2_FRCLINK		0x4000
#define PHCON2_TXDIS		0x2000
#define PHCON2_JABBER		0x0400
#define PHCON2_HDLDIS		0x0100

/* Packet Control Byte bits */
#define PKTCTRL_PHUGEEN		0x08
#define PKTCTRL_PPADEN		0x04
#define PKTCTRL_PCRCEN		0x02
#define PKTCTRL_POVERRIDE	0x01

#define INST_CONTROL_READ	0b00000000
#define INST_BUFFER_READ	0b00111010
#define INST_CONTROL_WRITE	0b01000000
#define INST_BUFFER_WRITE	0b01111010
#define INST_BIT_SET		0b10000000
#define INST_BIT_CLEAR		0b10100000
#define INST_RESET			0b11111111

#define ADDR_MASK			0b00011111
#define BANK_MASK			0b01100000

#define SRAM_END			0x1fff
#define RXSTART_INIT		0x0
#define RXSTOP_INIT			(SRAM_END - 1500)
#define TXSTART_INIT		(RXSTOP_INIT + 1)
#define TXSTOP_INIT			SRAM_END

#define enc_spi_start(enc) \
	do { \
		spiStart((enc)->driver, &enc->config); \
		spiSelect((enc)->driver); \
	} while(0)

#define enc_spi_stop(enc) \
	do { \
		spiUnselect((enc)->driver); \
		spiStop((enc)->driver); \
	} while(0)

void enc_reset(struct enc *enc)
{
	uint8_t d = INST_RESET;

	enc_spi_start(enc);
	spiSend(enc->driver, 1, &d);
	enc_spi_stop(enc);
}

static void enc_write_data(struct enc *enc, int n, uint8_t *data)
{
	enc_spi_start(enc);
	spiSend(enc->driver, n, data);
	enc_spi_stop(enc);
}

#define enc_write(e, n, ...) \
	enc_write_data(e, n, (uint8_t[]){__VA_ARGS__})

static void enc_read(struct enc *enc, uint8_t inst, int n, uint8_t *ret)
{
	enc_spi_start(enc);
	spiSend(enc->driver, 1, &inst);
	spiReceive(enc->driver, n, ret);
	enc_spi_stop(enc);
}

static void enc_bit_set(struct enc *enc, uint8_t addr, uint8_t mask)
{
	enc_write(enc, 2, INST_BIT_SET | (ADDR_MASK & addr), mask);
}

static void enc_bit_clr(struct enc *enc, uint8_t addr, uint8_t mask)
{
	enc_write(enc, 2, INST_BIT_CLEAR | (ADDR_MASK & addr), mask);
}

static void enc_set_bank(struct enc *enc, uint8_t bank)
{
	bank = BANK_NUM(bank);
	if (enc->bank == bank)
		return;

	enc_bit_clr(enc, ECON1, ECON1_BSEL0 | ECON1_BSEL1);
	enc_bit_set(enc, ECON1, bank);
	enc->bank = bank;
}

static void enc_register_write(struct enc *enc, uint8_t addr, uint8_t val)
{
	enc_set_bank(enc, addr);
	enc_write(enc, 2, INST_CONTROL_WRITE | (ADDR_MASK & addr), val);
}

static uint8_t enc_register_read(struct enc *enc, uint8_t addr)
{
	uint8_t ret[2] = { 0, 0 };
	bool dummy = NEEDS_DUMMY(addr);
	enc_set_bank(enc, addr);
	enc_read(enc, INST_CONTROL_READ | (ADDR_MASK & addr), dummy ? 2 : 1, ret);
	return ret[dummy ? 1 : 0];
}

static void enc_buffer_write(struct enc *enc, int len, uint8_t *data)
{
	enc_spi_start(enc);
	spiSend(enc->driver, 1, (uint8_t[]){INST_BUFFER_WRITE});
	spiSend(enc->driver, len, data);
	enc_spi_stop(enc);
}

#define enc_buffer_read(e, l, d) \
	enc_read(e, INST_BUFFER_READ, l, d);

static void enc_phy_write(struct enc *enc, uint8_t addr, uint16_t data)
{
	enc_register_write(enc, MIREGADR, addr);
	enc_register_write(enc, MIWRL, data);
	enc_register_write(enc, MIWRH, data >> 8);
	while(enc_register_read(enc, MISTAT) & MISTAT_BUSY)
		chThdSleepMicroseconds(20);
}

void enc_int_clear(struct enc *enc, uint8_t mask)
{
	enc_bit_clr(enc, EIR, mask);
}

uint8_t enc_int_flags(struct enc *enc)
{
	return enc_register_read(enc, EIR);
}

void enc_packet_send(struct enc *enc, uint16_t len1, uint8_t *data1,
		uint16_t len2, uint8_t *data2)
{
	enc_bit_set(enc, ECON1, ECON1_TXRST);
	enc_bit_clr(enc, ECON1, ECON1_TXRST);

	/* Set pointer to start of the byte */
	enc_register_write(enc, EWRPTL, TXSTART_INIT & 0xff);
	enc_register_write(enc, EWRPTH, TXSTART_INIT >> 8);
	/* Set end of the buffer to the end of the packet */
	enc_register_write(enc, ETXNDL, (TXSTART_INIT + len1 + len2) & 0xff);
	enc_register_write(enc, ETXNDH, (TXSTART_INIT + len1 + len2) >> 8);

	/* Per packet config byte, use defaults */
	enc_buffer_write(enc, 1, (uint8_t[]){0});
	enc_buffer_write(enc, len1, data1);
	if (len2 > 0)
		enc_buffer_write(enc, len2, data2);

	enc_bit_set(enc, ECON1, ECON1_TXRTS);
}

uint16_t enc_packet_receive(struct enc *enc, uint16_t maxlen, uint8_t *data)
{
	uint16_t stat;
	uint16_t len;

	if (enc_register_read(enc, EPKTCNT) == 0)
		return 0;

	/* Set the read pointer */
	enc_register_write(enc, ERDPTL, enc->ptr & 0xff);
	enc_register_write(enc, ERDPTH, enc->ptr >> 8);

	/* Read the next packet pointer (This works only on little-endian) */
	enc_buffer_read(enc, 2, (uint8_t *) &enc->ptr);

	/* Read packet length */
	enc_buffer_read(enc, 2, (uint8_t *) &len);
	len -= 4;

	/* Read the rest of the status bits */
	enc_buffer_read(enc, 2, (uint8_t *) &stat)

	if (len > maxlen)
		len = maxlen;

	enc_buffer_read(enc, len, data);

	enc_register_write(enc, ERXRDPTL, enc->ptr & 0xff);
	enc_register_write(enc, ERXRDPTH, enc->ptr >> 8);

	/* Decrement the EPKTCNT */
	enc_bit_set(enc, ECON2, ECON2_PKTDEC);

	return len;
}

void enc_drop_packets(struct enc *enc)
{
	/* Set the pointer to the start of the buffer */
	enc->ptr = RXSTART_INIT;
	enc_register_write(enc, ERXRDPTL, RXSTART_INIT & 0xff);
	enc_register_write(enc, ERXRDPTH, RXSTART_INIT >> 8);
	/* Set the packet counter to 0 */
	enc_register_write(enc, EPKTCNT, 0);
}

void enc_init(struct enc *enc)
{
	enc_reset(enc);
	chThdSleepMilliseconds(100);

	enc->ptr = RXSTART_INIT;
	/* RX buffer start */
	enc_register_write(enc, ERXSTL, RXSTART_INIT & 0xff);
	enc_register_write(enc, ERXSTH, RXSTART_INIT >> 8);
	/* RX buffer pointer */
	enc_register_write(enc, ERXRDPTL, RXSTART_INIT & 0xff);
	enc_register_write(enc, ERXRDPTH, RXSTART_INIT >> 8);
	/* RX buffer end */
	enc_register_write(enc, ERXNDL, RXSTOP_INIT & 0xff);
	enc_register_write(enc, ERXNDL, RXSTOP_INIT >> 8);

	/* TX buffer start */
	enc_register_write(enc, ETXSTL, TXSTART_INIT & 0xff);
	enc_register_write(enc, ETXSTH, TXSTART_INIT >> 8);
	/* TX buffer end */
	enc_register_write(enc, ETXNDL, TXSTOP_INIT & 0xff);
	enc_register_write(enc, ETXNDH, TXSTOP_INIT >> 8);

	/* Drop packets with invalid CRC */
	enc_register_write(enc, ERXFCON, ERXFCON_CRCEN);

	/* Enable rx/tx of pause frames and enables RX */
	enc_register_write(enc, MACON1, MACON1_TXPAUS | MACON1_RXPAUS | MACON1_MARXEN);
	enc_register_write(enc, MACON2, 0);
	/* Pad to 60 bytes and append CRC,  */
	enc_register_write(enc, MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN);
	/* Set inter frame gaps */
	enc_register_write(enc, MAIPGL, 0x12);
	enc_register_write(enc, MAIPGH, 0x0c);
	enc_register_write(enc, MABBIPG, 0x12);

	/* MAC is reversed */
	enc_register_write(enc, MAADR5, enc->mac[0]);
	enc_register_write(enc, MAADR4, enc->mac[1]);
	enc_register_write(enc, MAADR3, enc->mac[2]);
	enc_register_write(enc, MAADR2, enc->mac[3]);
	enc_register_write(enc, MAADR1, enc->mac[4]);
	enc_register_write(enc, MAADR0, enc->mac[5]);

	/* Disable loopback */
	enc_phy_write(enc, PHCON2, PHCON2_HDLDIS);
	/* Enable interrupts */
	enc_register_write(enc, EIE, EIE_INTIE | EIE_PKTIE | EIE_RXERIE);

	/* Set bank to 0 and enables RX */
	enc_register_write(enc, ECON1, ECON1_RXEN);
	enc->bank = 0;
}
