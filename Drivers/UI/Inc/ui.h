/*
 * ui.h
 *
 *  Created on: Jan 24, 2025
 *      Author: Juliano
 */

#ifndef UI_INC_UI_H_
#define UI_INC_UI_H_

#include <stdint.h>
#include <main.h>
#include "ssd1306.h"

#define BUFFER_SIZE		32

void ui_read_buttons(void);

void oled_print(char* buffer, int x, int y, FontDef font);

void ui_update_program(void);
void ui_print_header(void);
void ui_print_body(void);

void ui_reset_buttons(void);
void ui_go_to_program(uint32_t program);
void ui_resolve_enter(uint32_t program);
void ui_resolve_back(uint32_t program);
void ui_resolve_plus(uint8_t program);
void ui_resolve_minus(uint8_t program);

#endif /* UI_INC_UI_H_ */
