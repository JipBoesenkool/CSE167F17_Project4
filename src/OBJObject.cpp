#include "OBJObject.h"
#include "Window.h"


OBJObject::OBJObject()
{
	toWorld = glm::mat4(1.0f);
	origin = glm::mat4(1.0f);
	position = glm::vec3(0);
	rotation = glm::vec3(0);
}

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	origin = glm::mat4(1.0f);
	position = glm::vec3(0);
	rotation = glm::vec3(0);

	parse(filepath);
	SetupMesh();
}

OBJObject::~OBJObject()
{
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void OBJObject::parse(const char *filepath) 
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

	float vx, vy, vz;  // vertex coordinates
	float vnx, vny, vnz;  // vertex normals
	unsigned int vindex[3], nindex[3];
	float r,g,b;  // vertex color
	std::string firstToken;
	std::string vnPair;
	//debug counter
#ifdef NDEBUG
	int counter = 0;
#endif

	std::ifstream file(filepath);
	std::string line;
	while ( std::getline(file, line) )
	{
		std::istringstream iss(line);
		iss >> firstToken;

#ifdef NDEBUG
		counter++;
		std::cout << "line " << counter << ": " << line << std::endl;
#endif

		if (firstToken == "v")
		{
			iss >> vx >> vy >> vz;// >> r >> g >> b;
			vertices.push_back( glm::vec3(vx,vy,vz) );
			//TODO: store colors
		}
		else if (firstToken == "vn")
		{
			iss >> vnx >> vny >> vnz;
			normals.push_back( glm::vec3(vnx,vny,vnz) );
		}
		else if(firstToken == "f")
		{
			if(mesh.size() == 0)
			{
				//done parsing vectors
				mesh.resize( vertices.size() );
				for( int i = 0; i < vertices.size(); ++i ) {
					mesh[i] = Vertex{vertices[i], normals[i]};
				}
			}
			for( int i = 0; i < 3; ++i ) {
				iss >> vnPair;
				int delimPos = vnPair.find("//");
				int spacing = 2;
				if(delimPos < 0)
				{
					delimPos = vnPair.find("/");
					spacing = 1;
				}
				vindex[i] = std::stoi( vnPair.substr(0, delimPos) );
				nindex[i] = std::stoi( vnPair.substr(delimPos + spacing, vnPair.size()) );
				indices.push_back( vindex[i]-1 );
			}
		}
	}

	//Calibrate the object
	calibratePosition();
	calibrateScale();

	/*
	for( int i = 0; i < mesh.size(); ++i ) {
		glm::vec4 pos = glm::vec4(mesh[i].position, 1.0f);
		glm::vec4 newPos = origin * pos;
		std::cout<<"origin:"<<newPos.x<<", "<<newPos.y<<", "<<newPos.z<<std::endl;
		std::cout<<"new:"<<newPos.x<<", "<<newPos.y<<", "<<newPos.z<<std::endl;
	}

	position = glm::vec3(0.0f);
	scale = 1.0f;
	 */
	position = glm::vec3(0.0f);
	scale = 1.0f;
}

void OBJObject::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(Vertex), mesh.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)0);

	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)offsetof(Vertex, normal));

	glBindVertexArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void OBJObject::draw(GLuint shader)
{
	// We need to calculate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
	// Consequently, we need to forward the projection, view, and model matrices to the shader programs
	// Get the location of the uniform variables "projection" and "modelview"
	uProjection = glGetUniformLocation(shader, "projection");
	GLint uModel = glGetUniformLocation(shader, "model");
	GLint uView = glGetUniformLocation(shader, "view");
	// Now send these values to the shader program
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uModel, 1, GL_FALSE, &Window::V[0][0]);
	glUniformMatrix4fv(uView, 1, GL_FALSE, &toWorld[0][0]);
	// Now draw the cube. We simply need to bind the VAO associated with it.
	glBindVertexArray(VAO);
	// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
	glBindVertexArray(0);
}

void OBJObject::update()
{
	//update data for rendering
	//automaticRotation();
	glm::mat4 transform(1);

	//glm::mat4 rotationMatrix(1);
	//rotationMatrix = glm::rotate(rotationMatrix, this->rotation.z / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f) );
	//rotationMatrix = glm::translate(rotationMatrix, position);

	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, this->rotation.x / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, this->rotation.y / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, this->rotation.z / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(this->scale));

	//this->toWorld = rotationMatrix * transform;
	this->toWorld = origin * transform;
}

void OBJObject::move(glm::vec3 direction)
{
	position += direction;
}

void OBJObject::rotate(glm::vec3 rotation)
{
	this->rotation += rotation;
	if (this->rotation.x > 360.0f || this->rotation.x < -360.0f) this->rotation.x = 0.0f;
	if (this->rotation.y > 360.0f || this->rotation.y < -360.0f) this->rotation.y = 0.0f;
	if (this->rotation.z > 360.0f || this->rotation.z < -360.0f) this->rotation.z = 0.0f;
	//std::cout<<"obj rot:"<<this->rotation.x<<", "<<this->rotation.y<<", "<<this->rotation.z<<std::endl;
}

void OBJObject::automaticRotation()
{
	glm::vec3 rotation = glm::vec3(0, 1.0f, 0);
	rotate(rotation);
}

void OBJObject::manualRotation(float deg)
{
	glm::vec3 rotation = glm::vec3(0, 0, deg);
	rotate(rotation);
}

void OBJObject::scaleObject(bool scaleUp)
{
	(scaleUp) ? scale *= 2 : scale /= 2;
}

void OBJObject::resetPosition()
{
	this->position = glm::vec3(0);
}

void OBJObject::resetRotation()
{
	this->rotation = glm::vec3(0);
}

void OBJObject::resetScale()
{
	this->scale = 1.0f;
}

//Private functions
void OBJObject::calibratePosition()
{
	glm::vec3 min = glm::vec3(99.0f);
	glm::vec3 max = glm::vec3(-99.0f);
	glm::vec3 total = glm::vec3(0.0f);
	for( int i = 0; i < mesh.size(); ++i )
	{
		//min
		if(mesh[i].position.x < min.x) { min.x = mesh[i].position.x; }
		if(mesh[i].position.y < min.y) { min.y = mesh[i].position.y; }
		if(mesh[i].position.z < min.z) { min.z = mesh[i].position.z; }
		//max
		if(mesh[i].position.x > max.x) { max.x = mesh[i].position.x; }
		if(mesh[i].position.y > max.y) { max.y = mesh[i].position.y; }
		if(mesh[i].position.z > max.z) { max.z = mesh[i].position.z; }
		//to get midpoint
		total += mesh[i].position;
	}
	glm::vec3 div = glm::vec3( (float)mesh.size() );
	total = total/div;
	glm::vec3 newposition = glm::vec3(0.0f) - total;
	origin = glm::translate(origin, newposition);
}

void OBJObject::calibrateScale()
{
	glm::vec3 min = glm::vec3(99.0f);
	glm::vec3 max = glm::vec3(-99.0f);
	for( int i = 0; i < mesh.size(); ++i )
	{
		//min
		if(mesh[i].position.x < min.x) { min.x = mesh[i].position.x; }
		if(mesh[i].position.y < min.y) { min.y = mesh[i].position.y; }
		if(mesh[i].position.z < min.z) { min.z = mesh[i].position.z; }
		//max
		if(mesh[i].position.x > max.x) { max.x = mesh[i].position.x; }
		if(mesh[i].position.y > max.y) { max.y = mesh[i].position.y; }
		if(mesh[i].position.z > max.z) { max.z = mesh[i].position.z; }
	}
	//resize
	glm::vec3 boundingBox = max - min;
	//get biggest size
	float maxBound = boundingBox.x;
	if(boundingBox.y > maxBound){ maxBound = boundingBox.y; };
	if(boundingBox.z > maxBound){ maxBound = boundingBox.z; };
	float newscale = 2.0f/maxBound;
	origin = glm::scale(origin, glm::vec3(newscale));
}
