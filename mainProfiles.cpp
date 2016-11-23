#include <stdio.h>

#include "Base.h"
#include "Node.h"
#include "Element.h"
#include "Profile.h"

// #define EX_BASE_CHECK
 //#define EX_NODE_CHECK
// #define EX_ELEMENT_CHECK
//#define EX_ELEMENT_FL200X4
#define EX_PROFILE_CHECK

int main()
{

#if  defined(EX_BASE_CHECK)
    Base b;
    sprintf(Base::msg,"our first check!\n");
    b.appendLog(Base::msg);


#elif defined(EX_NODE_CHECK)
    // Node instance created on the stack
    Node n1 = Node();
    n1.nNo   = 1;
    n1.dx[0] = 2.;
    n1.dx[1] = 3.;
    n1.listData();

    // Node instance created on the Heap
    // do this for large memory bocks!!!
    // new is something like malloc
    Node* pn2 = new Node(2,21.,22.);
    pn2->listData();
    delete pn2;

// check the Element code: Fl 200x4
#elif defined(EX_ELEMENT_CHECK)
    Node*   pn1 = new Node(1,   0.,0.);
    Node*   pn2 = new Node(2, 200.,0.);

    // stack version
    Element pe1 = Element(1,pn1,pn2,4.);
    pe1.listData();
    // this is the same: (&pe1)->listData();

    // heap version
    Element* pe2 = new Element(2,pn1,pn2,4.);
    pe2->listData();

    delete pn1;
    delete
     pn2;
    delete pe2;

#elif defined(EX_ELEMENT_FL200X4)
    // check the results of an element
    // for a FL200x4 profile
    Node*    pn1 = new Node(1, 0.,-100);
    Node*    pn2 = new Node(2, 0.,+100);
    Element* pe1 = new Element(1,pn1,pn2,4.);
    pe1->setData();
    pe1->listData();

    delete pn1;
    delete pn2;
    delete pe1;

#elif defined(EX_PROFILE_CHECK)
    try
    {
        // check Profil class
        Profile* p = new Profile("Fl 200x4");
        p->addElementContainer(2);
        p->addNodeContainer(3);

        Node*    pn1 = new Node(1, 0.,-100.);
        Node*    pn2 = new Node(2, 0.,   0.);
        Node*    pn3 = new Node(3, 0.,+100.);
        Element* pe1 = new Element(1,pn1,pn2,4.);
        Element* pe2 = new Element(2,pn2,pn3,4.);
        p->addElement(pe1);
        p->addElement(pe2);
        p->setData();
        p->listData();
        delete p;
    }

    // if: string exception
    catch(const char* pS)
    {
        printf("Exception: %s",pS);
    }

    /*
    // else branch
    catch(...)
    {
        printf("Unhandled Exception\n");
    }
    */






#endif

    return 0;
}
