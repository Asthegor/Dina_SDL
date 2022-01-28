#pragma once
#include "Dina/Core/Core.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>
#include <map>

// Core
#include "Dina/Core/DinaGame.h"
#include "Dina/Core/Log.h"
#include "Dina/Core/Component.h"

//Scene
#include "Dina/Scene/GameState.h"
#include "Dina/Scene/State.h"


// Graphics
#include "Dina/Graphic/Graphic.h"
#include "Dina/Graphic/Texture.h"
#include "Dina/Graphic/Font.h"
#include "Dina/Graphic/Quad.h"
#include "Dina/Graphic/Animation.h"


// Menu
#include "Dina/Menu/MenuManager.h"


// Events
#include "Dina/Events/Events.h"
#include "Dina/Events/KeyCodes.h"
#include "Dina/Events/MouseCodes.h"
#include "Dina/Events/EventManager.h"


// Random
#include "Dina/Random/Random.h"


// Point d'entrée (fonction main)
#include "Dina/Core/EntryPoint.h"