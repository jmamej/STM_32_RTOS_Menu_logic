/*
 * Buttons.h
 *
 *  Created on: Oct 9, 2024
 *      Author: Juliano
 */
#ifndef BUTTONS_BUTTONS_H_
#define BUTTONS_BUTTONS_H_

#include <stdint.h>
#include <main.h>
#include <Buttons_config.h>

#define MAX_BUTTON_NUMBER	8
#define MIN_BUTTON_NUMBER	1

int8_t btn_init(void);
void btn_check_states(void);
uint8_t btn_event_num(void);
uint8_t btn_clear_event(uint8_t event_num);
uint8_t btn_reset_event(void);

#endif /* BUTTONS_BUTTONS_H_ */
