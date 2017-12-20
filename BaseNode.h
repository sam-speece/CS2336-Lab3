#ifndef BASENODE_H
#define BASENODE_H
#include <string>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class BaseNode
{
    public:
        BaseNode();
        BaseNode(string, double);

        virtual void setPilotName(string) = 0;
        virtual string getPilotName() = 0;
        virtual void setPilotArea(double) = 0;
        virtual double getPilotArea() = 0;

    protected:
        string pilotName;
        double pilotArea;

    private:
};

#endif // BASENODE_H
