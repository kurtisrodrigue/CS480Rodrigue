#include "object.h"

Object::Object()
{
    char obj_file[50] = "../src/dragon.obj";
    LoadOBJ(obj_file);
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

void Object::Update(unsigned int dt)
{\
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

void Object::LoadOBJ(char* obj)
{
    std::ifstream fin(obj);
    char line_header[10];
    char garbage[50]; //for comments
    char obj_name[50];
    unsigned int temp_num;
    float temp1, temp2, temp3;
    srand(time(0));
    //std::cout << "LoadOBJ " << std::endl;


    while( fin.good()) {

        if (fin.peek() == '#')
        {
            fin.getline(garbage, 50);
        }
        else
        {
            fin >> line_header; // read till white space
            if (!strcmp(line_header, "o"))
            {
                fin >> obj_name;
            }

            if (!strcmp(line_header, "v"))
            {
                fin >> temp1 >> temp2 >> temp3;
                Vertices.push_back(Vertex(glm::vec3(temp1, temp2, temp3),
                                         glm::vec3(float(rand() % 1000)/float(1000), float(rand() % 1000)/float(1000), float(rand() % 1000)/float(1000))));
                fin.getline(garbage, 50);
            }
            else if (!strcmp(line_header, "vn"))
            {
                fin.getline(garbage, 50); //implement later
            }
            else if (!strcmp(line_header, "f"))
            {
                for(int i = 0; i < 3; i++) // read the triangle
                {
                    fin >> temp_num;
                    Indices.push_back(temp_num);
                    fin >> garbage; // the "//#" part
                }

            }
            else
            {
                fin.getline(garbage, 50); //implement later
            }
        }


    }

}


