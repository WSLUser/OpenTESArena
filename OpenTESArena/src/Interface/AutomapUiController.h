#ifndef AUTOMAP_UI_CONTROLLER_H
#define AUTOMAP_UI_CONTROLLER_H

#include <string>

#include "../Math/Vector2.h"

class Game;
class Rect;

struct InputActionCallbackValues;

enum class MouseButtonType;

namespace AutomapUiController
{
	std::string getInputActionName();
	std::string getBackToGameInputActionName();

	void onBackToGameButtonSelected(Game &game);
	void onBackToGameInputAction(const InputActionCallbackValues &values);

	void onMouseButtonHeld(Game &game, MouseButtonType buttonType, const Int2 &position, double dt,
		Double2 *automapOffset);
}

#endif
