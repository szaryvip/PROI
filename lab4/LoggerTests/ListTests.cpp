#include "CppUnitTest.h"
#include "../LoggerLib/ListLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ListTests
{
	TEST_CLASS(ListTests)
	{
	public:

		TEST_METHOD(nodeCreateNodeWithContent)
		{
			Node<int> mynode(1);
			Assert::AreEqual(1, mynode.getContent());
			Assert::IsFalse(mynode.isGuard());
		}

		TEST_METHOD(nodeCreateNodeGuard)
		{
			Node<int> mynode(true);
			Assert::IsTrue(mynode.isGuard());
			Assert::AreEqual(0, mynode.getContent());
		}

		TEST_METHOD(nodeSetContent)
		{
			Node<int> mynode(1);
			Assert::AreEqual(1, mynode.getContent());
			mynode.setContent(2);
			Assert::AreEqual(2, mynode.getContent());
		}

		TEST_METHOD(nodeGetsAndSetsNextPrevious)
		{
			Node<int> mynode(1);
			Node<int> mynext(2);
			Node<int> previous(0);
			mynode.setNext(&mynext);
			mynode.setPrevious(&previous);
			Assert::AreEqual(mynext.getContent(), mynode.getNext()->getContent());
			Assert::AreEqual(previous.getContent(), mynode.getPrevious()->getContent());
		}

		TEST_METHOD(nodesCompare)
		{
			Node<int> mynode(1);
			Node<int> mynext(2);
			mynode.setNext(&mynext);
			Assert::IsTrue(mynext.operator==(*(mynode.getNext())));
		}

		TEST_METHOD(listCreateWithoutParam)
		{
			DoubleList<int> mylist;
			Assert::IsTrue(mylist.isEmpty());
		}

		TEST_METHOD(listEmptySize)
		{
			DoubleList<int> mylist;
			size_t exp = 0;
			Assert::AreEqual(exp, mylist.size());
		}

		TEST_METHOD(listEmptyRemove)
		{
			DoubleList<int> mylist;
			auto i = mylist.begin();
			Assert::ExpectException<std::invalid_argument>([&] { mylist.remove(i); });
		}

		TEST_METHOD(listEmptyAppend)
		{
			DoubleList<int> mylist;
			Assert::IsTrue(mylist.isEmpty());
			mylist.append(1);
			Assert::IsFalse(mylist.isEmpty());
		}

		TEST_METHOD(listCreateWithSth)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			Assert::IsFalse(mylist.isEmpty());
		}

		TEST_METHOD(listSize)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			Assert::AreEqual(3, int(mylist.size()));
		}

		TEST_METHOD(listInsert)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.begin();
			Assert::AreEqual(1, *i);
			mylist.insert(i, 4);
			Assert::AreEqual(1, *i);
			--i;
			Assert::AreEqual(4, *i);
		}

		TEST_METHOD(listInsertError)
		{
			DoubleList<int> mylist;
			auto i = mylist.begin();
			Assert::ExpectException<std::invalid_argument>([&] { mylist.insert(i, 1); });
		}
		
		TEST_METHOD(listRemove)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.begin();
			++i;
			Assert::AreEqual(2, *i);
			mylist.remove(i);
			Assert::AreEqual(size_t(2), mylist.size());
		}

		TEST_METHOD(listRemoveError)
		{
			DoubleList<int> mylist;
			auto i = mylist.begin();
			Assert::ExpectException<std::invalid_argument>([&] { mylist.remove(i); });
		}

		TEST_METHOD(listIteratorBegin)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.begin();
			Assert::AreEqual(1, *i);
		}

		TEST_METHOD(listIteratorEnd)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.end();
			Assert::AreEqual(0, *i); //0 because it points endGuard
		}

		TEST_METHOD(listIteratorRevBegin)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.revBegin();
			Assert::AreEqual(3, *i);
		}

		TEST_METHOD(listIteratorRevEnd)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.revEnd();
			Assert::AreEqual(0, *i);
		}

		TEST_METHOD(listIteratorInc)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.begin();
			++i;
			Assert::AreEqual(2, *i);
		}

		TEST_METHOD(listIteratorAdd)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.begin();
			i += 2;
			Assert::AreEqual(3, *i);
		}

		TEST_METHOD(listIteratorAddError)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.begin();
			Assert::ExpectException<std::invalid_argument>([&] {i += 4; });
		}

		TEST_METHOD(listIteratorDec)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.end();
			--i;
			Assert::AreEqual(3, *i);
		}

		TEST_METHOD(listIteratorSub)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.end();
			i -= 2;
			Assert::AreEqual(2, *i);
		}

		TEST_METHOD(listIteratorIncRev)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.revBegin();
			++i;
			Assert::AreEqual(2, *i);
		}

		TEST_METHOD(listIteratorAddRev)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.revBegin();
			i += 2;
			Assert::AreEqual(1, *i);
		}

		TEST_METHOD(listIteratorAddErrorRev)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.revBegin();
			Assert::ExpectException<std::invalid_argument>([&] {i += 4; });
		}

		TEST_METHOD(listIteratorDecRev)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.revEnd();
			--i;
			Assert::AreEqual(1, *i);
		}

		TEST_METHOD(listIteratorSubRev)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			auto i = mylist.revEnd();
			i -= 2;
			Assert::AreEqual(2, *i);
		}

		TEST_METHOD(listPop)
		{
			const size_t s = 3;
			int t[s] = { 1,2,3 };
			DoubleList<int> mylist(t, s);
			int poped = mylist.pop();
			Assert::AreEqual(3, poped);
			auto i = mylist.end();
			--i;
			Assert::AreEqual(2, *i);
		}



	};
}



