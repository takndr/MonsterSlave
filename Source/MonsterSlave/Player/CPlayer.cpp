#include "CPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"

#include "CPlayerAnim.h"

#include "Widgets/Inventory/CInventory.h"
#include "Widgets/Player/CPlayerMain.h"

#include "Items/CFieldItem.h"

#include "Component/CStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Component/COptionComponent.h"

#include "Player/CPlayerHair.h"
#include "Items/Weapons/CEquipBow.h"
#include "Items/Weapons/CEquipSword.h"

#include "Enemy/CBoss.h"

#include "Global.h"

ACPlayer::ACPlayer()
{
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
	CHelpers::CreateActorComponent(this, &OptionComponent, "Option");

	// MeshSpringArm Setting
	MeshSpringArm->SetRelativeLocation(FVector(0, 0, 60));
	MeshSpringArm->TargetArmLength = 300.0f;
	MeshSpringArm->bDoCollisionTest = false;
	MeshSpringArm->bUsePawnControlRotation = true;

	// MeshCamera Setting
	MeshCamera->bUsePawnControlRotation = true;

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
	if (animAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(animAsset.Class);
	}

	// Widget Setting
	CHelpers::GetClass(&InventoryWidgetClass, "/Game/Widgets/Widget/Inventory/WB_Inventory");
	CHelpers::GetClass(&PlayerMainWidgetClass, "/Game/Widgets/Widget/Player/WB_PlayerMain");
	
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	// Hair Set
	PlayerHair = ACPlayerHair::Spawn(GetWorld(), this);

	// Widget Create
	InventoryWidget = CreateWidget<UCInventory, APlayerController>(GetController<APlayerController>(), InventoryWidgetClass);
	InventoryWidget->AddToViewport();
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

	PlayerMainWidget = CreateWidget<UCPlayerMain, APlayerController>(GetController<APlayerController>(), PlayerMainWidgetClass);
	PlayerMainWidget->AddToViewport();
	PlayerMainWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

	// Status Setting
	CheckNull(StatusComponent);
	PlayerMainWidget->UpdateHealth();

	// Event Binding
	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::MeshComponentBeginOverlap);
	GetMesh()->OnComponentEndOverlap.AddDynamic(this, &ACPlayer::MeshComponentEndOverlap);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Event Binding
	// Weapon 관련
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACPlayer::Attack);
	PlayerInputComponent->BindAction("SwordWeapon", IE_Pressed, this, &ACPlayer::OnSwordWeapon);
	PlayerInputComponent->BindAction("BowWeapon", IE_Pressed, this, &ACPlayer::OnBowWeapon);
	PlayerInputComponent->BindAction("FirstSkill", IE_Pressed, this, &ACPlayer::FirstSkill);
	PlayerInputComponent->BindAction("SecondSkill", IE_Pressed, this, &ACPlayer::SecondSkill);

	// Inventory 관련
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ACPlayer::Inventory);
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &ACPlayer::PickUp);

	// Axis Event Binding
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnHorizontalLook(float Axis)
{
	float speed = OptionComponent->GetHorizontalSpeed();
	AddControllerYawInput(Axis * GetWorld()->GetDeltaSeconds() * speed);
}

void ACPlayer::OnVerticalLook(float Axis)
{
	float speed = OptionComponent->GetVerticalSpeed();
	AddControllerPitchInput(Axis * GetWorld()->GetDeltaSeconds() * speed);
}

void ACPlayer::OnZoom(float Axis)
{
	float rate = OptionComponent->GetZoomSpeed() * Axis * GetWorld()->GetDeltaSeconds();
	MeshSpringArm->TargetArmLength += rate;

	MeshSpringArm->TargetArmLength = FMath::Clamp(MeshSpringArm->TargetArmLength, OptionComponent->GetZoomMin(), OptionComponent->GetZoomMax());
}

void ACPlayer::OnSwordWeapon()
{
	if (WeaponComponent->IsSetSword() == false)
	{
		CLog::Log("Do Not Equip Sword, Check the Sword Equip Slot");
		return;
	}

	if (WeaponComponent->IsUnarmed() == true)
	{
		WeaponComponent->EquipSword();
	}
	else
	{
		// 일단은 장비 해제만
		if (WeaponComponent->IsEquipBow())
		{
			WeaponComponent->UnEquip();
			WeaponComponent->EquipSword();
		}
		else
		{
			WeaponComponent->UnEquip();
		}
		
	}
}

void ACPlayer::OnBowWeapon()
{
	if (WeaponComponent->IsSetBow() == false)
	{
		CLog::Log("Do Not Equip Bow, Check the Bow Equip Slot");
		return;
	}

	if (WeaponComponent->IsUnarmed() == true)
	{
		WeaponComponent->EquipBow();
	}
	else
	{
		// 일단은 장비 해제만
		if (WeaponComponent->IsEquipSword())
		{
			WeaponComponent->UnEquip();
			WeaponComponent->EquipBow();
		}
		else
		{
			WeaponComponent->UnEquip();
		}
	}
}

void ACPlayer::Attack()
{
	if (WeaponComponent->GetCurrentWeapon() != nullptr)
	{
		WeaponComponent->GetCurrentWeapon()->Attack();
	}
}

void ACPlayer::FirstSkill()
{
	if (WeaponComponent->GetCurrentWeapon() != nullptr)
	{
		WeaponComponent->GetCurrentWeapon()->FirstSkill();
	}
}

void ACPlayer::SecondSkill()
{
	if (WeaponComponent->GetCurrentWeapon() != nullptr)
	{
		WeaponComponent->GetCurrentWeapon()->SecondSkill();
	}
}

void ACPlayer::Inventory()
{
	CheckNull(InventoryWidget);

	if (InventoryWidget->IsOpened() == false)
	{
		InventoryWidget->Attach();
	}
	else
	{
		InventoryWidget->Detach();
	}
}

void ACPlayer::PickUp()
{
	CheckFalse(bCanPickUp);
	CheckNull(PickableActor);

	if (MyItems.Num() == MaxItem)
	{
		CLog::Log("Not Enough Inventory...");
		return;
	}

	FCItemStruct item;
	item = PickableActor->ItemDescription;
	
	AddItem(item);

	PickableActor->Destroy();
}

void ACPlayer::MeshComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PickableActor = Cast<ACFieldItem>(OtherActor);
	CheckNull(PickableActor);
}

void ACPlayer::MeshComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PickableActor = nullptr;
}

void ACPlayer::AddItem(const FCItemStruct& InItem)
{
	int32 index = InventoryWidget->AddItem(InItem);
	MyItems.Insert(InItem, index);
}

void ACPlayer::RemoveInventoryItem(const FCItemStruct& InItem)
{
	MyItems.Remove(InItem);
}

void ACPlayer::ReplaceInventoryItem(const FCItemStruct& OldItem, const FCItemStruct& NewItem)
{
	CLog::Log("Replace Inventory Item");
	int32 index;
	index = MyItems.Find(OldItem);
	MyItems.Remove(OldItem);
	MyItems.Insert(NewItem, index);
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	CheckTrueResult(StatusComponent->IsDead(), damageValue);

	CLog::Print(damageValue);

	StatusComponent->DecreaseHealth(damageValue);
	PlayerMainWidget->UpdateHealth();

	if (StatusComponent->IsDead())
	{
		CheckNullResult(DeadMontage, damageValue);
		PlayAnimMontage(DeadMontage);

		// TODO : 죽으면 아무것도 못하게(보강)
		return damageValue;
	}

	ACBoss* boss = Cast<ACBoss>(DamageCauser);
	if (boss->IsHeavyHit())
	{
		switch (WeaponComponent->GetWeaponType())
		{
		case EWeaponType::Unarmed:
			//PlayAnimMontage();
			break;
		case EWeaponType::Sword:
			//PlayAnimMontage();
			break;
		case EWeaponType::Bow:
			//PlayAnimMontage();
			break;
		}

	} 
	else
	{
		switch (WeaponComponent->GetWeaponType())
		{
		case EWeaponType::Unarmed:
			//PlayAnimMontage();
			break;
		case EWeaponType::Sword:
			//PlayAnimMontage();
			break;
		case EWeaponType::Bow:
			//PlayAnimMontage();
			break;
		}
	}

	return damageValue;
}

void ACPlayer::TakeDamageTest()
{
	StatusComponent->DecreaseHealth(10);
	PlayerMainWidget->UpdateHealth();
}

void ACPlayer::Dead()
{

}

void ACPlayer::EndDead()
{

}