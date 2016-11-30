#include "BaseGraphicEngine.h"

#include "Primitives.h"

BaseGraphicEngine::BaseGraphicEngine()
{
}

void BaseGraphicEngine::SetPrimitiveDrawParameters(uint32_t color, int zIndex)
{
	primitiveDrawColor = color;
	primitiveDrawZIndex = zIndex;
}

void BaseGraphicEngine::DrawLine(FPosition* pointA, FPosition* pointB)
{
	PrimitiveDrawInfo* drawInfo = new PrimitiveDrawInfo();
	drawInfo->Color = primitiveDrawColor;
	drawInfo->ZIndex = primitiveDrawZIndex;
	drawInfo->CallType = DrawType_Line;

	PrimitiveLineDraw* drawData = new PrimitiveLineDraw();
	drawData->xA = pointA->X;
	drawData->yA = pointA->Y;
	drawData->xB = pointB->X;
	drawData->yB = pointB->Y;
	
	drawInfo->DrawData = drawData;

	PrimitiveDrawables.Add(drawInfo);
}

void BaseGraphicEngine::DrawLine(FPosition* pointsArray, int arrayLength)
{
}

void BaseGraphicEngine::DrawLine(float xA, float yA, float xB, float yB)
{
	PrimitiveDrawInfo* drawInfo = new PrimitiveDrawInfo();
	drawInfo->Color = primitiveDrawColor;
	drawInfo->ZIndex = primitiveDrawZIndex;
	drawInfo->CallType = DrawType_Line;

	PrimitiveLineDraw* drawData = new PrimitiveLineDraw();
	drawData->xA = xA;
	drawData->yA = yA;
	drawData->xB = xB;
	drawData->yB = yB;

	drawInfo->DrawData = drawData;

	PrimitiveDrawables.Add(drawInfo);
}

void BaseGraphicEngine::DrawRect(FRectangle* rec)
{
	this->DrawRect(rec->Left, rec->Top, rec->Top + rec->Height(), rec->Left + rec->Width());
}

void BaseGraphicEngine::DrawRect(FPosition* startCorner, FPosition* opposingCorner)
{
}

void BaseGraphicEngine::DrawRect(float x, float y, float height, float width)
{
	PrimitiveDrawInfo* drawInfo = new PrimitiveDrawInfo();
	drawInfo->Color = primitiveDrawColor;
	drawInfo->ZIndex = primitiveDrawZIndex;
	drawInfo->CallType = DrawType_Rect;

	PrimitiveRectDraw* drawData = new PrimitiveRectDraw();
	drawData->x = x;
	drawData->y = x;
	drawData->w = width;
	drawData->h = height;

	drawInfo->DrawData = drawData;

	PrimitiveDrawables.Add(drawInfo);
}