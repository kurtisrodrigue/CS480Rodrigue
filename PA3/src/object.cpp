#include "object.h"

Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */

  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  angle = 0.0f;
  orbit_angle = 0.0f;
  orbit_radius = 10;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

Moon::Moon(Planet* origin)
{
    m_planet = origin;
    orbit_radius = 3;

}

Planet::Planet()
{

}

void Object::Update(unsigned int dt)
{
    if(orbit_direction)
    {
        orbit_angle += dt * M_PI/1000;
    }
    else
    {
        orbit_angle -= dt * M_PI/1000;
    }
    if(spin_direction)
    {
        angle +=  dt * M_PI/10;
    }
    else
    {
        angle -=  dt * M_PI/10;
    }

    model = glm::translate(glm::mat4(1.0f), glm::vec3(orbit_radius * cos(orbit_angle),0,orbit_radius * sin(orbit_angle)));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));

   //model = glm::translate(model, glm::vec3(orbit_radius * cos(orbit_angle),0,orbit_radius * sin(orbit_angle)));

    if(orbit_angle > 360)
    {
        orbit_angle -= 360;
    }
    if(angle > 360)
    {
        angle -= 360;
    }

}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

void Moon::Update(unsigned int dt)
{
    glm::mat4 temp_model(m_planet->model);
    if(orbit_direction)
    {
        orbit_angle += dt * M_PI/357;
    }
    else
    {
        orbit_angle -= dt * M_PI/357;
    }
    if(spin_direction)
    {
        angle +=  dt * M_PI/500;
    }
    else
    {
        angle -=  dt * M_PI/500;
    }

    model = glm::translate(glm::mat4(1.0f), glm::vec3(m_planet->orbit_radius * cos(m_planet->orbit_angle),0,m_planet->orbit_radius * sin(m_planet->orbit_angle)));
    model = glm::translate(model, glm::vec3(orbit_radius * cos(orbit_angle),0,orbit_radius * sin(orbit_angle)));
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

    if(orbit_angle > 360)
    {
        orbit_angle -= 360;
    }
    if(angle > 360)
    {
        angle -= 360;
    }
}

void Moon::Render()
{
    Object::Render();
}

void Planet::Update(unsigned int dt)
{
    if(orbit_direction)
    {
        orbit_angle += dt * M_PI/1500;
    }
    else
    {
        orbit_angle -= dt * M_PI/1500;
    }
    if(spin_direction)
    {
        angle +=  dt * M_PI/700;
    }
    else
    {
        angle -=  dt * M_PI/700;
    }

    model = glm::translate(glm::mat4(1.0f),
            glm::vec3(orbit_radius * cos(orbit_angle),
                    0,
                    orbit_radius * sin(orbit_angle)));

    for(int i = 0; i < m_moons.size(); i++)
    {
        m_moons[i]->model = glm::translate(glm::mat4(1.0f),
                                          glm::vec3(orbit_radius * cos(orbit_angle),
                                                    0,
                                                    orbit_radius * sin(orbit_angle)));
    }

    model = glm::rotate(model, angle, glm::vec3(0.0, 1.0, 0.0));

    if(orbit_angle > 360)
    {
        orbit_angle -= 360;
    }
    if(angle > 360)
    {
        angle -= 360;
    }
}
