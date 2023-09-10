#include "CBossHp.h"

#include "Components/ProgressBar.h"

#include "Global.h"

void UCBossHp::UpdateHealth(float currentHealth, float maxHealth) {
	BossHp->SetPercent(currentHealth / maxHealth);

}