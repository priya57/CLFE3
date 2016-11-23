#include "Node.h"
#include <stdio.h>

// default constructor
// (not needed because the second has optional parameters)
/*
Node::Node()
{
    nNo   = 0;
    dx[0] = 0.;
    dx[1] = 0.;
}
*/

// constructor with parameter interface
Node::Node(int nNo, double dx, double dy)
{
    this->nNo   = nNo;
    this->dx[0] = dx;
    this->dx[1] = dy;
}

// destructor
Node::~Node()
{
    //dtor
}

// print the data to the output device
void Node::listData()
{
    sprintf(msg,"> node: %2d, x = %10.3f, y = %10.3f\n",nNo,dx[0],dx[1]);
    appendLog(msg);
}

