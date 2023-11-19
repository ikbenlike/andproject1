#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

struct Box {
	friend std::ostream &operator<<(std::ostream&, Box const&);
private:
	double m_x = 0;
	double m_y = 0;
	double m_z = 0;
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
		size_t i = 0;
	    do {
			if(b.m_x < m_x && b.m_y < m_y && b.m_z < m_z) {
				return true;
			}
			b.rotate();
		} while(i++ < 2);
		return false;
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

struct Tree {
	friend std::ostream &operator<<(std::ostream&, Tree const&);
private:
	std::vector<Box> m_data;
	std::vector<Tree> m_children;

	void reduceFits() {
		for(auto i = m_data.begin(); i != m_data.end(); i++) {
			std::vector<Box> new_data = {};
			for(auto j = i; j != m_data.end(); j++) {
				if(i->canFit(*j)) {
					new_data.push_back(*j);
				}
			}
			if(new_data.size() != 0) {
				m_children.emplace_back(new_data);
			}
		}
	}
public:
	Tree(std::vector<Box> data)
	: m_data{data} { }

	void buildTree() {
		reduceFits();
		for(Tree &t : m_children) {
			t.buildTree();
		}
	}

	size_t findLongestBranch() {
		if(m_children.size() == 0) {
			return 0;
		}

		size_t longest = 0;
		for(Tree &t : m_children) {
			size_t length = t.findLongestBranch() + 1;
			if(length > longest) {
				longest = length;
			}
		}
		return longest;
	}
};

std::ostream &operator<<(std::ostream &s, Box const &b) {
	s << "Box { x=" << b.m_x;
	s << ", y=" << b.m_y;
	s << ", z=" << b.m_z;
	s << " } volume: " << b.volume();
	return s;
}

bool operator<(Box const &b1, Box const &b2) {
	return b1.volume() < b2.volume();
}

/*std::ostream &operator<<(std::ostream &s, Tree const &t) {
	t.print(s, 0);
	return s;
	}*/

int main() {
	size_t nbox = 0;
	std::vector<Box> boxes = {};
	std::cin >> nbox;
	boxes.resize(nbox);
	for(size_t i = 0; i < nbox; i++) {
	    boxes[i] = Box::readBox(std::cin);
	}

	std::sort(boxes.rbegin(), boxes.rend());
	Tree tree = Tree(boxes);
	tree.buildTree();
	std::cout << boxes.size() - tree.findLongestBranch() << std::endl;
	//std::cout << boxes.size() << std::endl;
}
