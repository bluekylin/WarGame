#ifndef __CHEX_MAP_H__
#define __CHEX_MAP_H__

#include "CCNode.h"
#include "CCMutableDictionary.h"
#include "TileSet.h"

namespace cocos2d
{
	/** @brief CHexMap knows how to parse and render a hex map.

		@
	*/

	class CHexMapLayer;

	struct CHexMapTilesetInfo
	{
	public:
		std::string		m_sName;
		//每个地块的大小（以像素为单位）
		CCSize			m_tTileUnitSize;
		//地块模板包的地块排列（横向排列数量，纵向排列数量）
		CCSize          m_tTileSetSize;
		//! filename containing the tiles (should be spritesheet / texture atlas)
		std::string		m_sSourceImage;
		//! size in pixels of the image
		CCSize			m_tImageSize;

		CCRect getTileRectAtIndex(unsigned int index)
		{
			CCRect rect;

			unsigned int x = index % int(m_tTileSetSize.width);
			unsigned int y = index / int(m_tTileSetSize.width);

			rect.size = m_tTileUnitSize;
			rect.origin.x = x * m_tTileUnitSize.width;
			rect.origin.y = y * m_tTileUnitSize.height;
			return rect;
		}
	};

	class /*CC_DLL*/ CHexMap : public CCNode
	{
		/** the map's size property measured in tiles */
		CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tMapSize, MapSize);
		/** the tiles's size property measured in pixels */
		CC_SYNTHESIZE_PASS_BY_REF(CCSize, m_tTileSize, TileSize);

	public:
		CHexMap();
		virtual ~CHexMap();

		static CHexMap* CreateHexMap();

		/** return the HexMapLayer for the specific layer */
		CHexMapLayer* findLayerByName(const char *layerName);

		CHexMapLayer* addLayer(CHexMapTilesetInfo *tilesetInfo, size_t width, size_t height, const std::vector<int>& map_raw, const TileSet& rTileSet);

	protected:
		CCDictionary<std::string, CHexMapLayer*> *m_pLayers;
	};
}


#endif