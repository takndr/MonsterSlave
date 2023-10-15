# Item
플레이어가 사용하기 위한 아이템들을 관리하기 위한 구조체
사용자가 직접 사용하기 위한 EquipItem, 필드에서 볼 수 있는 FieldItem으로 분류하여 작성하였다.

##Item Struct
FieldItem과 EquipItem이 같이 공유하는 Item에 들어가는 요소
```
UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Description;

UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Interact;

UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemType ItemType;

UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EWeaponType WeaponType;

UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class ACEquipItem> EquipWeaponClass;

UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Picture;

UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isWeapon;
```
* Name : 아이템의 이름
* Description : 아이템의 간단한 설명
* Interact : 필드 아이템 오브젝트와 상호작용할 때의 메시지
* ItemType : 아이템의 타입
* WeaponType : 아이템이 무기 일 시 무기 타입
* EquipWeaponClass : 아이템을 장착할 때 사용하는 오브젝트 레퍼런스
* Picture : 인벤토리에서 보여줄 아이템의 사진
* isWeapon : 아이템이 무기인지 아닌지 확인하는 변수
  
 ![아이템Struct](https://github.com/takndr/MonsterSlave/assets/126765215/d71ddfba-c5ba-4909-b507-882f5ec3c319)




## Field Item
플레이어가 착용하는 장비가 아닌 필드에서 일반적으로 볼 수 있는 아이템들로써, 플레이어가 근처에 가면 ItemStruct에 있는 Description문구가 출력되게 된다

![아이템Description](https://github.com/takndr/MonsterSlave/assets/126765215/42ee8889-bcc5-403d-8fc2-f75ce7fbad6e)


또한 미니맵에서 아이템이 있다는 것을 보여주기 위한 Paper Sprite Component가 포함되어 있다.

![스크린샷 2023-10-15 202006](https://github.com/takndr/MonsterSlave/assets/126765215/40f0386e-318c-4797-b7dd-d577d41327ad)

<미니맵에서 보여지는 스프라이트 이미지>

![미니맵sprite](https://github.com/takndr/MonsterSlave/assets/126765215/50be5591-4f54-4307-bd63-0b01353cea96)


## Equip Item
플레이어가 실제가 착용하는 장비
착용하게 되면 플레이어에게 붙을 소켓을 지정해주거나, 공격을 할 때 어떤 몽타주를 사용할지 관리할 수 있다.

![스크린샷 2023-10-15 203639](https://github.com/takndr/MonsterSlave/assets/126765215/4fa877c7-9091-43a8-87e6-714b2b71a481)
