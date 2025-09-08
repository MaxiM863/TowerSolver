#include "Graphics.hpp"
#include "Eigen/Dense"

#include "Node.hpp"
#include "Element.hpp"
#include "Constraint.hpp"
#include "Force.hpp"

#include "Solver.hpp"

#include <vector>
#include <fstream>
#include <algorithm>

class Tests
{

public:

    bool test_1()
    {
        Max::Node n1(0, Eigen::Vector3d(0, 0, 0));
        Max::Node n2(1, Eigen::Vector3d(0.0001, 0, 0));
        Max::Node n3(2, Eigen::Vector3d(0.00005, 1, 0));

        std::vector<Max::Node> nodes;

        nodes.push_back(n1);
        nodes.push_back(n2);
        nodes.push_back(n3);

        Material m1(1, 0.3, 1000);

        Section s1(0.5, &m1);

        std::vector<Max::Element> Truss;

        Max::Element e1(0, 1, 2, &s1);
        Max::Element e2(1, 0, 2, &s1);
        //Max::Element e3(2, 1, 2, &s1);

        Truss.push_back(e1);
        Truss.push_back(e2);
        //Truss.push_back(e3);

        std::vector<Constraint> totalConstraint;

        Constraint c1(&n1, std::vector<int>{0, 1, 2});
        Constraint c2(&n2, std::vector<int>{0, 1, 2});

        totalConstraint.push_back(c1);
        totalConstraint.push_back(c2);

        Force f1(&n3, Eigen::Vector3d(0, -1, 0));

        std::vector<Force> forces;

        forces.push_back(f1);

        ///////////////////////////////////////////////////////////////

        Solver S;

        Eigen::MatrixXd K = S.AssembleKMatrix(nodes, Truss);

        S.consoleMatrix(K);

        std::vector<int> freeDOFElements = S.FindDOF(nodes, totalConstraint);

        Eigen::MatrixXd reducedMatrix = S.condenseMatrix(K, freeDOFElements);

        S.consoleMatrix(reducedMatrix);

        Eigen::MatrixXd forcesMatrix = S.BuildForcesMatrix(nodes, forces);

        S.consoleMatrix(forcesMatrix);

        Eigen::MatrixXd reducedVector = S.condenseVector(forcesMatrix, freeDOFElements);

        S.consoleMatrix(reducedVector);

        ////////////////////////////////////////////////////////////////
        
        Eigen::VectorXd x = reducedMatrix.colPivHouseholderQr().solve(reducedVector);

        S.consoleMatrix(x);

        Eigen::VectorXd result(3);
        result << 0, 1, 0;

        if(result.norm() - x.norm() > 0.0001) return false;

        return true;
    }
};