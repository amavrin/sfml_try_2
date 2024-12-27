#include "Header.h"

const std::string SPACESHIP_IMAGE = "./Media/Texture/avion.gif";
const std::string GROUND_IMAGE = "./Media/Texture/ground.png";
const std::string FONT_FILE = "./Media/Font/arial.ttf";
const float VELOCITY = 100;
const float POWER_VELOCITY = 150;
const float GROUND_LEVEL = 430;
const float SAFE_SPEED = 100;


Game::Game()
	: mWindow(sf::VideoMode(640, 480), "SFML Application")
	, mTexture()
	, groundTexture()
	, mPlayer()
	, groundSprite()
	, mFont()
{
	bool ok = mTexture.loadFromFile(SPACESHIP_IMAGE);
	if (!ok) {
		throw std::exception("error load from spaceship.png");
	}
	ok = groundTexture.loadFromFile(GROUND_IMAGE);
	if (!ok) {
		throw std::exception("error load from ground.png");
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(400.f, 100.f);

	groundSprite.setTexture(groundTexture);
	groundSprite.setPosition(0.f, GROUND_LEVEL);

	mFont.loadFromFile(FONT_FILE);
	if (!ok) {
		throw std::exception("error load font from file");
	}
	mText.setFont(mFont);
	mText.setFillColor(sf::Color::White);
	mText.setCharacterSize(20);
	mText.setStyle(sf::Text::Bold);
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
	if (key == sf::Keyboard::Space)
		mIsPowerOn = isPressed;
}

void Game::update(sf::Time deltaTime)
{
	if (mPlayer.getPosition().y + mPlayer.getTexture()->getSize().y - 20 > GROUND_LEVEL) {
		mLanded = true;
		if (mVertSpeed > SAFE_SPEED) {
			mText.setString("mission fail: vertical speed is too high: " + std::to_string(mVertSpeed));
		}
		else {
			mText.setString("mission completed!");
		}
		return;
	}

	mVertSpeed += VELOCITY * deltaTime.asSeconds();
	sf::Vector2f movement(0.f, 0.f);
	if (mIsPowerOn) {
		float add_velocity = POWER_VELOCITY;
		mFuel -= mFuelPerSecond * deltaTime.asSeconds();
		if (mFuel < 0) {
			mFuel = 0;
			add_velocity = 0;
		}
		mVertSpeed -= add_velocity * deltaTime.asSeconds();
	}

	movement.y += mVertSpeed;
	mPlayer.move(movement * deltaTime.asSeconds());

	mText.setString("Vertial speed: " + std::to_string(-mVertSpeed) + "\nFuel: " + std::to_string(mFuel));
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(groundSprite);
	mWindow.draw(mPlayer);
	mWindow.draw(mText);
	mWindow.display();
}