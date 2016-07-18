/*
Helios Laser DAC main AS project (for SAM4S2B board)
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

Required Atmel Software Framework modules:
	DACC - Digital-to-Analog Converter
	Flash
	Generic Board Support (ATSAM4S2B)
	GPIO
	IOPORT
	SPI - Serial Peripheral Interface
	USB Device Vendor Class
	WDT - Watchdog Timer
*/

#ifndef MAIN_H_
#define MAIN_H_

#include "asf.h"
#include <malloc.h>

//macros
#define MAXSPEED 0xFFFF		//in pps	(65535)
#define MINSPEED 3			//in pps
#define MAXFRAMESIZE 0x1000	//in points (4096)

//global variables
uint16_t frameSize = 0;					//size of frame buffer in points
uint16_t framePos = 0;					//current position in frame in points
uint16_t newFrameSize = 0;				//incoming frame total size in points
bool newFrameReady = false;				//signals a new frame has been received and is ready to play when the current one ends
bool playing = false;					//signals a point should be output next systick
uint32_t outputSpeed = 20000;			//points per second rate
bool notRepeat = true;					//signals that current frame should be only be played once even if no new frame arrives before it ends
bool newNotRepeat = true;				//notRepeat value for pending frame

uint8_t* frameAddress;				//frame currently being played
uint8_t* newFrameAddress;			//pending frame waiting to be played
uint8_t* usbBulkBufferAddress;		//usb bulk transfer buffer
uint8_t* usbInterruptBufferAddress;	//usb interrupt transfer buffer

//functions
void speed_set(uint32_t rate);		//sets up the systick interrupt to match the playback rate (in pps)
void shutter_set(bool level);		//sets the shutter level
void statusled_set(bool level);		//sets the status LED level
void point_output(void);			//outputs current point (controlled by framePos and frameAddress variables)
void blank_and_center(void);		//blanks and centers output
void spi_init(void);				//sets up SPI module
void dac_init(void);				//sets up DACC module
void iopins_init(void);				//sets up IO module and pins

//USB transfer interrupts
void usb_bulk_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep);
void usb_interrupt_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep);

#endif /* MAIN_H_ */