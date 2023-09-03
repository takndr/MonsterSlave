#include "CPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"

#include "CPlayerAnim.h"

#include "Widgets/CInventory.h"
#include "Widgets/CPlayerHp.h"

#include "Items/CFieldItem.h"

#include "Component/CStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"

#include "Player/CPlayerHair.h"
#include "Items/Weapons/CEquipBow.h"
#include "Items/Weapons/CEquipSword.h"

#include "Global.h"

ACPlayer::ACPlayer() {
	PrimaryActorTick.bCanEverTick = true;

	// Create Scene Component
	CHelpers::CreateSceneComponent(this, &MeshSpringArm, "MeshSpringArm", GetCapsuleComponent());
	CHelpers::CreateSceneComponent(this, &MeshCamera, "MeshCamera", MeshSpringArm);
	CHelpers::CreateSceneComponent(this, &MinimapSpringArm, "MinimapSpringArm", GetCapsuleComponent());
	CHelpers::CreateSceneComponent(this, &MinimapCamera, "MinimapCamera", MinimapSpringArm);
	CHelpers::CreateSceneComponent(this, &MinimapSprite, "Sprite", GetMesh());

	// Create Actor Component
	CHelpers::CreateActorComponent(this, &StatusComponent, "Status");
	CHelpers::CreateActorComponent(this, &StateComponent, "State");
	CHelpers::CreateActorComponent(this, &WeaponComponent, "Weapon");

	// MeshSpringArm Setting
	MeshSpringArm->SetRelativeLocation(FVector(0, 0, 60));
	MeshSpringArm->TargetArmLength = 300.0f;
	MeshSpringArm->bDoCollisionTest = false;
	MeshSpringArm->bUsePawnControlRotation = true;

	// MinimapSpringArm Setting
	MinimapSpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	MinimapSpringArm->TargetArmLength = 3000.0f;
	MinimapSpringArm->bUsePawnControlRotation = false;
	MinimapSpringArm->bInheritPitch = false;
	MinimapSpringArm->bInheritYaw = false;
	MinimapSpringArm->bInheritRoll = false;

	// MinimapCamera Setting
	MinimapCamera->ProjectionType = ECameraProjectionMode::Orthographic;
	MinimapCamera->OrthoWidth = 2500.0f;

	// MinimapSprite Setting
	MinimapSprite->SetGenerateOverlapEvents(false);
	MinimapSprite->SetCollisionProfileName(TEXT("NoCollision"));
	MinimapSprite->bEditableWhenInherited = true;

	// Based Character Setting
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	// SkeletalMesh Setting
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetGenerateOverlapEvents(true);

	CHelpers::GetAsset(&PlayerBody, "SkeletalMesh'/Game/Player/Character/Mesh/Full_Mesh/SK_STgirl1.SK_STgirl1'");
	GetMesh()->SetSkeletalMesh(PlayerBody);

	ConstructorHelpers::FClassFinder<UCPlayerAnim> animAsset(TEXT("AnimBlueprint'/Game/Player/ABP_Player.ABP_Player_C'"));
	if (animAsset.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(animAsset.Class);
	}

	// Widget Setting
	CHelpers::GetClass(&InventoryWidgetClass, "/Game/Widgets/Widget/Inventory/WB_Inventory");
	CHelpers::GetClass(&PlayerHpWidgetClass, "/Game/Widgets/Widget/Player/WB_PlayerHp");
	
}

void ACPlayer::BeginPlay() {
	Super::BeginPlay();

	// Hair Set
	PlayerHair = ACPlayerHair::Spawn(GetWorld(), this);

	// Widget Create
	InventoryWidget = CreateWidget<UCInventory, APlayerController>(GetController<APlayerController>(), InventoryWidgetClass);
	InventoryWidget->AddToViewport();
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

	PlayerHpWidget = CreateWidget<UCPlayerHp>(GetController<APlayerController>(), PlayerHpWidgetClass);
	PlayerHpWidget->AddToViewport();
	PlayerHpWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

	// Status Setting
	CheckNull(StatusComponent);
	StatusComponent->MaxHp = 100;
	StatusComponent->CurrentHp = 100;
	PlayerHpWidget->UpdateHealth(StatusComponent->MaxHp, StatusComponent->CurrentHp);

	// Event Binding
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::MeshComponentBeginOverlap);
	GetMesh()->OnComponentEndOverlap.AddDynamic(this, &ACPlayer::MeshComponentEndOverlap);

}

void ACPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Event Binding
	// Weapon 관련
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACPlayer::Attack);
	PlayerInputComponent->BindAction("SwordWeapon", IE_Pressed, this, &ACPlayer::OnSwordWeapon);
	PlayerInputComponent->BindAction("BowWeapon", IE_Pressed, this, &ACPlayer::OnBowWeapon);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACPlayer::OffAim);
	// Inventory 관련
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ACPlayer::Inventory);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &ACPlayer::PickUp);

	// Axis Event Binding
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
}

void ACPlayer::OnMoveForward(float Axis) {
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis) {
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnHorizontalLook(float Axis) {
	AddControllerYawInput(Axis * GetWorld()->GetDeltaSeconds() * 45);
}

void ACPlayer::OnVerticalLook(float Axis) {
	AddControllerPitchInput(Axis * GetWorld()->GetDeltaSeconds() * 45);
}

void ACPlayer::OnSwordWeapon() {
	if (WeaponComponent->IsSetSword() == false) {
		CLog::Log("Do Not Equip Sword, Check the Sword Equip Slot");
		return;
	}

	if (WeaponComponent->IsUnarmed() == true) {
		CLog::Log("Sword Equipping");
		WeaponComponent->EquipSword();
	}
	else {
		// 일단은 장비 해제만
		CLog::Log("Sword UnEquipping");
		WeaponComponent->UnEquip();
	}
}

void ACPlayer::OnBowWeapon() {
	if (WeaponComponent->IsSetBow() == false) {
		CLog::Log("Do Not Equip Bow, Check the Bow Equip Slot");
		return;
	}

	if (WeaponComponent->IsUnarmed() == true) {
		CLog::Log("Bow Equipping");
		WeaponComponent->EquipBow();
	}
	else {
		// 일단은 장비 해제만
		CLog::Log("Bow UnEquipping");
		WeaponComponent->UnEquip();
	}
}

void ACPlayer::Attack() {
	if (WeaponComponent->GetCurrentWeapon() != nullptr) {
		WeaponComponent->GetCurrentWeapon()->Attack();
	}

}

void ACPlayer::OnAim() {
	if (WeaponComponent->IsUnarmed() == true) {
		CLog::Log("Do Not Equipped Item");
		return;
	}
	bAim = true;
	WeaponComponent->GetCurrentWeapon()->OnAim();
}

void ACPlayer::OffAim() {
	if (WeaponComponent->IsUnarmed() == true) {
		CLog::Log("Do Not Equipped Item");
		return;
	}
	bAim = false;
	WeaponComponent->GetCurrentWeapon()->OffAim();
}

void ACPlayer::Inventory() {
	CheckNull(InventoryWidget);

	if (InventoryWidget->IsOpened() == false) {
		InventoryWidget->Attach();
	}
	else {
		InventoryWidget->Detach();
	}
}

void ACPlayer::PickUp() {
	CheckFalse(bCanPickUp);
	CheckNull(PickableActor);

	if (MyItems.Num() == MaxItem) {
		CLog::Log("Not Enough Inventory...");
		return;
	}

	FCItemStruct item;
	item = PickableActor->ItemDescription;
	
	CLog::Log("PickUP : " + item.Name + ", Index : " + FString::FromInt(item.GetIndex()));

	AddItem(item);

	PickableActor->Destroy();
}

void ACPlayer::MeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	PickableActor = Cast<ACFieldItem>(OtherActor);
	CheckNull(PickableActor);
}

void ACPlayer::MeshComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	PickableActor = nullptr;
}

void ACPlayer::AddItem(const FCItemStruct& InItem) {
	CLog::Log("Add Item | Item : " + InItem.Name + ", Index : " + FString::FromInt(InItem.GetIndex()));
	int32 index = InventoryWidget->AddItem(InItem);
	MyItems.Insert(InItem, index);
}

void ACPlayer::RemoveInventoryItem(const FCItemStruct& InItem) {
	CLog::Log("Remove Inventory Item | Item : " + InItem.Name + ", Index : " + FString::FromInt(InItem.GetIndex()));
	MyItems.Remove(InItem);
}

void ACPlayer::ReplaceInventoryItem(const FCItemStruct& OldItem, const FCItemStruct& NewItem) {
	CLog::Log("Replace Inventory Item");
	int32 index;
	index = MyItems.Find(OldItem);
	MyItems.Remove(OldItem);
	MyItems.Insert(NewItem, index);
}
