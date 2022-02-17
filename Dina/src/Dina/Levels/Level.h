#pragma once
#include "Dina/Core/Component.h"
#include "tmx.h"
#include "Dina/Graphic/Graphic.h"
#include "Dina/Graphic/Texture.h"
#include "Dina/Graphic/Sprite.h"

namespace Dina
{
	typedef void resourceManager;


	class DINA_API Level : public Component
	{
	public:
		Level(const char* fileName);

		virtual ~Level();

		virtual void Load();

		virtual void Update(double deltatime);

		virtual void Draw();

	private:
		tmx_map* m_Map = nullptr;

		void Set_Color(int color);
		void Draw_All_Layers(tmx_map* map, tmx_layer* layers);
		void Draw_Image_Layer(tmx_image* image);
		void Draw_Layer(tmx_map* map, tmx_layer* layer);
		void Draw_Tile(void* image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
					   unsigned int dx, unsigned int dy, float opacity, double rotation);
		void Draw_Polyline(double** points, double x, double y, int pointsc);

		void Draw_Polygon(double** points, double x, double y, int pointsc);

		void Draw_Objects(tmx_map* map, tmx_object_group* objgr);
	};
}