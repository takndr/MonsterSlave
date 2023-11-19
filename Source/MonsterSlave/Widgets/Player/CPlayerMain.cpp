#include "Widgets/Player/CPlayerMain.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Component/CStatusComponent.h"
#include "Component/CWeaponComponent.h"		//--> WeaponImage ����� ��������Ʈ
#include "Items/CEquipItem.h"				//--> SkillCooldown �� SkillImage ����� ��������Ʈ

#include "Player/CPlayer.h"

#include "Global.h"

void UCPlayerMain::NativeConstruct()
{
	Super::NativeConstruct();
	OwnerCharacter = Cast<ACharacter>(GetOwningPlayerPawn());
	CheckNull(OwnerCharacter);

	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	weaponComp->OnWeaponTypeChanged.AddDynamic(this, &UCPlayerMain::OnWeaponChanged);
}

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

void UCPlayerMain::OnWeaponChanged(EWeaponType InPrevType, EWeaponType InNewType)
{
	// ���⼭ ��ų����� ��������Ʈ ���ε�, �̹��� ����
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	ACEquipItem* prevEquipItem = weaponComp->Weapons[(int32)InPrevType];
	ACEquipItem* newEquipItem = weaponComp->Weapons[(int32)InNewType];

	// ���� ���� ���ε� �Ǿ������� ����
	if (prevEquipItem != nullptr)
	{
		prevEquipItem->OnFirstSkillCoolDown.Clear();
		prevEquipItem->OffFirstSkillCoolDown.Clear();
		prevEquipItem->OnSecondSkillCoolDown.Clear();
		prevEquipItem->OffSecondSkillCoolDown.Clear();
	}
	// �̹����� �����ϰ�


	// ������ �������� ��Ÿ�ӵ� �Ⱥ�������
	FirstSkillCoolDown->SetVisibility(ESlateVisibility::Hidden);
	SecondSkillCoolDown->SetVisibility(ESlateVisibility::Hidden);

	// ���ο� ���� ��Ÿ�� �����Ű�� ��������Ʈ ���ε�
	if (newEquipItem != nullptr)
	{
		newEquipItem->OnFirstSkillCoolDown.AddDynamic(this, &UCPlayerMain::OnFirstSkillCoolDown);
		newEquipItem->OffFirstSkillCoolDown.AddDynamic(this, &UCPlayerMain::OffFirstSkillCoolDown);
		newEquipItem->OnSecondSkillCoolDown.AddDynamic(this, &UCPlayerMain::OnSecondSkillCoolDown);
		newEquipItem->OffSecondSkillCoolDown.AddDynamic(this, &UCPlayerMain::OffSecondSkillCoolDown);
	}
}

void UCPlayerMain::OnFirstSkillCoolDown(float InCoolDown)
{
	FirstSkillCoolDown->SetVisibility(ESlateVisibility::Visible);
	FirstSkillCoolDown->SetText(FText::AsNumber((uint8)ceil(InCoolDown)));
}

void UCPlayerMain::OffFirstSkillCoolDown()
{
	FirstSkillCoolDown->SetVisibility(ESlateVisibility::Hidden);
}

void UCPlayerMain::OnSecondSkillCoolDown(float InCoolDown)
{
	SecondSkillCoolDown->SetVisibility(ESlateVisibility::Visible);
	SecondSkillCoolDown->SetText(FText::AsNumber((uint8)ceil(InCoolDown)));
}

void UCPlayerMain::OffSecondSkillCoolDown()
{
	SecondSkillCoolDown->SetVisibility(ESlateVisibility::Hidden);
}


// ���� ������ �� ������ Image�� �������ִ� ��������Ʈ
// SkillCooldown ��������Ʈ ���� ��쿡�� ����ؼ� Text�� ���������� Text Visible���� ��� ���ְ�, Text ����
// ��ų�� ���� �� Text�� �����ִ� ��������Ʈ
// ��ų ���� �� ������ �� Text�� ������� �ϴ� ��������Ʈ


// ���� �˽�ų �ϳ� ������ ���� ����� ƨ��� ���� ����

void UCPlayerMain::OnQuestAccept()
{

}

void UCPlayerMain::OnQuestClear()
{

}