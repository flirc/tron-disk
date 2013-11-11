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

#ifndef I__LED_EFFECTS_H__
#define I__LED_EFFECTS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cpluspuls */

/**
 * wave_init() initialize the sine wave
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void wave_init(void);

/**
 * wave_brightness() this function is used to change the speed of the wave 
 * brightness.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void wave_brightness(void);

/**
 * glow_brightness() this function is used to change the speed of the glow
 * brightness functions.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void glow_brightness(void);

/**
 * outer_wave_pwm() this effect will look like a moving wave accross the outer
 * ring.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void outer_wave_pwm(void);

/**
 * outer_glow_pwm() this effect will make the outer ring glow in and out.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void outer_glow_pwm(void);

/**
 * inner_wave_pwm() this effect will look like a moving wave accross the inner
 * ring.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void inner_wave_pwm(void);

/**
 * inner_glow_pwm() this effect will make the inner ring glow in and out.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void inner_glow_pwm(void);

/**
 * outer_glow_ph_pwm() this effect will glow the outer ring out of phase of the
 * outer_glow_pwm.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void outer_glow_ph_pwm(void);

/**
 * outer_ring_spin() this effect will spin around the outer ring similar to the
 * effect in the movie tron.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void outer_ring_spin(void);

/**
 * reset_outer_ring_spin() Restore the outer ring spin LEDS that will rotate.
 * Call this before we do the spin.
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
void reset_outer_ring_spin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* I__LED_EFFECTS_H__ */
