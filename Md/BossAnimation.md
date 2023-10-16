# Boss애니메이션
보스는 지상에 있을 때와, 공중에 있을 때 두 가지의 기본 모션으로 동작

플레이어와 마찬가지로 각 기본모션은 BlendSpace로 구성되어있으나, 플레이어와 다른점은 2D가 아닌 1D를 사용하여 방향은 고려하지 않았음

![스크린샷 2023-10-16 202910](https://github.com/takndr/MonsterSlave/assets/126765215/3eb01c25-2305-4a4f-8f54-1c8f9ec99fc1)

지상 동작과 공중 동작이 바뀌는 경우는 보스의 페이즈 변경시에 일어나는 Fly변수에 따라 설정이 됨

![스크린샷 2023-10-16 202919](https://github.com/takndr/MonsterSlave/assets/126765215/e2bde33f-e362-4304-b770-ef2c72656f78)

Player와 마찬가지로 여러 몽타주들을 사용할때에는 상반신만 움직일지 혹은 몸 전체가 움직일지에 따라 다르게 블렌딩 작업을 진행함

![스크린샷 2023-10-16 202926](https://github.com/takndr/MonsterSlave/assets/126765215/38eb924a-a43a-4643-8c8e-cb824de7b2b0)
