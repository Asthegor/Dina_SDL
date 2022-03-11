#pragma once

namespace Dina
{
	enum class LevelSpriteType
	{
		NONE = 0, TEXTURE, SPRITE, FONT, MAX
	};

	struct LevelSprite
	{
		LevelSpriteType type;
		void* content;
	};

}