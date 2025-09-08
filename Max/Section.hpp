#ifndef SECTION_H
#define SECTION_H

#include "Material.hpp"

class Section{

public:

    Section(double area, Material* material)
    {
        m_area = area;
        m_material = material;
    }

    std::string GetString(){

        return "Section: Area: " + std::to_string(m_area) + ", " + m_material->GetString();
    }

    double m_area;
    Material* m_material;
};

#endif