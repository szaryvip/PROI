#include "Stack.h"


Stack::Stack(int *myArray) noexcept
{
	int i = 0;
	while(*(myArray + i) != '\0')
	{
		this->vect.push_back(*(myArray + i));
		i++;
	}
}

Stack::Stack(std::vector<int> v) noexcept
{
	this->vect = v;
}

std::vector<int> Stack::getVector() const noexcept
{
	return this->vect;
}

void Stack::push(int element) noexcept
{
	this->vect.push_back(element);
}

int Stack::pop()
{
	if (this->isEmpty())
		throw std::invalid_argument("Cannot pop from empty stack");
	int	value = this->vect.back();
	this->vect.pop_back();
	return value;
}

bool Stack::isEmpty() const noexcept
{
	return this->vect.empty();
}

Stack Stack::operator+(Stack const& s) const noexcept
{
	std::vector<int> newVector = this->vect;
	std::vector<int> secVector = s.getVector();
	for (unsigned int i = 0; i < secVector.size(); i++)
	{
		newVector.push_back(secVector[i]);
	}
	return Stack(newVector);
}

void Stack::operator+=(Stack const& s) noexcept
{
	std::vector<int> vector = s.getVector();
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		this->vect.push_back(vector[i]);
	}
}

int Stack::operator[](unsigned int index) const
{
	if (index >= this->vect.size()) 
		throw std::invalid_argument("Index out of range");
	return this->vect[index];
}

bool Stack::operator==(Stack const& s) const noexcept
{
	return this->vect == s.getVector();
}

bool Stack::operator!=(Stack const& s) const noexcept
{
	return !(*this == s);
}

void Stack::operator+=(int i) noexcept
{
	for (unsigned int j = 0; j < this->vect.size(); j++)
	{
		this->vect[j] += i;
	}
}

void Stack::operator*=(int i) noexcept
{
	for (unsigned int j = 0; j < this->vect.size(); j++)
	{
		this->vect[j] *= i;
	}
}

void Stack::operator/=(int i)
{
	if (i == 0)
		throw std::invalid_argument("Divide by zero exception");
	for (unsigned int j = 0; j < this->vect.size(); j++)
	{
		this->vect[j] /= i;
	}
}

Stack Stack::operator+(int i) const noexcept
{
	std::vector<int> startedVect = this->getVector();
	for (unsigned int j = 0; j < startedVect.size(); j++)
	{
		startedVect[j] += i;
	}
	Stack newStack(startedVect);
	return newStack;
}

Stack Stack::operator*(int i) const noexcept
{
	std::vector<int> startedVect = this->getVector();
	for (unsigned int j = 0; j < startedVect.size(); j++)
	{
		startedVect[j] *= i;
	}
	Stack newStack(startedVect);
	return newStack;
}

Stack Stack::operator/(int i) const
{	
	if (i == 0)
		throw std::invalid_argument("Divide by zero exception");
	std::vector<int> startedVect = this->getVector();
	for (unsigned int j = 0; j < startedVect.size(); j++)
	{
		startedVect[j] /= i;
	}
	Stack newStack(startedVect);
	return newStack;
}

std::ostream& operator<<(std::ostream& stream, Stack const& s)
{
	std::vector<int> vector = s.getVector();
	stream << "[";
	if (vector.size() > 0)
	{
		stream << vector[0];
		for (unsigned int j = 1; j < vector.size(); j++)
		{
			stream << ", ";
			stream << vector[j];
		}
	}
	stream << "]";
	return stream;
}

