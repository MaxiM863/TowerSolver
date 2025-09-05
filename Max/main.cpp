#include "Graphics.hpp"
#include "Eigen/Dense"

#include "Node.hpp"
#include "Element.hpp"

using namespace Eigen;
using namespace Max;

int main(int argv, char** args)
{

    Node n1(0, Vector3d(0, 0, 0));
    Node n2(0, Vector3d(0, 0, 1));

    Element e1(0, &n1, &n2);
    
    Graphics G;

    G.MaximRender();

    return 0;
}