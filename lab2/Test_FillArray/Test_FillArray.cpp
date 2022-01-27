#include "CppUnitTest.h"
#include "../FillArray/FillArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<>
inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<std::array<std::array<int, maxColumns>, maxRows>>(const std::array<std::array<int, maxColumns>, maxRows>& t)
{
	std::wstring result;
	result += L"{";
	for (auto& row : t)
	{
		result += L"{";
		for (auto& v : row)
		{
			result += ToString(v);
			result += L",";
		}
		result += L"},";
	}
	result += L"}";
	return result;
};

namespace TestFillArray
{
	TEST_CLASS(TestFillArray)
	{
	public:

		TEST_METHOD(TestMethodSquare)
		{
			std::array<std::array<int, maxColumns>, maxRows> templ = { { {1,3,4}, {2,5,8}, {6,7,9} } };
			std::array<std::array<int, maxColumns>, maxRows> test = { };
			fillArray(test, 3, 3);
			Assert::AreEqual(templ, test);
		}

		TEST_METHOD(TestMethodRectangle1)
		{
			std::array<std::array<int, maxColumns>, maxRows> templ = { { {1,3,4}, {2,5,9}, {6,8,10}, {7,11,12} } };
			std::array<std::array<int, maxColumns>, maxRows> test = { };
			fillArray(test, 4, 3);
			Assert::AreEqual(templ, test);
		}

		TEST_METHOD(TestMethodRectangle2)
		{
			std::array<std::array<int, maxColumns>, maxRows> templ = { { {1,3,4,9}, {2,5,8,10}, {6,7,11,12} } };
			std::array<std::array<int, maxColumns>, maxRows> test = { };
			fillArray(test, 3, 4);
			Assert::AreEqual(templ, test);
		}
	};
}

