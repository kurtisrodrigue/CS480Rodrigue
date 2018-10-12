#include "object.h"

Object::Object()
{
    LoadOBJ("../assets/sphere.obj");
    
    Magick::Image *image;
    image = new Magick::Image("../assets/8k_sun.jpg");
    image->write(&m_blob, "RGBA");

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    delete image;

  angle = 0.0f;
  orbit_angle = 0.0f;

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

void Object::LoadOBJ(const char* obj)
{
    Assimp::Importer importer;
    std::ifstream fin(obj);
    
    m_aiscene = importer.ReadFile(obj, aiProcess_Triangulate);
    
    for (int i = 0; i < m_aiscene->mNumMeshes; i++) {
        for (int j = 0; j < m_aiscene->mMeshes[i]->mNumVertices; j++) {
            glm::vec3 temp_vertex(float(m_aiscene->mMeshes[i]->mVertices[j].x),
                                  float(m_aiscene->mMeshes[i]->mVertices[j].y),
                                  float(m_aiscene->mMeshes[i]->mVertices[j].z));
            glm::vec2 temp_textures;
            if(m_aiscene->mMeshes[i]->mTextureCoords[0] != NULL)
            temp_textures = glm::vec2(float(m_aiscene->mMeshes[i]->mTextureCoords[0][j].x),
                                      float(m_aiscene->mMeshes[i]->mTextureCoords[0][j].y));
            
            Vertices.push_back(Vertex(temp_vertex, temp_vertex,temp_textures));
        }
        
        
    }
    for (int i = 0; i < m_aiscene->mNumMeshes; i++) {
        for (int j = 0; j < m_aiscene->mMeshes[i]->mNumFaces; j++) {
            Indices.push_back(m_aiscene->mMeshes[i]->mFaces[j].mIndices[0]);
            Indices.push_back(m_aiscene->mMeshes[i]->mFaces[j].mIndices[1]);
            Indices.push_back(m_aiscene->mMeshes[i]->mFaces[j].mIndices[2]);
            
        }
    }
}

Sun::Sun()
{
    texture_file = "../assets/8k_sun.jpg";

    orbit_radius = 0;
}

Mercury::Mercury()
{
	texture_file = "../assets/8k_mercury.jpg";

    orbit_radius = 4;
}

Venus::Venus()
{
    texture_file = "../assets/8k_venus_surface.jpg";

    orbit_radius = 6;
}

Earth::Earth()
{
    texture_file = "../assets/1_earth_8k.jpg";

    orbit_radius = 8;
}

Mars::Mars()
{
	texture_file = "../assets/8k_mars.jpg";

	orbit_radius = 10;
}

Jupiter::Jupiter()
{
	texture_file = "../assets/8k_jupiter.jpg";

	orbit_radius = 16;
}

Saturn::Saturn()
{
	texture_file = "../assets/8k_saturn.jpg";

	orbit_radius = 20;
}

Uranus::Uranus()
{
	texture_file = "../assets/2k_uranus.jpg";

	orbit_radius = 24;
}

Neptune::Neptune()
{
	texture_file = "../assets/2k_neptune.jpg";

	orbit_radius = 28;
}

Pluto::Pluto()
{
	texture_file = "../assets/pluto_texture.jpg";

	orbit_radius = 4;
}