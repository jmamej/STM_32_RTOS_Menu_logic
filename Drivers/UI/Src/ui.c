/*
 * ui.c
 *
 *  Created on: Jan 24, 2025
 *      Author: Juliano
 */
#include <stdlib.h>
#include <stdio.h>
#include "ui.h"
#include "buttons.h"


uint8_t b_enter, b_back, b_plus, b_minus;
uint8_t program;

char oled_buffer[BUFFER_SIZE] = {0};

//if button press was acknowledged, b_button will be set;
void ui_read_buttons(void){
	for(int i = 0; i < NUM_OF_BUTTONS; i++){
		if(btn_event_num() >> i & 1){
			switch(i){
			case 0:
				b_enter = 1;
				break;
			case 1:
				b_back = 1;
				break;
			case 2:
				b_plus = 1;
				break;
			case 3:
				b_minus = 1;
				break;
			}
			btn_clear_event(i);
		}
	}
}

void ui_update_program(void){
	switch(program){
	case 0x00:
		ui_resolve_enter(0x01);
		ui_resolve_plus(0x10);
		ui_resolve_minus(0x30);
		break;
	case 0x01:
		ui_resolve_back(0x00);
		break;
	case 0x10:
		ui_resolve_enter(0x11);
		ui_resolve_back(0x00);
		ui_resolve_plus(0x20);
		ui_resolve_minus(0x00);
		break;
	case 0x11:
		ui_resolve_enter(0x12);
		ui_resolve_back(0x10);
		ui_resolve_plus(0x13);
		ui_resolve_minus(0x15);
		break;
	case 0x12:
		ui_resolve_back(0x11);
		break;
	case 0x13:
		ui_resolve_enter(0x14);
		ui_resolve_back(0x10);
		ui_resolve_plus(0x15);
		ui_resolve_minus(0x11);
		break;
	case 0x14:
		ui_resolve_back(0x13);
		break;
	case 0x15:
		ui_resolve_enter(0x16);
		ui_resolve_back(0x10);
		ui_resolve_plus(0x11);
		ui_resolve_minus(0x13);
		break;
	case 0x16:
		ui_resolve_back(0x15);
		break;
	case 0x20:
		ui_resolve_enter(0x21);
		ui_resolve_back(0x00);
		ui_resolve_plus(0x30);
		ui_resolve_minus(0x10);
		break;
	case 0x21:
		ui_resolve_enter(0x22);
		ui_resolve_back(0x20);
		ui_resolve_plus(0x25);
		ui_resolve_minus(0x25);
		break;
	case 0x22:
		ui_resolve_back(0x21);
		ui_resolve_plus(0x23);
		ui_resolve_minus(0x24);
		break;
	case 0x23:
		ui_resolve_back(0x21);
		ui_resolve_plus(0x24);
		ui_resolve_minus(0x22);
		break;
	case 0x24:
		ui_resolve_back(0x21);
		ui_resolve_plus(0x22);
		ui_resolve_minus(0x23);
		break;
	case 0x25:
		ui_resolve_enter(0x26);
		ui_resolve_back(0x20);
		ui_resolve_plus(0x21);
		ui_resolve_minus(0x21);
		break;
	case 0x26:
		ui_resolve_back(0x25);
		ui_resolve_plus(0x27);
		ui_resolve_minus(0x28);
		break;
	case 0x27:
		ui_resolve_back(0x25);
		ui_resolve_plus(0x28);
		ui_resolve_minus(0x26);
		break;
	case 0x28:
		ui_resolve_back(0x25);
		ui_resolve_plus(0x26);
		ui_resolve_minus(0x27);
		break;
	case 0x30:
		ui_resolve_enter(0x31);
		ui_resolve_back(0x00);
		ui_resolve_plus(0x00);
		ui_resolve_minus(0x20);
		break;
	case 0x31:
		ui_resolve_back(0x30);
		ui_resolve_plus(0x32);
		ui_resolve_minus(0x33);
		break;
	case 0x32:
		ui_resolve_back(0x30);
		ui_resolve_plus(0x33);
		ui_resolve_minus(0x31);
		break;
	case 0x33:
		ui_resolve_back(0x30);
		ui_resolve_plus(0x31);
		ui_resolve_minus(0x32);
		break;
	default:
		ui_go_to_program(0x00);
		break;
	}
	ui_reset_buttons();
}
//Font_11x18	Font_7x10
//handles oled header
void ui_print_header(void){
		sprintf(oled_buffer, "Program: 0x%.2X", program);
		oled_print(oled_buffer, 2, 0, Font_7x10);
}

//handles ui body - main logic
void ui_print_body(void){
	switch(program){
	case 0x00:
		sprintf(oled_buffer, "Main");
		break;
	case 0x01:
		sprintf(oled_buffer, "Sub main");
		break;
	case 0x10:
		sprintf(oled_buffer, "P1");
		break;
	case 0x11:
		sprintf(oled_buffer, "P1 sub 1.0");
		break;
	case 0x12:
		sprintf(oled_buffer, "P1 sub 1.1");
		break;
	case 0x13:
		sprintf(oled_buffer, "P1 sub 2.0");
		break;
	case 0x14:
		sprintf(oled_buffer, "P1 sub 2.1");
		break;
	case 0x15:
		sprintf(oled_buffer, "P1 sub 3.0");
		break;
	case 0x16:
		sprintf(oled_buffer, "P1 sub 3.1");
		break;
	case 0x20:
		sprintf(oled_buffer, "P2");
		break;
	case 0x21:
		sprintf(oled_buffer, "P2 sub 1.0");
		break;
	case 0x22:
		sprintf(oled_buffer, "P2 sub 1.1");
		break;
	case 0x23:
		sprintf(oled_buffer, "P2 sub 1.2");
		break;
	case 0x24:
		sprintf(oled_buffer, "P2 sub 1.3");
		break;
	case 0x25:
		sprintf(oled_buffer, "P2 sub 2.0");
		break;
	case 0x26:
		sprintf(oled_buffer, "P2 sub 2.1");
		break;
	case 0x27:
		sprintf(oled_buffer, "P2 sub 2.2");
		break;
	case 0x28:
		sprintf(oled_buffer, "P2 sub 2.3");
		break;
	case 0x30:
		sprintf(oled_buffer, "P3");
		break;
	case 0x31:
		sprintf(oled_buffer, "P3 sub 1.0");
		break;
	case 0x32:
		sprintf(oled_buffer, "P3 sub 2.0");
		break;
	case 0x33:
		sprintf(oled_buffer, "P3 sub 3.0");
		break;
	default:
		sprintf(oled_buffer, "Default");
		break;
	}
	oled_print(oled_buffer, 8, 26, Font_11x18);
}

//if certain button is not accepted in certain program, it will not keep its state until it is accepted. Prevents going into unwanted program.
void ui_reset_buttons(void){
	b_enter = 0;
	b_back = 0;
	b_plus = 0;
	b_minus = 0;
}

//go to program - other condition
void ui_go_to_program(uint32_t program_id){
	program = program_id;
}

//go to program if button is pressed
void ui_resolve_enter(uint32_t program_id){
	if(b_enter)	program = program_id;
	b_enter = 0;
}

void ui_resolve_back(uint32_t program_id){
	if(b_back)	program = program_id;
	b_back = 0;
}

void ui_resolve_plus(uint8_t program_id){
	if(b_plus)	program = program_id;
	b_plus = 0;
}

void ui_resolve_minus(uint8_t program_id){
	if(b_minus)	program = program_id;
	b_minus = 0;
}

void oled_print(char* buffer, int x, int y, FontDef font){
	ssd1306_SetCursor(x, y);
	ssd1306_WriteString(buffer, font);	//Font_11x18	Font_7x10
}

