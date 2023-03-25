#include "main.h"

// Prints the time and date in ITM (SWV console)
void show_date_time_itm(){
	RTC_DateTypeDef rtc_date;
	RTC_TimeTypeDef rtc_time;

	memset(&rtc_date, 0, sizeof(rtc_date));
	memset(&rtc_time, 0, sizeof(rtc_time));

	// Gets the time from the microcontroller's RTC
	HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
	// Gets the date from the microcontroller's RTC
	HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);

	// Extracts the time format
	char* timeFormat;
	timeFormat = (rtc_time.TimeFormat == RTC_HOURFORMAT12_AM) ? "AM" : "PM";

	// Displays the time in hh:mm:ss (AM/PM) by sending to queue
	printf("%s: \t%02d:%02d:%02d %s", "\nCurrent Time&Date", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds, timeFormat);

	// Displays the date in dd/mm/yyyy
	printf("\t%02d/%02d/%02d", rtc_date.Date, rtc_date.Month, 2000+rtc_date.Year);
}

// Prints the time and date in UART
void show_date_time(){
	static char showTime[40];
	static char showDate[40];

	RTC_DateTypeDef rtc_date;
	RTC_TimeTypeDef rtc_time;

	static char* time = showTime;
	static char* date = showDate;

	memset(&rtc_date, 0, sizeof(rtc_date));
	memset(&rtc_time, 0, sizeof(rtc_time));

	// Gets the time from the microcontroller's RTC
	HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
	// Gets the date from the microcontroller's RTC
	HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);

	// Extracts the time format
	char* timeFormat;
	timeFormat = (rtc_time.TimeFormat == RTC_HOURFORMAT12_AM) ? "AM" : "PM";

	// Displays the time in hh:mm:ss (AM/PM) by sending to queue
	sprintf((char*)showTime, "%s: \t%02d:%02d:%02d %s", "\nCurrent Time&Date", rtc_time.Hours, rtc_time.Minutes, rtc_time.Seconds, timeFormat);
	xQueueSend(q_data_print, (void*)&time, portMAX_DELAY);

	// Displays the date in dd/mm/yyyy
	sprintf((char*)showDate, "\t%02d/%02d/%02d", rtc_date.Date, rtc_date.Month, 2000+rtc_date.Year);
	xQueueSend(q_data_print, (void*)&date, portMAX_DELAY);

}

// Sets the time
void rtc_config_time(RTC_TimeTypeDef* time){
//	time->TimeFormat = RTC_HOURFORMAT12_AM;
	HAL_RTC_SetTime(&hrtc, time, RTC_FORMAT_BIN);
}

// Sets the date
void rtc_config_date(RTC_DateTypeDef* date){
	HAL_RTC_SetDate(&hrtc, date, RTC_FORMAT_BIN);
}

// Validates the RTC information received from the user
int validate_rtc(RTC_TimeTypeDef* time, RTC_DateTypeDef* date){
	if (time){
		if ((time->Hours > 12) || (time->Minutes > 59) || (time->Seconds > 59)){
			return 1;
		}
	}
	if (date){
		if ((date->Date > 31) || (date->Month > 12) || (date->Year > 99) || (date->WeekDay > 7)){
			return 1;
		}
	}
	return 0;
}
