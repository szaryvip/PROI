#include "CppUnitTest.h"
#include "../LoggerLib/LoggerLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LoggerTests
{
	TEST_CLASS(LoggerTests)
	{
	public:
		
		TEST_METHOD(createMessage)
		{
			Message mess;
			mess.text = "Test message";
			mess.severity = Severity::Info;
			Assert::IsTrue("Test message" == mess.text);
			Assert::IsTrue(Severity::Info == mess.severity);
		}

		TEST_METHOD(createChannelConsoleWithout)
		{
			ChannelConsole channel;
			Assert::IsTrue(Severity::None == channel.minimumSeverity());
			Assert::IsTrue(Severity::Error == channel.maximumSeverity());
		}

		TEST_METHOD(createChannelConsoleParams)
		{
			ChannelConsole channel(Severity::Trace, Severity::Warn);
			Assert::IsTrue(Severity::Trace == channel.minimumSeverity());
			Assert::IsTrue(Severity::Warn == channel.maximumSeverity());
		}

		TEST_METHOD(createChannelConsoleOnStringStream)
		{
			std::stringstream ss;
			ss << "test";
			ChannelConsole channel(Severity::Trace, Severity::Warn, ss);
			Assert::IsTrue(Severity::Trace == channel.minimumSeverity());
			Assert::IsTrue(Severity::Warn == channel.maximumSeverity());
			Assert::IsTrue("test" == channel.getContent());
		}

		TEST_METHOD(writeChannelConsole)
		{
			ChannelConsole channel;
			Assert::IsTrue(Severity::None == channel.minimumSeverity());
			Assert::IsTrue(Severity::Error == channel.maximumSeverity());
			Message mess;
			mess.text = "test";
			mess.severity = Severity::Error;
			channel.write(mess);
			Assert::IsTrue("test" == channel.getContent());
		}

		TEST_METHOD(writeChannelConsoleBadSeverity)
		{
			ChannelConsole channel(Severity::None, Severity::Info);
			Message mess;
			mess.text = "test";
			mess.severity = Severity::Error;
			channel.write(mess);
			Assert::IsTrue("" == channel.getContent());
		}

		TEST_METHOD(createChannelFileWithout)
		{
			ChannelFile channel;
			Assert::IsTrue(Severity::None == channel.minimumSeverity());
			Assert::IsTrue(Severity::Error == channel.maximumSeverity());
		}

		TEST_METHOD(createChannelFileParams)
		{
			ChannelFile channel(Severity::Trace, Severity::Warn);
			Assert::IsTrue(Severity::Trace == channel.minimumSeverity());
			Assert::IsTrue(Severity::Warn == channel.maximumSeverity());
		}

		TEST_METHOD(createChannelFileOnFile)
		{
			ChannelFile channel(Severity::Trace, Severity::Warn, "my_logs.txt");
			Assert::IsTrue(Severity::Trace == channel.minimumSeverity());
			Assert::IsTrue(Severity::Warn == channel.maximumSeverity());
			Assert::IsTrue("" == channel.getContent());
		}

		TEST_METHOD(writeChannelFile)
		{
			ChannelFile channel;
			Assert::IsTrue(Severity::None == channel.minimumSeverity());
			Assert::IsTrue(Severity::Error == channel.maximumSeverity());
			Message mess;
			mess.text = "test";
			mess.severity = Severity::Error;
			channel.write(mess);
			Assert::IsTrue("test" == channel.getContent());
		}

		TEST_METHOD(writeChannelFileBadSeverity)
		{
			ChannelFile channel(Severity::None, Severity::Info);
			Message mess;
			mess.text = "test";
			mess.severity = Severity::Error;
			channel.write(mess);
			Assert::IsTrue("" == channel.getContent());
		}

		TEST_METHOD(loggerAddChannel)
		{
			MyLogger logger;
			ChannelFile chfile;
			logger.addChannel(&chfile);
			Message mess;
			mess.text = "test";
			mess.severity = Severity::Info;
			logger.writeToChannels(mess);
			Assert::IsTrue("test" == chfile.getContent());	
		}

		TEST_METHOD(loggerWriteToAll)
		{
			ChannelFile channel1(Severity::None, Severity::Info);
			ChannelConsole channel2(Severity::None, Severity::Error);
			ILoggerChannel* t[2] = { &channel1, &channel2 };
			DoubleList<ILoggerChannel*> chlist;
			chlist.append(&channel1);
			chlist.append(&channel2);
			MyLogger logger(&chlist);
			Message mess;
			mess.text = "test";
			mess.severity = Severity::Info;
			logger.writeToChannels(mess);
			//Assert::IsTrue("test" == channel1.getContent());
			//Assert::IsTrue("test" == channel2.getContent());
		}

		TEST_METHOD(loggerWriteNotToAll)
		{
			ChannelFile channel1(Severity::None, Severity::Info);
			ChannelConsole channel2;
			ILoggerChannel* t[2] = { &channel1, &channel2 };
			DoubleList<ILoggerChannel*> chlist(t, 2);
			MyLogger logger(&chlist);
			Message mess;
			mess.text = "test";
			mess.severity = Severity::Error;
			logger.writeToChannels(mess);
			//Assert::IsTrue("" == channel1.getContent());
			//Assert::IsTrue("test" == channel2.getContent());
		}
	};
}
