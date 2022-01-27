#pragma once
#include "ListLib.h"
#include <iostream>
#include <sstream> 
#include <fstream> 

enum Severity
{
	None,
	Trace,
	Info,
	Warn,
	Error
};

struct Message
{
	std::string text;
	Severity severity;
};

class ILoggerChannel
{
private:
	Severity minSeverity = Severity::None;
	Severity maxSeverity = Severity::Error;
protected:
	std::string content = "";
public:
	ILoggerChannel() noexcept;
	ILoggerChannel(Severity smin, Severity smax) noexcept;
	Severity minimumSeverity() const noexcept;
	Severity maximumSeverity() const noexcept;
	std::string getContent() const noexcept;
	virtual void write(Message mess) = 0;
	virtual ~ILoggerChannel() = default;
};

class ChannelConsole : public ILoggerChannel
{
	
public:
	ChannelConsole() noexcept;
	ChannelConsole(Severity smin, Severity smax) noexcept;
	ChannelConsole(Severity smin, Severity smax,std::stringstream& s) noexcept;
	void write(Message mess) noexcept;
	~ChannelConsole() = default;

};

class ChannelFile : public ILoggerChannel
{
private:
	std::string fileName = "logs.txt";
public:
	ChannelFile() noexcept;
	ChannelFile(Severity smin, Severity smax) noexcept;
	ChannelFile(Severity smin, Severity smax, std::string fName) noexcept;
	void write(Message mess) noexcept;
	~ChannelFile() = default;
};

class MyLogger
{
private:
	DoubleList<ILoggerChannel*> channelList;
public:
	MyLogger() noexcept = default;
	MyLogger(DoubleList<ILoggerChannel*>* iList) noexcept;
	void addChannel(ILoggerChannel* channel) noexcept;
	void writeToChannels(Message mess) noexcept;
	~MyLogger() = default;
};
