#pragma once
#include "tmx.h"
#include "Dina/Graphic/Sprite.h"
#include "LevelSprite.h"
#include <vector>

namespace Dina
{
	typedef void resourceManager;

	class DINA_API Level
	{
	public:
		Level();

		virtual ~Level();

		void Load(const char* fileName);
		void Update(double deltatime);
		void Draw(int offsetX = 0, int offsetY = 0);

		Point GetDimensions();


		bool HasId(int col, int row);
		Point ConvertCoordToRowCol(Point point);

	private:
		tmx_map* m_Map = nullptr;
		FPoint m_Scale;
		FPoint m_Offset;

		//std::vector<Surface*> m_Surfaces;

		void Generate_Datas(tmx_layer* layer, tmx_layer* parent_layer = nullptr);



		unsigned int GetIdFromLayer(tmx_layer* layer, int col, int row);

		void Create_ImageSprite(tmx_image* image, tmx_layer* parent_layer = nullptr);
		void Create_LayerSprites(tmx_layer* layer, tmx_layer* parent_layer = nullptr);
		void Create_Objects(tmx_object_group* objgr, tmx_layer* parent_layer = nullptr);

		Sprite* Create_Sprite(void* image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
							  unsigned int dx, unsigned int dy, float opacity, double rotation);

		//void Set_Color(int color);
		//void Draw_All_Layers(tmx_map* map, tmx_layer* layers);
		//void Draw_Image_Layer(tmx_image* image);
		//void Draw_Layer(tmx_map* map, tmx_layer* layer);
		//void Draw_Tile(void* image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
		//			   unsigned int dx, unsigned int dy, float opacity, double rotation);
		//void Draw_Polyline(double** points, double x, double y, int pointsc);
		//void Draw_Polygon(double** points, double x, double y, int pointsc);
		//void Draw_Objects(tmx_map* map, tmx_object_group* objgr);

		std::vector<LevelSprite> m_LevelSprites;
	};
}