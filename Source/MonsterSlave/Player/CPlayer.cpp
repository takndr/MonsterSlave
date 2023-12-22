#include "CPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"

#include "CPlayerAnim.h"

#include "Widgets/Inventory/CInventory.h"
#include "Widgets/Quest/CQuestMain.h"
#include "Widgets/Player/CPlayerMain.h"
#include "Widgets/Player/CPlayerStatus.h"
#include "Widgets/Player/CPlayerQuestLog.h"

#include "Component/CPlayerStatusComponent.h"
#include "Component/CStateComponent.h"
#include "Component/CWeaponComponent.h"
#include "Component/COptionComponent.h"
#include "Component/CQuestComponent.h"

#include "Player/CPlayerHair.h"
#include "Items/Weapons/CEquipBow.h"
#include "Items/Weapons/CEquipSword.h"

#include "Enemy/CEnemy.h"

#include "Quest/CNpc.h"
#include "Items/CFieldItem.h"
#include "Items/CItemData.h"

#include "GameMode/CSaveGame.h"
#include "GameMode/CGameInstance.h"

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
	CHelpers::CreateActorComponent(this, &PlayerStatusComponent, "Status");
	CHelpers::CreateActorComponent(this, &StateComponent, "State");
	CHelpers::CreateActorComponent(this, &WeaponComponent, "Weapon");
	CHelpers::CreateActorComponent(this, &OptionComponent, "Option");
	CHelpers::CreateActorComponent(this, &QuestComponent, "Quest");

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
	CHelpers::GetClass(&QuestMainWidgetClass, "/Game/Widgets/Widget/Quest/WB_QuestMain");
	CHelpers::GetClass(&StatusWidgetClass, "/Game/Widgets/Widget/Player/WB_PlayerStatus");
	CHelpers::GetClass(&QuestLogWidgetClass, "/Game/Widgets/Widget/Player/WB_PlayerQuestLog");
}

void ACPlayer::BeginPlay()
{
	// Hair Set
	PlayerHair = ACPlayerHair::Spawn(GetWorld(), this);

	// Widget Create
	InventoryWidget = CreateWidget<UCInventory, APlayerController>(GetController<APlayerController>(), InventoryWidgetClass);
	QuestMainWidget = CreateWidget<UCQuestMain, APlayerController>(GetController<APlayerController>(), QuestMainWidgetClass);
	PlayerMainWidget = CreateWidget<UCPlayerMain, APlayerController>(GetController<APlayerController>(), PlayerMainWidgetClass);
	StatusWidget = CreateWidget<UCPlayerStatus, APlayerController>(GetController<APlayerController>(), StatusWidgetClass);
	QuestLogWidget = CreateWidget<UCPlayerQuestLog, APlayerController>(GetController<APlayerController>(), QuestLogWidgetClass);
	
	PlayerMainWidget->AddToViewport();
	PlayerMainWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

	Super::BeginPlay();
	
	// Widget Add
	InventoryWidget->AddToViewport();
	InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

	QuestMainWidget->AddToViewport();
	QuestMainWidget->SetVisibility(ESlateVisibility::Collapsed);

	StatusWidget->AddToViewport();
	StatusWidget->SetVisibility(ESlateVisibility::Collapsed);

	

	// Status Setting
	CheckNull(PlayerStatusComponent);
	PlayerMainWidget->UpdateHealth();

	// ����� ���� ������ ����
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	if (saveGame != nullptr)
	{
		Items = saveGame->PlayerItems;
		Quests = saveGame->PlayerQuests;
		for (auto quest : Quests)
		{
			quest->BeginPlay();
		}
	}

	// ��Ż�� ���� ���� ��������Ʈ ���ε�
	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstance != nullptr)
	{
		gameInstance->OnGameSave.AddDynamic(this, &ACPlayer::SaveDatas);
	}
	//TArray<AActor*> outActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPortal::StaticClass(), outActors);
	//for (auto outActor : outActors)
	//{
	//	ACPortal* outPortal = Cast<ACPortal>(outActor);
	//	if (outPortal == nullptr) continue;

	//	outPortal->OnPortalSave.AddDynamic(this, &ACPlayer::SaveDatas);
	//}
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Event Binding
	// Weapon ����
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACPlayer::Attack);
	PlayerInputComponent->BindAction("SwordWeapon", IE_Pressed, this, &ACPlayer::OnSwordWeapon);
	PlayerInputComponent->BindAction("BowWeapon", IE_Pressed, this, &ACPlayer::OnBowWeapon);
	PlayerInputComponent->BindAction("FirstSkill", IE_Pressed, this, &ACPlayer::FirstSkill);
	PlayerInputComponent->BindAction("SecondSkill", IE_Pressed, this, &ACPlayer::SecondSkill);

	// Inventory ����
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ACPlayer::Inventory);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACPlayer::Interact);
	
	PlayerInputComponent->BindAction("Status", IE_Pressed, this, &ACPlayer::OnStatus);
	PlayerInputComponent->BindAction("QuestLog", IE_Pressed, this, &ACPlayer::OnQuestLog);

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
		WeaponComponent->GetCurrentWeapon()->GetEquipItem()->Attack();
	}
}

void ACPlayer::FirstSkill()
{
	if (WeaponComponent->GetCurrentWeapon() != nullptr)
	{
		WeaponComponent->GetCurrentWeapon()->GetEquipItem()->FirstSkill();
	}
}

void ACPlayer::SecondSkill()
{
	if (WeaponComponent->GetCurrentWeapon() != nullptr)
	{
		WeaponComponent->GetCurrentWeapon()->GetEquipItem()->SecondSkill();
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

void ACPlayer::Interact()
{	
	if (OnInteract.IsBound())
	{
		OnInteract.Execute();
	}
}

void ACPlayer::OnStatus()
{
	CheckNull(StatusWidget);

	if (StatusWidget->IsOpened() == false)
	{
		StatusWidget->Attach();
	}
	else
	{
		StatusWidget->Detach();
	}
}

void ACPlayer::OnQuestLog()
{
	CheckNull(QuestLogWidget);

	if (QuestLogWidget->IsOpened() == false)
	{
		QuestLogWidget->Attach();
	}
	else
	{
		QuestLogWidget->Detach();
	}
}

void ACPlayer::AddItem(class UCItemData* InItem)
{
	int32 index = InventoryWidget->AddItem(InItem);
	Items.Insert(InItem, index);
}

void ACPlayer::RemoveInventoryItem(class UCItemData* InItem)
{
	Items.Remove(InItem);
}

void ACPlayer::ReplaceInventoryItem(class UCItemData* OldItem, class UCItemData* NewItem)
{
	int32 index;
	index = Items.Find(OldItem);
	Items.Remove(OldItem);
	Items.Insert(NewItem, index);
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	CheckTrueResult(PlayerStatusComponent->IsDead(), damageValue);

	damageValue -= PlayerStatusComponent->GetDefenseStat() * 5;

	PlayerStatusComponent->DecreaseHealth(damageValue);
	PlayerMainWidget->UpdateHealth();

	if (PlayerStatusComponent->IsDead())
	{
		// TODO : ������ �ƹ��͵� ���ϰ�(����)
		StateComponent->SetDead();
		Dead();

		return damageValue;
	}

	// �÷��̾ �ǰݴ����� �� �ǰݸ�Ÿ��
	Hitted(DamageCauser);

	return damageValue;
}

void ACPlayer::Hitted(AActor* DamageCauser)
{
	CheckNull(HitMontage);
	CheckNull(KnockbackMontage);

	ACEnemy* enemy = Cast<ACEnemy>(DamageCauser);
	CheckNull(enemy);

	if (enemy->IsHitNormal())
	{
		PlayAnimMontage(HitMontage);
	}

	if (enemy->IsHitKnockBack())
	{
		PlayAnimMontage(KnockbackMontage);
	}
}

void ACPlayer::TakeDamageTest()
{
	PlayerStatusComponent->DecreaseHealth(10);
	PlayerMainWidget->UpdateHealth();
}

void ACPlayer::IncreaseStatTest()
{
	PlayerStatusComponent->IncreaseRemainStat(5);
}


void ACPlayer::Dead()
{
	CheckNull(DieMontage);

	APlayerController* controller = GetController<APlayerController>();
	if (!!controller)
	{
		DisableInput(controller);
	}

	PlayAnimMontage(DieMontage);

	GetCapsuleComponent()->SetCollisionProfileName("Spectator");
	WeaponComponent->OffAllCollisions();

	UKismetSystemLibrary::K2_SetTimer(this, "EndDead", 3.0f, false);
}

void ACPlayer::EndDead()
{
	// TODO : �÷��̾ �װ� ���� ��� ó���� ���ΰ�
	// �ٽ� ������ �� �ִ� ����
}

void ACPlayer::SaveDatas()
{
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	if (Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0)) != nullptr)
	{
		saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	}

	saveGame->PlayerItems = Items;
	saveGame->PlayerQuests = Quests;
	saveGame->CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	saveGame->LastPlayerLocation = GetActorLocation();

	UGameplayStatics::SaveGameToSlot(saveGame, "Test", 0);
}