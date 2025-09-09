#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "Node.hpp"

#include<vector>

class Constraint
{

public:

    Constraint(Max::Node* n, std::vector<int> isConstraint)
    {
        m_nodeID = n->m_ID;
        m_isConstraint = isConstraint;
    }

    std::string GetSTring(){

        std::string dofList = "";

        for(int i = 0; i < (int)m_isConstraint.size(); i++)
        {

            dofList += std::to_string(m_isConstraint[i]);
            if(i < (int)m_isConstraint.size() - 1) dofList += ", ";
        }

        return "Constraint at node: " + std::to_string(m_nodeID) + "DOF list: " + dofList;
    }

    std::vector<int> m_isConstraint;
    int m_nodeID;
};

#endif