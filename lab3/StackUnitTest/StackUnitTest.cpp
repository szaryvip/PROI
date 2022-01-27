#include "CppUnitTest.h"
#include "../StackLib/Stack.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<>
inline std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<std::vector<int>>(const std::vector<int>& t)
{
	std::wstring result;
	result += L"{";
	for (auto& element : t)
	{
		result += ToString(element);
		result += L",";
	}
	result += L"}";
	return result;
};

namespace StackUnitTest
{
	TEST_CLASS(StackUnitTest)
	{
	public:
		
		TEST_METHOD(constructorWithoutParameters)
		{
			Stack stack;
			Assert::IsTrue(stack.isEmpty());
		}


		TEST_METHOD(constructorWithVector)
		{
			std::vector<int> vector = { 1, 2, 3 };
			Stack stack(vector);
			Assert::IsFalse(stack.isEmpty());
			Assert::AreEqual(vector, stack.getVector());
		}

		TEST_METHOD(getVector)
		{
			std::vector<int> vector1 = { 1,2,3 };
			Stack stack(vector1);
			std::vector<int> vector2 = stack.getVector();
			Assert::AreEqual(vector1, vector2);
		}

		TEST_METHOD(popFunction)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 1,2 };
			Stack stack(vector1);
			int poped = stack.pop();
			Assert::AreEqual(3, poped);
			Assert::AreEqual(vector2, stack.getVector());
		}

		TEST_METHOD(popFromEmptyStack)
		{
			Stack stack;
			Assert::ExpectException<std::invalid_argument>([&] {stack.pop(); });
		}

		TEST_METHOD(pushFunction)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 1,2,3,4 };
			Stack stack(vector1);
			int toPush = 4;
			stack.push(toPush);
			Assert::AreEqual(vector2, stack.getVector());
		}

		TEST_METHOD(isEmpty)
		{
			std::vector<int> vector = {};
			Stack stack(vector);
			Assert::IsTrue(stack.isEmpty());
		}

		TEST_METHOD(addStacks)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 1,2,3,4 };
			std::vector<int> vector3 = { 1,2,3,1,2,3,4 };
			Stack stack1(vector1);
			Stack stack2(vector2);
			Stack stack3 = stack1 + stack2;
			Assert::AreEqual(vector3, stack3.getVector());
		}

		TEST_METHOD(addStackToStack)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 1,2,3,4 };
			std::vector<int> vector3 = { 1,2,3,1,2,3,4 };
			Stack stack1(vector1);
			Stack stack2(vector2);
			stack1 += stack2;
			Assert::AreEqual(vector3, stack1.getVector());
		}

		TEST_METHOD(indexOperator)
		{
			std::vector<int> vector1 = { 1,2,3 };
			int expected = 2;
			Stack stack(vector1);
			Assert::AreEqual(expected, stack[1]);
		}

		TEST_METHOD(equalityOperatorPositive)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 1,2,3 };
			Stack stack1(vector1);
			Stack stack2(vector2);
			Assert::IsTrue(stack1==stack2);
		}

		TEST_METHOD(notEqualityOperatorPositive)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 1,2,3,4 };
			Stack stack1(vector1);
			Stack stack2(vector2);
			Assert::IsTrue(stack1 != stack2);
		}

		TEST_METHOD(equalityOperatorNegative)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 1,2,3,4 };
			Stack stack1(vector1);
			Stack stack2(vector2);
			Assert::IsFalse(stack1 == stack2);
		}

		TEST_METHOD(notEqualityOperatorNegative)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 1,2,3 };
			Stack stack1(vector1);
			Stack stack2(vector2);
			Assert::IsFalse(stack1 != stack2);
		}

		TEST_METHOD(addIntegerOperator)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 3,4,5 };
			int toAdd = 2;
			Stack stack(vector1);
			stack += toAdd;
			Assert::AreEqual(vector2, stack.getVector());
		}

		TEST_METHOD(addIntegerToEmptyStack)
		{
			int toAdd = 2;
			Stack stack;
			stack += toAdd;
			Assert::IsTrue(stack.isEmpty());
		}

		TEST_METHOD(multiplyStackOperator)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 3,6,9 };
			int multiply = 3;
			Stack stack(vector1);
			stack *= multiply;
			Assert::AreEqual(vector2, stack.getVector());
		}

		TEST_METHOD(divideStackOperator)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 3,6,9 };
			int divide = 3;
			Stack stack(vector2);
			stack /= divide;
			Assert::AreEqual(vector1, stack.getVector());
		}

		TEST_METHOD(divideStack2)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 4,6,11 };
			int divide = 3;
			Stack stack(vector2);
			stack /= divide;
			Assert::AreEqual(vector1, stack.getVector());
		}

		TEST_METHOD(addWithNewStackOperator)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 3,4,5 };
			int toAdd = 2;
			Stack stack(vector1);
			Stack stack2;
			stack2 = stack + toAdd;
			Assert::AreEqual(vector2, stack2.getVector());
		}

		TEST_METHOD(multiplyWithNewStackOperator)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 3,6,9 };
			int multiply = 3;
			Stack stack(vector1);
			Stack stack2;
			stack2 = stack * multiply;
			Assert::AreEqual(vector2, stack2.getVector());
		}

		TEST_METHOD(divideWithNewStackOperator)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 3,6,9 };
			int divide = 3;
			Stack stack(vector2);
			Stack stack2;
			stack2 = stack / divide;
			Assert::AreEqual(vector1, stack2.getVector());
		}
		
		TEST_METHOD(divideByZero)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 3,6,9 };
			int divide = 0;
			Stack stack(vector2);
			Assert::ExpectException<std::invalid_argument>([&] {stack.operator/(divide); });
		}

		TEST_METHOD(divideByZeroWithNewStack)
		{
			std::vector<int> vector1 = { 1,2,3 };
			std::vector<int> vector2 = { 3,6,9 };
			int divide = 0;
			Stack stack(vector2);
			Stack stack2;
			Assert::ExpectException<std::invalid_argument>([&] {stack.operator/(divide); });
		}

		TEST_METHOD(indexOperatorOutOfRange)
		{
			std::vector<int> vector1 = { 1,2,3 };
			Stack stack(vector1);
			Assert::ExpectException<std::invalid_argument>([&] {stack.operator[](4); });
		}

		TEST_METHOD(streamOperator)
		{
			std::vector<int> vector1 = { 1,2,3 };
			Stack stack(vector1);
			std::stringstream ss;
			ss << stack;
			std::string text = ss.str();
			std::string expected = "[1, 2, 3]";
			Assert::AreEqual(expected, text);
		}

		TEST_METHOD(streamOperatorEmptyStack)
		{
			Stack stack;
			std::stringstream ss;
			ss << stack;
			std::string text = ss.str();
			std::string expected = "[]";
			Assert::AreEqual(expected, text);
		}

	};
}
