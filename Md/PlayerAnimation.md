# Player애니메이션
Player는 무기를 착용하지 않은 기본 Unarmed와 여러 무기를 착용했을 때의 기본 모션이 나뉘어져 있음

각 기본 모션은 BlendSpace로 구성하였으며, 방향마다 다르게 모션을 취하게 하기 위해 BlendSpace2D를 사용하였음

![스크린샷 2023-10-16 202620](https://github.com/takndr/MonsterSlave/assets/126765215/f18abf55-654c-41ba-ae10-35fc01770735)

각 무기마다 우클릭 유지 시에 다른 기본 모션이 실행 되도록 설정함

Aim변수는 AnimInstance에서 Tick으로 계속 확인하도록 진행

![스크린샷 2023-10-16 202610](https://github.com/takndr/MonsterSlave/assets/126765215/1120f695-2fba-4875-8584-7ba786fdef2a)

AnimInstance에서 Tick으로 현재 캐릭터의 WeaponType을 받아서 현재 무기에 따라서 기본 모션을 바꿀 수 있게 설정

![스크린샷 2023-10-16 202651](https://github.com/takndr/MonsterSlave/assets/126765215/cc473f3d-2319-46c7-bc38-7d26b89dbb54)

여러 몽타주들을 사용할때에는 상반신만 움직일지 혹은 몸 전체가 움직일지에 따라 다르게 블렌딩 작업을 진행함

![스크린샷 2023-10-16 202702](https://github.com/takndr/MonsterSlave/assets/126765215/1b149aa5-bdbe-489e-b730-6194e1ed634f)
