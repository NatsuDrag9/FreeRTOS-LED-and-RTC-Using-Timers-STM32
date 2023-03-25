#include "main.h"

void process_command(command_t* cmd);
int extract_command(command_t* cmd);
uint8_t getnumber(uint8_t*, uint8_t);

const char* invalid_msg = "\n//// Invalid Option ////\n";

void menu_task_handler(void* parameters){
	uint32_t cmd_addr;
	command_t* cmd;
	uint8_t option;

	const char* main_menu_msg = "\n==================\n"
								"|      Menu      |\n"
								"==================\n"
									"LED Effect ----> 0\n"
									"Date and Time ----> 1\n"
									"Exit ----> 2\n"
									"Enter your choice here: ";

	while(1){
		xQueueSend(q_data_print, &main_menu_msg, portMAX_DELAY);

		// Waits to receive notification from cmd_task_handler
		xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);

		cmd = (command_t*)cmd_addr;
		if (cmd->length == 1){
			option = cmd->payload[0] - 48;	// ASCII to integer

			switch(option){
				case 0:
					current_state = state_LedEffect;
					xTaskNotify(handle_led_task, 0, eNoAction);
					break;

				case 1:
					current_state = state_RtcMenu;
					xTaskNotify(handle_rtc_task, 0, eNoAction);
					break;

				case 2:
					// Breaks to exit implementation
					break;

				default:
					xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
					continue;//			else if (!strcmp((char*)cmd->payload, "exit")){
					//				// Update the state variable
					//				current_state = state_MainMenu;
					//
					//				// Notify main menu task
					//				xTaskNotify(handle_menu_task, 0, eNoAction);
					//				break;
					//			}
			}
		}
		else{
			// Invalid entry
			xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
		}

		// Exit implementation of main menu is to wait and go back to while loop
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
	}
}

void cmd_task_handler(void* parameters){

	BaseType_t ret;
	command_t cmd;


	while(1){
		// Waits for the notification from UART
		ret = xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

		// Processes the received user data (command for other tasks) stored in the data_input_queue
		if (ret == pdTRUE){
			process_command(&cmd);
		}

	}
}

void process_command(command_t* cmd){
	extract_command(cmd);

	switch(current_state){
		// Sends notification to relevant task
		case state_MainMenu:
			xTaskNotify(handle_menu_task, (uint32_t)cmd, eSetValueWithOverwrite);
			break;

		case state_LedEffect:
			xTaskNotify(handle_led_task, (uint32_t)cmd, eSetValueWithOverwrite);
			break;

		case state_RtcMenu:
		case state_RtcTimeConfig:
		case state_RtcReport:
			xTaskNotify(handle_rtc_task, (uint32_t)cmd, eSetValueWithOverwrite);
			break;
		default:
			// do nothing
			break;
	}
}

int extract_command(command_t* cmd){
	uint8_t item;
	BaseType_t status;

	// Checks whether queue has any messages or not
	status = uxQueueMessagesWaiting(q_data_input);
	if (!status){
		// Queue is empty
		return -1;
	}

	// Stores the received data as command in payload
	uint8_t i = 0;
	do{
		status = xQueueReceive(q_data_input, &item, 0);
		if (status == pdTRUE){
			cmd->payload[i++] = item;
		}
	} while (item != '\r');

	// Replace '\r' with '\0' and stores the length without '\r'
	cmd->payload[i-1] = '\0';
	cmd->length = i-1;

	return 0;
}


void led_task_handler(void* parameters){
	uint32_t cmd_addr;
	command_t* cmd;

	const char* led_menu_msg = "==================\n"
								"|    LED Effect   |\n"
								"===================\n"
									"(none, e1, e2, e3) \n"
									"Enter your choice here: ";

	// Waits for notification from main menu task initially
//	xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

	while(1){
		// Waits for notification from main menu task
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

		// Print LED menu
		xQueueSend(q_data_print, &led_menu_msg, portMAX_DELAY);

		// Wait for LED command from user
		xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);
		cmd = (command_t*)cmd_addr;

		if(cmd->length <= 4){
			// Max length of user input characters can only be length of "none"
			if(!strcmp((char*)cmd->payload, "none")) {
				led_effect_stop();
			}
			else if(!strcmp((char*)cmd->payload, "e1")){
				led_effect(1);
			}
			else if(!strcmp((char*)cmd->payload, "e2")){
				led_effect(2);
			}
			else if(!strcmp((char*)cmd->payload, "e3")){
				led_effect(3);
			}
			else{
				// Else print invalid message
				xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
			}
		}
		else {
			// Print invalid message when user input length > 4
			xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
		}
		// Update the state variable
		current_state = state_MainMenu;

		// Notify main menu task
		xTaskNotify(handle_menu_task, 0, eNoAction);
	}

}

// Converts the received number from ASCII to decimal
uint8_t getnumber(uint8_t* p, uint8_t len){
	uint8_t value = 0;
	if (len > 1){
		value = (p[0]-48)*10 + p[1]-48;
	}
	else{
		value = p[0]-48;
	}
	return value;
}

void rtc_task_handler(void* parameters){
	const char* rtc_msg = "==================\n"
								"|       RTC       |\n"
								"===================\n";

	const char* rtc_menu_msg =	"\nConfigure Time    ------> 0\n"
								"Configure Date    ------> 1\n"
								"Enable Reporting  ------> 2\n"
								"Exit              ------> 3\n"
								"Enter your choice here: ";

	const char* rtc_hour_msg = "Enter hour(1-12): ";
	const char* rtc_min_msg = "Enter minutes(0-59): ";
	const char* rtc_sec_msg = "Enter seconds(0-59): ";
	const char* rtc_timeFormat_msg = "Enter AM/PM: ";

	const char* rtc_date_msg = "Enter date(1-31): ";
	const char* rtc_month_msg = "Enter month(1-12): ";
	const char* rtc_dow_msg = "Enter day of week(1-7 Sun=1): ";
	const char* rtc_year_msg = "Enter year(0-99): ";

	const char* rtc_msg_config = "Configuration Successful";
	const char* rtc_msg_report = "Enable time&date reporting(y/n)? ";

	uint32_t cmd_addr;
	command_t* cmd;
	static int rtc_time_state = 0;
	static int rtc_date_state = 0;
	int menu_code;
	RTC_TimeTypeDef rtc_time;
	RTC_DateTypeDef rtc_date;
//	char* str = "dummy";

	while(1){
		// Waits for notification from main menu task
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

		// Print RTC menu and show current time and date information
		xQueueSend(q_data_print, &rtc_msg, portMAX_DELAY);
		show_date_time();
		xQueueSend(q_data_print, &rtc_menu_msg, portMAX_DELAY);

		while (current_state != state_MainMenu){
			// Wait for RTC command from user
			xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);
			cmd = (command_t*)cmd_addr;

			switch(current_state){
				case state_RtcMenu:
					// Sets the current_state to RTC menu options based on user input
					// Takes care of invalid inputs from the user
					if (cmd->length == 1){
						menu_code = cmd->payload[0] - 48;
						switch(menu_code){
							case 0:
								current_state = state_RtcTimeConfig;
								xQueueSend(q_data_print, &rtc_hour_msg, portMAX_DELAY);
								break;
							case 1:
								current_state = state_RtcDateConfig;
								xQueueSend(q_data_print, &rtc_date_msg, portMAX_DELAY);
								break;
							case 2:
								current_state = state_RtcReport;
								xQueueSend(q_data_print, &rtc_msg_report, portMAX_DELAY);
								break;
							case 3:
								current_state = state_MainMenu;
								break;
							default:
								current_state = state_MainMenu;
								xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
								break;
						}
					}
					else {
						current_state = state_MainMenu;
						xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
					}
					break;

				case state_RtcTimeConfig:
					switch (rtc_time_state){
					// Gets the previously asked hh input from the user
					// Gets min and ss input from the user
					// Invalid cases are considered
						case HH_CONFIG:
							rtc_time.Hours = getnumber(cmd->payload, cmd->length);
							rtc_time_state = MM_CONFIG;
							xQueueSend(q_data_print, &rtc_min_msg, portMAX_DELAY);
							break;

						case MM_CONFIG:
							rtc_time.Minutes = getnumber(cmd->payload, cmd->length);
							rtc_time_state = SS_CONFIG;
							xQueueSend(q_data_print, &rtc_sec_msg, portMAX_DELAY);
							break;

						case SS_CONFIG:
							rtc_time.Seconds = getnumber(cmd->payload, cmd->length);
							rtc_time_state = TIME_FORMAT_CONFIG;
							xQueueSend(q_data_print, &rtc_timeFormat_msg, portMAX_DELAY);
							break;

						case TIME_FORMAT_CONFIG:
							if (!strcmp((char*)cmd->payload, "AM")){
								rtc_time.TimeFormat = RTC_HOURFORMAT12_AM;
							}
							else if (!strcmp((char*)cmd->payload, "PM")){
								rtc_time.TimeFormat = RTC_HOURFORMAT12_PM;
							}
							if (!validate_rtc(&rtc_time, NULL)){
								rtc_config_time(&rtc_time);
								xQueueSend(q_data_print, &rtc_msg_config, portMAX_DELAY);
								show_date_time();
							}
							else {
								xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
								rtc_time_state = 0;
							}
							current_state = state_MainMenu;
							break;

						default:
							// do nothing
							break;
					}
					break;

				case state_RtcDateConfig:
					switch (rtc_date_state){
					// Gets the previously asked date input from the user
					// Gets mm and yy input from the user
					// Invalid cases are considered
						case DATE_CONFIG:
							rtc_date.Date = getnumber(cmd->payload, cmd->length);
							rtc_date_state = MONTH_CONFIG;
							xQueueSend(q_data_print, &rtc_month_msg, portMAX_DELAY);
							break;

						case MONTH_CONFIG:
							rtc_date.Month = getnumber(cmd->payload, cmd->length);
							rtc_date_state = DAY_CONFIG;
							xQueueSend(q_data_print, &rtc_dow_msg, portMAX_DELAY);
							break;

						case DAY_CONFIG:
							rtc_date.WeekDay = getnumber(cmd->payload, cmd->length);
							rtc_date_state = YEAR_CONFIG;
							xQueueSend(q_data_print, &rtc_year_msg, portMAX_DELAY);
							break;

						case YEAR_CONFIG:
							rtc_date.Year = getnumber(cmd->payload, cmd->length);
							if (!validate_rtc(NULL, &rtc_date)){
								rtc_config_date(&rtc_date);
								xQueueSend(q_data_print, &rtc_msg_config, portMAX_DELAY);
								show_date_time();
							}
							else {
								xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
								rtc_date_state = 0;
							}
							current_state = state_MainMenu;
							break;

						default:
							// do nothing
							break;
					}
					break;

				case state_RtcReport:
					// Start rtc_timer when user input is 'y' else stop
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					if (cmd->length == 1){
						if (cmd->payload[0] == 'y'){
							if(xTimerIsTimerActive(rtc_timer) == pdFALSE){
								xTimerStart(rtc_timer, portMAX_DELAY);
							}
							else if(cmd->payload[0] == 'n'){
								xTimerStop(rtc_timer, portMAX_DELAY);
							}
							else {
								xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
							}
						}
					}
					else{
						xQueueSend(q_data_print, &invalid_msg, portMAX_DELAY);
					}
					current_state = state_MainMenu;
					break;

				default:
					// do nothing
					break;
			} // main switch ends

		} // current_state while loop ends

		// Notifies main menu task
		xTaskNotify(handle_menu_task, 0, eNoAction);

	} // main while loop ends
}

void print_task_handler(void* parameters){
	uint32_t* msg;
	while(1){
		xQueueReceive(q_data_print, &msg, portMAX_DELAY);
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen((char*)msg), HAL_MAX_DELAY);
	}
}
