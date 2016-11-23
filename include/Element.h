#ifndef ELEMENT_H
#define ELEMENT_H

#include "Node.h"

// Element of a profile structure
class Element : public Base
{
    public:
        Element(int nNo, Node* n1, Node* n2, double dt);
        virtual ~Element();

        // input attributes
        int     nNo;        // Element's number
        double  dt;         // thickness
        //  |Node address
        //  ||arry of Node addresses
        Node**  pN;         // Node container
        int     nNoX;       // Number of Nodes:  2:line / 3:arg

        // result data, element's contribution to the section values
        double  dL;         // length
        double  dA;         // area
        double  dS[2];      // static moment
        double  dI[3];      // moment of inertia

        void listData();

        // initialize the result data
        void initResults();

        // calculate the elments result values
        void setData();

    protected:
    private:
};

#endif // ELEMENT_H
