#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
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

	virtual void mouseHover(Input &input) {}
	virtual void mouseNotHovering(Input &input) {}
	bool isMouseOverChildren();

	bool withinBounds(sf::Vector2f pos);

	const std::string name;

protected:
	template <typename T>
	T *getChild(int index) {
		return dynamic_cast<T*>(getChild(index).get());
	}

	std::unique_ptr<Gui> &getChild(int index);
	int addChild(std::unique_ptr<Gui> child);
	void removeChild(std::unique_ptr<Gui> child);

	void destroyAllChildren();

	virtual void mouseOverChild(std::unique_ptr<Gui> &child, Input &input);

	std::vector<std::unique_ptr<Gui>> children;

private:
	bool mouseOverChildren;
};