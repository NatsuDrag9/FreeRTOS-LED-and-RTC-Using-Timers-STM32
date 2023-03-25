#include "main.h"

void turn_off_all_leds(void);
void turn_on_all_leds(void);
void turn_on_even_leds(void);
void turn_on_odd_leds(void);

// Stops any active led effect and if no timer is active
// then nothing happens
void led_effect_stop(void){
	for(int i = 0; i < 3; i++){
		xTimerStop(handle_led_timers[i], portMAX_DELAY);
	}
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
}

// Starts the software timers that implement the led effects
void led_effect(int n){
	led_effect_stop();
	xTimerStart(handle_led_timers[n-1], portMAX_DELAY);
}

// LED Effect 1 -- Toggles all 3 LEDs
void LED_Effect1(void){
	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
//	static int flag = 1;
//	(flag ^= 1) ? turn_off_all_leds() : turn_on_all_leds();
}

// Turns off all LEDs
//void turn_off_all_leds(void){
//	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
//}

// Turns on all LEDs
//void turn_on_all_leds(void){
//	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
//}

// LED Effect 2 -- Alternatively toggles even and odd LEDs
void LED_Effect2(void){
	static int flag = 1;
	(flag ^= 1) ? turn_on_even_leds() : turn_on_odd_leds();
}

// Turns on even LEDs (i.e. LD2)
void turn_on_even_leds(void){
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
}

// Turns on odd LEDs (i.e. LD1 and LD3)
void turn_on_odd_leds(void){
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
}

// LED Effect 3
void LED_Effect3(void){
	static int i = 1;
	if (i%3 == 1){
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
	}
	else if (i%3 == 2){
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
	}
	else if (i%3 == 0){
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
	}
	else if (i > 3){
		i = 1;
		HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
	}
	i = i+1;
}
