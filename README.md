# Portfolio - MonsterSlave
개인 포트폴리오 프로젝트 / C++ BluePrint<br>

## 프로젝트 소개
> ![Main](https://github.com/takndr/MonsterSlave/assets/126765215/84b04f6f-68e3-4e9b-bce6-ac0834084905)<br>
> ![Boss](https://github.com/takndr/MonsterSlave/assets/126765215/dd836a5e-9879-4ddc-9bf1-0cc7f39213b3)<br>
> <br>
> 대세 모바일 게임은 원신의 UI를 착안하여 제작하였고<br>
> 몬스터헌터에서 용을 잡는 것을 생각하여 보스를 용으로 설정해보았습니다<br>
> 지금까지의 버전은 게임 시작 후, 기본적인 튜토리얼 느낌으로 제작하였으며<br>
> 현재 제작 중인 레벨은 오픈월드 형태로 거대하게 제작 중에 있습니다.<br>
> 주로 게임을 플레이하면서 사용하는 기능 및 전투 시스템을 확인할 수 있도록 작성하였습니다.<br>
>

## 개발 환경
* Unreal Engine 4.27<br>
* Visual Studio 2019<br>

## 개발 기간 
* 23년 07월 10일 ~ (현재 진행 중)


## 주요 기능(목차)
클릭하면 해당 세부 기능을 확인하실 수 있습니다.

### 사용자 정의 컴포넌트 - [상세보기](https://github.com/takndr/MonsterSlave/blob/main/Md/Component/Component.md)

* 언리얼에서 제공해주는 다양한 컴포넌트들이 존재하지만, 원하는 사용처에 맞게 사용하고자 사용자 정의 컴포넌트를 새로 제작하였습니다.<br>
* 종류는 총 7가지 입니다.<br>


### 플레이어 - [상세보기](https://github.com/takndr/MonsterSlave/blob/main/Md/Player/Player.md)

* 플레이어가 컨트롤 할 수 있는 캐릭터로 이동, 공격, 상호작용등을 진행합니다.<br>
* 공격을 하여 적을 처치하여 본인을 성장 시킬 수도 있고, 이동을 하여 여러가지 맵을 탐험할 수도 있습니다.<br>
* 플레이어는 여러가지 위젯을 통해 본인을 성장하거나, 장비를 착용할 수 있습니다.<br>


### 인벤토리 - [상세보기](https://github.com/takndr/MonsterSlave/blob/main/Md/Inventory/Inventory.md)

* 플레이어가 가지고 있는 위젯 중 하나로, 흔히 가방을 생각하고 제작하였습니다.<br>
* 퀘스트를 클리어하거나, 적을 처치하고 드랍한 아이템을 주워서 관리할 수 있습니다.<br>
* 아이템을 관리할 수 있는 주 위젯이기 때문에, 여러가지 위젯과 델리게이트로 연동되어 있습니다.<br>


### 아이템 - [상세보기](https://github.com/takndr/MonsterSlave/blob/main/Md/Item/Item.md)

* 여러가지 아이템을 관리하기 위해 DataAsset형태로 관리하였습니다.<br>
* DataAsset안에 아이템 구조체를 가지고 있고, 해당 구조체로 아이템이 어떤 형태인지 자유롭게 적용할 수 있습니다.<br>


### 퀘스트 - [상세보기](https://github.com/takndr/MonsterSlave/blob/main/Md/Quest/Quest.md)

* 맵에 있는 NPC들이 퀘스트를 소유하고 있고, 플레이어는 해당 퀘스트를 진행할 수도 아닐 수도 있습니다.<br>
* 아이템과 마찬가지로 여러가지 종류로 관리하기 위해 DataAsset형태로 제작하였고, 퀘스트 구조체로 퀘스트가 어떤 내용인지 자유롭게 작성할 수 있습니다.<br>


### 적군(일반 적, 보스) - [상세보기](https://github.com/takndr/MonsterSlave/blob/main/Md/Enemy/Enemy.md)

* 플레이어가 공격을 통하여 처치할 수 있습니다. 일반 잡몹 3마리와 보스 1마리를 제작해보았습니다.<br>
* 위 적군들은 각각 마다 다른 체력, 속도 등을 가지고 있으며, 잡몹과 보스의 행동능력도 서로 다르게 제작하였습니다.<br>
* 보스의 경우에는 총 3개의 페이즈로 구성되어 있으며, 공격을 피해가며 총 3번의 처치를 해야합니다.<br>

## 데이터 관리

* SaveGame을 이용하여, 게임을 나중에 재시작하여도 현재 플레이어가 가지고 있는 아이템 및 클리어 하거나 진행중인 퀘스트, 스탯등을 저장하고 있습니다.<br>
* 현재 게임에서 저장 시점은 포탈을 타서 맵을 이동할 때 저장하도록 델리게이트 설정을 하였습니다.<br>
* 델리게이트로 지정을 하였기 때문에, 이후 저장 시점을 원하는 대로 지정하고자 할 때 그 시점에서 함수를 바인딩만 하면 되도록 작성하였습니다.<br>