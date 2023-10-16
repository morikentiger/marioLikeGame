#include <SFML/Graphics.hpp>

const float GRAVITY = 9.8f; // 重力
const float JUMP_STRENGTH = -30.0f; // ジャンプの強さ
const float ACCELERATION = 2.0f; // 水平方向の加速度
float max_velocity = 10.0f; // 最高速度
const float FRICTION = 0.9f; // 摩擦係数

class Character {
public:
    Character(float startX, float startY) : velocity(0, 0), onGround(false) {
        shape.setSize(sf::Vector2f(40, 60));
        shape.setPosition(startX, startY);
        shape.setFillColor(sf::Color::Red);
    }

    void update() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			max_velocity = 20.0f;
		} else {
			max_velocity = 10.0f;
		}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x -= ACCELERATION;
			if (velocity.x <= -max_velocity) {
				velocity.x = -max_velocity;
			}
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x += ACCELERATION;
			if (velocity.x >= max_velocity) {
				velocity.x = max_velocity;
			}
        } else {
            velocity.x *= FRICTION;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (onGround) {
				velocity.y = JUMP_STRENGTH;
        	    onGround = false;
			}
			velocity.y -= JUMP_STRENGTH/15;
        } else {
			velocity.y += GRAVITY;
		}

        
        shape.move(velocity.x, velocity.y);

        if (shape.getPosition().y > 500) { // 地面の仮の位置
            shape.setPosition(shape.getPosition().x, 500);
            velocity.y = 0;
            onGround = true;
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool onGround;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario-like Movement");

    Character character(400, 500);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		window.setFramerateLimit(30);


        character.update();

        window.clear();
        character.draw(window);
        window.display();
    }

    return 0;
}
