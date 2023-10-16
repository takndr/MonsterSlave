# AIController
보스가 특정 상황마다 다른 행동을 취하기 위해 Behavior Tree를 사용해야하는데, 그렇기 때문에 사용자 정의 AIController를 제작하였음

## Perception
보스가 플레이어를 감지할 때 Sight Perception을 사용하였음

![Perception](https://github.com/takndr/MonsterSlave/assets/126765215/2d0d3b97-d4cb-491c-8155-4b350b7a5d63)



## Blackboard
BehaviorTree를 제어하기 위해 여러가지 Key를 사용하여 원활하게 제어한다

![Blackboard](https://github.com/takndr/MonsterSlave/assets/126765215/9ee5234c-43f9-437c-b335-a6caeeb0eed6)

* PhaseKey : 현재 보스가 몇 페이즈인지 확인하는 Key
* BehaviorKey : 현재 보스가 어떤 행동을 취할지 확인하는 Key
* PhaseChangedKey : 현재 보스가 페이즈 변경이 가능한지 확인하는 Key
* PlayerKey : Sight Perception에서 보스가 감지한 플레이어의 캐릭터 Key
  