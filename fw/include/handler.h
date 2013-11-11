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

#include <avr/io.h> 

#ifndef I__HANDLER_H__
#define I__HANDLER_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cpluspuls */

/* number of functions handler can handle */
#define HANDLER_MAX 8

/* prescale timer by 1 */
#define TCCR0_VAL 0x01

#ifndef ENABLE
#define ENABLE 1
#endif
#ifndef DISABLE 
#define DISABLE 0
#endif

struct pool {
	void (*handler)(void); 
	volatile uint32_t cnt_start;
	volatile uint32_t cnt;
	uint8_t priority;
	uint8_t mask;
};

/**
 * scheduler_init() initializes routines and timers for the interrupt handler
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void scheduler_init(void);

/**
 * scheduler_disable() turns off the interrupt handler
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void scheduler_disable(void);

/**
 * reg_handler() registers a timed interrupt request with the interrupt handler
 *
 * @param fptr     - function pointer to the handler function
 * @param s_cnt    - start count of thi timer
 * @param msk      - ENABLE/DISABLE
 *
 * @return      None.
 */
void reg_handler(void* fptr, uint32_t s_cnt, uint8_t msk);

/**
 * update_reg_handler() ability to enable/disable handlers
 *
 * @param fptr  - function pointer to the handler function
 * @param s_cnt - start count of thi timer
 * @param msk   - ENABLE/DISABLE
 *
 * @return      None.
 */
void update_reg_handler(void* fptr, unsigned long s_cnt, unsigned char msk);

/**
 * set_all_handlers() ability to enable/disable handlers
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void set_all_handlers(uint8_t mask);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* I__HANDLER_H__ */
