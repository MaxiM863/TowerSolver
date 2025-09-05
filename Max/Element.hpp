#include <Eigen/Dense>

#include <stdlib.h>
#include <iostream>
#include <string>

#include "Node.hpp"

class Element
{
public:
    
    Node* m_n1;
    Node* m_n2;

    int m_ID;

    Element(int id, Node* n1, Node* n2)
    {

        m_ID = id;
        
        m_n1 = n1;
        m_n2 = n2;
    }

    std::string get_string()
    { 
        std::string retVal = "";

        retVal += "Element:" + std::to_string(m_ID) + ", " + m_n1->get_string() + " ; " + m_n2->get_string();

        return retVal;
    }
};