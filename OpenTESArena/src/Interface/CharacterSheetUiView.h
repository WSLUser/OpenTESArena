#ifndef CHARACTER_SHEET_UI_VIEW_H
#define CHARACTER_SHEET_UI_VIEW_H

#include "../Assets/TextureAssetReference.h"
#include "../Math/Rect.h"
#include "../Math/Vector2.h"
#include "../Media/Color.h"
#include "../Media/TextureUtils.h"
#include "../Rendering/ArenaRenderUtils.h"
#include "../Rendering/RenderTextureUtils.h"
#include "../UI/ArenaFontName.h"
#include "../UI/TextAlignment.h"
#include "../UI/TextBox.h"

class Game;

namespace CharacterSheetUiView
{
	constexpr int PlayerNameTextBoxX = 10;
	constexpr int PlayerNameTextBoxY = 8;
	const std::string PlayerNameTextBoxFontName = ArenaFontName::Arena;
	const Color PlayerNameTextBoxColor(199, 199, 199);
	constexpr TextAlignment PlayerNameTextBoxAlignment = TextAlignment::TopLeft;

	constexpr int PlayerRaceTextBoxX = 10;
	constexpr int PlayerRaceTextBoxY = 17;
	const std::string PlayerRaceTextBoxFontName = ArenaFontName::Arena;
	const Color PlayerRaceTextBoxColor(199, 199, 199);
	constexpr TextAlignment PlayerRaceTextBoxAlignment = TextAlignment::TopLeft;

	constexpr int PlayerClassTextBoxX = 10;
	constexpr int PlayerClassTextBoxY = 26;
	const std::string PlayerClassTextBoxFontName = ArenaFontName::Arena;
	const Color PlayerClassTextBoxColor(199, 199, 199);
	constexpr TextAlignment PlayerClassTextBoxAlignment = TextAlignment::TopLeft;

	TextBox::InitInfo getPlayerNameTextBoxInitInfo(const std::string_view &text, const FontLibrary &fontLibrary);
	TextBox::InitInfo getPlayerRaceTextBoxInitInfo(const std::string_view &text, const FontLibrary &fontLibrary);
	TextBox::InitInfo getPlayerClassTextBoxInitInfo(const std::string_view &text, const FontLibrary &fontLibrary);

	const Int2 DoneButtonCenterPoint(25, ArenaRenderUtils::SCREEN_HEIGHT - 15);
	constexpr int DoneButtonWidth = 21;
	constexpr int DoneButtonHeight = 13;

	constexpr int NextPageButtonX = 108;
	constexpr int NextPageButtonY = 179;
	constexpr int NextPageButtonWidth = 49;
	constexpr int NextPageButtonHeight = 13;

	constexpr int BackToStatsButtonX = 0;
	constexpr int BackToStatsButtonY = 188;
	constexpr int BackToStatsButtonWidth = 47;
	constexpr int BackToStatsButtonHeight = 12;

	constexpr int SpellbookButtonX = 47;
	constexpr int SpellbookButtonY = 188;
	constexpr int SpellbookButtonWidth = 76;
	constexpr int SpellbookButtonHeight = 12;

	constexpr int DropButtonX = 123;
	constexpr int DropButtonY = 188;
	constexpr int DropButtonWidth = 48;
	constexpr int DropButtonHeight = 12;

	const Int2 ScrollDownButtonCenterPoint(16, 131);
	constexpr int ScrollDownButtonWidth = 9;
	constexpr int ScrollDownButtonHeight = 9;

	const Int2 ScrollUpButtonCenterPoint(152, 131);
	constexpr int ScrollUpButtonWidth = 9;
	constexpr int ScrollUpButtonHeight = 9;

	Int2 getBodyOffset(Game &game);
	Int2 getHeadOffset(Game &game);
	Int2 getShirtOffset(Game &game);
	Int2 getPantsOffset(Game &game);

	Int2 getNextPageOffset();

	TextureAssetReference getPaletteTextureAssetRef();
	TextureAssetReference getStatsBackgroundTextureAssetRef();
	TextureAssetReference getEquipmentBackgroundTextureAssetRef();
	TextureAssetReference getNextPageButtonTextureAssetRef();
	TextureAssetReference getBodyTextureAssetRef(Game &game);
	TextureAssetReference getHeadTextureAssetRef(Game &game);
	TextureAssetReference getShirtTextureAssetRef(Game &game);
	TextureAssetReference getPantsTextureAssetRef(Game &game);

	UiTextureID allocBodyTexture(Game &game);
	UiTextureID allocShirtTexture(Game &game);
	UiTextureID allocPantsTexture(Game &game);
	UiTextureID allocHeadTexture(Game &game);
	UiTextureID allocStatsBgTexture(TextureManager &textureManager, Renderer &renderer);
	UiTextureID allocEquipmentBgTexture(TextureManager &textureManager, Renderer &renderer);
	UiTextureID allocNextPageTexture(TextureManager &textureManager, Renderer &renderer);
}

#endif
