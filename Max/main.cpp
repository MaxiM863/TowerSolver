#include "Graphics.hpp"
#include "Eigen/Dense"
#include "Solver.hpp"
#include "Tests.hpp"

#include <vector>
#include <fstream>
#include <algorithm>


using namespace Eigen;
using namespace Max;
using namespace std;

int main(int argv, char** args)
{

    Tests T;

    if(!T.test_1()){

        std::cout << "Test as fail" << std::endl;

        return 1;
    } 

    ////////////////////////////////////////////////////////////////

    std::cout << "Bonjour!" << std::endl << "Program of Truss entity computation:" << std::endl << std::endl;

    /*
    if(argv == 1) return 2;

    std::ifstream file(args[1]); // Open the file
    if (!file) {
        std::cerr << "Error: File could not be opened!" << std::endl;
        return 1;
    }

    /////////////////////////////////////////////////////////////////


    std::vector<Max::Node> nodes;

    Material m1(1, 0.3, 1000);

    Section s1(0.5, &m1);

    std::vector<Max::Element> Truss;

    std::vector<Constraint> totalConstraint;

    std::vector<Force> forces;


    std::string line;
    while (std::getline(file, line)) { 
        
        // Read line by line
        std::cout << line << std::endl; // Print each line
        
        if(line.substr(1) == "N")
        {
            

            std::stringstream ss(line.substr(7));
            std::string word;
            std::vector<std::string> result;

            while (std::getline(ss, word, ' ')) { // Split by space
                
                result.push_back(word);
            }
        }
    }

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

    S.consoleMatrix(x);*/


    ////////////////////////////////////////////////////////////////
    Graphics G;

    G.MaximRender();

    return 0;
}