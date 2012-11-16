#ifndef __CHEXMAP_LAYER_H__
#define __CHEXMAP_LAYER_H__

#include "CCSpriteBatchNode.h"
#include "TileSet.h"

namespace cocos2d
{
	/** @brief CHexMapLayer represents the Hex Map layer.

	*/
	struct CHexMapTilesetInfo;

	class /*CC_DLL*/ CHexMapLayer : public CCSpriteBatchNode
	{
		/** pointer to the map of tiles */
		CC_SYNTHESIZE(unsigned int*, m_pTiles, Tiles);
		/** Tilset information for the layer */
		CC_PROPERTY(CHexMapTilesetInfo*, m_pTileSet, TileSet);
	public:
		CHexMapLayer() : m_pTiles(nullptr), m_pTileSet(nullptr), m_pReusedTile(nullptr), 
			m_pTileIndexArrayBaseOnAtlasIndex(nullptr), m_fContentScaleFactor(1.0f),
			m_fHeight(0), m_fWidth(0)
		{}
		virtual ~CHexMapLayer();

		static CHexMapLayer * createLayerWithTilesetInfo(CHexMapTilesetInfo *tilesetInfo, int AllocatedTilesNum);

		/** Creates the tiles */
		void setupTiles(const std::vector<int>& map_raw, unsigned int width, unsigned int height, const TileSet& rTileSet);

		/* optimization methos */
		CCSprite* appendTileForGID(unsigned int gid, const CCPoint& pos);
		CCSprite* insertTileForGID(unsigned int gid, const CCPoint& pos);
		CCSprite* updateTileForGID(unsigned int gid, const CCPoint& pos);

	protected:
		//! name of the layer
		std::string m_sLayerName;

		// 已创建的地块数量
		int m_TilesNum;

		//! used for optimization
		CCSprite			*m_pReusedTile;
		// 
		_ccCArray			*m_pTileIndexArrayBaseOnAtlasIndex;
        
        // used for retina display
        float               m_fContentScaleFactor;

		float	m_fWidth;
		float	m_fHeight;

		CCPoint positionForHexAt(const CCPoint& pos);
	};
}

#endif