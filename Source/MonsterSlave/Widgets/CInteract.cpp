#include "CInteract.h"

#include "Components/TextBlock.h"

#include "Global.h"

bool UCInteract::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	return true;
}

void UCInteract::SetInteractText(FString Description) {
	FText text = FText::FromString(Description);
	Interact->SetText(text);

}