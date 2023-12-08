> **1. BehaviorComponent<br>**
> + AI컨트롤러에서 AI들을 컨트롤 하기 위해 사용하는 BehaviorType을 컨트롤 할 수 있는 컴포넌트<br>
>
> **2. StateComponent<br>**
> + 플레이어가 어떠한 행동을 취할 때, 다른 행동을 할 수 없도록 현재 어떤 상태인지를 컨트롤 할 수 있는 컴포넌트<br>
>
> **3. StatusComponent<br>**
> + *캐릭터*의 현재 체력 및 속도를 컨트롤 할 수 있는 컴포넌트<br>
>
> **4. PlayerStatusComponent<br>**
> + 위 StatusComponent는 모든 캐릭터가 사용 가능하다면, 플레이어만을 위한 컴포넌트<br>
> + 주로 플레이어의 스텟을 관리 및 저장합니다.<br>
>				    
> **5. WeaponComponent<br>**
> + 플레이어가 장착한 무기들을 관리하는 컴포넌트<br>
> + 무기 교체 및 현재 플레이어가 장착한 무기들을 저장하고 관리합니다.<br>
>
> **6. QuestComponent<br>**
> + 퀘스트들을 관리하는 컴포넌트<br>
> + 주로 *NPC*들이 해당 컴포넌트를 가지며, 현재 퀘스트들의 상태 및 전체 퀘스트들을 저장하고 관리합니다.<br>
>
> **7. OptionComponent<br>**
> + 플레이어가 게임을 플레이함에 있어 마우스 감도 및 카메라 확대/축소등을 관리하는 컴포넌트<br>