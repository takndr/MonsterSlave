# StateComponent
캐릭터의 현재 상태 등을 관리하여, 특정 행동의 제약을 걸 수 있게 관리하는 Component
```
  UENUM(BlueprintType)
  enum class EStateType : uint8
  {
	  Idle, Equip, Action, Evade, Dead
  };
```
* Idle : 캐릭터가 현재 아무것도 하고 있지 않은 상태(움직임 같은 일반적인 상태 제외)
* Equip : 캐릭터가 무기를 장착/해제 하고 있는 상태
* Action : 캐릭터가 공격하고 있는 상태
* Evade : 캐릭터가 회피 동작을 하고 있는 상태
* Dead : 캐릭터가 체력이 0이되어 죽어 있는 상태