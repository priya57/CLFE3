#ifndef NODE_H
#define NODE_H

#include "Base.h"

// Node of the profile
class Node : public Base
{
    public:
        // Node();      // Defaultinterface: no parameters
        Node(int nNo = 0, double dx = 0., double dy = 0.);
        virtual ~Node();

        int     nNo;    // Node's number
        double  dx[2];  // Coordinates

        // list the Node's data
        void    listData();

    protected:
    private:
};

#endif // NODE_H
