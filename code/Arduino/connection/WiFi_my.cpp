﻿#include "WiFi_my.h"
#include "DebugSerial.h"

WiFi_my::WiFi_my(unsigned long speed) :IConnector(&Serial2) {
	//Добавить вывод IP
	DEBUG_PRINTLN("Constructor wifi");
	if (is_inited_)
	{
		return;
	}
	is_inited_ = true;
	Serial2.begin(speed);
	is_server_started_ = false;
	DEBUG_PRINTLN("Constructor wifi2");
	for (uint32_t i = 0; i <= MAX_CONNECT_ID; i++) {
		connected_ids_[i] = NOT_CONNECTED;
	}
	start_tcp_server();
	DEBUG_PRINTLN("Constructor wifi3");
}

bool WiFi_my::start_tcp_server() {
	device_->print(SET_WIFI_MODE_COM);
	String answer = read_answer();
	if (!answer.startsWith(SET_WIFI_MODE_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		is_server_started_ = false;
		return false;
	}
	DEBUG_PRINTLN("WiFi_my mode was set.");

	device_->print(ENABLE_MULTIPLE_CONNECTION_COM);
	answer = read_answer();
	if (!answer.startsWith(ENABLE_MULTIPLE_CONNECTION_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		is_server_started_ = false;
		return false;
	}
	DEBUG_PRINTLN("multiple connection was set.");

	device_->print(SETUP_SERVER_COM);
	answer = read_answer();
	if (!answer.startsWith(SETUP_SERVER_COM) && !answer.endsWith(POSITIVE_ANSWER)) {
		is_server_started_ = false;
		return false;
	}
	DEBUG_PRINTLN("server started.");
	DEBUG_PRINTLN("Port: " + PORT);
	device_->print(GET_IP_MAC);
	answer = read_answer();
	String ip = answer.substring(answer.indexOf("+CIFSR:APIP,\"") + String("+CIFSR:APIP,\"").length(),
		answer.indexOf("+CIFSR:APMAC,") - 3);
	DEBUG_PRINTLN("IP: " + ip);
	is_server_started_ = true;
	return true;
}

void WiFi_my::stop_connection(int id) {
	device_->print(DELETE_TCP_CONNECTION + String(char(id)) + EOC);
	String answer = read_answer();
	if (!answer.endsWith(POSITIVE_ANSWER)) {
		DEBUG_PRINTLN("Error in deleting the connection.(stopConnection method).");
	}
}

String WiFi_my::read_answer() {
	char buf[BUFFER_SIZE];
	for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (device_->available()) {
			device_->readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	DEBUG_PRINTLN("Read ans: " + String(buf));
	return String(buf);
}

int WiFi_my::wait_client() {
	String answer = read_answer();
	String str_number = answer.substring(0, answer.indexOf(",CONNECT"));
	int num = atoi(str_number.c_str());
	return num;
}

bool WiFi_my::is_need_to_read_message() {
	//DEBUG_PRINTLN("IMPORTANT: " + String((int)'\|'));
	//DEBUG_PRINTLN(String(__LINE__));
	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
	if (device_->available()) {
		device_->readBytes(buf, BUFFER_SIZE);
	}
	else {
		return !data_buffer_.isEmpty();
	}
	String buf_str(buf);
	if (buf_str.startsWith("\r\n")) {
		buf_str = buf_str.substring(2);
	}
	//DEBUG_PRINTLN("Buf: ");
	//DEBUG_PRINTLNHEX(bufStr);
	String sub_str = buf_str.substring(0, buf_str.indexOf("\r\n"));
	//uint32_t starOfNewSubstr = bufStr.indexOf("\r\n") + 2;
	while (buf_str.indexOf("\r\n") != -1) {
		//DEBUG_PRINT("SubStr: ");
		//DEBUG_PRINTLNHEX(subStr);
		if (sub_str.indexOf(",CONNECT") != -1) {
			String str_number = sub_str.substring(0, sub_str.indexOf(",CONNECT"));
			uint32_t num = str_number.toInt();
			connected_ids_[num] = CONNECTED;
			DEBUG_PRINTLN("Connected: " + String(num));
		}
		else if (sub_str.indexOf(",CLOSED") != -1) {
			String str_number = sub_str.substring(0, sub_str.indexOf(",CLOSED"));
			uint32_t num = str_number.toInt();
			connected_ids_[num] = NOT_CONNECTED;
			DEBUG_PRINTLN("Disconnected: " + String(num));
		}
		else if (sub_str.indexOf("+IPD,") != -1) {
			String data = sub_str.substring(sub_str.indexOf(":") + 1);
			if (data.length()) {
				data_buffer_.push(data);
				DEBUG_PRINT("Get data: ");
				DEBUG_PRINTLNHEX(data);
			}
		}
		//...

		buf_str = buf_str.substring(buf_str.indexOf("\r\n") + 2);
		sub_str = buf_str.substring(0, buf_str.indexOf("\r\n"));
	}
	//DEBUG_PRINTLN(String(__LINE__));
	return !data_buffer_.isEmpty();
}

String WiFi_my::get_message() {
	char buf[BUFFER_SIZE];
	for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
		buf[i] = 0;
	}
	while (true) {
		if (device_->available()) {
			device_->readBytes(buf, BUFFER_SIZE);
			break;
		}
	}
	String data = String(buf);
	DEBUG_PRINTLN("Read: " + data);
	int infoStartIndex = data.indexOf(":") + 1;
	String info = data.substring(infoStartIndex);
	return info;
}

void WiFi_my::write_answer(String data) {
	if (!data.length()) {
		return;
	}
	String command = SEND_BUFFER_COM + data.length() + EOC;					// may be space needed.(between command and length.)
	device_->print(command);
	String answer = read_answer();
	/*if (!answer.endsWith(">")) {
		DEBUG_PRINTLN("Can't send info.(method send)");
		isServerStarted = false;
		return;
	}*/
	device_->print(data);
	answer = read_answer();
	if (!answer.endsWith("SEND OK" + EOC)) {
		DEBUG_PRINTLN("Error in answer(method send)");
	}
}

String WiFi_my::read_message() {

	if (!data_buffer_.isEmpty()) {
		String data = data_buffer_.pop();
		//data = data.substring(0, data.indexOf("|"));
		DEBUG_PRINT("FROM VECTOR: ");
		DEBUG_PRINTLNHEX(data);
		return data;
	}
	return String();
}