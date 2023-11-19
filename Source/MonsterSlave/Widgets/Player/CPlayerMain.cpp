#include "Widgets/Player/CPlayerMain.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Component/CStatusComponent.h"
#include "Component/CWeaponComponent.h"		//--> WeaponImage 변경용 델리게이트
#include "Items/CEquipItem.h"				//--> SkillCooldown 및 SkillImage 변경용 델리게이트

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
	// 여기서 스킬쿨관련 델리게이트 바인딩, 이미지 변경
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(OwnerCharacter);
	ACEquipItem* prevEquipItem = weaponComp->Weapons[(int32)InPrevType];
	ACEquipItem* newEquipItem = weaponComp->Weapons[(int32)InNewType];

	// 이전 무기 바인딩 되어있으면 해제
	if (prevEquipItem != nullptr)
	{
		prevEquipItem->OnFirstSkillCoolDown.Clear();
		prevEquipItem->OffFirstSkillCoolDown.Clear();
		prevEquipItem->OnSecondSkillCoolDown.Clear();
		prevEquipItem->OffSecondSkillCoolDown.Clear();
	}
	// 이미지들 변경하고


	// 기존에 보여지던 쿨타임들 안보여지고
	FirstSkillCoolDown->SetVisibility(ESlateVisibility::Hidden);
	SecondSkillCoolDown->SetVisibility(ESlateVisibility::Hidden);

	// 새로운 무기 쿨타임 적용시키게 델리게이트 바인딩
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


// 무기 변경할 때 기존에 Image들 변경해주는 델리게이트
// SkillCooldown 델리게이트 같은 경우에는 계속해서 Text가 보여져야함 Text Visible관련 계속 켜주고, Text 변경
// 스킬을 썻을 때 Text를 보여주는 델리게이트
// 스킬 쿨이 다 돌았을 때 Text를 사라지게 하는 델리게이트


// 현재 검스킬 하나 돌리고 무기 변경시 튕기는 현상 있음

void UCPlayerMain::OnQuestAccept()
{

}

void UCPlayerMain::OnQuestClear()
{

}