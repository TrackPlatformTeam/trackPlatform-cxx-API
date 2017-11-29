#pragma once
#include <Arduino.h>

class Constants
{
public:
	// static const uint8_t bluetooth_RX;
	// static const uint8_t bluetooth_TX;
	static const uint32_t bluetooth_serial_speed;

	// static const uint8_t wifi_RX;
	// static const uint8_t wifi_TX;
	static const uint32_t wifi_serial_speed;

	// static const uint8_t usb_RX;
	// static const uint8_t usb_TX;
	static const uint32_t usb_serial_speed;

	//static const uint8_t dbg_uart_RX;
	//static const uint8_t dbg_uart_TX;
	static const uint32_t dbg_uart_speed;

	static const uint8_t left_engine_enable;
	static const uint8_t left_engine_straight_pin;
	static const uint8_t left_engine_reverse_pin;
	static const uint8_t right_engine_straight_pin;
	static const uint8_t right_engine_reverse_pin;
	static const uint8_t right_engine_enable;

	static const uint8_t distance_sensor_read_pin;
	static const uint8_t distance_sensor_a_pin;
	static const uint8_t distance_sensor_b_pin;
	static const uint8_t distance_sensor_c_pin;

	static const uint8_t line_sensor_read_pin;
	static const uint8_t line_sensor_a_pin;
	static const uint8_t line_sensor_b_pin;
	static const uint8_t line_sensor_c_pin;

	static const uint8_t servo_horizontal_pin;
	static const uint8_t servo_vertical_pin;

	static const char commands_delimetr;
	static const char commands_stop_symbol;
	static const uint32_t commands_wait_time;

	static const uint8_t min_speed;
	static const uint8_t max_speed;
	static const uint16_t servo_delay;

	static const uint8_t count_distance_sensors;
	static const int16_t distance_calculation_a;
	static const int16_t distance_calculation_b;

	static const uint8_t count_line_sensors;
	static const uint16_t minimal_line_bound;

	static const uint32_t wait_command_time_in_ms;

	static const String good_answer;
	static const String bad_answer;

	Constants();
	~Constants();
};
