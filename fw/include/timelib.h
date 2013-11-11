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

#ifndef I__TIMELIB_H__
#define I__TIMELIB_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cpluspuls */

/* time definitions */
struct timeval {
	uint64_t tv_sec;
	uint64_t tv_msec;
};

/* not supported */
struct timezone {
        int     tz_minuteswest; /* minutes west of Greenwich */
        int     tz_dsttime;     /* type of dst correction */
};

/**
 * time_elapsed_ms() returns back the ms elapsed
 *
 * @param - timeval - captured starting point of the timer
 *
 * @return - time elapsed
 */
uint64_t time_elapsed_ms(const struct timeval *start);

/**
 * time_has_elapsed()  returns boolean if time parameter has passed
 *
 * @param - timeval - captured starting point of the timer
 * @param - ms      - amount of time to pass
 *
 * @return - Boolean - True if time has passed
 */
int time_has_elapsed_ms(const struct timeval *start, uint64_t ms);

/**
 * time_has_elapsed_not_safe()  returns boolean if time parameter has passed
 *
 * @param - timeval - captured starting point of the timer
 * @param - ms      - amount of time to pass
 *
 * @return - Boolean - True if time has passed
 */
int
time_has_elapsed_not_safe(uint64_t ms);

/**
 * gettimeofday() captures current value of timer
 *
 * @param - time - container for time
 * @param - tz - not used, kept for cross compatibility
 */
uint64_t gettimeofday(struct timeval *time, const struct timezone *tz);

/**
 * timer_start() starts the onboard clock, just a 3ms timer, does not keep time
 *
 * @param - none
 *
 * @return - none
 */
void timer_start(void);

/**
 * timer_stop() stops the 3ms timer
 *
 * @param - none
 *
 * @return - none
 */
void timer_stop(void);

/**
 * timer_start_not_safe() starts a timer that is not thread safe
 *
 * @param - none
 *
 * @return - none
 */
void timer_start_not_safe(void);

/**
 * timer_reset() starts a timer that is not thread safe
 *
 * @param - none
 *
 * @return - none
 */
void timer_reset(void);

#endif /* I__TIMELIB_H__ */
