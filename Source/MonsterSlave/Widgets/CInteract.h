#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CInteract.generated.h"

UCLASS()
class MONSTERSLAVE_API UCInteract : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetInteractText(FString Description);

protected:
	virtual bool Initialize() override;

private:

// ===================================

public:

protected:

private:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* Interact;
};
