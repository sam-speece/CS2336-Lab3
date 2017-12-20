#include "DoubleLinkNode.h"

//default constructor that sets the pointers equal to nullptr
DoubleLinkNode::DoubleLinkNode() : BaseNode()
{
    nextPtr = nullptr;
    prevPtr = nullptr;
}

//overloaded constructor that calls the BaseNode constructor to initialize the area and name and sets the next
//pointer and previous pointer to other DoubleLinkNode objects
DoubleLinkNode::DoubleLinkNode(DoubleLinkNode *nptr, DoubleLinkNode *pptr, string name, double area) : BaseNode(name, area)
{
    nextPtr = nptr;
    prevPtr = pptr;
}

//copy constructor that copies name, area, next and previous pointer
DoubleLinkNode::DoubleLinkNode(const DoubleLinkNode& other)
{
    nextPtr = other.nextPtr;
    prevPtr = other.prevPtr;
    setPilotArea(other.pilotArea);
    setPilotName(other.pilotName);
}

//destructor for DoubleLinkNode
DoubleLinkNode::~DoubleLinkNode()
{
    delete nextPtr;
    delete prevPtr;
}
