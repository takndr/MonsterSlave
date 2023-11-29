#include "Widgets/Player/CPlayerStatus.h"

#include "GameFramework/Character.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"

#include "Widgets/Inventory/CEquipSlot.h"
#include "Component/CPlayerStatusComponent.h"

#include "Global.h"

void UCPlayerStatus::NativeConstruct()
{
	Super::NativeConstruct();

	OwnerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());

	HPButton->OnClicked.AddDynamic(this, &UCPlayerStatus::OnClickHPButton);
	PowerButton->OnClicked.AddDynamic(this, &UCPlayerStatus::OnClickPowerButton);
	SpeedButton->OnClicked.AddDynamic(this, &UCPlayerStatus::OnClickSpeedButton);
	DefenseButton->OnClicked.AddDynamic(this, &UCPlayerStatus::OnClickDefenseButton);

	UCPlayerStatusComponent* playerStatusComp = CHelpers::GetComponent<UCPlayerStatusComponent>(OwnerCharacter);
	CheckNull(playerStatusComp);

	if (playerStatusComp->GetRemainStat() == 0)
	{
		DisappearIncreaseButton();
	}

	playerStatusComp->OnHpStat.BindUFunction(this, "SetHpStatText");
	playerStatusComp->OnPowerStat.BindUFunction(this, "SetPowerStatText");
	playerStatusComp->OnSpeedStat.BindUFunction(this, "SetSpeedStatText");
	playerStatusComp->OnDefenseStat.BindUFunction(this, "SetDefenseStatText");

	FText text;
	text = FText::FromString(FString::FromInt(playerStatusComp->GetHpStat()));
	HPStat->SetText(text);
	text = FText::FromString(FString::FromInt(playerStatusComp->GetPowerStat()));
	PowerStat->SetText(text);
	text = FText::FromString(FString::FromInt(playerStatusComp->GetSpeedStat()));
	SpeedStat->SetText(text);
	text = FText::FromString(FString::FromInt(playerStatusComp->GetDefenseStat()));
	DefenseStat->SetText(text);
	text = FText::FromString(FString::FromInt(playerStatusComp->GetRemainStat()));
	StatusPointText->SetText(text);

	playerStatusComp->OnButtonAppear.BindUFunction(this, "AppearIncreaseButton");
	playerStatusComp->OnButtonDisappear.BindUFunction(this, "DisappearIncreaseButton");
}

void UCPlayerStatus::Attach()
{
	bOpened = true;
	SetVisibility(ESlateVisibility::Visible);

	FInputModeGameAndUI inputMode;

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = true;
	controller->SetInputMode(inputMode);
}

void UCPlayerStatus::Detach()
{
	bOpened = false;
	SetVisibility(ESlateVisibility::Collapsed);

	FInputModeGameOnly inputMode;

	UWorld* world = GetWorld();
	CheckNull(world);
	APlayerController* controller = world->GetFirstPlayerController();
	CheckNull(controller);

	controller->bShowMouseCursor = false;
	controller->SetInputMode(inputMode);
}

void UCPlayerStatus::OnClickHPButton()
{
	if (OnIncreaseHpStat.IsBound())
	{
		OnIncreaseHpStat.Execute();
	}
}

void UCPlayerStatus::OnClickPowerButton()
{
	if (OnIncreasePowerStat.IsBound())
	{
		OnIncreasePowerStat.Execute();
	}
}

void UCPlayerStatus::OnClickSpeedButton()
{
	if (OnIncreaseSpeedStat.IsBound())
	{
		OnIncreaseSpeedStat.Execute();
	}
}

void UCPlayerStatus::OnClickDefenseButton()
{
	if (OnIncreaseDefenseStat.IsBound())
	{
		OnIncreaseDefenseStat.Execute();
	}
}

void UCPlayerStatus::SetHpStatText(float InStat, float InRemainStat)
{
	FText statText, remainText;
	
	statText = FText::FromString(FString::FromInt(InStat));
	remainText = FText::FromString(FString::FromInt(InRemainStat));

	HPStat->SetText(statText);
	StatusPointText->SetText(remainText);
}

void UCPlayerStatus::SetPowerStatText(float InStat, float InRemainStat)
{
	FText statText, remainText;

	statText = FText::FromString(FString::FromInt(InStat));
	remainText = FText::FromString(FString::FromInt(InRemainStat));

	PowerStat->SetText(statText);
	StatusPointText->SetText(remainText);
}

void UCPlayerStatus::SetSpeedStatText(float InStat, float InRemainStat)
{
	FText statText, remainText;

	statText = FText::FromString(FString::FromInt(InStat));
	remainText = FText::FromString(FString::FromInt(InRemainStat));

	SpeedStat->SetText(statText);
	StatusPointText->SetText(remainText);
}

void UCPlayerStatus::SetDefenseStatText(float InStat, float InRemainStat)
{
	FText statText, remainText;

	statText = FText::FromString(FString::FromInt(InStat));
	remainText = FText::FromString(FString::FromInt(InRemainStat));

	DefenseStat->SetText(statText);
	StatusPointText->SetText(remainText);
}

void UCPlayerStatus::AppearIncreaseButton(float InStat)
{
	HPButton->SetVisibility(ESlateVisibility::Visible);
	PowerButton->SetVisibility(ESlateVisibility::Visible);
	SpeedButton->SetVisibility(ESlateVisibility::Visible);
	DefenseButton->SetVisibility(ESlateVisibility::Visible);

	FText remainText;
	remainText = FText::FromString(FString::FromInt(InStat));
	StatusPointText->SetText(remainText);
}

void UCPlayerStatus::DisappearIncreaseButton()
{
	HPButton->SetVisibility(ESlateVisibility::Hidden);
	PowerButton->SetVisibility(ESlateVisibility::Hidden);
	SpeedButton->SetVisibility(ESlateVisibility::Hidden);
	DefenseButton->SetVisibility(ESlateVisibility::Hidden);
}
