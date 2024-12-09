#include "block.hpp"

Block::Block(Vector2 position)
{
	this->position = position;
}

void Block::Draw() {
	DrawRectangle(position.x, position.y, 3, 3, { 122, 255, 0, 255 });
}