#include "Widgets/Enemy/CDummyHp.h"

#include "Global.h"

void UCDummyHp::UpdateHealth(float CurrentHp, float MaxHp)
{
	HpRatio = CurrentHp / MaxHp;
}
