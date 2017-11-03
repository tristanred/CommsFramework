#include "Tile.h"

#include <Graphic/Base Classes/BaseSprite.h>
#include <Graphic/Base Classes/BaseText.h>
#include <Geometry/FPosition.h>

Tile::Tile()
{
    Position = new FPosition();
    TileSprite = NULL;
    TileHelpText = NULL;
}


Tile::~Tile()
{
    delete(Position);
}

void Tile::SetTilePosition(FPosition* pos)
{
    this->Position = pos;

    if (this->TileSprite != NULL)
    {
        this->TileSprite->SetPos(*pos);
    }

    if (this->TileHelpText != NULL)
    {
        this->TileHelpText->SetPos(*pos);
    }
}

void Tile::SetTilePosition(float x, float y)
{
    if (Position != NULL)
    {
        delete(Position);
    }

    Position = new FPosition(x, y);

    this->SetTilePosition(Position);
}
