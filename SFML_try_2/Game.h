#pragma once


class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void render();
	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Texture groundTexture;
	sf::Sprite mPlayer;
	sf::Sprite groundSprite;
	sf::Font mFont;
	sf::Text mText;
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void update(sf::Time deltaTime);
	bool mIsPowerOn;

	float mVertSpeed = 0;
	bool mLanded = false;
	float mFuel = 100;
	float mFuelPerSecond = 30;
	sf::Time timeSinceLastUpdate;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};