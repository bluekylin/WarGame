#include "CHexMap.h"
#include "CHexMapLayer.h"

namespace cocos2d
{
	//static
	CHexMap* CHexMap::CreateHexMap()
	{
		CHexMap *pRet = new CHexMap();
		return pRet;
	}

	CHexMap::CHexMap()
		: m_pLayers(nullptr)
	{
		setContentSize(CCSizeZero);
	}

	CHexMap::~CHexMap()
	{
	}

	CHexMapLayer* CHexMap::addLayer(CHexMapTilesetInfo *tilesetInfo, size_t width, size_t height, const std::vector<int>& map_raw, const TileSet& rTileSet)
	{
		CHexMapLayer *layer = CHexMapLayer::createLayerWithTilesetInfo(tilesetInfo, width * height);
		layer->setupTiles(map_raw, width, height, rTileSet); 
		addChild((CCNode*)layer, 0, 0);


		// record the CHexMapLayer object by it's name
		//std::string layerName = layer->getLayerName();
		//m_pLayers->setObject(layer, layerName);

		// update content size with the max size
		const CCSize& childSize = layer->getContentSize();
		CCSize currentSize = this->getContentSize();
		currentSize.width = MAX( currentSize.width, childSize.width );
		currentSize.height = MAX( currentSize.height, childSize.height );
		this->setContentSize(currentSize);

		return layer;
	}
}