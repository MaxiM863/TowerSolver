#ifndef FORCE_H
#define FORCE_H

#include <sstream>
#include "Eigen/Dense"

#include "Node.hpp"

class Force
{

public:

    Force(Max::Node* n, Eigen::Vector3d& force)
    {
        m_ID = n->m_ID;
        m_force = force;
    }

    std::string GetString(){

        std::stringstream a;

        a << m_force;       

        return "Force nbr: " + std::to_string(m_ID) + ", " + a.str();
    }

    int m_ID;
    Eigen::Vector3d m_force;
};

#endif