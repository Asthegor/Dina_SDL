#pragma once

#ifdef DINA_BUILD_DLL

	#define DINA_API __declspec(dllexport)

#else

	#define DINA_API __declspec(dllimport)

#endif // DINA_BUILD_DLL

#ifdef DINA_ENABLE_ASSERTS
	#define DINA_ASSERT(x, ...) {if (!(x)) { DINA_ERROR(__VA_ARGS__); __debugbreak(); } }
	#define DINA_CORE_ASSERT(x, ...) {if (!(x)) { DINA_CORE_ERROR(__VA_ARGS__); __debugbreak(); } }
#else
	#define DINA_ASSERT(x, ...)
	#define DINA_CORE_ASSERT(x, ...)
#endif // DINA_ENABLE_ASSERTS


#define TMXEXPORT DINA_API



/**************************************       Warning C4251/C4275       **************************************/
// File Game.h
#include <string>
namespace Dina
{
	struct DINA_API std::_Container_base12;
	template union DINA_API std::_String_val<std::_Simple_types<char>>::_Bxty;
	template class DINA_API std::_String_val<std::_Simple_types<char>>;
	template class DINA_API std::_Compressed_pair<std::allocator<char>, std::_String_val<std::_Simple_types<char>>, true>;
	template class DINA_API std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
}
// File GameState.h
#include "Dina/Scene/State.h"
#include <map>
namespace Dina
{
	template class DINA_API std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, Dina::State*>>>;
	template class DINA_API std::_Compressed_pair<std::allocator<std::_Tree_node<std::pair<const std::string, Dina::State*>, std::_Default_allocator_traits<std::string>::void_pointer>>, std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, Dina::State*>>>, true>;
	template class DINA_API std::_Compressed_pair<std::less<std::string>, std::_Compressed_pair<std::allocator<std::_Tree_node<std::pair<const std::string, Dina::State*>, std::_Default_allocator_traits<std::string>::void_pointer>>, std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, Dina::State*>>>, true>, true>;
	template class DINA_API std::map<std::string, Dina::State*, std::less<std::string>, std::allocator<std::pair<const std::string, Dina::State*>>>;
}
// File MenuItem.h
#include <functional>
namespace Dina
{
	template class DINA_API std::function<void()>;
}
// File MenuManager.h
#include "Dina/Menu/MenuItem.h"
namespace Dina
{
	template class DINA_API std::_Vector_val<std::_Simple_types<Dina::MenuItem*>>;
	template class DINA_API std::_Compressed_pair<std::allocator<Dina::MenuItem*>, std::_Vector_val<std::_Simple_types<Dina::MenuItem*>>, true>;
	template class DINA_API std::vector<Dina::MenuItem*, std::allocator<Dina::MenuItem*>>;
}
// File Random.h
#include <random>
namespace Dina
{
	template class DINA_API std::mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 2567483615, 11, 4294967295, 7, 2636928640, 15, 4022730752, 18, 1812433253>;
}
// File Animation.h
namespace Dina
{
	template class DINA_API std::_Vector_val<std::_Simple_types<Dina::Texture*>>;
	template class DINA_API std::_Compressed_pair<std::allocator<Dina::Texture*>, std::_Vector_val<std::_Simple_types<Dina::Texture*>>, true>;
	template class DINA_API std::vector<Dina::Texture*, std::allocator<Dina::Texture*>>;
}
// File Spritesheet.h
#include "Dina/Graphic/Sprite.h"
namespace Dina
{
	template class DINA_API std::_Vector_val<std::_Simple_types<Dina::Sprite*>>;
	template class DINA_API std::_Compressed_pair<std::allocator<Dina::Sprite*>, std::_Vector_val<std::_Simple_types<Dina::Sprite*>>, true>;
	template class DINA_API std::vector<Dina::Sprite*, std::allocator<Dina::Sprite*>>;
}
//File MapGenerator.h
#include "Dina/Graphic/Texture.h"
namespace Dina
{
	template class DINA_API std::_Vector_val<std::_Simple_types<std::vector<Dina::FPoint, std::allocator<Dina::FPoint>>>>;
	template class DINA_API std::_Compressed_pair<std::allocator<std::vector<Dina::FPoint, std::allocator<Dina::FPoint>>>, std::_Vector_val<std::_Simple_types<std::vector<Dina::FPoint, std::allocator<Dina::FPoint>>>>, true>;
	template class DINA_API std::vector<std::vector<Dina::FPoint, std::allocator<Dina::FPoint>>, std::allocator<std::vector<Dina::FPoint, std::allocator<Dina::FPoint>>>>;
}
// File Level.h
#include "Dina/Levels/LevelSprite.h"
namespace Dina
{
	template class DINA_API std::_Vector_val<std::_Simple_types<Dina::LevelSprite>>;
	template class DINA_API std::_Compressed_pair<std::allocator<Dina::LevelSprite>, std::_Vector_val<std::_Simple_types<Dina::LevelSprite>>, true>;
	template class DINA_API std::vector<Dina::LevelSprite, std::allocator<Dina::LevelSprite>>;
}
/*************************************************************************************************************/