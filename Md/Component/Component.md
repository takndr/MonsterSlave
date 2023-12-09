## 사용자 정의 컴포넌트

> **1. BehaviorComponent<br>**
> + AI컨트롤러에서 AI들을 컨트롤 하기 위해 사용하는 BehaviorType을 컨트롤 할 수 있는 컴포넌트<br>
> ```
>   UENUM(BlueprintType)
>   enum class EBehaviorType : uint8
>   {
> 	  Wait, Rotate, Move, Action
>   };
> ```
> * Wait : 보스가 아무것도 안하게 대기하는 행동
> * Rotate : 보스가 플레이어 쪽으로 바라보게 하는 행동
> * Move : 보스가 플레이어 쪽으로 이동하는 행동
> * Action : 보스가 플레이어한테 공격하는 행동

> **2. StateComponent<br>**
> + 플레이어가 어떠한 행동을 취할 때, 다른 행동을 할 수 없도록 현재 어떤 상태인지를 컨트롤 할 수 있는 컴포넌트<br>
> ```
>   UENUM(BlueprintType)
>   enum class EStateType : uint8
>   {
> 	  Idle, Equip, Action, Evade, Dead
>   };
> ```
> * Idle : 캐릭터가 현재 아무것도 하고 있지 않은 상태(움직임 같은 일반적인 상태 제외)
> * Equip : 캐릭터가 무기를 장착/해제 하고 있는 상태
> * Action : 캐릭터가 공격하고 있는 상태
> * Evade : 캐릭터가 회피 동작을 하고 있는 상태
> * Dead : 캐릭터가 체력이 0이되어 죽어 있는 상태

> **3. StatusComponent<br>**
> + *캐릭터*의 현재 체력 및 속도를 컨트롤 할 수 있는 컴포넌트<br>

> **4. PlayerStatusComponent<br>**
> + 위 StatusComponent는 모든 캐릭터가 사용 가능하다면, 플레이어만을 위한 컴포넌트<br>
> + 주로 플레이어의 스텟을 관리 및 저장합니다.<br>	
> + StatusComponent를 상속받아 새롭게 작성하였기에, StatusComponent에서 가지고 있는 체력관리 및 이동속도 컨트롤도 가능하며<br>
> + 플레이어의 속도 스탯에 기본 이동속도를 추가로 하여 속도를 관리합니다.<br>
		    
> **5. WeaponComponent<br>**
> + 플레이어가 장착한 무기들을 관리하는 컴포넌트<br>
> + 무기 교체 및 현재 플레이어가 장착한 무기들을 저장하고 관리합니다.<br>
> ```
>   UENUM(BlueprintType)
>   enum class EWeaponType : uint8
>   {
> 	  Unarmed, Sword, Bow
>   };
> ```
> * Unarmed : 캐릭터가 아무것도 착용하지 않았을 때
> * Sword : 캐릭터가 칼을 착용하였을 때
> * Bow : 캐릭터가 활을 착용하였을 때

> **6. QuestComponent<br>**
> + 퀘스트들을 관리하는 컴포넌트<br>
> + 주로 *NPC*들이 해당 컴포넌트를 가지며, 현재 퀘스트들의 상태 및 전체 퀘스트들을 저장하고 관리합니다.<br>

> **7. OptionComponent<br>**
> + 플레이어가 게임을 플레이함에 있어 마우스 감도 및 카메라 확대/축소등을 관리하는 컴포넌트<br>