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

#include <avr/wdt.h>
#include <avr/power.h>
#include <util/delay.h>

#include <prjutil.h>
#include <main.h>
#include <descriptors.h>
#include <bitfield.h>
#include <timelib.h>
#include <handler.h>
#include <led_effects.h>

#include <LUFA/Version.h>
#include <LUFA/Drivers/USB/USB.h>

/* Global Variables */
volatile uint8_t dataToSend[IN_EP_SIZE];
volatile uint8_t dataReceived[OUT_EP_SIZE];

static void forward_inner_on(void);
static void backward_off(void);

static void sw_init(void);
static void hw_init(void);

#define MAX_STATES	6
void switch_state(uint8_t state)
{
	switch (state) {
	case 0:
		hw_init();
		set_all_handlers(DISABLE);
		update_reg_handler(inner_glow_pwm, 1, ENABLE);
		update_reg_handler(outer_ring_spin, 200, ENABLE);
		update_reg_handler(glow_brightness, 100, ENABLE);
		break;
	case 1:
		set_all_handlers(DISABLE);
		update_reg_handler(inner_glow_pwm, 1, ENABLE);
		update_reg_handler(glow_brightness, 100, ENABLE);
		update_reg_handler(wave_brightness, 100, ENABLE);
		update_reg_handler(outer_glow_pwm, 1, ENABLE);
		break;
	case 2:
		set_all_handlers(DISABLE);
		update_reg_handler(inner_glow_pwm, 1, ENABLE);
		update_reg_handler(glow_brightness, 175, ENABLE);
		update_reg_handler(wave_brightness, 175, ENABLE);
		update_reg_handler(outer_glow_ph_pwm, 1, ENABLE);
		break;
	case 3:
		set_all_handlers(DISABLE);
		update_reg_handler(inner_glow_pwm, 1, ENABLE);
		update_reg_handler(glow_brightness,100, ENABLE);
		update_reg_handler(wave_brightness,100, ENABLE);
		update_reg_handler(outer_wave_pwm, 1, ENABLE);
		break;
	case 4:
		set_all_handlers(DISABLE);
		update_reg_handler(outer_wave_pwm, 1, ENABLE);
		update_reg_handler(wave_brightness,30, ENABLE);
		update_reg_handler(inner_wave_pwm, 1, ENABLE);
		break;
	case 5:
		set_all_handlers(DISABLE);
		backward_off();
		break;
	default:
		state = 0;
		update_reg_handler(outer_wave_pwm, 1, DISABLE);
		update_reg_handler(outer_glow_pwm, 1, DISABLE);
		break;
	}
}

int main(void)
{
	volatile uint8_t state = 0;
	struct timeval s;

	timer_start();
	gettimeofday(&s, NULL); 

	sw_init();

	reg_handler(inner_glow_pwm, 1, DISABLE);
	reg_handler(outer_wave_pwm, 1, DISABLE);
	reg_handler(inner_wave_pwm, 1, DISABLE);
	reg_handler(outer_glow_pwm, 1, DISABLE);
	reg_handler(outer_glow_ph_pwm, 1, DISABLE);
	reg_handler(outer_ring_spin, 200, DISABLE);

	reg_handler(glow_brightness,100, DISABLE);
	reg_handler(wave_brightness,100, DISABLE);

	switch_state(state++);
	while(1){
		if (time_has_elapsed_ms(&s, 1000)) {
			if (bit_is_clear(PINC, 6)) {
				switch_state(state++);
				gettimeofday(&s, NULL); 

				if (state == MAX_STATES)
					state = 0;
			}
		}

		Main_Task();
		USB_USBTask();
	}
}

/* IR - inner ring */
#define IR_DDR		DDRB
#define IR_PORT		PORTB
/* OR - outer ring */
#define OR_DDR		DDRD
#define OR_PORT		PORTD
#define ORH_DDR		DDRF
/* ORH - outer ring high (greater than 8 leds) */
#define ORH_PORT	PORTF
#define ORH_SHIFT	4

void output_leds(uint8_t in, int out)
{
	IR_PORT = in;
	OR_PORT = out;
	ORH_PORT = out>>(8-ORH_SHIFT);
}

void sw_init(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Disable JTAG and IVCE bits */
	MCUCR = (1 << JTD) | (1 << IVCE) | (0 << PUD);
	MCUCR = (1 << JTD) | (0 << IVSEL) | (0 << IVCE) | (0 << PUD);

	sbi(DDRF, 7);
	USB_Init();
	wave_init();
}

void hw_init(void)
{
	IR_DDR  = 0xFF;
	IR_PORT = 0x00;

	OR_DDR	= 0xFF;
	OR_PORT = 0x00;

	sbi(ORH_DDR, ORH_SHIFT);
	sbi(ORH_DDR, ORH_SHIFT+1);
	sbi(ORH_DDR, ORH_SHIFT+2);
	sbi(ORH_DDR, ORH_SHIFT+3);

	cbi(ORH_PORT, ORH_SHIFT);
	cbi(ORH_PORT, ORH_SHIFT+1);
	cbi(ORH_PORT, ORH_SHIFT+2);
	cbi(ORH_PORT, ORH_SHIFT+3);

	/* Input with internal Pullup */
	cbi(DDRC, 6);
	sbi(PORTC, 6);

	forward_inner_on();
	output_leds(0xFF, 0xFFFF);
	_delay_ms(1000);

	reset_outer_ring_spin();
	scheduler_init();
}

void EVENT_USB_Device_UnhandledControlRequest(void)
{
	if (USB_ControlRequest.bmRequestType == DEVICE_TO_HOST) {

		/* Send data to the host */
		Endpoint_ClearSETUP();

		switch (USB_ControlRequest.bRequest) {
			default:
				break;
		}

		/* Write data to the control endpoint */
		Endpoint_Write_Control_Stream_LE(&dataToSend,
				sizeof(dataToSend));

	        /* Finalize stream transfer or clear the host abort */
		Endpoint_ClearOUT();
	}

	if (USB_ControlRequest.bmRequestType == HOST_TO_DEVICE) {

		/* Acknowledge the SETUP packet, ready for data transfer */
		Endpoint_ClearSETUP();

		Endpoint_Read_Control_Stream_LE(&dataReceived,
				sizeof(dataReceived));

		switch (USB_ControlRequest.bRequest) {
			case UPGRADE:
				DDRD = 0xFF;
				PORTD = 0;
				DDRB = 0xFF; 
				PORTB = 0x0;
				DDRF = 0xFF;
				PORTF = 0;
				cli();
				UDCON = 1;
				USBCON = (1<<FRZCLK);
				UCSR1B = 0;
				_delay_ms(5);
#if defined(__AVR_AT90USB162__)                /* Teensy 1.0 */
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0;
    TIMSK0 = 0; TIMSK1 = 0; UCSR1B = 0;
    DDRB = 0; DDRC = 0; DDRD = 0;
    PORTB = 0; PORTC = 0; PORTD = 0;
    asm volatile("jmp 0x3E00");
#elif defined(__AVR_ATmega32U4__)              /* Teensy 2.0 */
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
    DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
    PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
    asm volatile("jmp 0x7E00");
#elif defined(__AVR_AT90USB646__)              /* Teensy++ 1.0 */
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
    DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
    PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
    asm volatile("jmp 0xFC00");
#elif defined(__AVR_AT90USB1286__)             /* Teensy++ 2.0 */
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
    DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
    PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
    asm volatile("jmp 0x1FC00");
#endif 
				break;
			case LEDS_OFF:
				PORTD = 0;
				PORTF = 0;
				PORTC = 0;
			default:
				break;
		}

		/* Finalize stream transfer to clear last packet from host */
		Endpoint_ClearIN();
	}

}

/** Sends data to the host */
void SendDataToHost(void)
{
	/* Select the IN Endpoint */
	Endpoint_SelectEndpoint(IN_EP);

	/* Check if IN Endpoint is ready for Read/Write */
	if (Endpoint_IsReadWriteAllowed())
	{
		/* Write data to the host */
		Endpoint_Write_Stream_LE(&dataToSend, 0);

		/* Finalize the stream transfer to send the last packet */
		Endpoint_ClearIN();
	}
}

/** Reads data from the host */
void ReceiveDataFromHost(void)
{
	/* Select the OUT Endpoint */
	Endpoint_SelectEndpoint(OUT_EP);

	/* Check if the OUT EP contains a packet */
	if (Endpoint_IsOUTReceived()) {
		/* Check to see if the packet contains data */
		if (Endpoint_IsReadWriteAllowed()) {
			/* Read in data from the host */
			Endpoint_Read_Stream_LE(&dataReceived,
					sizeof(dataReceived));
		}

		/* Handshake the OUT Endpoint */
		Endpoint_ClearOUT();
	}
}


static int on_time = 300;
static void forward_inner_on(void)
{
	int i = 0;
	uint8_t val = 1;
	for (i = 0; i < 8; i++) {
		output_leds(val, 0);	
		_delay_ms(on_time);

		if (val == 0x80)
			val = 0x01;
		else
			val = val << 1;
			val |= 1;
	}
}

static void backward_off(void)
{
	scheduler_disable();
	uint8_t inner = 0xFF;
	uint16_t outer = 0xFFF;
	output_leds(inner, outer);
	_delay_ms(500);

	int i = 0;
	for (i = 0; i < 12; i++) {
		outer = outer << 1;
		_delay_ms(on_time-125);
		output_leds(inner, outer);
	}

	for (i = 0; i < 8; i++) {
		inner = inner >> 1;
		_delay_ms(on_time);
		output_leds(inner, outer);
	}
}

void Main_Task(void)
{
	if (USB_DeviceState != DEVICE_STATE_Configured) {
		return;
	}

	ReceiveDataFromHost();

	SendDataToHost();
}
