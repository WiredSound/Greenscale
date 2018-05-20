#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Input.h"

class Gui : public sf::Drawable {
public:
	Gui(std::string guiName);

	virtual void update(Input &input);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateChildren(Input &input);
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual sf::Vector2f getAbsolutePosition() = 0;
	virtual sf::Vector2f getAbsoluteSize() = 0;

	virtual void mouseHover(sf::Vector2i position, const std::vector<sf::Mouse::Button> &mouseButtonsJustClicked) {}
	virtual void mouseNotHovering(sf::Vector2i position) {}
	bool isMouseOverChildren();

	bool withinBounds(sf::Vector2f pos);

	const std::string name;

protected:
	std::unique_ptr<Gui> &getChild(int index);
	void addChild(std::unique_ptr<Gui> child);
	void removeChild(std::unique_ptr<Gui> child);

	void destroyAllChildren();

	virtual void mouseOverChild(std::unique_ptr<Gui> &child, Input &input);

	std::vector<std::unique_ptr<Gui>> children;

private:
	bool mouseOverChildren;
};