#include "Engine.h"
#include <iostream>

// engine constructor
Engine::Engine()
{
    // create a RenderWindow
    VideoMode customMode(800, 600); // custom resolution
    m_Window.create(customMode, "Your Game Title");}

// run()
void Engine::run()
{
    // initialize the clock to track time frame
    Clock clock;

    // construct a Particle for unit tests
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete. Starting engine..." << endl;

    // game loop
    while (m_Window.isOpen())
    {
        // restart clock - return the time elapsed since the last frame
        Time time = clock.restart();

        // convert the clock time to seconds
        float timetoSeconds = time.asSeconds();

        // call input
        input();

        // call update
        update(timetoSeconds);

        // call draw
        draw();
    }
}

// input()
void Engine::input()
{
    // poll the Windows event queue
    Event event;
    while (m_Window.pollEvent(event))
    {
        // handle the Escape key pressed and closed events to exit the program
        if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            m_Window.close();

        // handle the left mouse button pressed event
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            // create 5 particles with random number of points in the range [25:50] - or any #
            for (int i = 0; i < 5; ++i)
            {
                // random number in [25, 50]
                int numPoints = rand() % 26 + 25; 

                // pass the position of the mouse click into the constructor
                Vector2i mousePosition = Mouse::getPosition(m_Window);
                m_particles.emplace_back(m_Window, numPoints, mousePosition);
            }
        }
    }
}

// loop through m_particles and call update on each Particle in the
// vector whose ttl (time to live) has not expired
void Engine::update(float dtAsSeconds)
{
    // create an iterator for the particle vector
    auto it = m_particles.begin();

    // loop through particles
    while (it != m_particles.end())
    {
        // check if particle's ttl has not expired
        if (it->getTTL() > 0.0)
        {
            // call update on the particle
            it->update(dtAsSeconds);

            // increment the iterator
            ++it;
        }
        else
        {
            // erase the particle if its ttl has expired
            it = m_particles.erase(it);
            // don't increment the iterator - erase returns the next iterator
        }
    }
}

// draws each particles()
void Engine::draw()
{
    // clear the window
    m_Window.clear();

    /* loop through each Particle and draw it
    use polymorphism to call your Particle::draw() function */
    for (const auto& particle : m_particles)
    {
        m_Window.draw(particle);
    }

    // display the window
    m_Window.display();
}
