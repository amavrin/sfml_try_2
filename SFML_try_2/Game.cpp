#include "Header.h"

Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application")
	, mTexture()
	, groundTexture()
	, mPlayer()
	, groundSprite()
{
	bool ok = mTexture.loadFromFile("avion.gif");
	if (!ok) {
		throw std::exception("error load from spaceship.png");
	}
	ok = groundTexture.loadFromFile("ground.png");
	if (!ok) {
		throw std::exception("error load from ground.png");
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);

	groundSprite.setTexture(groundTexture);
	groundSprite.setPosition(0.f, 430.f);
}

void Game::run()
{
	sf::Clock clock;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key,
	bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;
	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(groundSprite);
	mWindow.draw(mPlayer);
	mWindow.display();
}