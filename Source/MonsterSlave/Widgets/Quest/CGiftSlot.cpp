#include "Widgets/Quest/CGiftSlot.h"

#include "Components/Image.h"

#include "Items/CItemData.h"

void UCGiftSlot::NativeConstruct()
{
	if (ItemData != nullptr)
	{
		SlotImage->SetBrushFromTexture(ItemData->Item.Picture);
		SlotImage->SetBrushSize(FVector2D(32.0f));
		SlotImage->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}