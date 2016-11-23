#ifndef PROFILE_H
#define PROFILE_H

#include "Base.h"

// specify the classes
class Node;
class Element;

class Profile : public Base
{
    public:
        Profile(const char* pName);
        virtual ~Profile();

        // methods

        // memory to store Node instances
        int addNodeContainer(int nLength);

        // memory to store Element instances
        int addElementContainer(int nLength);

        // insert an element
        int addElement(Element* pE);

        // delete instances
        void resetContainers();

        // checking methodes
        int checkElement(Element* pE);
        int checkNode(Node* pN);

        // result methodes
        void resetResults();    // initialize the result data
        void setData();         // calculate the results

        void listData();        // list the profile's data

        // attributs
        char    pName[256];     // profile name

        //  |Node address
        //  ||arry of Node addresses
        Node**      pNC;        // Node container
        int         nNoX;       // max. number of Nodes

        //  |Element address
        //  ||arry of Element addresses
        Element**   pEC;        // Element container
        int         nElX;       // max. number of Elements

        // section values
        double      dA;         // area
        double      dS[2];      // static moment
        double      dIu[3];     // I in user csys
        double      de[2];      // center of mass
        double      dIc[3];     // I in center of mass csys
        double      dIp[2];     // I in main csys
        double      dAlpha;     // rotation angle

        // helpers
        double      dEps;       // precision, minimal positiv number

    protected:
    private:
};

#endif // PROFILE_H
