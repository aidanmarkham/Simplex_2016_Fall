#include "Node.h"
using namespace Simplex;

void Simplex::Node::SetParent(Node * p)
{
	parentNode = p;
	g = parentNode->g + 1;
}

Simplex::Node::Node()
{
	
}



Simplex::Node::Node(Node * p)
{
	parentNode = p;
	g = parentNode->g + 1;
}



Simplex::Node::~Node()
{

}
