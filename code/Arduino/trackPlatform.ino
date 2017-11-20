#include "connection/DebugSerial.h"
#include "management/MainManager.h"
#include "connection/ConnectionManager.h"
#include "config/CommandsEnum.h"

void setup()
{
	DEBUG_PRINTF("Firmware was compiled on %s %s\n", __DATE__, __TIME__);
	DEBUG_PRINTF("Supports API from %d to %d\n", APIWithCRC, APIWithCRC);

	DEBUG_PRINTLN("Trying to start Arduino");

	// First init of static fields
	MainManager::get_manager();
	ConnectionManager::get_manager();

	DEBUG_PRINTLN("Arduino was started");
}

void loop()
{
	MainManager::get_manager()->run();
}
