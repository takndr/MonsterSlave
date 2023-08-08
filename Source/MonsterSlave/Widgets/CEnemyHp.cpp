#include "CEnemyHp.h"

#include "Components/ProgressBar.h"

#include "Global.h"

bool UCEnemyHp::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	CheckNullResult(EnemyHp, false);

	return false;
}

void UCEnemyHp::UpdateHealth(float currentHealth, float maxHealth) {
	EnemyHp->SetPercent(currentHealth / maxHealth);

}