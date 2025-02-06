/*
 * Buttons.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Juliano
 */
#include <Buttons.h>
#include <Buttons_config.h>
#include <stdlib.h>

uint8_t** button_state;
uint8_t btn_ack = 0;
uint8_t btn_event = 0;
uint8_t btn_check_index = 0;
GPIO_TypeDef** btn_port;
uint16_t* btn_pin;
volatile uint32_t last_button_press_timer = 0;

#if NUM_OF_BUTTONS > MAX_BUTTON_NUMBER
#error Number of button exccedes MAX_BUTTON_NUMBER (8)
#endif
#if NUM_OF_BUTTONS < MIN_BUTTON_NUMBER
#error Number of buttons is below MIN_BUTTON_NUMBER (1)
#endif
#if BTN_ON_ACK > NUM_OF_READS
#error Ammount of ON states, exceedes NUM_OF_READS array
#endif
#if BTN_OFF_ACK > NUM_OF_READS
#error Ammount of OFF states, exceedes NUM_OF_READS array
#endif


static uint8_t ammount_of_on_states(uint8_t btn_num) {
	uint8_t result = 0;
	for(int i = 0; i < NUM_OF_READS; i++) {
		result += button_state[btn_num][i];
	}
	return result;
}


int8_t btn_init() {

    button_state = (uint8_t **)calloc(NUM_OF_BUTTONS, sizeof(uint8_t *));
    if (button_state == NULL) {
        return -1;
    }

    for (int i = 0; i < NUM_OF_BUTTONS; i++) {
        button_state[i] = (uint8_t *)calloc(NUM_OF_READS, sizeof(uint8_t));
        if (button_state[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(button_state[j]);
            }
            free(button_state);
            return -2;
        }
    }

	btn_port = (GPIO_TypeDef**)malloc(NUM_OF_BUTTONS * sizeof(GPIO_TypeDef*));
	btn_pin = (uint16_t*)malloc(NUM_OF_BUTTONS * sizeof(uint16_t));

	if (btn_port == NULL || btn_pin == NULL) {
		free(btn_port);
		free(btn_pin);
		return -3;
	}

#if NUM_OF_BUTTONS >= 1
	btn_port[0] = BUTTON_0_GPIO_Port;
	btn_pin[0] = BUTTON_0_Pin;
#endif
#if NUM_OF_BUTTONS >= 2
	btn_port[1] = BUTTON_1_GPIO_Port;
	btn_pin[1] = BUTTON_1_Pin;
#endif
#if NUM_OF_BUTTONS >= 3
	btn_port[2] = BUTTON_2_GPIO_Port;
	btn_pin[2] = BUTTON_2_Pin;
#endif
#if NUM_OF_BUTTONS >= 4
	btn_port[3] = BUTTON_3_GPIO_Port;
	btn_pin[3] = BUTTON_3_Pin;
#endif
#if NUM_OF_BUTTONS >= 5
	btn_port[4] = BUTTON_4_GPIO_Port;
	btn_pin[4] = BUTTON_4_Pin;
#endif
#if NUM_OF_BUTTONS >= 6
	btn_port[5] = BUTTON_5_GPIO_Port;
	btn_pin[5] = BUTTON_5_Pin;
#endif
#if NUM_OF_BUTTONS >= 7
	btn_port[6] = BUTTON_6_GPIO_Port;
	btn_pin[6] = BUTTON_6_Pin;
#endif
#if NUM_OF_BUTTONS >= 8
	btn_port[7] = BUTTON_7_GPIO_Port;
	btn_pin[7] = BUTTON_7_Pin;
#endif
	return 0;
}

void btn_check_states() {

	if(btn_check_index >= NUM_OF_READS)	btn_check_index = 0;

	for(int i = 0; i < NUM_OF_BUTTONS; i++) {
#ifdef	IDLE_HIGH
		button_state[i][btn_check_index] = !HAL_GPIO_ReadPin(btn_port[i], btn_pin[i]);
#else
		button_state[i][btn_check_index] = HAL_GPIO_ReadPin(btn_port[i], btn_pin[i]);
#endif
	}

	for(int i = 0; i < NUM_OF_BUTTONS; i++) {
		if(ammount_of_on_states(i) >= BTN_ON_ACK && (btn_ack >> i & 1) == 0) {
			btn_ack |= 1<<i;
#ifndef ON_RELEASE
			btn_event |= (1<<i);
			last_button_press_timer = HAL_GetTick();
#endif
		}
		else if(ammount_of_on_states(i) <= (NUM_OF_READS - BTN_OFF_ACK) && (btn_ack>>i & 1) == 1) {
#ifdef ON_RELEASE
			btn_event |= (1<<i);
			last_button_press_timer = HAL_GetTick();
#endif
			btn_ack &= ~(1<<i);
		}
	}
	btn_check_index++;
}

uint8_t btn_event_num() {
	return btn_event;
}

uint8_t btn_clear_event(uint8_t event_num) {
	btn_event &= ~1<<event_num;
	return btn_event;
}

uint8_t btn_reset_event(void) {
	btn_event = 0;
	return btn_event;
}

