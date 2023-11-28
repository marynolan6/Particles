#include "Particle.h"
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics/RenderWindow.hpp>


/* generating a randomized shape with numPoints vertices, centered on 
mouseClickPosition mapped to the Cartesian plane, which is centered at (0,0) 
- give the particle initial vertical, horizontal, and angular / spin velocities */

bool Particle::almostEqual(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}

void Particle::unitTests()
{
    int score = 0;
    cout << "Testing RotationMatrix constructor...";
    double theta = M_PI / 4.0;
    RotationMatrix r(M_PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }
    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }
    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }
    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed. Expected (0,0). Received: (" << m_centerCoordinate.x <<
            "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed. +1" << endl;
        score++;
    }
    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(M_PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1,
            j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ")"
            << "(" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
                rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }
    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0, j)) || !
            almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ")"
                << "(" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
                scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }
    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !
            almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ")"
                << "(" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
                translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed. +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }
    cout << "Score: " << score << " / 7" << endl;
}

//Construct m_A before Particle constructor
//m_A(2,m_numPoints);


Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition)
    : m_A(2, numPoints) // initialize m_A with the chosen size
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
  m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

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
  //Construct a VertexArray named lines
  sf::VertexArray lines(TriangleFan, m_numPoints + 1);

  //Declare a local vector2f named center
  Vector2f center(target.mapCoordsToPixel(m_centerCoordinate));

  //Assign lines[0].position with center
  lines[0].position = center;

  //Assign lines[0].color with m_color
  //On canvas it doesn't specify m_color1 or m_color2 so I just chose 1 bc I wasn't sure
  lines[0].color = m_color1;

  //Loop j from 1 up to and including m_numPoints
  for (int j = 1; j <= m_numPoints; j++)
  {
    //Assign lines[j].position with the coordinate from column j - 1 in m_A, 
    //mapped from Cartesian to pixel coordinates using mapCoordsToPixel

    Vector2f point;
    point.x = m_A.getRows();
    point.y = m_A.getCols() - 1;


    Vector2i coord = target.mapCoordsToPixel(point, target.getView());
    Vector2f temp;
    temp.x = coord.x;
    temp.y = coord.y;
    lines[j].position = temp;

    
    //Assign lines[j].color with m_color2
    lines[j].color = m_color2;
  }

  //When loop is finished draw the Vertex array
  target.draw(lines);
}

// updating the state of the particle
void Particle::update(float dt)
{
    // Subtract dt from m_ttl
    m_ttl -= dt;

    // Call rotate with an angle of dt * m_radiansPerSec
    rotate(dt * m_radiansPerSec);

    // Call scale using the global constant SCALE
    scale(SCALE);

    // Calculate how far to shift/translate our particle using velocity (dx, dy)
    float dx = m_vx * dt;

    // Change vertical velocity due to gravity
    // Adjust the value of G as needed
    float G = 1000.0; // Adjust this value experimentally
    m_vy -= G * dt;

    // Assign m_vy * dt to dy
    float dy = m_vy * dt;

    // Call translate using dx, dy as arguments
    translate(dx, dy);
}

// translation transformation to the particle's matrix of coordinates - moves horizonal/vertical
void Particle::translate(double xShift, double yShift)
{
    // Construct a TranslationMatrix T with the specified shift values xShift and yShift
    TranslationMatrix T(xShift, yShift, m_A.getCols());

    // Add it to m_A as m_A = T + m_A
    m_A = T + m_A;
    
    // Update the particle's center coordinate
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}

// rotation matrix we will use is algebraically derived to rotate coordinates about the origin
// temporarily shift our particle to the origin before rotating it
void Particle::rotate(double theta)
{
    // Store the value of m_centerCoordinate in a Vector2f temp
    Vector2f temp = m_centerCoordinate;

    // Call translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
    translate(-temp.x, -temp.y);

    // Construct a RotationMatrix R with the specified angle of rotation theta
    RotationMatrix R(theta);

    // Multiply it by m_A as m_A = R * m_A
    m_A = R * m_A;

    // Shift our particle back to its original center
    translate(temp.x, temp.y);
}

// scaling transformation to the particle's matrix of coordinates
void Particle::scale(double c) 
{
  // temporarily shift back to the origin here before scaling:
  // Store the value of m_centerCoordinate in a Vector2f temp
  Vector2f temp = m_centerCoordinate;

  // Call translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
  //translate(-temp.x, -temp.y);
  translate(-m_centerCoordinate.x, -m_centerCoordinate.y);

  //Construct a ScalingMatrix S with the specified scaling multiplier c
  ScalingMatrix S(c);

  // Multiply it by m_A as m_A = S * m_A
  m_A = S * m_A;

  // Shift our particle back to its original center
  translate(temp.x, temp.y);
}
