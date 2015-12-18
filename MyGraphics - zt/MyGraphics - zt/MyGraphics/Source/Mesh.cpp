
#include "Mesh.h"
#include "GL\glew.h"
#include "Vertex.h"

/******************************************************************************/
/*!
\brief
Default constructor - generate VBO/IBO here

\param meshName - name of mesh
*/
/******************************************************************************/
Mesh::Mesh(const std::string &meshName)
	: name(meshName)
	, mode(DRAW_TRIANGLES)
{
	// Generate Buffers
	glGenBuffers(1, &vertexBuffer); //generate vertex buffer
	glGenBuffers(1, &indexBuffer); //generate index buffer

}

/******************************************************************************/
/*!
\brief
Destructor - delete VBO/IBO here
*/
/******************************************************************************/
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}

/******************************************************************************/
/*!
\brief
OpenGL render code
*/
/******************************************************************************/
void Mesh::Render()
{
	glEnableVertexAttribArray(0); // 1st attribute buffer: vertices
	glEnableVertexAttribArray(1); // 2nd attribute buffer : colors
	glEnableVertexAttribArray(2); // 3nd attribute buffer : normals


	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position)+sizeof(Color)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	
	switch (mode){

	case DRAW_TRIANGLES:		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);  break;
	case DRAW_TRIANGLE_STRIP:	glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0); break;
	case DRAW_LINES:			glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0); break;

	default: break;
	}


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}