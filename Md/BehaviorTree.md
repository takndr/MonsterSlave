# BehaviorTree

![behaviorTree](https://github.com/takndr/MonsterSlave/assets/126765215/8e34292a-00be-43a8-be9f-79b77db90577)


## Service
> 보스의 여러가지 행동을 컨트롤 하기 위해, 특정 조건이 달성되면 특정 행동이 실행되게 작성하였음
> 
> Player가 보스의 시야각 30도 정도 안에 없으면 RotateTask가 실행
> 
> Player가 보스와의 거리가 일정 거리 안에 없으면 MoveTask가 실행
> 
> 위 2개도 아니면 AttackTask가 실행



## Task
> 보스의 이동같은 경우에는 내장되어있는 Task를 사용하지만 공격 및 회전, 페이즈 변경 같은 경우에는 여러 조건들이 포함되어 있기 때문에 사용자 설정 Task를 사용하였음
> * AttackTask
>   
>   보스의 공격은 총 3가지로 이루어져 있으며, 각 공격별로 다른 Task를 사용하여 제어하였음
>   
> * RotateTask
>   
>   보스가 Player를 감지하고는 있으나, 현재 Player가 보스의 시야각 외부에 있을 경우, 보스가 볼 수 있는 시야각 내로 적절한 속도로 회전한다.
>   
> * PhaseChangeTask
>   
>   보스의 페이즈를 변경하는 Task