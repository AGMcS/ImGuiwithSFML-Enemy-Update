#include "Enemy.h"

float Enemy::getPositionX()
{
	return positionX;
}

float Enemy::getPositionY()
{
	return positionY;
}

void Enemy::setPosition(float x, float y)
{
	this->positionX = x;
	this->positionY = y;
}

float Enemy::getWidth() {
	return width;
}

float Enemy::getHeight() {
	return height;
}

void Enemy::setRectSize(float w, float h)
{
	this->width = w;
	this->height = h;
}

void Enemy::flippedRect() {
	if (animation.flipped) {
		rectScale.x = -5.f;
	}
	else {
		rectScale.x = 5.f;
	}
}

void Enemy::setEnemyShape()
{
	enemyRect.setSize({ width, height });
	enemyRect.setPosition({ positionX, positionY });
}

void Enemy::setTexture()
{
	texture.loadFromFile(animation.fileName);
}

bool Enemy::getDirection() {
	return direction;
}

void Enemy::setDirection(float pointA, float pointB)
{
	if (enemyRect.getPosition().x <= pointA) {
		direction = true;
		animation.flipped = false;
		setScaleValues(3.f, 3.f);
	}

	if (enemyRect.getPosition().x >= pointB) {
		direction = false;
		animation.flipped = true;
		setScaleValues(-3.f, 3.f);
	}
}

void Enemy::setXVelocity() {
	if (direction) {
		velx = 2.f;
	}
	else {
		velx = -2.f;
	}
}

float Enemy::getXVelocity() {
	return velx;
}

sf::Vector2f Enemy::getRectScale() {
	return this->rectScale;
}

void Enemy::moveEnemyX(float pointA, float pointB) {
	setDirection(pointA, pointB);
	setXVelocity();
	positionX += velx;
	enemyRect.setPosition(positionX, positionY);
}

bool Enemy::getDeath() {
	return death;
}

float Enemy::getEnemyHealth() {
	return enemyHealth;
}

float Enemy::getDecreaseHealth() {
	return decreaseHealth;
}

void Enemy::setEnemyHealth() {
	enemyHealth -= decreaseHealth;
}

void Enemy::enemyCollision(Player& player, Enemy& enemy) {
	if (enemyRect.getGlobalBounds().intersects(player.hurtBox.getGlobalBounds())) {
		if (player.animation.coordinates.left == 1300) {
			setEnemyHealth();
			setScaleValues(0.f, 0.f);
		}
		player.setPlayerHealth();
	}
	else {
		if (animation.flipped) {
			setScaleValues(-3.f, 3.f);
		}
		else {
			setScaleValues(3.f, 3.f);
		}
	}
	if (enemyRect.getGlobalBounds().intersects(player.bullet.getGlobalBounds()) && player.bullet.getFillColor() == sf::Color::White) {
		setEnemyHealth();
		setScaleValues(0.f, 0.f);
		if (enemyRect.getGlobalBounds().intersects(player.bullet.getGlobalBounds()) && player.bullet.getFillColor() == sf::Color::White) {
			player.bullet.setFillColor(sf::Color::Transparent);
		}
	}

	if (enemyHealth == 0) {
		enemy.setPosition(2000, 1000);
	}
}

void Enemy::setScaleValues(float x, float y)
{
	scaleX = x;
	scaleY = y;
}


void Enemy::update(sf::RenderWindow& window)
{
	animation.Animate(enemyRect, animation.switchTime);
	enemyRect.setScale(scaleX, scaleY);
	window.draw(enemyRect);
	
}

Enemy::Enemy(float positionX, float positionY, float width, float height, std::string fileName, int incrementFrame, int endPoint)
{
	setPosition(positionX, positionY);
	setRectSize(width, height);
	animation.setFileName(fileName);

	animation.setAnimation(0, 0, width, height, endPoint);

	setTexture();
	enemyRect.setTexture(&texture);
	enemyRect.setOrigin(24, 32);

	setEnemyShape();
}