#include "Profile.h"
#include "Element.h"

#include <string.h>
#include <stdio.h>

Profile::Profile(const char* pName)
{
    // this->pName = pName;  // not working!!
    //      | destination char*
    //      |            | source: const char*
    strcpy(this->pName,pName);

    // initialize the containers
    nNoX = 0;
    pNC  = 0;       // no Node container memory!!!    nElX = 0;
    pEC  = 0;       // no Element container memory!!!    dEps = 0.1;

    // reset the result variables
    resetResults();
}

Profile::~Profile()
{
    // all stored instances are
    // removed automatically
    resetContainers();
}

// create the Element container
int Profile::addElementContainer(int nLength)
{
    // check old container
    if (pEC) throw ("*** error: Element container already exists!\n");

    // check the length
    if (nLength < 1) throw("*** error: wrong container length!\n");

    // allocate the memory
    //               |Element address
    //               |  |vector to store element addresses
    pEC = new Element*[nLength];
    if (!pEC) throw("*** error: allocating the Element container!\n");

    // initialize with 0-values: no instance are stored
    memset((void*)pEC,0,sizeof(Element*)*nLength);

    // store the length
    nElX = nLength;

    return 1;
}

// create the Node container
int Profile::addNodeContainer(int nLength)
{
    // check old container
    if (pNC) throw ("*** error: Node container already exists!\n");

    // check the length
    if (nLength < 1) throw("*** error: wrong container length!\n");

    // allocate the memory
    //               |Node address
    //               |  |vector to store node addresses
    pNC = new Node*[nLength];
    if (!pNC) throw("*** error: allocating the Node container!\n");

    // initialize with 0-values: no instance are stored
    memset((void*)pNC,0,sizeof(Node*)*nLength);

    // store the length
    nNoX = nLength;

    return 1;
}

// add an element to the element container
int Profile::addElement(Element* pE)
{
    // check the element data
    checkElement(pE);

    // add the Element instance,
    // if an instance already exists delete it
    if (pEC[pE->nNo -1]) delete pEC[pE->nNo -1];
    pEC[pE->nNo -1] = pE;

    // do the same for the nodes
    for (int i=0;i<pE->nNoX;i++)
    {
        if (pNC[pE->pN[i]->nNo -1])
        {
            if (pNC[pE->pN[i]->nNo -1] != pE->pN[i])
            delete pNC[pE->pN[i]->nNo -1];
        }
        pNC[pE->pN[i]->nNo -1] = pE->pN[i];
    }

    return 1;
}

// check the element's data
int Profile::checkElement(Element* pE)
{
    // valid element?
    if (!pE) throw("*** error: unvalid Element address!\n");

    // indexing ok: we use 1 based indexing
    if (pE->nNo < 1 || pE->nNo > nElX)
    {
        sprintf(msg,"*** error: element %d invalid number.\n",pE->nNo);
        throw(msg);
    }

    // check the thickness
    if (pE->dt < dEps)  throw("*** error: invalid element thickness.\n");

    // check the node instances of the element
    for (int i=0;i<pE->nNoX;i++)
    {
        checkNode(pE->pN[i]);
    }

    return 1;
}

// check the node's data
int Profile::checkNode(Node* pN)
{
    if (!pN) throw("*** error: invalid Node address.\n");

    if (pN->nNo < 1 || pN->nNo > nNoX)
             throw("*** error: invalid Node number!\n");

    return 1;
}

// free all allocated memory
void Profile::resetContainers()
{
    // free all Element instances
    for (int i;i<nElX;i++)
    {
        if (pEC[i]) delete pEC[i];
    }
    // reset the container
    delete [] pEC;
    pEC  = 0;        // reset the address
    nElX = 0;        // reset the length

    // free all Node instances
    for (int i;i<nNoX;i++)
    {
        if (pNC[i]) delete pNC[i];
    }
    // reset the container
    delete [] pNC;
    pNC  = 0;        // reset the address
    nNoX = 0;        // reset the length
}

// reset all result data
void Profile::resetResults()
{
    dA      = 0.;
    memset((void*)dS,   0,sizeof(double)*2);
    memset((void*)dIu,  0,sizeof(double)*3);
    memset((void*)de,   0,sizeof(double)*2);
    memset((void*)dIc,  0,sizeof(double)*3);
    memset((void*)dIp,  0,sizeof(double)*2);
    dAlpha  = 0.;
}

// calculate the profile's section values
void Profile::setData()
{
    // sum up all element values
    for (int i=0;i<nElX;i++)
    {
        // if element not exists, try next
        if (!pEC[i])    continue;

        // calculate the element's contribution
        pEC[i]->setData();

        // sum up element values
        dA += pEC[i]->dA;
        for (int j=0;j<2;j++) dS[j] +=pEC[i]->dS[j];
        for (int j=0;j<3;j++) dIu[j]+=pEC[i]->dI[j];

    }
}

// print the profile's data
void Profile::listData()
{
    sprintf(msg,"Profile................: %s\n",pName);
    appendLog(msg);

    // print elements data
    for (int i=0;i<nElX;i++)
    {
        // if element not exists, try next
        if (!pEC[i])    continue;
        pEC[i]->listData();
    }

    // print the result values
    sprintf(msg,"Area...................: %10.2f cm^2\n",dA/1.e2);
    appendLog(msg);
    sprintf(msg,"Static Moment..........: %10.2f %10.2f cm^3\n",
                                            dS[0]/1.e3,dS[1]/1.e3);
    appendLog(msg);
    sprintf(msg,"Moment of Inertia......: %10.2f %10.2f %10.2f cm^4\n",
                                            dIu[0]/1.e4,dIu[1]/1.e4,dIu[2]/1.e4);
    appendLog(msg);

}



