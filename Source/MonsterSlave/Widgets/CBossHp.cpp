#include "CBossHp.h"

#include "Components/ProgressBar.h"

#include "Global.h"

bool UCBossHp::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(BossHp, false);
	CheckNullResult(BossName, false);

	return false;
}

void UCBossHp::UpdateHealth(float currentHealth, float maxHealth) {
	BossHp->SetPercent(currentHealth / maxHealth);

}