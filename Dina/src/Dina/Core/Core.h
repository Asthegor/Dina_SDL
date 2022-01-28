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





/**************************************       Warning C4251/C4275       **************************************/
// Fichier Game.h
#include <string>
namespace Dina
{
	struct DINA_API std::_Container_base12;
	template union DINA_API std::_String_val<std::_Simple_types<char>>::_Bxty;
	template class DINA_API std::_String_val<std::_Simple_types<char>>;
	template class DINA_API std::_Compressed_pair<std::allocator<char>, std::_String_val<std::_Simple_types<char>>, true>;
	template class DINA_API std::basic_string<char, std::char_traits<char>, std::allocator<char>>;
}
// Fichier GameState.h
#include "Dina/Scene/State.h"
#include <map>
namespace Dina
{
	template class DINA_API std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, Dina::State*>>>;
	template class DINA_API std::_Compressed_pair<std::allocator<std::_Tree_node<std::pair<const std::string, Dina::State*>, std::_Default_allocator_traits<std::string>::void_pointer>>, std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, Dina::State*>>>, true>;
	template class DINA_API std::_Compressed_pair<std::less<std::string>, std::_Compressed_pair<std::allocator<std::_Tree_node<std::pair<const std::string, Dina::State*>, std::_Default_allocator_traits<std::string>::void_pointer>>, std::_Tree_val<std::_Tree_simple_types<std::pair<const std::string, Dina::State*>>>, true>, true>;
	template class DINA_API std::map<std::string, Dina::State*, std::less<std::string>, std::allocator<std::pair<const std::string, Dina::State*>>>;
}
// Fichier MenuItem.h
#include <functional>
namespace Dina
{
	template class DINA_API std::function<void()>;
}
// Fichier MenuManager.h
#include "Dina/Menu/MenuItem.h"
#include <vector>
namespace Dina
{
	template class DINA_API std::_Vector_val<std::_Simple_types<Dina::MenuItem*>>;
	template class DINA_API std::_Compressed_pair<std::allocator<Dina::MenuItem*>, std::_Vector_val<std::_Simple_types<Dina::MenuItem*>>, true>;
	template class DINA_API std::vector<Dina::MenuItem*, std::allocator<Dina::MenuItem*>>;
}
// Fichier Random.h
#include <random>
namespace Dina
{
	template class DINA_API std::mersenne_twister_engine<unsigned int, 32, 624, 397, 31, 2567483615, 11, 4294967295, 7, 2636928640, 15, 4022730752, 18, 1812433253>;
	//template class DINA_API std::random_device;
}
// Fichier Animation.h
namespace Dina
{
	template class DINA_API std::_Vector_val<std::_Simple_types<Dina::Texture*>>;
	template class DINA_API std::_Compressed_pair<std::allocator<Dina::Texture*>, std::_Vector_val<std::_Simple_types<Dina::Texture*>>, true>;
	template class DINA_API std::vector<Dina::Texture*, std::allocator<Dina::Texture*>>;
}
/*************************************************************************************************************/