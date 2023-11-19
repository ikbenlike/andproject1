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
	bool m_used = false;
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

    bool canFit(Box b) {
		if(m_used) {
			return false;
		}
		if(!(m_full && m_n_inside <= b.m_n_inside + 1)) {
			int i = 0;
			do {
				if(b.m_x < m_x && b.m_y < m_y && b.m_z < m_z) {
					return true;
				}
			} while(i++ < 2);
		}
		return false;
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

std::vector<size_t> findSubsequenceIndices(std::vector<Box> boxes) {
	
}

int main() {
	size_t nbox = 0;
	std::vector<Box> boxes = {};
	//std::list<Box> boxes = {};
	std::cin >> nbox;
	//sorted_boxes.resize(nbox);
	boxes.resize(nbox);
	for(size_t i = 0; i < nbox; i++) {
	    boxes[i] = Box::readBox(std::cin);
	}

	std::sort(boxes.begin(), boxes.end());
	//std::copy(sorted_boxes.begin(), sorted_boxes.end(), boxes.begin());



	std::cout << boxes.size() << std::endl;
}
