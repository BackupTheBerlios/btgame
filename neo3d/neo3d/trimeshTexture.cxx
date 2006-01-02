#include "trimeshTexture.h"
#include <stdlib.h>
#include <stdio.h>

TriMeshTexture::TriMeshTexture() : DrawObject()
{
    vertexes = (vertex *)malloc(sizeof(vertex) * TRIMESHBUFFER * 3);
    texPos = (vertex *)malloc(sizeof(vertex) * TRIMESHBUFFER * 3);
    textures = (int *)malloc(sizeof(int) * TRIMESHBUFFER);
    for (int i = 0; i < TRIMESHBUFFER * 3; i++) {
        vertexes[i] = newVertex();
        texPos[i] = newVertex();
    }
    max_vertexes = TRIMESHBUFFER * 3;
    len = 0;
}

TriMeshTexture::~TriMeshTexture()
{
    delete(vertexes);
    delete(texPos);
    delete(textures);
}

void TriMeshTexture::addTriangle(vertex texPos1, vertex v1, 
                     vertex texPos2, vertex v2, 
                     vertex texPos3, vertex v3, 
		     int texture)
{
    if (len >= (max_vertexes - 20)) {
        max_vertexes += TRIMESHBUFFER * 3;
        vertexes = (vertex *)realloc(vertexes, sizeof(vertex) * max_vertexes);
        texPos = (vertex *) realloc(texPos, sizeof(vertex) * max_vertexes);
	textures = (int *) realloc(textures, sizeof(int) * max_vertexes / 3);
        for (int i = len; i < max_vertexes; i++) {
            vertexes[i] = newVertex();
            texPos[i] = newVertex();
        }
    }
    textures[len/3] = texture;

    texPos[len][0] = texPos1[0];
    texPos[len][1] = texPos1[1];
    vertexes[len][0] = v1[0];
    vertexes[len][1] = v1[1];
    vertexes[len][2] = v1[2];
    len++;

    texPos[len][0] = texPos2[0];
    texPos[len][1] = texPos2[1];
    vertexes[len][0] = v2[0];
    vertexes[len][1] = v2[1];
    vertexes[len][2] = v2[2];
    len++;

    texPos[len][0] = texPos3[0];
    texPos[len][1] = texPos3[1];
    vertexes[len][0] = v3[0];
    vertexes[len][1] = v3[1];
    vertexes[len][2] = v3[2];
    len++;
}

void TriMeshTexture::draw()
{
    glPushMatrix();
    glMultMatrixd(mat);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    for (int i = 0; i < len; i+=3) {
      if ((i%3) == 0) {
	glBindTexture(GL_TEXTURE_2D, textures[i/3]); 
	if (glGetError() != GL_NO_ERROR)
	  printf("Error while drawing\n");
	//	    printf("%i %i\n", len, textures[i/3]);
      }
      glBegin(GL_TRIANGLES);
      
      glTexCoord2f(texPos[i][0], texPos[i][1]);
      glVertex3f(vertexes[i][0], vertexes[i][1], vertexes[i][2]);
      glTexCoord2f(texPos[i+1][0], texPos[i+1][1]);
      glVertex3f(vertexes[i+1][0], vertexes[i+1][1], vertexes[i+1][2]);
      glTexCoord2f(texPos[i+2][0], texPos[i+2][1]);
      glVertex3f(vertexes[i+2][0], vertexes[i+2][1], vertexes[i+2][2]);
      glEnd();
    }
    glDisable(GL_TEXTURE_2D);
	
    glPopMatrix();
}
