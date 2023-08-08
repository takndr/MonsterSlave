#include "Widgets/CPlayerHp.h"

#include "Components/ProgressBar.h"

#include "Global.h"

void UCPlayerHp::UpdateHealth(float MaxHp, float CurrentHp) {
	PlayerHpBar->SetPercent(CurrentHp / MaxHp);

}