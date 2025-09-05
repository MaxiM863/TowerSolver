#include <Eigen/Dense>

#include <stdlib.h>
#include <iostream>
#include <string>

class Node
{
public:

    Node(int id, Eigen::Vector3d position)
    {

        m_ID = id;
        m_pos = position;
    }

    Eigen::Vector3d m_pos;
    int m_ID;

    std::string get_string()
    { 
        std::string retVal = "";

        retVal += "ID:" + std::to_string(m_ID) + ", " + "Position-xyz:" + std::to_string(m_pos[0]) + ":" + std::to_string(m_pos[1]) + ":" + std::to_string(m_pos[2]);

        return retVal;
    }
};