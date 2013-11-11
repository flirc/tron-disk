/*
 * Copyright 2013 Jason Kotzin, Flirc Inc. All rights reserved.
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
 * official policies, either expressed or implied, of Jason Kotzin.
 */

#include <handler.h>
#include <avr/interrupt.h>
#include <bitfield.h>
#include <prjutil.h>

struct pool f_pool[HANDLER_MAX] = {{0}};

void scheduler_init(void)
{
	sbi(TCCR0B,CS00);
	cbi(TCCR0B,CS01);
	cbi(TCCR0B,CS02);
	sbi(TIMSK0,TOIE0);
	sei();
}

void scheduler_disable(void)
{
	cbi(TCCR0B,CS00);
	cbi(TCCR0B,CS01);
	cbi(TCCR0B,CS02);
}

SIGNAL(TIMER0_OVF_vect)
{
	uint8_t i;

	cli();
	cbi(TCCR0B,CS00);
	cbi(TCCR0B,CS01);
	cbi(TCCR0B,CS02);
	cbi(TIMSK0,TOIE0);

	for(i = 0; i < HANDLER_MAX; i++) {
		if (f_pool[i].mask == ENABLE && f_pool[i].handler != NULL) {
			f_pool[i].cnt--;
			if(!f_pool[i].cnt) {
				f_pool[i].handler();
				f_pool[i].cnt = f_pool[i].cnt_start;
			}
		}
	}

	sbi(TIMSK0, TOIE0);
	sbi(TCCR0B,CS00);
	cbi(TCCR0B,CS01);
	cbi(TCCR0B,CS02);
	sei();
}

void reg_handler(void *fptr, uint32_t s_cnt, uint8_t msk)
{
	uint8_t i;

	for (i = 0; i < HANDLER_MAX; i++) {
		if (f_pool[i].handler == NULL)
			break;
	}

	f_pool[i].mask = DISABLE;
	f_pool[i].handler = fptr;
	f_pool[i].cnt_start = s_cnt;
	f_pool[i].cnt = s_cnt;
}

void
update_reg_handler(void* fptr, uint32_t s_cnt, uint8_t msk)
{
	uint8_t i;

	for (i = 0; i < HANDLER_MAX; i++) {
		if (f_pool[i].handler == fptr) {
			f_pool[i].cnt_start = s_cnt;
			f_pool[i].mask = msk;
		}
	}
}

void
set_all_handlers(uint8_t mask)
{
	uint8_t i;

	for (i = 0; i < HANDLER_MAX; i++)
		f_pool[i].mask = mask;
}
