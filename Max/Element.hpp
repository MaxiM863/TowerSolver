#ifndef ELEMENT_H
#define ELEMENT_H

#include "Eigen/Dense"

#include <stdlib.h>
#include <iostream>
#include <string>

#include "Node.hpp"
#include "Section.hpp"

namespace Max
{
    class Element
    {
    public:
        
        int m_n1ID;
        int m_n2ID;

        int m_ID;

        Section* m_section;

        Element(int id, int n1ID, int n2ID, Section* section)
        {

            m_ID = id;
            
            m_n1ID = n1ID;
            m_n2ID = n2ID;

            m_section = section;
        }

        std::string get_string()
        { 
            std::string retVal = "";

            retVal += "Element:" + std::to_string(m_ID) + ", " + "Node-1: " + std::to_string(m_n1ID) + " ; " + "Node-2: " + std::to_string(m_n2ID);

            return retVal;
        }
    };
}

#endif