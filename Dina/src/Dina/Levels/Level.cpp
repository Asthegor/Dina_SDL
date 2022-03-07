#include "dinapch.h"
#include "Level.h"

namespace Dina
{
	Level::Level(const char* fileName)
	{
		m_Map = tmx_load(fileName);
		DINA_CORE_ASSERT(m_Map, "Unable to load '{0}' map", fileName);
	}

	Level::~Level()
	{
		tmx_map_free(m_Map);
	}

	void Level::Load()
	{}

	void Level::Update(double deltatime)
	{}

	void Level::Draw()
	{
		//Set_Color(m_Map->backgroundcolor);
		Draw_All_Layers(m_Map, m_Map->ly_head);
	}

	void Level::Set_Color(int color)
	{
		tmx_col_bytes tmx_color = tmx_col_to_bytes(color);
		Graphic::SetBackgroundColor({ tmx_color.r, tmx_color.g, tmx_color.b, tmx_color.a });
	}
	void Level::Draw_All_Layers(tmx_map* map, tmx_layer* layers)
	{
		while (layers)
		{
			if (layers->visible)
			{

				if (layers->type == L_GROUP)
				{
					Draw_All_Layers(map, layers->content.group_head); // recursive call
				}
				else if (layers->type == L_OBJGR)
				{
					Draw_Objects(map, layers->content.objgr); // Function to be implemented
				}
				else if (layers->type == L_IMAGE)
				{
					Draw_Image_Layer(layers->content.image); // Function to be implemented
				}
				else if (layers->type == L_LAYER)
				{
					Draw_Layer(map, layers); // Function to be implemented
				}
			}
			layers = layers->next;
		}
	}
	void Level::Draw_Image_Layer(tmx_image* image)
	{
		Graphic::DrawTexture(new Texture { static_cast<SDL_Texture*>(image->resource_image) });

	}
	void Level::Draw_Layer(tmx_map* map, tmx_layer* layer)
	{
		unsigned long i, j;
		unsigned int gid, x, y, w, h, flags;
		float op;
		tmx_tileset* ts;
		tmx_image* im;
		void* image;
		op = static_cast<float>(layer->opacity);
		for (i = 0; i < map->height; i++)
		{
			for (j = 0; j < map->width; j++)
			{
				gid = (layer->content.gids[(i * map->width) + j]) & TMX_FLIP_BITS_REMOVAL;
				if (map->tiles[gid] != NULL)
				{
					ts = map->tiles[gid]->tileset;
					im = map->tiles[gid]->image;
					x = map->tiles[gid]->ul_x;
					y = map->tiles[gid]->ul_y;
					w = ts->tile_width;
					h = ts->tile_height;
					if (im)
					{
						image = im->resource_image;
					}
					else
					{
						image = ts->image->resource_image;
					}
					flags = (layer->content.gids[(i * map->width) + j]) & ~TMX_FLIP_BITS_REMOVAL;
					Draw_Tile(image, x, y, w, h, j * ts->tile_width, i * ts->tile_height, op, flags); // Function to be implemented
				}
			}
		}
	}
	void Level::Draw_Tile(void* image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
						  unsigned int dx, unsigned int dy, float opacity, double rotation)
	{
		SDL_Rect src_rect, dest_rect;
		src_rect.x = sx;
		src_rect.y = sy;
		src_rect.w = dest_rect.w = sw;
		src_rect.h = dest_rect.h = sh;
		dest_rect.x = dx;
		dest_rect.y = dy;
		Texture* texture = new Texture { static_cast<SDL_Texture*>(image) };
		texture->SetAngle(rotation);
		Point* origin = new Point{};
		origin->x = 0;
		origin->y = sh;
		texture->SetOrigin(origin);

		Sprite* sprite = new Sprite { texture,
									  static_cast<int>(sx), static_cast<int>(sy),
									  static_cast<int>(sw), static_cast<int>(sh) };
		sprite->SetDimensions({ static_cast<int>(dx), static_cast<int>(dy),
								static_cast<int>(sw), static_cast<int>(sh) });
		Graphic::DrawSprite(sprite);
	}
	void Level::Draw_Polyline(double** points, double x, double y, int pointsc)
	{
		Graphic::DrawPolyline(points, x, y, pointsc);
	}

	void Level::Draw_Polygon(double** points, double x, double y, int pointsc)
	{
		Draw_Polyline(points, x, y, pointsc);
		if (pointsc > 2)
		{
			Graphic::DrawLine(static_cast<int>(x + points[0][0]), static_cast<int>(y + points[0][1]),
							  static_cast<int>(x + points[pointsc - 1][0]), static_cast<int>(y + points[pointsc - 1][1]));
		}
	}

	void Level::Draw_Objects(tmx_map* map, tmx_object_group* objgr)
	{
		Set_Color(objgr->color);
		tmx_object* head = objgr->head;
		while (head)
		{
			if (head->visible)
			{
				switch (head->obj_type)
				{
					case OT_ELLIPSE:
						/* No function in SDL2 */
						break;
					case OT_POINT:
						/* TODO: draw the point */
						break;
					case OT_POLYGON:
						Draw_Polygon(head->content.shape->points, head->x, head->y, head->content.shape->points_len);
						break;
					case OT_POLYLINE:
						Draw_Polyline(head->content.shape->points, head->x, head->y, head->content.shape->points_len);
						break;
					case OT_SQUARE:
						Graphic::DrawRectangle({ static_cast<int>(head->x),static_cast<int>(head->y),static_cast<int>(head->width),static_cast<int>(head->height) });
						break;
					case OT_TEXT:
						/* TODO:  display the text */
						break;
					case OT_TILE:
						int gid = head->content.gid & TMX_FLIP_BITS_REMOVAL;
						if (map->tiles[gid] != NULL)
						{
							void* image;
							tmx_tileset* ts = map->tiles[gid]->tileset;
							tmx_image* im = map->tiles[gid]->image;
							int x = static_cast<int>(map->tiles[gid]->ul_x);
							int y = static_cast<int>(map->tiles[gid]->ul_y);
							int w = static_cast<int>(ts->tile_width);
							int h = static_cast<int>(ts->tile_height);
							if (im)
							{
								image = im->resource_image;
							}
							else
							{
								image = ts->image->resource_image;
							}
							Draw_Tile(image, x, y, w, h, static_cast<int>(head->x), static_cast<int>(head->y - head->height), 1, head->rotation);
						}
						break;
				}
			}
			head = head->next;
		}
	}

}