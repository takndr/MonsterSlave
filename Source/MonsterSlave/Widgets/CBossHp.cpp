#include "CBossHp.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Global.h"

void UCBossHp::UpdateHealth(float currentHealth, float maxHealth) {
	BossHp->SetPercent(currentHealth / maxHealth);
}

void UCBossHp::UpdateName(FText InText) {
	BossName->SetText(InText);
}