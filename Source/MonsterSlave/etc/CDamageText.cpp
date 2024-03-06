#include "CDamageText.h"

#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetTextLibrary.h"

#include "Widgets/CDamageWidget.h"


#include "Global.h"

ACDamageText::ACDamageText()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &DamageWidgetComp, "DamageWidgetComp", Scene);

	InitialLifeSpan = 1.0f;

	TSubclassOf<UUserWidget> damageWidgetClass;
	CHelpers::GetClass(&damageWidgetClass, "/Game/Widgets/Widget/etc/WB_Damage");
	DamageWidgetComp->SetWidgetClass(damageWidgetClass);
	DamageWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

}

void ACDamageText::BeginPlay()
{
	Super::BeginPlay();
	
	if (DamageWidgetComp->GetUserWidgetObject() == nullptr)
	{
		DamageWidgetComp->InitWidget();
	}
}

void ACDamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDamageText::SetDamageText(float InDamage) {
	if (DamageWidgetComp->GetUserWidgetObject() == nullptr)
	{
		DamageWidgetComp->InitWidget();
	}

	UCDamageWidget* damageWidget = Cast<UCDamageWidget>(DamageWidgetComp->GetUserWidgetObject());
	CLog::Log("SetDamageText");
	FText text = UKismetTextLibrary::Conv_FloatToText(InDamage, ERoundingMode::HalfToEven);

	damageWidget->SetDamageWidget(text);
}

