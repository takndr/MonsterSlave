#include "etc/CPortal.h"

#include "Components/BoxComponent.h"

#include "Component/CWeaponComponent.h"
#include "Component/CStatusComponent.h"

#include "Widgets/CInteract.h"
#include "Player/CPlayer.h"
#include "GameMode/CSaveGame.h"
#include "Items/CEquipItem.h"

#include "Global.h"

ACPortal::ACPortal()
{
	CHelpers::CreateSceneComponent(this, &Box, "Box", RootComponent);

	// Widget Setting
	CHelpers::GetClass(&InteractWidgetClass, "/Game/Widgets/Widget/WB_Interact");
}

void ACPortal::BeginPlay()
{
	Super::BeginPlay();
	
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACPortal::BeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACPortal::EndOverlap);

	InteractWidget = CreateWidget<UCInteract>(GetWorld(), InteractWidgetClass);
	CheckNull(InteractWidget);

	InteractWidget->AddToViewport();
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	InteractWidget->SetInteractText("Portal");
}

void ACPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPortal::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Visible);

	player->OnInteract.BindUFunction(this, "OnInteract");
}

void ACPortal::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACPlayer* player = Cast<ACPlayer>(OtherActor);
	CheckNull(player);

	CheckNull(InteractWidget);
	InteractWidget->SetVisibility(ESlateVisibility::Hidden);

	player->OnInteract.Unbind();
}

void ACPortal::OnInteract()
{
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	CheckNull(controller);

	ACPlayer* player = Cast<ACPlayer>(controller->GetPawn());
	CheckNull(player);

	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	// 인벤토리 저장
	//saveGame->Items = player->MyItems;
	saveGame->Item = player->Items;
	// 장착장비 인벤 표기

	// 현재 Weapon 장착 정보 저장
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(player);
	if (weaponComp != nullptr)
	{
		if (weaponComp->GetSwordWeapon() != nullptr)
		{
			saveGame->SwordItem = (weaponComp->GetSwordWeapon()->Item);
		}

		if (weaponComp->GetBowWeapon() != nullptr)
		{
			saveGame->BowItem = (weaponComp->GetBowWeapon()->Item);
		}

		if (weaponComp->GetWeaponType() != EWeaponType::Unarmed)
		{
			saveGame->WeaponType = weaponComp->GetWeaponType();
		}
	}

	// 현재 플레이어 Status 저장
	UCStatusComponent* statusComp = CHelpers::GetComponent<UCStatusComponent>(player);
	if (statusComp != nullptr)
	{
		saveGame->MaxHp = statusComp->GetMaxHp();
		saveGame->CurrentHp = statusComp->GetCurrentHp();
		saveGame->MoveSpeed = statusComp->GetMoveSpeed();
	}


	UGameplayStatics::SaveGameToSlot(saveGame, "Test", 0);


	FString map = "/Game/Maps/" + NextMap;
	UGameplayStatics::OpenLevel(GetWorld(), (FName)map);
	//controller->ClientTravel(map, ETravelType::TRAVEL_Absolute);
}
