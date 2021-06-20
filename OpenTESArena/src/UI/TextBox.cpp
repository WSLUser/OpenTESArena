#include <algorithm>

#include "SDL.h"

#include "FontDefinition.h"
#include "FontLibrary.h"
#include "TextAlignment.h"
#include "TextBox.h"
#include "../Rendering/Renderer.h"

#include "components/debug/Debug.h"
#include "components/utilities/StringView.h"

TextBox::Properties::Properties(int fontDefIndex, const TextRenderUtils::TextureGenInfo &textureGenInfo,
	const Color &defaultColor, TextAlignment alignment, const std::optional<TextRenderUtils::TextShadowInfo> &shadowInfo,
	int lineSpacing)
	: textureGenInfo(textureGenInfo), defaultColor(defaultColor), shadowInfo(shadowInfo)
{
	this->fontDefIndex = fontDefIndex;
	this->alignment = alignment;
	this->lineSpacing = lineSpacing;
}

TextBox::Properties::Properties()
	: Properties(-1, TextRenderUtils::TextureGenInfo(), Color(), static_cast<TextAlignment>(-1), std::nullopt, 0) { }

void TextBox::InitInfo::init(const Rect &rect, Properties &&properties)
{
	this->rect = rect;
	this->properties = std::move(properties);
}

TextBox::TextBox()
{
	this->dirty = false;
}

bool TextBox::init(const Rect &rect, const Properties &properties, Renderer &renderer)
{
	this->rect = rect;
	this->properties = properties;

	const int textureWidth = properties.textureGenInfo.width;
	const int textureHeight = properties.textureGenInfo.height;
	this->texture = renderer.createTexture(Renderer::DEFAULT_PIXELFORMAT,
		SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);

	if (this->texture.get() == nullptr)
	{
		DebugLogError("Couldn't create text box texture (" + std::to_string(textureWidth) + "x" +
			std::to_string(textureHeight) + ").");
		return false;
	}

	if (SDL_SetTextureBlendMode(this->texture.get(), SDL_BLENDMODE_BLEND) != 0)
	{
		DebugLogError("Couldn't set SDL texture blend mode.");
		return false;
	}

	this->dirty = true;

	return true;
}

bool TextBox::init(const InitInfo &initInfo, Renderer &renderer)
{
	return this->init(initInfo.rect, initInfo.properties, renderer);
}

const Rect &TextBox::getRect() const
{
	return this->rect;
}

const Texture &TextBox::getTexture() const
{
	DebugAssert(!this->dirty);
	return this->texture;
}

void TextBox::setText(const std::string_view &text)
{
	this->text = std::string(text);
	this->dirty = true;
}

void TextBox::addOverrideColor(int charIndex, const Color &overrideColor)
{
	this->colorOverrideInfo.add(charIndex, overrideColor);
	this->dirty = true;
}

void TextBox::clearOverrideColors()
{
	this->colorOverrideInfo.clear();
	this->dirty = true;
}

void TextBox::updateTexture(const FontLibrary &fontLibrary)
{
	if (!this->dirty)
	{
		return;
	}

	uint32_t *texturePixels;
	int pitch;
	if (SDL_LockTexture(this->texture.get(), nullptr, reinterpret_cast<void**>(&texturePixels), &pitch) != 0)
	{
		DebugLogError("Couldn't lock text box texture for updating.");
		return;
	}

	const FontDefinition &fontDef = fontLibrary.getDefinition(this->properties.fontDefIndex);
	BufferView2D<uint32_t> textureView(texturePixels, this->texture.getWidth(), this->texture.getHeight());

	// Clear texture.
	textureView.fill(0);

	if (this->text.size() > 0)
	{
		const std::vector<std::string_view> textLines = TextRenderUtils::getTextLines(this->text);
		const std::vector<int> xOffsets = TextRenderUtils::makeAlignmentXOffsets(textLines, this->properties.alignment, fontDef);
		DebugAssert(xOffsets.size() == textLines.size());

		// Draw text to texture.
		// @todo: might need to adjust X and Y by some function of shadow offset. Might also need to draw all shadow lines
		// before all regular lines.
		int y = 0;
		for (int i = 0; i < static_cast<int>(textLines.size()); i++)
		{
			const std::string_view &textLine = textLines[i];
			const int xOffset = xOffsets[i];
			const TextRenderUtils::ColorOverrideInfo *colorOverrideInfoPtr =
				(this->colorOverrideInfo.getEntryCount() > 0) ? &this->colorOverrideInfo : nullptr;
			const TextRenderUtils::TextShadowInfo *shadowInfoPtr =
				this->properties.shadowInfo.has_value() ? &(*this->properties.shadowInfo) : nullptr;
			TextRenderUtils::drawTextLine(textLine, fontDef, xOffset, y, this->properties.defaultColor,
				colorOverrideInfoPtr, shadowInfoPtr, textureView);

			y += fontDef.getCharacterHeight() + this->properties.lineSpacing;
		}
	}

	SDL_UnlockTexture(this->texture.get());

	this->dirty = false;
}
