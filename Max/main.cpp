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

    std::ifstream file(args[1]); // Open the file
    if (!file) {
        std::cerr << "Error: File could not be opened!" << std::endl;
        return 1;
    }

    /////////////////////////////////////////////////////////////////


    


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






    ////////////////////////////////////////////////////////////////
    //Graphics G;

    //G.MaximRender();

    return 0;
}