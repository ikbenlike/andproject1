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
	std::vector<Box> m_data = {};
	std::vector<Tree> m_children = {};

	void print(std::ostream &s, size_t indent) const {
		for(size_t i = 0; i < indent; i++) {
			s << "  ";
		}
		s << "| data: " << m_data.size();
		s << ", children: " << m_children.size();
		s << std::endl;
		for(Tree t : m_children) {
			t.print(s, indent + 1);
		}
	}
	
	void reduceFits() {
		/*for(Box b : m_data) {
			std::cout << b << std::endl;
			}*/
		for(auto i = m_data.begin(); i < m_data.end(); i++) {
			std::vector<Box> new_data = {};
			for(auto j = i + 1; j < m_data.end(); j++) {
				if(i->canFit(*j)) {
					new_data.push_back(*j);
				}
			}
			if(new_data.size() != 0) {
				m_children.push_back(Tree(new_data));
				/*std::cout << "Inserting new child node" << std::endl;
				std::cout << "Parent size: " << m_data.size() << std::endl;
				std::cout << "Generation size: " << new_data.size() << std::endl;*/
			}
		}
		//std::cout << "final child count: " << m_children.size() << std::endl;
	}
public:
	Tree(std::vector<Box> data = {})
	: m_data{data} { }

	void buildTree() {
		reduceFits();
		std::cout << "Data count: " << m_data.size() << std::endl;
		std::cout << "Child count: " << m_children.size() << std::endl;
		for(Tree t : m_children) {
			t.buildTree();
		}
	}

	size_t findLongestBranch() {
		std::cout << "m_data.size(): " << m_data.size() << std::endl;
		std::cout << "m_children.size(): " << m_children.size() << std::endl;
		if(m_children.size() == 0) {
			return 1;
		}
		size_t longest = 0;
		for(Tree t : m_children) {
			size_t length = t.findLongestBranch();
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

std::ostream &operator<<(std::ostream &s, Tree const &t) {
	t.print(s, 0);
	return s;
}

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
	std::cout << tree << std::endl;
	std::cout << tree.findLongestBranch() << std::endl;
	//std::cout << boxes.size() << std::endl;
}
