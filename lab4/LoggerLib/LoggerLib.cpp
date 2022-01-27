#include "LoggerLib.h"

ILoggerChannel::ILoggerChannel() noexcept
{
	minSeverity = Severity::None;
	maxSeverity = Severity::Error;
}

ILoggerChannel::ILoggerChannel(Severity smin, Severity smax) noexcept
{
	minSeverity = smin;
	maxSeverity = smax;
}

Severity ILoggerChannel::minimumSeverity() const noexcept
{
	return minSeverity;
}

Severity ILoggerChannel::maximumSeverity() const noexcept
{
	return maxSeverity;
}

std::string ILoggerChannel::getContent() const noexcept
{
	return content;
}

ChannelConsole::ChannelConsole() noexcept
	:ILoggerChannel()
{
}

ChannelConsole::ChannelConsole(Severity smin, Severity smax) noexcept
	:ILoggerChannel(smin, smax)
{
}

ChannelConsole::ChannelConsole(Severity smin, Severity smax,std::stringstream& s) noexcept
	:ILoggerChannel(smin, smax)
{
	content += s.str();
	std::cout << s.str();
}

void ChannelConsole::write(Message mess) noexcept
{
	if (minimumSeverity() <= mess.severity && maximumSeverity() >= mess.severity)
	{
		content += mess.text;
		std::cout << mess.text << std::endl;
	}
}

ChannelFile::ChannelFile() noexcept
	:ILoggerChannel()
{
}

ChannelFile::ChannelFile(Severity smin, Severity smax) noexcept
	:ILoggerChannel(smin, smax)
{
}

ChannelFile::ChannelFile(Severity smin, Severity smax, std::string fName) noexcept
	:ILoggerChannel(smin, smax)
{
	fileName = fName;
}

void ChannelFile::write(Message mess) noexcept
{
	if (minimumSeverity() <= mess.severity && maximumSeverity() >= mess.severity)
	{
		content += mess.text;
		std::ofstream MyFile;
		MyFile.open(fileName, std::ios_base::app);
		MyFile << mess.text << std::endl;
		MyFile.close();
	}
	
}

MyLogger::MyLogger(DoubleList<ILoggerChannel*>* iList) noexcept
{
	channelList = iList;
}

void MyLogger::addChannel(ILoggerChannel* channel) noexcept
{
	channelList.append(channel);
}

void MyLogger::writeToChannels(Message mess) noexcept
{
	for (auto i = channelList.begin(); i != channelList.end(); ++i)
	{
		(*i)->write(mess);
	}
}
