#include "Widgets/CPlayerHp.h"

#include "Components/ProgressBar.h"

#include "Global.h"

void UCPlayerHp::UpdateHealth(float CurrentHp, float MaxHp) {
	PlayerHpBar->SetPercent(CurrentHp / MaxHp);

}