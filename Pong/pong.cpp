#include "Bat.h"
#include "Ball.h"
#include<sstream>
#include<cstdlib>
#include<SFML/Graphics.hpp>
int main()
{
	VideoMode vm(1366,768);
	RenderWindow window(vm,"Pong Game",Style::Fullscreen);
	
	int score=0;
	int lives=3;
	Bat bat(1366/2,768-20);
	Ball ball(1366/2,0);
	Text hud;
	Font font;
	font.loadFromFile("font/KOMIKAP_.ttf");
	hud.setFont(font);
	hud.setCharacterSize(30);
	hud.setFillColor(Color::White);
	hud.setPosition(20,20);
	Clock clock;
	while(window.isOpen())
	{
		Event event1;
		while(window.pollEvent(event1))
		{
			if(event1.type==event1.Closed)
			{
				window.close();
			}
		}
		
		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}
		if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}
		Time dt=clock.restart();
		bat.update(dt);
		ball.update(dt);
		std::stringstream ss;
		ss<<"Score:"<<score<<" "<<"Lives:"<<lives;
		hud.setString(ss.str());
		
		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
			{
				// reverse the ball direction
				ball.reboundBottom();
				// Remove a life
				lives--;
				// Check for zero lives
				if (lives < 1) 
				{
					// reset the score
					score = 0;
					// reset the lives
					lives = 3;
				}
			}
		// Handle ball hitting top
		if (ball.getPosition().top < 0)
			{
				ball.reboundBatOrTop();
				// Add a point to the players score
				score++;
			}
		// Handle ball hitting sides
		if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width> window.getSize().x)
			{
			ball.reboundSides();
			}
		// Has the ball hit the bat?
		if(ball.getPosition().intersects(bat.getPosition()))
			{
			// Hit detected so reverse the ball and score a point
			ball.reboundBatOrTop();
			}	
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
		
	}
	return 0;
}
