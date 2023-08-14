#include "Widgets/CInvenEquip.h"

#include "Global.h"

bool UCInvenEquip::Initialize() {
	bool bSuccess = Super::Initialize();
	CheckFalseResult(bSuccess, false);

	return true;
}