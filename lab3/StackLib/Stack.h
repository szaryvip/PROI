#pragma once
#include <iostream>
#include <sstream>
#include <vector>

class Stack
{
private:
	std::vector<int> vect;

public:
	Stack() noexcept = default;
	Stack(int *myArray) noexcept;
	Stack(std::vector<int> v) noexcept;
	
	std::vector<int> getVector() const noexcept;

	int pop();
	void push(int element) noexcept;
	
	bool isEmpty() const noexcept;

	Stack operator+(Stack const& s) const noexcept;
	void operator+=(Stack const& s) noexcept;

	int operator[](unsigned int index) const;
	
	bool operator==(Stack const& s) const noexcept;
	bool operator!=(Stack const& s) const noexcept;
	
	void operator+=(int i) noexcept;
	void operator*=(int i) noexcept;
	void operator/=(int i);

	Stack operator+(int i) const noexcept;
	Stack operator*(int i) const noexcept;
	Stack operator/(int i) const;

};

std::ostream& operator<<(std::ostream& stream, Stack const& s);
