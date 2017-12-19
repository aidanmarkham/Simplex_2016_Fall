#pragma once
namespace Simplex {
	class Node {
		
	public:
		Node* parentNode;
		bool blocked;
		int g;
		int h;
		int score;
		int x;
		int y;
		int startx;
		int starty;
		void SetParent(Node* p);
		Node();

		Node(Node* p);

		~Node();
	};
}