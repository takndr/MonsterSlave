# BehaviorComponent
보스가 가진 Behavior Tree의 제어를 위한 Behavior Type을 관리하는 Component
```
  UENUM(BlueprintType)
  enum class EBehaviorType : uint8
  {
	  Wait, Rotate, Move, Action
  };
```
* Wait : 보스가 아무것도 안하게 대기하는 행동
* Rotate : 보스가 플레이어 쪽으로 바라보게 하는 행동
* Move : 보스가 플레이어 쪽으로 이동하는 행동
* Action : 보스가 플레이어한테 공격하는 행동
