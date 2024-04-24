#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>

class House {
	public:
		House(int size, char border = 'X', char fill = '*');

		void Draw(std::ostream& output = std::cout);
		friend std::ostream& operator<<(std::ostream& os, House& h);

		void Shrink();
		void Grow();
		int GetSize();

		int Perimeter();
		double Area();

		int SetBorder(char c);
		int SetFill(char c);

		void Summary();

	private:
		int m_size;
		char m_border;
		char m_fill;
};