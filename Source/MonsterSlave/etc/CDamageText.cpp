#include "CDamageText.h"

#include "Components/TextRenderComponent.h"
#include "Kismet/KismetTextLibrary.h"




#include "Global.h"

ACDamageText::ACDamageText()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &Scene, "Scene");
	CHelpers::CreateSceneComponent(this, &Text, "Text", Scene);

	InitialLifeSpan = 10.0f;

	// TODO : DamageText의 컬러 설정
}

void ACDamageText::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACDamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDamageText::SetDamageText(float InDamage) {
	FText text = UKismetTextLibrary::Conv_FloatToText(InDamage, ERoundingMode::HalfToEven);
	Text->SetText(text);
}

