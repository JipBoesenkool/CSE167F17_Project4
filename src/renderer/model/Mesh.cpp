//
// Created by Jip Boesenkool on 26/10/2017.
//
#include "Mesh.h"

//Static (global)
Mesh Mesh::ParseObj(const char* filepath)
{
	Mesh mesh;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	float vx, vy, vz;  // vertex coordinates
	float vnx, vny, vnz;  // vertex normals
	unsigned int vindex[3], nindex[3];
	float r,g,b;  // vertex color
	std::string firstToken;
	std::string vnPair;

	//Parse .obj
	std::ifstream file(filepath);
	std::string line;
	while ( std::getline(file, line) )
	{
		std::istringstream iss(line);
		iss >> firstToken;

		if (firstToken == "v")
		{
			iss >> vx >> vy >> vz;// >> vertX >> vertY >> vertZ;
			vertices.push_back( glm::vec3(vx,vy,vz) );
			//TODO: store colors
		}
		else if (firstToken == "vn")
		{
			iss >> vnx >> vny >> vnz;// normX>>normY>>normZ
			normals.push_back( glm::vec3(vnx,vny,vnz) );
		}
		else if(firstToken == "f")
		{
			//done parsing vectors, collect them into mesh
			if(mesh.m_vertices.size() == 0)
			{
				mesh.m_vertices.resize( vertices.size() );
				for( int i = 0; i < vertices.size(); ++i ) {
					mesh.m_vertices[i] = Vertex{vertices[i], normals[i], glm::vec2(0)};
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
				mesh.m_indices.push_back( vindex[i]-1 );
			}
		}
	}

	mesh.Normalize();
	return mesh;
}

//Public Functions
void Mesh::Normalize()
{
	glm::vec3 min = glm::vec3(99.0f);
	glm::vec3 max = glm::vec3(-99.0f);
	glm::vec3 total = glm::vec3(0.0f);
	for( int i = 0; i < m_vertices.size(); ++i )
	{
		//min
		if(m_vertices[i].m_position.x < min.x) { min.x = m_vertices[i].m_position.x; }
		if(m_vertices[i].m_position.y < min.y) { min.y = m_vertices[i].m_position.y; }
		if(m_vertices[i].m_position.z < min.z) { min.z = m_vertices[i].m_position.z; }
		//max
		if(m_vertices[i].m_position.x > max.x) { max.x = m_vertices[i].m_position.x; }
		if(m_vertices[i].m_position.y > max.y) { max.y = m_vertices[i].m_position.y; }
		if(m_vertices[i].m_position.z > max.z) { max.z = m_vertices[i].m_position.z; }
		//to get midpoint
		total += m_vertices[i].m_position;
	}
	glm::vec3 div = glm::vec3( (float)m_vertices.size() );
	total = total/div;

	//resize
	glm::vec3 boundingBox = max - min;
	//get biggest size
	float maxBound = boundingBox.x;
	if(boundingBox.y > maxBound){ maxBound = boundingBox.y; };
	if(boundingBox.z > maxBound){ maxBound = boundingBox.z; };
	float boundSize = 2.0f;
	float newscale = boundSize/maxBound;

	glm::vec3 newposition = glm::vec3(0.0f) - total;
	for( int i = 0; i < m_vertices.size(); ++i ) {
		m_vertices[i].m_position += newposition;
		m_vertices[i].m_position *= newscale;
	}
}
