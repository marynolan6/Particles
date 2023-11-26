#include "Particle.h"
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics/RenderWindow.hpp>

/* generating a randomized shape with numPoints vertices, centered on 
mouseClickPosition mapped to the Cartesian plane, which is centered at (0,0) 
- give the particle initial vertical, horizontal, and angular / spin velocities */

//Initialize Matrix member variable m_A

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition)
{
  //Initialize m_ttl with global constant TTL;
  m_ttl = TTL;

  //Initialize m_numPoints with numPoints
  m_numPoints = numPoints;

  //Initialize m_radiansPerSec to a random angular velocity
  m_radiansPerSec = ((float) rand() / (RAND_MAX)) * M_PI;

  //Call setCenter on m_cartesianPlane
  m_cartesianPlane.setCenter(0,0);

  //Call setSize on m_cartesianPlane
  m_cartesianPlane.setSize(target.getSize().x , (-1.0) * target.getSize().y);

  //Store the location of the center of this particle on the Cartesian plane in m_centerCoordinate
  m_centerCoordinate = m_cartesianPlane.mapPixelToCoords(mouseClickPosition);

  //Assign m_vx and m_vy to random pixel velocities
  m_vx = rand() % 401 + 100;
  m_vy = rand() % 401 + 100;

  //Assign m_color1 and m_color2 with Colors, red and blue, we can change later
  m_color1.r = 255;
  m_color1.g = 0;
  m_color1.b = 0;

  m_color2.r = 43;
  m_color2.g = 0;
  m_color2.b = 255;

  //Generate numPoint vertices by sweeping a circular arc with randomized radii
  //Initialize theta to an angle between {0:PI/2}
  float theta = ((float) rand() / (RAND_MAX)) * (M_PI/2);

  //Initialize dTheta
  float dTheta = 2 * M_PI / (numPoints - 1);

  //Loop from j up to numPoints
  for (int j = 0; j < numPoints; j++)
  {
    //declare local variables r,dx, dy;
    float r, dx, dy;
    
    //Assign a random number between 20:80 to r
    r = rand() % 61 + 20;

    //Assign dx and dy
    dx = r * cos(theta);
    dy = r * sin(theta);

    //Assign the Cartesian coordinate of the newly generated vertex to m_A
    m_A(0, j) = m_centerCoordinate.x + dx;
    m_A(1, j) = m_centerCoordinate.y + dy;

    //Increment theta by dTheta to move it to the next location for the next iteration
    theta+=dTheta;
  }

}

// overrides the virtual function from sf::Drawable to allow our draw function to polymorph
void Particle::draw(RenderTarget& target, RenderStates states) const 
{
  
}

// updating the state of the particle
void Particle::update(float dt) 
{
  
}

// rotation transformation to the particle's matrix of coordinates - specified by theta in radians
void Particle::rotate(double theta) 
{
  
}

// scaling transformation to the particle's matrix of coordinates
void Particle::scale(double c) 
{
  
}

// translation transformation to the particle's matrix of coordinates - moves horizonal/vertical
void Particle::translate(double xShift, double yShift) 
{
  
}

// if 2 double-precision floating-point numbers are ~equal
bool Particle::almostEqual(double a, double b, double eps) 
{
  
}

// rotations, scaling, and translations
void Particle::unitTests() 
{
  
}
