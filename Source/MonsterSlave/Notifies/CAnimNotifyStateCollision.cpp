#include "Notifies/CAnimNotifyStateCollision.h"

#include "Component/CWeaponComponent.h"
#include "Items/Weapons/CEquipSword.h"

#include "Global.h"

FString UCAnimNotifyStateCollision::GetNotifyName_Implementation() const {
	return "Collision";
}

void UCAnimNotifyStateCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) {
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// 무기 콜리젼 켜기
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);
	ACEquipSword* swordEquip = Cast<ACEquipSword>(weaponComp->GetCurrentWeapon());
	CheckNull(swordEquip);

	swordEquip->OnCollision();
}

void UCAnimNotifyStateCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
	Super::NotifyEnd(MeshComp, Animation);

	// 무기 콜리젼 끄기
	UCWeaponComponent* weaponComp = CHelpers::GetComponent<UCWeaponComponent>(MeshComp->GetOwner());
	CheckNull(weaponComp);
	ACEquipSword* swordEquip = Cast<ACEquipSword>(weaponComp->GetCurrentWeapon());
	CheckNull(swordEquip);

	swordEquip->OffCollision();
}