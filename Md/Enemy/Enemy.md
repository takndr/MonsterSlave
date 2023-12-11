## 적군(일반 적, 보스)

> ### 1. 일반 적 <br>
>
> #### 일반 적이 가지고 있는 
> **1. PaperSpriteComponent<br>**
> 미니맵에서 적을 표기해주는 스프라이트 이미지<br>
> **2. StautsComponent<br>**
> 일반 적의 체력, 속도 등을 관리하는 컴포넌트<br>
> **3. StateComponent<br>**
> 일반 적이 어떠한 행동을 취할 때, 다른 행동을 할 수 없도록 현재 어떤 상태인지를 컨트롤 할 수 있는 컴포넌트<br>
> **4. WidgetComponent<br>**
> 일반 적의 HP를 실시간으로 확인 할 수 있도록 하는 위젯을 관리하는 컴포넌트<br>
> **5. CapsuleComponent<br>**
> 적이 공격할 때, 데미지를 주기 위한 Collision관련 컴포넌트<br>
>
> * [적 구성]
> * [적 애니메이션 구성]
>
> ### 2. 보스 <br>
>
> #### 보스가 가지고 있는 컴포넌트
> **1. PaperSpriteComponent<br>**
> 미니맵에서 보스를 표기해주는 스프라이트 이미지<br>
> **2. StautsComponent<br>**
> 보스의 체력, 속도 등을 관리하는 컴포넌트<br>
> **3. StateComponent<br>**
> 보스가 어떠한 행동을 취할 때, 다른 행동을 할 수 없도록 현재 어떤 상태인지를 컨트롤 할 수 있는 컴포넌트<br>
> **4. CapsuleComponent<br>**
> 보스가 공격할 때, 데미지를 주기 위한 Collision관련 컴포넌트<br>
>
> * [보스 구성]
> * [보스 애니메이션 구성]
>
> ### 3. AI<br>
>
> #### AI컨트롤러<br>
> 해당 컨트롤러를 가진 캐릭터가 물체를 판별하는 방법은 Sight Perception을 이용하여 감지하도록 설장하였습니다.<br>
> #### BlackBoard<br>
>
> #### BehaviorTree<br>
> 일반 적 BehaviorTree
>
> 보스 BehaviorTree