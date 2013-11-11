/*
 * Copyright 2011 Robert C. Curtis. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    
 *    2. Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBERT C. CURTIS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ROBERT C. CURTIS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * official policies, either expressed or implied, of Robert C. Curtis.
 */

#ifndef I__BITFIELD_H__
	#define I__BITFIELD_H__

/* Bitfield Macros
 *
 * A bitfield is any range of bits in a word. A bitfield definition
 * needs to specify the SIZE and SHIFT in the following format:
 * 	#define BITFIELD_NAME SIZE:SHIFT
 * Examples (X is don't care, F is the field):
 * 	Register: XXXXXFFX = Bitfield 2:1
 * 	Register: XXXXXFFF = Bitfield 3:0
 * 	Register: XXXXFXXX = Bitfield 1:3
 */
#define _BFSIZE(bf)	(1 ? bf)
#define _BFSHIFT(bf)	(0 ? bf)

#ifndef BF
#define BF(bfdef, bfval)			\
	(((bfval) & ((1 << _BFSIZE(bfdef)) - 1)) << _BFSHIFT(bfdef))
#endif

#ifndef INSERTBF
#define INSERTBF(bfdef, bfval, targetval)	\
	do { \
		(targetval) = ((targetval) \
			& ~(((1 << _BFSIZE(bfdef)) - 1) << _BFSHIFT(bfdef))) \
			| BF(bfdef, bfval); \
	} while(0)
#endif

#ifndef GETBF
#define GETBF(bfdef, val)			\
	((val >> _BFSHIFT(bfdef)) & ((1 << _BFSIZE(bfdef)) - 1))
#endif

/*******************************************************************************
 * clear bit and set bit macros
 * 	We do this a lot, set individual bits and clear individual bits
 */
#define sbi(reg, bit_number)    reg |= _BV(bit_number)
#define cbi(reg, bit_number)    reg &= ~_BV(bit_number)
#define tgl(reg, bit_number)	reg ^= (1<<bit_number)
/******************************************************************************/

/*******************************************************************************
 * Useful Masking macros
 */
#define HIGH_BYTE(x)		(x>>8)
#define LOW_BYTE(x)		(x&0xFF)
/******************************************************************************/

#endif /* I__BITFIELD_H__ */
