#ifndef DOUBLELINKNODE_H
#define DOUBLELINKNODE_H
#include "BaseNode.h"

class DoubleLinkNode : public BaseNode
{
    public:
        DoubleLinkNode();
        DoubleLinkNode(DoubleLinkNode*, DoubleLinkNode*, string, double);
        DoubleLinkNode(const DoubleLinkNode&);
        virtual ~DoubleLinkNode();

        void setPilotName(string name) {pilotName = name;};
        string getPilotName() {return pilotName;};
        void setPilotArea(double area) {pilotArea = area;};
        double getPilotArea() {return pilotArea;};

        void setNextPtr(DoubleLinkNode *ptr) {nextPtr = ptr;};
        DoubleLinkNode* getNextPtr() {return nextPtr;};
        void setPrevPtr(DoubleLinkNode *ptr) {prevPtr = ptr;};
        DoubleLinkNode* getPrevPtr() {return prevPtr;};

    protected:

    private:
        DoubleLinkNode *nextPtr;
        DoubleLinkNode *prevPtr;
};

#endif // DOUBLELINKNODE_H
