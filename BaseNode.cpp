#include "BaseNode.h"

BaseNode::BaseNode()
{
    pilotName = "";
    pilotArea = 0;
}

BaseNode::BaseNode(string name, double area)
{
    pilotName = name;
    pilotArea = area;
}
