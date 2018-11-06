#include "object.h"

Object::Object()
{

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::Object(const char* obj, const char* tex, float siz)
{
	size = siz;

	LoadOBJ(obj, tex);

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
{
	btTransform trans;
	btScalar m[16];
	m_physics->m_dynamicsWorld->stepSimulation(dt, 1);
	m_rigidbody->getMotionState()->getWorldTransform(trans);
	trans.getOpenGLMatrix(m);
	model = glm::make_mat4(m);
	Scale();


}

void Object::Scale()
{
	model = glm::scale(model,glm::vec3(size,size,size));
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

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}


void Object::LoadOBJ(const char* obj, const char* tex)
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
				                          -m_aiscene->mMeshes[i]->mTextureCoords[0][j].y);
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

	Magick::Image *image;
	image = new Magick::Image(tex);
	image->write(&m_blob, "RGBA");

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(), image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete image;
}


