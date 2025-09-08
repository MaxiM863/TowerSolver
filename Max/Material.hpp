#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{

public:

    Material(double youngModulus, double poisson, double density)
    {
        m_YoungModulus = youngModulus;
        m_poisson = poisson;
        m_density = density;
    }

    std::string GetString(){

        return "Material: " + std::to_string(m_YoungModulus);
    }

    double m_YoungModulus;
    double m_poisson;
    double m_density;


};

#endif