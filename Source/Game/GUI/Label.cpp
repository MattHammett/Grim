#include "Label.h"
#include "../../Utility/Singletons.h"
using namespace Grim;

Label::Label()
{
	m_Text.setFont(Singletons::resources.findFont("FONT_DEFAULT"));
	m_Text.setCharacterSize(20);
	m_Text.setString("Dexterity: 582\n XP: 500/1240\n ");
}

void Label::handle(sf::RenderWindow& target, sf::Event& events)
{
}

void Label::tick(sf::RenderWindow& target, float32 dt)
{
}

void Label::render(sf::RenderTarget& target, sf::RenderStates& state)
{
	target.draw(m_Text, state);
}
