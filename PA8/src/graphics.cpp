#include "graphics.h"

Graphics::Graphics()
{

  ambient = glm::vec4(0.3f, 0.3f, 0.1f, 1);
  specular = glm::vec4(0.3f, 0.3f, 0.1f, 1);
  diffuse = glm::vec4(0.3f, 0.3f, 0.1f, 1);

  per_frag = true;
}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }
  phys_eng = new PhysicsEngine;
  phys_eng->createObjects();

  // Set up the shaders
  m_shader.push_back(new Shader("../shaders/shader.frag", "../shaders/shader.vert"));
  if(!m_shader[0]->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader[0]->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader[0]->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader[0]->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  m_shader.push_back(new Shader("../shaders/perfrag.frag", "../shaders/pervert.vert"));
  if(!m_shader[1]->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader[1]->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader[1]->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader[1]->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader[per_frag]->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader[per_frag]->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader[per_frag]->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }


  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{
  // Update the object
  phys_eng->Update(dt);
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 temp = m_camera->GetView();
	//light == camera position
	light = glm::vec4(temp[0][3], temp[1][3], temp[1][3], 1.0f);

  // Start the correct program
  m_shader[per_frag]->Enable();
  m_projectionMatrix = m_shader[per_frag]->GetUniformLocation("projectionMatrix");
  m_viewMatrix = m_shader[per_frag]->GetUniformLocation("viewMatrix");
  m_modelMatrix = m_shader[per_frag]->GetUniformLocation("modelMatrix");

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

  // Render the objects
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(phys_eng->m_plane->GetModel()));
  phys_eng->m_plane->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(phys_eng->m_ball->GetModel()));
  phys_eng->m_ball->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(phys_eng->m_cylinder1->GetModel()));
  phys_eng->m_cylinder1->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(phys_eng->m_cylinder2->GetModel()));
  phys_eng->m_cylinder2->Render();

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(phys_eng->m_cylinder3->GetModel()));
  phys_eng->m_cylinder3->Render();

  m_lightPos = m_shader[per_frag]->GetUniformLocation("LightPosition");

  m_ambient = m_shader[per_frag]->GetUniformLocation("AmbientProduct");
  m_diffuse = m_shader[per_frag]->GetUniformLocation("DiffuseProduct");
  m_specular = m_shader[per_frag]->GetUniformLocation("SpecularProduct");
  m_shininess = m_shader[per_frag]->GetUniformLocation("Shininess");

	glUniform4fv(m_lightPos, 1, glm::value_ptr(light));
	glUniform4fv(m_ambient, 1, glm::value_ptr(ambient));
	glUniform4fv(m_diffuse, 1, glm::value_ptr(diffuse));
	glUniform4fv(m_specular, 1, glm::value_ptr(specular));
	glUniform1fv(m_shininess, 1, &shininess);


  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

void Graphics::Launch()
{
  //phys_eng->Launch();
}

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}

