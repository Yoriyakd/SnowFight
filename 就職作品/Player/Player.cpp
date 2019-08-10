#include "Player.h"

extern ResourceManager *resourceManager;

//privateメソッド

void Player::Move(void)
{

}

int Player::ShootSnowball(void)
{
	return 0;
}

//publicメソッド

Player::Player()
{
	mesh = resourceManager->GetXFILE("Player/player.x");
}

Player::~Player()
{

}

bool Player::Update(void)
{
	Move();
	D3DXMatrixTranslation(&mat, 0, 0, 0);
	return true;
}

void Player::SetCamera(void)
{
}

void Player::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
