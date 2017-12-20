#include "LinkedList.h"

//creates LinkedList pointer array and sets head and tail to nullptr
LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
}

//sets the head pointer to point to the address of the DoubleLinkNode passed in
LinkedList::LinkedList(DoubleLinkNode& pilot)
{
    head = &pilot;
    tail = &pilot;
}

//loops through the LinkedList and deletes the dynamic memory
LinkedList::~LinkedList()
{
    destroy(this->head);
}

//while the head pointer does not point to the same thing as the tail pointer print out the contents of the DoubleLinkNode
ostream& operator<<(ostream& outFile, LinkedList *pilotList)
{
    DoubleLinkNode *current;
    current = pilotList->head;
    while(current)
    {
        outFile << fixed << showpoint << setprecision(2);
        outFile << setw(10) << left << current->getPilotName() << current->getPilotArea() << endl;
        current = current->getNextPtr();
    }
    return outFile;
}

//recursively deletes the LinkedList and every DoubleLinkNode in the LinkedList
void LinkedList::destroy(DoubleLinkNode *item)
{
    if(item)
        destroy(item->getNextPtr());
    else
        delete item;
}

//inserts the DoubleLinkNode pilot into the LinkedList by first checking the head pointer is not nullptr.  If it is then assign the
//the pilot to the head and tail.  If not then assign the DoubleLinkNode previousPointer at the tail to point to the address of the Node
//being added in and the DoubleLinkNodes nextPointer point to the Node's address, then make the tail pointer point to the new DoubleLinkNode's address
void LinkedList::insertPilot(DoubleLinkNode *pilot)
{
    if(!head)
    {
        head = pilot;
        tail = pilot;
    }else
    {
        pilot->setPrevPtr(tail);
        tail->setNextPtr(pilot);
        tail = pilot;

    }
}

//bubble sort that takes in a string to determine whether to sort by alphabetical or by area size.  Loops through
//the LinkedList and finds a value smaller than the first and switches the two DoubleLinkNode objects
void LinkedList::sortLinkedList(string command)
{
    DoubleLinkNode *current, *next, *prev, *traverse;
    bool unsorted;

    do{
        unsorted = false;
        current = head;
        while(current->getNextPtr())
        {
            next = current->getNextPtr();
            prev = current->getPrevPtr();
            if(swapNodes(command, current, next))
            {
                if(prev)
                {
                    prev->setNextPtr(next);
                }

                DoubleLinkNode* nextNext = next->getNextPtr();
                if (nextNext) {
                    nextNext->setPrevPtr(current);
                }
                current->setPrevPtr(next);
                next->setPrevPtr(prev);
                current->setNextPtr(next->getNextPtr());
                next->setNextPtr(current);

                if(!prev)
                    head = next;
                unsorted = true;
            }
            else
                current = current->getNextPtr();
        }
    }while(unsorted);
}

bool LinkedList::swapNodes(string command, DoubleLinkNode *first, DoubleLinkNode *second)
{
    if(command == "area")
    {
        if(first->getPilotArea() > second->getPilotArea())
            return true;
        return false;
    }
    if(strcmp(first->getPilotName().c_str(), second->getPilotName().c_str()) > 0)
        return true;
    return false;
}

//traverses through LinkedList while not at the end and if the name or area matches then it deletes the pointer and returns
//true.  If it reaches the end of the LinkedList it returns false
bool LinkedList::searchList(string name, double area)
{
    DoubleLinkNode *current;
    current = head;
    if(name.size() > 0 && area == 0)
    {
        while(current)
        {
            if(strcmp(current->getPilotName().c_str(), name.c_str()) == 0)
                return true;
            current = current->getNextPtr();
        }
        return false;
    }else if(name.size() == 0 && area != 0)
    {
        while(current)
        {
            if(current->getPilotArea() == area)
                return true;
            current = current->getNextPtr();
        }
        return false;
    }
    return false;
}
