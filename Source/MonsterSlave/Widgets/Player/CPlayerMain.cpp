#include "Widgets/Player/CPlayerMain.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Component/CStatusComponent.h"

#include "Global.h"

void UCPlayerMain::UpdateHealth()
{
	UCStatusComponent* statusComp = CHelpers::GetComponent<UCStatusComponent>(GetOwningPlayerPawn());
	CheckNull(statusComp);

	Health->SetPercent(GetHealthRatio());

	float currentHp = statusComp->GetCurrentHp();
	CurrentHP->SetText(FText::FromString(FString::FromInt(currentHp)));

	float maxHp = statusComp->GetMaxHp();
	MaxHP->SetText(FText::FromString(FString::FromInt(maxHp)));
}

float UCPlayerMain::GetHealthRatio()
{
	UCStatusComponent* statusComp = CHelpers::GetComponent<UCStatusComponent>(GetOwningPlayerPawn());
	
	if (statusComp == nullptr)
	{
		return 0.0f;
	}

	return statusComp->GetHpRatio();
}