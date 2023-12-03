#include "Component/CPlayerStatusComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GameMode/CSaveGame.h"
#include "etc/CPortal.h"

#include "Player/CPlayer.h"
#include "Widgets/Player/CPlayerStatus.h"

#include "Global.h"

void UCPlayerStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	UCharacterMovementComponent* movementComponent = CHelpers::GetComponent<UCharacterMovementComponent>(OwnerCharacter);
	CheckNull(movementComponent);

	// ����� ���� ������ ����
	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	if (saveGame != nullptr && Cast<ACPlayer>(OwnerCharacter) != nullptr)
	{
		MaxHp = saveGame->MaxHp;
		CurrentHp = saveGame->CurrentHp;
		movementComponent->MaxWalkSpeed = saveGame->MoveSpeed;

		HpStat = saveGame->HpStat;
		PowerStat = saveGame->PowerStat;
		SpeedStat = saveGame->SpeedStat;
		DefenseStat = saveGame->DefenseStat;
		RemainStatusPoint = saveGame->RemainStatPoint;

		SetHealth();
		SetSpeed();
	}

	// ��Ż�� ���� ���� ��������Ʈ ���ε�
	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPortal::StaticClass(), outActors);
	for (auto outActor : outActors)
	{
		ACPortal* outPortal = Cast<ACPortal>(outActor);
		if (outPortal == nullptr) continue;

		outPortal->OnPortalSave.AddDynamic(this, &UCPlayerStatusComponent::SaveStatusDatas);
	}

	// Owner�� �÷��̾��� ��� PlayerStatus���� ��������Ʈ ���ε� ����
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	if (player != nullptr)
	{
		UCPlayerStatus* statusWidget = player->GetPlayerStatus();

		statusWidget->OnIncreaseHpStat.BindUFunction(this, "OnHP");
		statusWidget->OnIncreasePowerStat.BindUFunction(this, "OnPower");
		statusWidget->OnIncreaseSpeedStat.BindUFunction(this, "OnSpeed");
		statusWidget->OnIncreaseDefenseStat.BindUFunction(this, "OnDefense");
	}
}

void UCPlayerStatusComponent::SaveStatusDatas()
{
	ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	CheckNull(player);

	UCSaveGame* saveGame = Cast<UCSaveGame>(UGameplayStatics::CreateSaveGameObject(UCSaveGame::StaticClass()));
	CheckNull(saveGame);

	if (Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0)) != nullptr)
	{
		saveGame = Cast<UCSaveGame>(UGameplayStatics::LoadGameFromSlot("Test", 0));
	}

	saveGame->MaxHp = MaxHp;
	saveGame->CurrentHp = CurrentHp;
	saveGame->MoveSpeed = MoveSpeed;

	saveGame->HpStat = HpStat;
	saveGame->PowerStat = PowerStat;
	saveGame->SpeedStat = SpeedStat;
	saveGame->DefenseStat = DefenseStat;
	saveGame->RemainStatPoint = RemainStatusPoint;

	UGameplayStatics::SaveGameToSlot(saveGame, "Test", 0);
}

void UCPlayerStatusComponent::OnHP()
{
	DecreaseRemainStat(1);
	HpStat++;
	SetHealth();

	if (OnHpStat.IsBound())
	{
		OnHpStat.Execute(HpStat, RemainStatusPoint);
	}
}

void UCPlayerStatusComponent::OnPower()
{
	DecreaseRemainStat(1);
	PowerStat++;

	if (OnPowerStat.IsBound())
	{
		OnPowerStat.Execute(PowerStat, RemainStatusPoint);
	}
}

void UCPlayerStatusComponent::OnDefense()
{
	DecreaseRemainStat(1);
	DefenseStat++;

	if (OnDefenseStat.IsBound())
	{
		OnDefenseStat.Execute(DefenseStat, RemainStatusPoint);
	}
}

void UCPlayerStatusComponent::OnSpeed()
{
	DecreaseRemainStat(1);
	SpeedStat++;
	SetSpeed();

	if (OnSpeedStat.IsBound())
	{
		OnSpeedStat.Execute(SpeedStat, RemainStatusPoint);
	}
}

void UCPlayerStatusComponent::IncreaseRemainStat(float dx)
{
	RemainStatusPoint += dx;

	if (OnButtonAppear.IsBound())
	{
		OnButtonAppear.Execute(RemainStatusPoint);
	}
}

void UCPlayerStatusComponent::DecreaseRemainStat(float dx)
{
	RemainStatusPoint -= dx;

	CheckFalse(RemainStatusPoint <= 0);

	if (OnButtonDisappear.IsBound())
	{
		OnButtonDisappear.Execute();
	}
}

void UCPlayerStatusComponent::SetHealth()
{
	MaxHp += HpStat * 50;
	CurrentHp += HpStat * 50;
	
	// �÷��̾� ü�� ���� ���ε�
	if (OnHealthTextSetting.IsBound())
	{
		OnHealthTextSetting.Execute();
	}
}

void UCPlayerStatusComponent::SetSpeed()
{
	UCharacterMovementComponent* movementComponent = CHelpers::GetComponent<UCharacterMovementComponent>(OwnerCharacter);
	CheckNull(movementComponent);

	movementComponent->MaxWalkSpeed = MoveSpeed + SpeedStat * 200;
}
