#include "stdafx.h"
#include "platformInclude.h"
#include "frog.h"

void Frog::init()
{
	remakeSphere(10, 0.2f);
}

void Frog::update()
{
	
}

void Frog::draw()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		glVertex3fv(points[i].getV());
		++i;
		glNormal3fv(points[i].getV());
	}
	glEnd();
}

void Frog::remakeSphere(const int &detail, const float &radius)
{
	// Clear list:
	points.clear();
	
	// Work out stepTheta and stepPhi:
	float stepTheta = 2.0f * KG_PI / detail,
		stepPhi = KG_PI / detail;
	
	// Start stacks loop:
	for (int i = 0; i < detail; ++i)
	{
		// Calculate phi:
		float phi = i / (float)detail * KG_PI;
		
		// Start Slices loop:
		for (int j = 0; j < detail; ++j)
		{
			// Calculate theta:
			float theta = j / (float)detail * 2.0f * KG_PI;
			
			// Add points and normals to the vertex/normals list:
			points.push_back(Vector3(
				radius * sinf(phi) * cosf(theta),
				radius * sinf(phi) * sinf(theta),
				radius * cosf(phi)));
			points.push_back(Vector3(
				sinf(phi) * cosf(theta),
				sinf(phi) * sinf(theta),
				cosf(phi)));
			points.push_back(Vector3(
				radius * sinf(phi) * cosf(theta + stepTheta),
				radius * sinf(phi) * sinf(theta + stepTheta),
				radius * cosf(phi)));
			points.push_back(Vector3(
				sinf(phi) * cosf(theta + stepTheta),
				sinf(phi) * sinf(theta + stepTheta),
				cosf(phi)));
			points.push_back(Vector3(
				radius * sinf(phi + stepPhi) * cosf(theta + stepTheta),
				radius * sinf(phi + stepPhi) * sinf(theta + stepTheta),
				radius * cosf(phi + stepPhi)));
			points.push_back(Vector3(
				sinf(phi + stepPhi) * cosf(theta + stepTheta),
				sinf(phi + stepPhi) * sinf(theta + stepTheta),
				cosf(phi + stepPhi)));
			points.push_back(Vector3(
				radius * sinf(phi + stepPhi) * cosf(theta),
				radius * sinf(phi + stepPhi) * sinf(theta),
				radius * cosf(phi + stepPhi)));
			points.push_back(Vector3(
				sinf(phi + stepPhi) * cosf(theta),
				sinf(phi + stepPhi) * sinf(theta),
				cosf(phi + stepPhi)));
		}
	}
}
