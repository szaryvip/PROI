#pragma once
#include <stdexcept>

template< class T >
class Node
{
private:
	T content;
	Node<T>* next = nullptr;
	Node<T>* previous = nullptr;
	bool guard = false;

public:
	Node() noexcept
		:content(0)
	{
	}

	Node(T con) noexcept
		:content(con)
	{
	}

	Node(bool g) noexcept
		:guard(g)
	{
	}

	Node(T con, bool g) noexcept
		:content(con), guard(g)
	{
	}

	~Node() noexcept = default;

	T getContent() const noexcept
	{
		return content;
	}

	void setContent(T value) noexcept
	{
		content = value;
	}

	bool isGuard() const noexcept
	{
		return guard;
	}

	Node<T>* getNext() const noexcept
	{
		return next;
	}

	Node<T>* getPrevious() const noexcept
	{
		return previous;
	}

	void setNext(Node<T>* ptr) noexcept
	{
		next = ptr;
	}

	void setPrevious(Node<T>* ptr) noexcept
	{
		previous = ptr;
	}

	bool operator==(Node<T> node) const noexcept
	{
		return (getContent() == node.getContent() && isGuard() == node.isGuard());
	}

	bool operator!=(Node<T> node) const noexcept
	{
		return !(operator==(node));
	}
};


template< typename T >
class DoubleList
{
private:
	Node<T>* beginGuard;
	Node<T>* endGuard;

public:
	class Iterator
	{
		friend DoubleList;
	private:
		Node<T>* current;
		bool isReversed = false;
		Iterator(Node<T>* node) noexcept
			:current(node)
		{
		}
		Iterator(Node<T>* node, bool rev) noexcept
			:current(node), isReversed(rev)
		{
		}

	public:
		T operator*() noexcept
		{
			return current->getContent();
		}

		Iterator& operator++()
		{
			if (current->isGuard())
				throw std::invalid_argument("Invalid argument, index out of range");
			if (!(isReversed))
				current = current->getNext();
			else
				current = current->getPrevious();
			return *this;
		}

		Iterator& operator--()
		{
			if (!(isReversed))
				current = current->getPrevious();
			else
				current = current->getNext();
			if (current->isGuard())
				throw std::invalid_argument("Invalid argument, index out of range");
			return *this;
		}

		Iterator& operator+=(int i)
		{
			while (i > 0)
			{
				operator++();
				i--;
			}

			return *this;
		}

		Iterator& operator-=(int i)
		{
			while (i > 0)
			{
				operator--();
				i--;
			}
			return *this;
		}

		bool operator==(Iterator i) const noexcept
		{
			return (current == (i.current));
		}

		bool operator!=(Iterator i) const noexcept
		{
			return !(operator==(i));
		}

	};

	DoubleList() noexcept
	{
		beginGuard = new Node<T>(true);
		endGuard = new Node<T>(true);
		beginGuard->setNext(endGuard);
		endGuard->setPrevious(beginGuard);
	}

	DoubleList(T t[], const unsigned int len) noexcept
		:DoubleList()
	{
		for (unsigned int i = 0; i < len; ++i)
		{
			append(*(t + i));
		}
	}

	~DoubleList() noexcept
	{
		for (Node<T>* n = beginGuard; n != nullptr;)
		{
			Node<T>* tmp = n;
			n = n->getNext();
			delete tmp;
		}
	}

	bool isEmpty() const noexcept
	{
		return (*(beginGuard->getNext()) == *endGuard);
	}

	size_t size() noexcept
	{
		size_t size = 0;
		if (isEmpty())
			return 0;
		for (auto i = begin(); i != end(); ++i)
		{
			size++;
		}
		return size;
	}

	void append(T value) noexcept
	{
		Node<T>* newNode = new Node<T>(value);
		auto previous = endGuard->getPrevious();
		previous->setNext(newNode);
		newNode->setPrevious(previous);
		newNode->setNext(endGuard);
		endGuard->setPrevious(newNode);
	}

	void insert(Iterator i, T value)
	{
		if (isEmpty())
			throw std::invalid_argument("List is empty, you can only append");
		Node<T>* currentThere = i.current;
		Node<T>* newNode = new Node<T>(value);
		currentThere->getPrevious()->setNext(newNode);
		newNode->setPrevious(currentThere->getPrevious());
		newNode->setNext(currentThere);
		currentThere->setPrevious(newNode);
	}

	void remove(Iterator i)
	{
		if (isEmpty())
			throw std::invalid_argument("List is empty!");
		Node<T>* currentThere = i.current;
		currentThere->getPrevious()->setNext(currentThere->getNext());
		currentThere->getNext()->setPrevious(currentThere->getPrevious());
		i.current = currentThere->getNext();
		delete currentThere;
	}

	T pop()
	{
		if(isEmpty())
			throw std::invalid_argument("List is empty!");
		Node<T>* last = endGuard->getPrevious();
		T data = last->getContent();
		Node<T>* beforeLast = last->getPrevious();
		beforeLast->setNext(endGuard);
		endGuard->setPrevious(beforeLast);
		delete last;
		return data;
	}

	DoubleList<T>& operator=(DoubleList<T>* l) noexcept
	{
		DoubleList<T> newList;
		for (auto i = l->begin(); i != l->end(); ++i)
		{
			newList.append(*i);
		}
		return newList;
	}

	Iterator begin() const noexcept
	{
		return Iterator(beginGuard->getNext());
	}

	Iterator end() noexcept
	{
		return Iterator(endGuard);
	}

	Iterator revBegin() const noexcept
	{
		return Iterator(endGuard->getPrevious(), true);
	}

	Iterator revEnd() noexcept
	{
		return Iterator(beginGuard, true);
	}
};
