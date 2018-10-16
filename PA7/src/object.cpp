#include "object.h"

Object::Object(std::string file)
{
    orbit_direction = 1;
    spin_direction = 1;

    LoadOBJ("../assets/sphere.obj");

    Magick::Image *image;
    image = new Magick::Image(file);
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

Moon::Moon(Planet* origin) : Object("../assets/8k_mercury.jpg")
{
    m_planet = origin;
    orbit_radius = 3;
}

Planet::Planet(std::string file) : Object(file)
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


    model = glm::scale(glm::mat4(1.0f), glm::vec3(m_size, m_size, m_size));
    model = glm::translate(model, glm::vec3(orbit_radius * cos(orbit_angle),0,orbit_radius * sin(orbit_angle)));
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

glm::mat4 Object::Scale()
{
	return glm::scale(model, glm::vec3(m_size, m_size, m_size));
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);

    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,Texture));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glActiveTexture(GL_TEXTURE0);
  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
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
        orbit_angle += m_orbitSpeed * dt * M_PI/15000;
    }
    else
    {
        orbit_angle -= m_orbitSpeed * dt * M_PI/15000;
    }
    if(spin_direction)
    {
        angle +=  dt * M_PI/7000;
    }
    else
    {
        angle -=  dt * M_PI/7000;
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
    model = glm::scale(model, glm::vec3(m_size/750.0f, m_size/750.0f, m_size/750.0f));


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
            {
	            temp_textures = glm::vec2(m_aiscene->mMeshes[i]->mTextureCoords[0][j].x,
	                                      m_aiscene->mMeshes[i]->mTextureCoords[0][j].y);
            }


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

Sun::Sun(std::string file) : Object(file)
{
    orbit_radius = 0;
    m_size = 15;

    m_planets.push_back(new Mercury("../assets/8k_mercury.jpg"));
    m_planets.push_back(new Venus("../assets/8k_venus_surface.jpg"));
    m_planets.push_back(new Earth("../assets/1_earth_8k.jpg"));
    m_planets.push_back(new Mars("../assets/8k_mars.jpg"));
    m_planets.push_back(new Jupiter("../assets/8k_jupiter.jpg"));
    m_planets.push_back(new Saturn("../assets/8k_saturn.jpg"));
    m_planets.push_back(new Uranus("../assets/2k_uranus.jpg"));
    m_planets.push_back(new Neptune("../assets/2k_neptune.jpg"));
    m_planets.push_back(new Pluto("../assets/pluto_texture.jpg"));
}

void Sun::refactorOrbits()
{
    static bool factored = false;
    if(factored)
    {
       for(int i = 0; i < m_planets.size(); i++)
       {
           m_planets[i]->orbit_radius *= m_planets[i]->orbit_radius;
       }
       factored = false;
    }
    else
    {
        for(int i = 0; i < m_planets.size(); i++)
        {
            m_planets[i]->orbit_radius = sqrt(m_planets[i]->orbit_radius);
        }
        factored = true;
    }
}

void Sun::Update(unsigned int dt)
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



    model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 1.0, 0.0));
    model = glm::scale(model, glm::vec3(m_size/10.0f, m_size/10.0f, m_size/10.0f));
}

Mercury::Mercury(std::string file): Planet(file)
{

    orbit_radius = 3.9;
    m_size = 38;
    m_orbitSpeed = 5.5;
}

Venus::Venus(std::string file): Planet(file)
{

    orbit_radius = 7.2;
	m_size = 94;
    m_orbitSpeed = 4.3;
}

Earth::Earth(std::string file): Planet(file)
{

    orbit_radius = 10;
	m_size = 100;
    m_orbitSpeed = 3.8;
}

Mars::Mars(std::string file): Planet(file)
{

	orbit_radius = 15.2;
	m_size = 53;
    m_orbitSpeed = 3.2;
}

Jupiter::Jupiter(std::string file): Planet(file)
{

	orbit_radius = 50.2;
	m_size = 1121;
    m_orbitSpeed = 5.5;
}

Saturn::Saturn(std::string file): Planet(file)
{

	orbit_radius = 95.8;
	m_size = 945;
    m_orbitSpeed = 3.4;
}

Uranus::Uranus(std::string file): Planet(file)
{

	orbit_radius = 192;
	m_size = 401;
    m_orbitSpeed = 7.6;
}

Neptune::Neptune(std::string file): Planet(file)
{

	orbit_radius = 300.5;
	m_size = 388;
    m_orbitSpeed = 2.2;
}

Pluto::Pluto(std::string file): Planet(file)
{

	orbit_radius = 394.8;
	m_size = 18.6;
    m_orbitSpeed = 1.7;
}