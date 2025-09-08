#ifndef SOLVER_H
#define SOLVER_H

#include "Eigen/Dense"

#include "Node.hpp"
#include "Element.hpp"
#include "Constraint.hpp"
#include "Force.hpp"

#include <vector>
#include <fstream>
#include <algorithm>

class Solver
{


public:


    Eigen::MatrixXd condenseMatrix(const Eigen::MatrixXd& matrix, const std::vector<int>& freeDOFs) 
    {
        int n = (int)freeDOFs.size();
        Eigen::MatrixXd condensedMatrix(n, n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                condensedMatrix(i, j) = matrix(freeDOFs[i], freeDOFs[j]);
            }
        }

        return condensedMatrix;
    }

    Eigen::MatrixXd condenseVector(const Eigen::MatrixXd& vector, const std::vector<int>& freeDOFs) 
    {
        int n = (int)freeDOFs.size();
        Eigen::MatrixXd condensedVector(n,1);

        
        for (int j = 0; j < n; ++j) {

            condensedVector(j, 0) = vector(freeDOFs[j]);
        } 

        return condensedVector;
    }

    void consoleMatrix(const Eigen::MatrixXd& data)
    {

        // Create an ofstream object
        std::ofstream outFile("outputData.txt");

        for(int i = 0; i < data.rows(); i++)
        {

            for(int j =0; j< data.cols(); j++)
            {
                double d = data(i, j);

                outFile << d << " : ";
            }

            outFile << std::endl;
        }

        outFile << std::endl;

        outFile.close();
    }

    void consoleVector(const Eigen::VectorXd& data)
    {

        // Create an ofstream object
        std::ofstream outFile("outputDataVec.txt");

        for(int i = 0; i < data.size(); i++)
        {

            double d = data(i);

                outFile << d << " : ";
            
        }

        outFile << std::endl;

        outFile.close();
    }

    // Function to assemble the global stiffness matrix
    void assembleGlobalMatrix(Eigen::MatrixXd& globalK, const Eigen::MatrixXd& elementK, const std::vector<int>& dofMap) 
    {
        for (int i = 0; i < (int)dofMap.size(); ++i) {
            for (int j = 0; j < (int)dofMap.size(); ++j) {

                globalK(dofMap[i], dofMap[j]) += elementK(i, j);
            }
        }
    }

    void multiplyInGlobalMatrix(Eigen::MatrixXd& globalK, const std::vector<int>& dofMap, double factor) 
    {
        for (int i = 0; i < (int)dofMap.size(); ++i) {
            for (int j = 0; j < (int)dofMap.size(); ++j) {

                globalK(dofMap[i], dofMap[j]) *= factor;
            }
        }
    }

    Eigen::MatrixXd AssembleKMatrix(std::vector<Max::Node> nodes, std::vector<Max::Element> Truss)
    {
        const int aaa = 3 * (int)nodes.size();

        Eigen::MatrixXd Total_DOF(aaa, aaa);
        Total_DOF.setZero();
        
        for(int ii = 0; ii < (int)Truss.size(); ii++)
        {

            Eigen::Matrix<double,6,6> K = computeElementStiffness(nodes[Truss[ii].m_n2ID].m_pos, nodes[Truss[ii].m_n1ID].m_pos, Truss[ii].m_section->m_material->m_YoungModulus * Truss[ii].m_section->m_area / (nodes[Truss[ii].m_n2ID].m_pos - nodes[Truss[ii].m_n1ID].m_pos).norm());

            consoleMatrix(K);

            std::vector<int> dofMap;

            for(int op = 0; op < 3; op++)
            {
            
                dofMap.push_back(Truss[ii].m_n1ID * 3 + op);
                dofMap.push_back(Truss[ii].m_n2ID * 3 + op);
            }

            // Sort in ascending order
            std::sort(dofMap.begin(), dofMap.end());
            
            assembleGlobalMatrix(Total_DOF, K, dofMap);
        }

        consoleMatrix(Total_DOF);
        
        double commonFactor = 1;

        for(int i = 0; i < (int)Truss.size(); i++)
        {

            commonFactor *= (nodes[Truss[i].m_n2ID].m_pos - nodes[Truss[i].m_n1ID].m_pos).norm();
        }

        for(int ii = 0; ii < (int)Truss.size(); ii++)
        {

            std::vector<int> dofMap;

            for(int op = 0; op < 3; op++)
            {
            
                dofMap.push_back(Truss[ii].m_n1ID * 3 + op);
                dofMap.push_back(Truss[ii].m_n2ID * 3 + op);
            }
                
            std::sort(dofMap.begin(), dofMap.end());

            multiplyInGlobalMatrix(Total_DOF, dofMap, commonFactor / (nodes[Truss[ii].m_n2ID].m_pos - nodes[Truss[ii].m_n1ID].m_pos).norm());       
        }

        return Total_DOF;
    }

    Eigen::MatrixXd computeElementStiffness(const Eigen::Vector3d& node1, const Eigen::Vector3d& node2, const double EAL) {

        Eigen::Vector3d L = node2 - node1;

        consoleMatrix(L);

        double length = L.norm();
        Eigen::Vector3d direction = L / length;

        consoleMatrix(direction);

        Eigen::MatrixXd a(2,6);
        a << L[0], L[1], L[2], 0, 0, 0, 0, 0, 0, L[0], L[1], L[2];


        consoleMatrix(a);

        Eigen::MatrixXd b(2,2);
        b << 1, -1, -1, 1;

        consoleMatrix(b);

        Eigen::MatrixXd kLocal = a.transpose() * b * a;


        consoleMatrix(kLocal);

        // Local stiffness matrix in the element's coordinate system
        /*MatrixXd kLocal(2, 2);
        kLocal << 1, -1,
                -1,  1;

        // Scale by EA/L
        kLocal *= EAL;

        // Expand to global stiffness matrix
        MatrixXd kGlobal(6, 6);
        kGlobal.setZero();
        kGlobal.block<3, 3>(0, 0) = kLocal(0, 0) * T.block<3, 3>(0, 0);
        kGlobal.block<3, 3>(0, 3) = kLocal(0, 1) * T.block<3, 3>(0, 0);
        kGlobal.block<3, 3>(3, 0) = kLocal(1, 0) * T.block<3, 3>(0, 0);
        kGlobal.block<3, 3>(3, 3) = kLocal(1, 1) * T.block<3, 3>(0, 0);
    */
        return EAL * kLocal;
    }

    std::vector<int> FindDOF(std::vector<Max::Node> nodes, std::vector<Constraint> totalConstraint)
    {
        std::vector<int> freeDOFElements;

        for(int ii = 0; ii < (int)nodes.size(); ii++)
        {       
            for(int j = 0; j < 3; j++)
            {

                bool test = false;

                for(int u = 0; u < (int)totalConstraint.size(); u++)
                {

                    for(int y = 0; y < (int)totalConstraint[u].m_isConstraint.size(); y++)
                    {                        
                        int posInMatrix = totalConstraint[u].m_nodeID * 3 + totalConstraint[u].m_isConstraint[y];
                        if(posInMatrix == 3 * ii + j)
                        {

                            test = true;
                        }
                    }
                }

                if(!test)
                {
                    
                    bool test2 = false;

                    for(int u=0; u < (int)freeDOFElements.size(); u++)
                    {

                        if(freeDOFElements[u] == 3 * ii + j) test2 = true;
                    }

                    if(!test2)
                    {
                        
                        freeDOFElements.push_back(3 * ii + j);
                    }
                }
            }
        }

        return freeDOFElements;
    }

    Eigen::MatrixXd BuildForcesMatrix(std::vector<Max::Node> nodes, std::vector<Force> forces)
    {

        Eigen::MatrixXd forcesAdded(3 * nodes.size(), 1);
        forcesAdded.setZero();

        for(int ii = 0; ii < (int)nodes.size(); ii++)
        {
            
            for(int i = 0; i < (int)forces.size(); i++)
            {
                if(forces[i].m_ID == ii)
                {

                    forcesAdded(ii * 3 + 0, 0) += (forces[i].m_force)[0];
                    forcesAdded(ii * 3 + 1, 0) += (forces[i].m_force)[1];
                    forcesAdded(ii * 3 + 2, 0) += (forces[i].m_force)[2];
                }
            }
        }

        return forcesAdded;
    }
};

#endif