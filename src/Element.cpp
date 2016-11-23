#include <stdio.h>
#include "Element.h"

#include <memory.h>
#include <math.h>

// constructor for line elements
Element::Element(int nNo, Node* n1, Node* n2, double dt)
{
    nNoX = 2;   // we have line!

    this->nNo   = nNo;
    this->dt    = dt;

    // allocate the Node container
    //       -Node address
    //       -----  | number of Node addresses
    pN    = new Node*[nNoX];
    pN[0] = n1;
    pN[1] = n2;

    // initialize the result values
    initResults();
}

// destructor
Element::~Element()
{
    // delete the Node container
    delete [] pN;
}

// initialize the result data
void Element::initResults()
{
    dL = 0.;
    dA = 0.;

    //       | inspecified address
    //       |    | address operator
    //       |    |   | 1st item
    //       |    |   |  | byte to use
    //       |    |   |  |
    memset((void*)&dS[0],0,sizeof(double)*2);
    memset((void*)&dI[0],0,sizeof(double)*3);

    /*! this we can do for array with only 1 index!
    memset((void*)dS,...)
    */
}

// calculation of the result data
// the element's contribution to the section value sum
void Element::setData()
{
    // helpers
    double  dxc[2];     // element's center coordinates
    double  dLp[2];     // projected length

    // check the node addresses
    for (int i=0;i<nNoX;i++)
    {
        if (!pN[i]) throw("*** error: node not available!");
    }

    // set the helpers
    for (int i=0;i<2;i++)

    {

        dxc[i] = (pN[0]->dx[i] + pN[1]->dx[i])/2.;
        dLp[i] = (pN[1]->dx[i] - pN[0]->dx[i]);
    }

    // calculate the element's length
    dL = sqrt(dLp[0]*dLp[0] + dLp[1]*dLp[1]);
    /*
    dL = sqrt(pow(dLp[0],2) + pow(dLp[1],2));
    */

    // element's area
    dA = dL*dt;

    // static moment
    for (int i=0;i<2;i++)
    {
        dS[i] = dxc[(i+1)%2]*dA;
    }

    // moment of inertia
    int j;
    for (int i=0;i<2;i++)
    {
        j     = (i+1)%2;
        dI[i] = (pow(dLp[j],2)/12. + pow(dxc[j],2))*dA;
    }
    dI[2] = (dLp[0]*dLp[1]/12. + dxc[0]*dxc[1])*dA;
}

// print Element data
void Element::listData()
{
    sprintf(msg,"> element %2d, node %2d - %2d, t = %6.2f\n",
                nNo,pN[0]->nNo,pN[1]->nNo,dt);
    appendLog(msg);

    for (int i=0;i<nNoX;i++) pN[i]->listData();

    // print the result data
    sprintf(msg,"  L.........: %12.5e mm\n",dL);
    appendLog(msg);
    sprintf(msg,"  A.........: %12.5e cm^2\n",dA/1.e2);
    appendLog(msg);
    sprintf(msg,"  Sx........: %12.5e cm^3\n",dS[0]/1.e3);
    appendLog(msg);
    sprintf(msg,"  Sy........: %12.5e cm^3\n",dS[1]/1.e3);
    appendLog(msg);
    sprintf(msg,"  Ixx.......: %12.5e cm^4\n",dI[0]/1.e4);
    appendLog(msg);
    sprintf(msg,"  Iyy.......: %12.5e cm^4\n",dI[1]/1.e4);
    appendLog(msg);
    sprintf(msg,"  Ixy.......: %12.5e cm^4\n",dI[2]/1.e4);
    appendLog(msg);
}
