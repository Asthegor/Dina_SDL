#include "dinapch.h"
#include "Level.h"
#include <vector>

namespace Dina
{
	Level::Level() :
		m_Scale({ 1, 1 })
	{
	}

	Level::~Level()
	{
		tmx_map_free(m_Map);
	}

	void Level::Load(const char* fileName)
	{
		m_Map = tmx_load(fileName);
		DINA_CORE_ASSERT(m_Map != nullptr, "Unable to load '{0}' map", fileName);
		if (!m_Map)
		{
			DINA_CORE_ERROR("Unable to load '{0}' map", fileName);
			return;
		}
		Generate_Datas(m_Map->ly_head);
	}


	void Level::Generate_Datas(tmx_layer* layer, tmx_layer* parent_layer)
	{
		while (layer)
		{
			switch (layer->type)
			{
				case L_GROUP:
					{
						Generate_Datas(layer->content.group_head, parent_layer);
					}
					break;
				case L_OBJGR:
					{
						Create_Objects(layer->content.objgr, parent_layer);
					}
					break;
				case L_IMAGE:
					{
						Create_ImageSprite(layer->content.image, parent_layer);
						//Draw_Image_Layer(layer->content.image);
					}
					break;
				case L_LAYER:
					{
						Create_LayerSprites(layer, parent_layer);
					}
					break;
			}
			layer = layer->next;
		}

	}
	void Level::Create_ImageSprite(tmx_image* image, tmx_layer* parent_layer)
	{
		if (image)
		{
			Texture* texture = new Texture { static_cast<SDL_Texture*>(image->resource_image) };
			if (texture)
			{
				LevelSprite ls = { LevelSpriteType::TEXTURE, texture };
				m_LevelSprites.emplace_back(ls);
			}
			else
				DINA_CORE_WARN("Texture not created");
		}
		else
			DINA_CORE_WARN("Image not found");
	}
	void Level::Create_LayerSprites(tmx_layer* layer, tmx_layer* parent_layer)
	{
		SDL_Texture* texture = Graphic::CreateTexture(m_Map->width * m_Map->tile_width, m_Map->height * m_Map->tile_height);

		unsigned long i, j;
		unsigned int gid, x, y, w, h, flags;
		tmx_tileset* ts;
		tmx_image* im;
		void* image;
		if (parent_layer)
		{
			layer->opacity *= parent_layer->opacity;
			layer->offsetx += parent_layer->offsetx;
			layer->offsety += parent_layer->offsety;
		}
		float op = static_cast<float>(layer->opacity);
		unsigned int offsetX = static_cast<unsigned int>(layer->offsetx * m_Scale.x);
		unsigned int offsetY = static_cast<unsigned int>(layer->offsety * m_Scale.y);

		for (i = 0; i < m_Map->height; i++)
		{
			for (j = 0; j < m_Map->width; j++)
			{
				gid = (layer->content.gids[(i * m_Map->width) + j]) & TMX_FLIP_BITS_REMOVAL;
				if (m_Map->tiles[gid] != NULL)
				{
					ts = m_Map->tiles[gid]->tileset;
					im = m_Map->tiles[gid]->image;
					x = static_cast<unsigned int>(m_Map->tiles[gid]->ul_x * m_Scale.x);
					y = static_cast<unsigned int>(m_Map->tiles[gid]->ul_y * m_Scale.y);
					w = ts->tile_width;
					h = ts->tile_height;
					
					image = im ? im->resource_image : ts->image->resource_image;

					flags = (layer->content.gids[(i * m_Map->width) + j]) & ~TMX_FLIP_BITS_REMOVAL;
					Sprite* sprite = Create_Sprite(image, x + offsetX, y + offsetY, w, h, j * ts->tile_width, i * ts->tile_height, op, flags);

					LevelSprite ls = { LevelSpriteType::SPRITE, sprite };
					m_LevelSprites.emplace_back(ls);
				}
			}
		}
	}

	void Level::Create_Objects(tmx_object_group* objgr, tmx_layer* parent_layer)
	{
		tmx_object* head = objgr->head;
		while (head)
		{
			if (head->visible)
			{
				switch (head->obj_type)
				{
					case OT_ELLIPSE:
					case OT_POINT:
						break;
					case OT_POLYGON:
						//Draw_Polygon(head->content.shape->points, head->x, head->y, head->content.shape->points_len);
						break;
					case OT_POLYLINE:
						//Draw_Polyline(head->content.shape->points, head->x, head->y, head->content.shape->points_len);
						break;
					case OT_SQUARE:
						//Graphic::DrawRectangle({ static_cast<int>(head->x),static_cast<int>(head->y),static_cast<int>(head->width),static_cast<int>(head->height) });
						break;
					case OT_TEXT:
						/* TODO:  display the text */
						break;
					case OT_TILE:
						int gid = head->content.gid & TMX_FLIP_BITS_REMOVAL;
						if (m_Map->tiles[gid] != NULL)
						{
							void* image;
							tmx_tileset* ts = m_Map->tiles[gid]->tileset;
							tmx_image* im = m_Map->tiles[gid]->image;
							int x = static_cast<int>(m_Map->tiles[gid]->ul_x);
							int y = static_cast<int>(m_Map->tiles[gid]->ul_y);
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
							Sprite* sprite = Create_Sprite(image, x, y, w, h, static_cast<int>(head->x), static_cast<int>(head->y - head->height), 1, head->rotation);

							LevelSprite ls = { LevelSpriteType::SPRITE, sprite };
							m_LevelSprites.emplace_back(ls);
						}
						break;
				}
			}
			head = head->next;
		}
	}

	Sprite* Level::Create_Sprite(void* image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
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
		texture->SetOrigin(new Point(0, sh));

		Sprite* sprite = new Sprite { texture,
									  static_cast<int>(sx), static_cast<int>(sy),
									  static_cast<int>(sw), static_cast<int>(sh) };
		sprite->SetDimensions({ static_cast<int>(dx), static_cast<int>(dy),
								static_cast<int>(sw), static_cast<int>(sh) });
		return sprite;
	}





	void Level::Update(double deltatime)
	{}

	void Level::Draw(int offsetX, int offsetY)
	{
		//Draw_All_Layers(m_Map, m_Map->ly_head);

		//
		for (auto levelSprite : m_LevelSprites)
		{
			switch (levelSprite.type)
			{
				case LevelSpriteType::SPRITE:
					{
						Sprite* sprite = static_cast<Sprite*>(levelSprite.content);
						Quad oldSpriteDim = *(sprite->GetDimensions());
						Quad* dim = sprite->GetDimensions();
						int x = dim->x - offsetX;
						int y = dim->y - offsetY;
						sprite->SetDimensions({ x, y, dim->width, dim->height });
						Graphic::DrawSprite(sprite);
						sprite->SetDimensions({ oldSpriteDim.x, oldSpriteDim.y, oldSpriteDim.width, oldSpriteDim.height });
					}
					break;

				case LevelSpriteType::TEXTURE:
					{
						Texture* texture = static_cast<Texture*>(levelSprite.content);
						Quad* dim = texture->GetDimensions();
						dim->x -= offsetX;
						dim->y -= offsetY;
						Graphic::DrawTexture(texture);
					}
					break;

				case LevelSpriteType::FONT:
					//Font* font = static_cast<Font*>(levelSprite.content);
					//Graphic::DrawSurface(font->GetSurface(), offsetX, offsetY);
					break;
			}
		}
	}

	Point Level::GetDimensions()
	{
		return { static_cast<int>(m_Map->width * m_Map->tile_width), static_cast<int>(m_Map->height * m_Map->tile_height) };
	}

	bool Level::HasId(int col, int row)
	{
		tmx_layer* layer = m_Map->ly_head;
		while (layer)
		{
			auto gid = GetIdFromLayer(layer, col, row);
			if (gid > 0)
			{
				return true;
			}
			layer = layer->next;
		}
		return false;
	}



	Point Level::ConvertCoordToRowCol(Point point)
	{
		Point res;

		int mw = static_cast<int>(m_Map->width);
		int mh = static_cast<int>(m_Map->height);
		int tw = m_Map->tile_width;
		int th = m_Map->tile_height;

		if (point.x < 0 || point.x > static_cast<int>(m_Map->width * m_Map->tile_width))
			res.x = -1;
		else
			res.x = static_cast<int>(std::floor(static_cast<double>(point.x) / static_cast<double>(m_Map->tile_width)) + 1.0);

		if (point.y < 0 || point.y > static_cast<int>(m_Map->height * m_Map->tile_height))
			res.y = -1;
		else
			res.y = static_cast<int>(std::floor(static_cast<double>(point.y) / static_cast<double>(m_Map->tile_height)));

		return res;
	}

	unsigned int Level::GetIdFromLayer(tmx_layer* layer, int col, int row)
	{
		switch (layer->type)
		{
			case L_GROUP:
				return GetIdFromLayer(layer->content.group_head, col, row);
			case L_LAYER:
				return layer->content.gids[(row * m_Map->width) + col];
			default:
				return 0;
		}
	}

	/*
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
					Draw_All_Layers(map, layers->content.group_head);
				}
				else if (layers->type == L_OBJGR)
				{
					Draw_Objects(map, layers->content.objgr);
				}
				else if (layers->type == L_IMAGE)
				{
					Draw_Image_Layer(layers->content.image);
				}
				else if (layers->type == L_LAYER)
				{
					Draw_Layer(map, layers);
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

					image = im ? im->resource_image : ts->image->resource_image;

					flags = (layer->content.gids[(i * map->width) + j]) & ~TMX_FLIP_BITS_REMOVAL;
					Draw_Tile(image, x, y, w, h, j * ts->tile_width, i * ts->tile_height, op, flags);
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
		texture->SetOrigin(new Point(0, sh));

		Sprite* sprite = new Sprite { texture,
									  static_cast<int>(sx), static_cast<int>(sy),
									  static_cast<int>(sw), static_cast<int>(sh) };
		sprite->SetDimensions({ static_cast<int>(dx), static_cast<int>(dy),
								static_cast<int>(sw), static_cast<int>(sh) });
		Graphic::DrawSprite(sprite);
		delete sprite;
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
						// No function in SDL2
						break;
					case OT_POINT:
						// TODO: draw the point
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
						// TODO:  display the text
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
	*/
}