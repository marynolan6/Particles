#include "Particle.h"
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics/RenderWindow.hpp>

/* generating a randomized shape with numPoints vertices, centered on 
mouseClickPosition mapped to the Cartesian plane, which is centered at (0,0) 
- give the particle initial vertical, horizontal, and angular / spin velocities */
Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition)
{
  
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
