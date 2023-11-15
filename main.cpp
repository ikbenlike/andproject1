#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

enum class CanFit {
	No,
	Yes,
	YesReplace
};

struct Box {
	friend std::ostream &operator<<(std::ostream&, Box const&);
private:
	double m_x = 0;
	double m_y = 0;
	double m_z = 0;
	bool m_full = false;
	size_t m_n_inside = 0;
	Box *m_inner = nullptr;
public:
	Box(double x = 0, double y = 0, double z = 0)
	: m_x{x}, m_y{y}, m_z{z} { }

	double volume() const {
		return m_x * m_y * m_z;
	}

	void rotate() {
		double tmp = m_x;
		m_x = m_y;
		m_y = m_z;
		m_z = tmp;
	}

	CanFit canFit(Box b) {
		if(!(m_full && m_n_inside <= b.m_n_inside + 1)) {
			int i = 0;
			do {
				if(b.m_x < m_x && b.m_y < m_y && b.m_z < m_z) {
					/*std::cout << b << std::endl;
					std::cout << "fits in: " << std::endl;
					std::cout << *this << std::endl;*/
					if(m_full)
						return CanFit::YesReplace;
					return CanFit::Yes;
				}
			} while(i++ < 2);
		}
		return CanFit::No;
	}

	Box insert(Box b) {
		Box r = Box();
		if(m_full) {
			r = *m_inner;
		}
		else {
			m_inner = new Box();
		}
	    m_n_inside = b.m_n_inside + 1;
		*m_inner = b;
		m_full = true;
		return r;
	}
	
	/*bool insert(Box b) {
		if(!(m_full && n_inside > b.n_inside + 1)) {
			int i = 0;
			do {
				if(b.m_x < m_x && b.m_y < m_y && b.m_z < m_z) {
					m_full = true;
					return true;
				}
				b.rotate();
			} while(i++ < 2);
		}
		return false;
		}*/
	
	static Box readBox(std::istream &s) {
		double x = 0;
		double y = 0;
		double z = 0;
		s >> x;
		s >> y;
		s >> z;
		return Box(x, y, z);
	}
};

std::ostream &operator<<(std::ostream &s, Box const &b) {
	s << "Box { x=" << b.m_x;
	s << ", y=" << b.m_y;
	s << ", z=" << b.m_z;
	s << " } volume: " << b.volume();
	s << " full: " << b.m_full;
	s << " contains: " << b.m_n_inside;
	return s;
}

bool operator<(Box const &b1, Box const &b2) {
	return b1.volume() < b2.volume();
}

int main() {
	size_t nbox = 0;
	std::vector<Box> sorted_boxes = {};
	std::list<Box> boxes = {};
	std::cin >> nbox;
	//std::cout << "amount of boxes: " << nbox << std::endl;
	sorted_boxes.resize(nbox);
	boxes.resize(nbox);
	for(size_t i = 0; i < nbox; i++) {
		sorted_boxes[i] = Box::readBox(std::cin);
	}

	std::sort(sorted_boxes.begin(), sorted_boxes.end());
	std::copy(sorted_boxes.begin(), sorted_boxes.end(), boxes.begin());
	/*for(auto i = boxes.begin(); i != boxes.end();) {
		bool inc = true;
		for(auto j = i; j != boxes.end(); j++) {
			if(j->insert(*i)) {
				inc = false;
				i = boxes.erase(i);
				break;
			}
		}
		if(inc)
			i++;
			}*/
	for(auto i = boxes.begin(); i != boxes.end();) {
		bool inc = true;
		for(auto j = i; j != boxes.end(); j++) {
			CanFit fits = j->canFit(*i);
			if(fits != CanFit::No) {
				inc = false;
				Box tmp = j->insert(*i);
				if(fits == CanFit::YesReplace) {
					*i = tmp;
				}
				else {
					i = boxes.erase(i);
				}
			}
		}
		if(inc)
			i++;
	}
	/*for(Box b : boxes) {
		std::cout << b << std::endl;
		}*/
	std::cout << boxes.size() << std::endl;
}
