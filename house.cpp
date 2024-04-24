#include "house.hpp"

// draw to specified output stream
// this is done so we can use file streams not just std::cout
void House::Draw(std::ostream& output) {
	// trangle drawing loop
	for (int y = 0; y < this->m_size + 2; y++) {
		// spaces before house
		for (int i = 0; i < this->m_size + 1 - y; i++) {
			output << ' ';
		}
		// frist wall
		output << this->m_border;
		// second wall if needed
		if (y != 0) {
			// spaces inside house
			for (int i = 0; i < y * 2 - 1; i++) {
				// alternate fill pattern
				if (i % 2) 
					// special case for last row of triangle
					// if we are on the last row and we are on the first
					// or last fill character draw the border character
					if (y == this->m_size + 1 && (i < 3 || i > this->m_size * 2 - 3))
						output << this->m_border;
					else
						output << this->m_fill;
				else
					output << ' ';
			}
			output << this->m_border;
		}
		output << std::endl;
	}
	// square/base drawing loop
	for (int y = 0; y < this->m_size - 1; y++) {
		// always print 2 spaces and start a wall
		output << "  " << this->m_border;
		for (int i = 0; i < this->m_size * 2 - 3; i++) {
			// alternate fill pattern
			if (i % 2) 
				// special case for last row
				if (y == this->m_size - 2)
					output << this->m_border;
				else
					output << this->m_fill;
			else
				output << ' ';
		}
		output << this->m_border << std::endl;
	}
}

std::ostream& operator<<(std::ostream& os, House& h) {
	// draw to specified output stream
	h.Draw(os);
	// return stream so we can chain << operators
    return os;
}

House::House(int size, char border, char fill) {
	// check if size is within min or max value
	if (size >= 3)
		if (size <= 30)
			this->m_size = size;
		else
			this->m_size = 30;
	else
		this->m_size = 3;

	// set border and fill, character validity check is done by the function
	this->SetBorder(border);
	this->SetFill(fill);
}

int House::SetBorder(char c) {
	// character validity check
	if (c >= 33 && c <= 126) {
		this->m_border = c;
		return 0;
	} else {
		// if invalid fall back to default and return an error
		this->m_border = 'X';
		return 1;
	}
}

int House::SetFill(char c) {
	// character validity check
	if (c >= 33 && c <= 126) {
		this->m_fill = c;
		return 0;
	} else {
		// if invalid fall back to default and return an error
		this->m_fill = 'X';
		return 1;
	}
}

int House::GetSize() {
	return this->m_size;
}

void House::Grow() {
	if (this->m_size < 30)
		this->m_size++;
}

void House::Shrink() {
	if (this->m_size > 3)
		this->m_size--;
}

int House::Perimeter() {
	// perimeter of roof(3 * its sides, which are 2 bigger than m_size)
	return 3 * (this->m_size + 2)
	// perimeter of base(4 * its sides)
		+ 4 * this->m_size;
}

double House::Area() {
	// area of roof(one side, which is 2 bigger than m_size, squared, times the square root of 3, divided by 4)
	return (pow(this->m_size + 2, 2) * sqrt(3)) / 4
	// area of base(one side squared)
	 + pow(this->m_size, 2);
}
void House::Summary() {
	std::cout << "Base size: " << this->m_size << std::endl
		<< "Perimeter: " << this->Perimeter() << std::endl
		// always print 2 decimal points
		<< "Area: " << std::setprecision(2) << std::fixed << this->Area() << std::endl
		<< "Picture: " << std::endl;
	this->Draw();
}