#include "../LoggerLib/LoggerLib.h"

int main()
{
	ChannelFile channel1(Severity::None, Severity::Error);
	ChannelConsole channel2;
	ILoggerChannel* t[2] = { &channel1, &channel2 };
	DoubleList<ILoggerChannel*> chlist(t, 2);
	MyLogger logger(&chlist);
	Message mess;
	mess.text = "tes33";
	mess.severity = Severity::Error;
	logger.writeToChannels(mess);
}