#include "object.h"

Object::Object()
{
	std::string obj_file = "../assets/";
	std::string file_name;
	std::cout << "Please enter the name of the file you would like to load (include extension): " << std::endl;
	std::cin >> file_name;
	obj_file = obj_file + file_name;
	LoadOBJ(obj_file.c_str());
	/* The index works at a 0th index
	for(unsigned int i = 0; i < Indices.size(); i++)
	{
	Indices[i] = Indices[i] - 1;
	}*/

	Magick::Image *image;
	image = new Magick::Image("../assets/granite.jpg");
	image->write(&m_blob, "RGBA");

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	delete image;


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
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

	glActiveTexture(GL_TEXTURE0);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
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
