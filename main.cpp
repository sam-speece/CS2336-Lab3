/*Project 3 - Maintenance Project
Sam Speece - sds160130
CS 2336.004
October 7, 2016*/

#include <stdlib.h>
#include <sstream>
#include "LinkedList.h"

using namespace std;

istream& operator>>(istream&, DoubleLinkNode&);
bool validatePilot(string);
string findName(string&);
double findArea(string&);
bool validateCommands(string);

int main()
{
    //initialize all variables and open all files
    ifstream inRoutes("pilot_routes3.txt");
    ifstream inCommands("commands3.txt");
    ofstream outResults("results.txt");
    ofstream outAreas("pilot_areas.txt");
    string line;
    LinkedList *pilotList;
    DoubleLinkNode *pilot;

    //if pilot_areas and pilot_routes are open then read in values and store them in DoubleLinkNodes and put them in the LinkedList
    if(inRoutes.is_open() && outAreas.is_open())
    {
        pilotList = new LinkedList;
        pilot = new DoubleLinkNode;

        while(!inRoutes.eof())
        {
            inRoutes >> *pilot;
            if(pilot->getPilotArea() != 0 && pilot->getPilotName() != "")
                pilotList->insertPilot(pilot);
            pilot = new DoubleLinkNode;
        }
    }else
        cout << "Could not find file.";

    //if commands.txt and results.txt is open the validate the line and then do the command
    if(inCommands.is_open() && outResults.is_open())
    {
        while(!inCommands.eof())
        {
            getline(inCommands, line);
            if(validateCommands(line))
            {
                if(line.substr(0, 4) == "sort")
                    pilotList->sortLinkedList(line.substr(5));
                else if(isalpha(line[0]))
                {
                    if(pilotList->searchList(line, 0))
                        outResults << setw(10) << left << line << "found" << endl;
                    else
                        outResults << setw(10) << left << line << "not found" << endl;
                }else if(isdigit(line[0]))
                {
                    double area = atof(line.c_str());
                    if(pilotList->searchList("", area))
                        outResults << setw(10) << left << line << "found" << endl;
                    else
                        outResults << setw(10) << left << line << "not found" << endl;
                }
            }
        }
    }else
        cout << "Could not find file.";

    outAreas << pilotList;

    delete pilotList;
    delete pilot;

    inRoutes.close();
    inCommands.close();
    outResults.close();
    outAreas.close();

    return 0;
}

//overloaded input operator that does input validation of line.  If the line is valid then it inserts the
//values into a DoubleLinkNode object and inserts it into the LinkedList.  If it's not valid then it does nothing.
istream& operator>>(istream& inData, DoubleLinkNode& pilot)
{
    string line;
    getline(inData, line);
    if(validatePilot(line))
    {
        pilot.setPilotName(findName(line));
        pilot.setPilotArea(findArea(line));
    }
    return inData;
}

//takes in the line and checks all possible invalid cases
bool validatePilot(string line)
{
    int numLetters, numDigits, numCommas, numDots, numInvalid;
    string check;

    //while string stream is not at the end of line, get a substring to the first space and check if it is all letters or if it is a coordinate
    //which is all numbers or comma and decimals
    stringstream ss(line);

    while(getline(ss, check, ' '))
    {
        //reset counters
        numLetters = 0;
        numDigits = 0;
        numCommas = 0;
        numDots = 0;
        numInvalid = 0;

        for(unsigned int i = 0; i < check.size(); i++)
        {
            if(isalpha(check[i]))
                numLetters++;
            else if(isdigit(check[i]))
                numDigits++;
            else if(check[i] == ',')
                numCommas++;
            else if(check[i] == '.')
                numDots++;
            else if(check[i] == '-')
                continue;
            else
                numInvalid++;
        }
        //checks for invalid characters not covered in counters (misc punctuation
        if(numInvalid > 0)
            return false;
        //checks there are no numbers or punctuation in name and no letters in coordinates
        if(numLetters > 0 && (numCommas > 0 || numDots > 0))
            return false;
        //checks there are spaces between each coordinate
        if(numCommas > 1)
            return false;
        //checks there is a comma and not a space between numbers in coordinates
        if(numDigits > 0 && numCommas == 0)
            return false;
    }
    return true;
}

//takes in a string which should contain the line from the file.  It assumes the line is valid and keeps adding each character
//to the string name from the string line until it comes across a number, then it truncates the line so that the name is not part
//of the string line and returns the string name.
string findName(string& line)
{
    int i = 0;
    string name;

    while(isalpha(line[i + 1]) || isspace(line[i + 1]))
    {
        if(isspace(line[i]))
        {
            if(line[i + 1] == ',')
                return "";
            if(!isalpha(line[i + 1]))
                return name;
        }
        name += line[i];
        i++;
    }
    line = line.substr(i + 1);

    return name;
}

//takes in the remaining string which should only contain a string line of coordinates.  It then loops through and counts the
//number of coordinates and instantiates the dynamic array.  Then it loops through a second time and converts each coordinate to a
//double and inserts it into the dynamic array.
double findArea(string& line)
{
    double *xArray, *yArray;
    double area = 0;
    int arraySize = 0, i = 0;
    string coordinate, number;
    bool isX = true, isY = false;

    //finds amount of coordinates in line
    for(unsigned int j = 0; j < line.size(); j++)
    {
        if(isspace(line[j]))
            arraySize++;
    }

    xArray = new double[arraySize + 2];
    yArray = new double[arraySize + 2];

    stringstream ss(line);
    while(getline(ss, coordinate, ' '))
    {
        if(isspace(coordinate[0]) || isspace(coordinate[coordinate.size() - 1]))
            return 0;
        stringstream ss2(coordinate);
        while(getline(ss2, number, ','))
        {
            if(isX)
            {
                xArray[i] = atof(number.c_str());
                isX = false;
                isY = true;

            }
            else if(isY)
            {
                yArray[i] = atof(number.c_str());
                isX = true;
                isY = false;
                i++;
            }
        }
    }

    //finds area using summation
    area += (xArray[1] + xArray[0]) * (yArray[1] - yArray[0]);
    i = 1;
    while(xArray[i] != xArray[0] || yArray[i] != yArray[0])
    {
        area += (xArray[i+1] + xArray[i]) * (yArray[i+1] - yArray[i]);
        i++;
    }
    delete xArray;
    delete yArray;

    if(area < 0)
        area = area * -1;

    return area/2.0;
}

//takes in a line from the commands.txt file and makes sure that the commands are valid
bool validateCommands(string line)
{
    stringstream ss(line);
    string check;
    int numLetters, numDigits, numDots, numInvalid;

    while(getline(ss, check, ' '))
    {
        numLetters = 0;
        numDigits = 0;
        numDots = 0;
        numInvalid = 0;

        for(unsigned int i = 0; i < check.size(); i++)
        {
            if(isalpha(check[i]))
                numLetters++;
            else if(isdigit(check[i]))
                numDigits++;
            else if(check[i] == '.')
                numDots++;
            else
                numInvalid++;
        }

        //checks there are no invalid characters
        if(numInvalid > 0)
            return false;
        //checks there are no numbers in words and no letters in numbers
        if(numLetters > 0 && (numDigits > 0 || numDots > 0))
            return false;
        //checks there aren't multiple dots in numbers
        if(numDigits > 0 && numDots > 1)
            return false;
    }
    return true;
}
