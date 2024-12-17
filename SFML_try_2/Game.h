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
	sf::CircleShape mPlayer;
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void update(sf::Time deltaTime);
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
	sf::Time timeSinceLastUpdate;
	const float PlayerSpeed = 100.f;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};