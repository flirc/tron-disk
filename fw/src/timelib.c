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

#include <stdint.h>
#include <avr/interrupt.h>
#include <prjutil.h>
#include <timelib.h>
#include <bitfield.h>

static volatile uint64_t time;
static struct timeval timer_not_safe;

uint64_t
time_elapsed_ms(const struct timeval *start)
{
	struct timeval now;
	uint64_t msdiff;

	gettimeofday(&now, NULL);
	msdiff = now.tv_msec - start->tv_msec;

	return msdiff;
}

int
time_has_elapsed_ms(const struct timeval *start, uint64_t ms)
{
	return (time_elapsed_ms(start) >= ms);
}

uint64_t
gettimeofday(struct timeval *t, const struct timezone *tz)
{
	t->tv_msec = time;
	return 0;
}

void
timer_start(void)
{
	sbi(TCCR1B, WGM12);  /* CTC Mode */
	sbi(TCCR1C, FOC1A);  /* Force output compare */
	cbi(TCCR1B, CS12);    /* /64 prescalar */
	sbi(TCCR1B, CS11);    /* /64 prescalar */
	sbi(TCCR1B, CS10);    /* /64 prescalar */
	sbi(TIMSK1, OCIE1A); /* Output compare match enable */
	OCR1A = 124;	     /* 1ms Timer */
}

void
timer_stop(void)
{
	cbi(TCCR1B, CS20);
	cbi(TCCR1B, CS21);
	cbi(TCCR1B, CS22);
	timer_reset();
}

void
timer_start_not_safe(void)
{
	gettimeofday(&timer_not_safe, NULL);
}

void
timer_reset(void)
{
	TCNT0 = 0;
}

int
time_has_elapsed_not_safe(uint64_t ms)
{
	return (time_elapsed_ms(&timer_not_safe) >= ms);
}

SIGNAL(TIMER1_COMPA_vect)
{
	sei();
	time += 1;
	sei();
}
