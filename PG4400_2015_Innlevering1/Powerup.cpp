#include  "PowerUp.h";

PowerUp::PowerUp()
{
	duration = 5;
}

PowerUp::~PowerUp () {

}

void PowerUp::Update(const double& dt)
{
	rect.y += fallSpeed * dt;
	duration -= dt;
}