#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "DoubleLinkNode.h"

using namespace std;

class LinkedList
{
    public:
        LinkedList();
        LinkedList(DoubleLinkNode&);
        ~LinkedList();

        void setHead(DoubleLinkNode *h) {head = h;};
        DoubleLinkNode* getHead() {return head;};
        void setTail(DoubleLinkNode *t) {tail = t;};
        DoubleLinkNode* getTail() {return tail;};

        friend ostream& operator<<(ostream&, LinkedList*);

        void destroy(DoubleLinkNode*);
        void insertPilot(DoubleLinkNode*);
        void sortLinkedList(string);
        bool swapNodes(string, DoubleLinkNode*, DoubleLinkNode*);
        bool searchList(string, double);

    protected:

    private:
        DoubleLinkNode *head;
        DoubleLinkNode *tail;

};

#endif // LINKEDLIST_H
