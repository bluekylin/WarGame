#include "CHexMapLayer.h"
#include "CHexMap.h"
#include "CCTextureCache.h"
#include "CCSpriteBatchNode.h"
#include "CCDirector.h"
#include "CCSprite.h"

namespace cocos2d
{
	// static 
	CHexMapLayer* CHexMapLayer::createLayerWithTilesetInfo(CHexMapTilesetInfo *tilesetInfo, int AllocatedTilesNum)
	{
		CHexMapLayer* pRet = new CHexMapLayer();

		CCTexture2D *texture = nullptr;
		if( tilesetInfo )
		{
			texture = CCTextureCache::sharedTextureCache()->addImage(tilesetInfo->m_sSourceImage.c_str());
		}

		if (pRet->initWithTexture(texture, (unsigned int)AllocatedTilesNum))
		{
			// layerInfo
			pRet->m_sLayerName = tilesetInfo->m_sName;
			pRet->m_fContentScaleFactor = CCDirector::sharedDirector()->getContentScaleFactor(); 

			// tilesetInfo
			pRet->setTileSet(tilesetInfo);

			pRet->m_pTileIndexArrayBaseOnAtlasIndex = ccCArrayNew((unsigned int)AllocatedTilesNum);
			pRet->setContentSizeInPixels(CCSizeMake(tilesetInfo->m_tTileSetSize.width * tilesetInfo->m_tTileUnitSize.width, tilesetInfo->m_tTileSetSize.height * tilesetInfo->m_tTileUnitSize.height));
            //m_tMapTileSize.width /= pRet->m_fContentScaleFactor;
           // m_tMapTileSize.height /= pRet->m_fContentScaleFactor;

			return pRet;
		}
		delete pRet;
		return nullptr;
	}

	CHexMapLayer::~CHexMapLayer()
	{
	}

	CHexMapTilesetInfo * CHexMapLayer::getTileSet()
	{
		return m_pTileSet;
	}

	void CHexMapLayer::setTileSet(CHexMapTilesetInfo* var)
	{
		//CC_SAFE_RETAIN(var);
		//CC_SAFE_RELEASE(m_pTileSet);
		m_pTileSet = var;
	}

	void CHexMapLayer::setupTiles(const std::vector<int>& map_raw, unsigned int width, unsigned int height, const TileSet& rTileSet)
	{
		m_fWidth = width;
		m_fHeight = height;
		// By default all the tiles are aliased
		// pros:
		//  - easier to render
		// cons:
		//  - difficult to scale / rotate / etc.
		m_pobTextureAtlas->getTexture()->setAliasTexParameters();

		for( unsigned int y=0; y < height; y++ ) 
		{
			for( unsigned int x=0; x < width; x++ ) 
			{
				unsigned int pos = x + width * y;
				unsigned int gid = rTileSet[ map_raw[ pos ] ].IconIndex;

				// gid are stored in little endian.
				// if host is big endian, then swap
				//if( o == CFByteOrderBigEndian )
				//	gid = CFSwapInt32( gid );
				/* We support little endian.*/

				// XXX: gid == 0 --> empty tile
				if( gid != 0 ) 
				{
					this->appendTileForGID(gid, CCPointMake((float)x, (float)y));

					// Optimization: update min and max GID rendered by the layer
					//m_uMinGID = MIN(gid, m_uMinGID);
					//m_uMaxGID = MAX(gid, m_uMaxGID);
				}
			}
		}
	}

	CCPoint CHexMapLayer::positionForHexAt(const CCPoint& pos)
	{
		float diffY = 0;
		if( (int)pos.x % 2 == 1 )
		{
			diffY = -m_pTileSet->m_tTileUnitSize.height/2 ;
		}

        CCPoint xy = CCPointMake(pos.x * m_pTileSet->m_tTileUnitSize.width*3/4,
                                (m_fHeight - pos.y - 1) * m_pTileSet->m_tTileUnitSize.height + diffY);
        return xy;
	}

	CCSprite* CHexMapLayer::appendTileForGID(unsigned int gid, const CCPoint& pos)
	{
		CCRect rect = m_pTileSet->getTileRectAtIndex(gid);
        rect = CCRectMake(rect.origin.x / m_fContentScaleFactor, rect.origin.y / m_fContentScaleFactor, rect.size.width/ m_fContentScaleFactor, rect.size.height/ m_fContentScaleFactor);

		int z = (int)(pos.x + pos.y * m_fWidth);

		if( ! m_pReusedTile )
		{
			m_pReusedTile = new CCSprite();
			m_pReusedTile->initWithBatchNode(this, rect);
		}
		else
		{
			m_pReusedTile->initWithBatchNode(this, rect);
		}
		
		m_pReusedTile->setPosition(positionForHexAt(pos));
		//m_pReusedTile->setVertexZ((float)vertexZForPos(pos));
		m_pReusedTile->setAnchorPoint(CCPointZero);
		//m_pReusedTile->setOpacity(m_cOpacity);

		// optimization:
		// The difference between appendTileForGID and insertTileforGID is that append is faster, since
		// it appends the tile at the end of the texture atlas
		unsigned int indexForZ = m_pTileIndexArrayBaseOnAtlasIndex->num;

		// don't add it using the "standard" way.
		addQuadFromSprite(m_pReusedTile, indexForZ);

		// append should be after addQuadFromSprite since it modifies the quantity values
		ccCArrayInsertValueAtIndex(m_pTileIndexArrayBaseOnAtlasIndex, (void*)z, indexForZ);

		return m_pReusedTile;
	}
}