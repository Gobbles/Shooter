#include <memory>
#include <SFML\Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void Run();
private:
	void Update();
	void Draw();

	sf::RenderWindow window;
};