## 아이템

### 아이템 구조체 구성
> ```
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	FString Name = "NULL";
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	FString Description;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	FString Interact;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	EItemType ItemType;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	EWeaponType WeaponType;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	TSubclassOf<class ACEquipItem> EquipWeaponClass;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	TSubclassOf<class ACFieldItem> FieldWeaponClass;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	UTexture2D* Picture;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	UTexture2D* WeaponIcon;
> 
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	UTexture2D* FirstSkillIcon;
>
> UPROPERTY(BlueprintReadWrite, EditAnywhere)
> 	UTexture2D* SecondSkillIcon;
> ```
> * Name : 아이템의 이름<br>
> * Description : 아이템의 간단한 설명<br>
> * Interact : 필드 아이템 오브젝트와 상호작용할 때의 메시지<br>
> * ItemType : 아이템의 타입<br>
> * WeaponType : 아이템이 무기 일 시 무기 타입<br>
> * EquipWeaponClass : 아이템을 장착할 때 사용하는 오브젝트 레퍼런스<br>
> * FieldWeaponClass : 아이템이 드랍될 때 사용하는 오브젝트 레퍼런스<br>
> * Picture : 인벤토리에서 보여줄 아이템의 사진<br>
> * WeaponIcon : 플레이어 메인 위젯에서 현재 무기를 간단하게 보여줄 아이콘 형태의 Texture<br>
> * FirstSkillIcon : 플레이어 메인 위젯에서 현재 무기의 첫 번째 스킬을 간단하게 보여줄 아이콘 형태의 Texture<br>
> * SecondSkillIcon : 플레이어 메인 위젯에서 현재 무기의 두 번째 스킬을 간단하게 보여줄 아이콘 형태의 Texture<br>


### Equip Weapon vs Field Weapon
플레이어가 장착하는 무기와 필드에 드랍되는 형태의 무기는 서로 다른 역할을 하기 때문에<br>
서로 다른 객체를 사용하여 다르게 활용할 수 있도록 진행하였습니다.<br>
> #### Field Item
> * 플레이어가 착용하는 장비가 아닌 필드에서 일반적으로 볼 수 있는 아이템들<br>플레이어가 근처에 가면 구조체에 있는 Description문구가 출력되게 된다<br>
> ![아이템Description](https://github.com/takndr/MonsterSlave/assets/126765215/42ee8889-bcc5-403d-8fc2-f75ce7fbad6e)<br>
> * 또한 미니맵에서 아이템이 있다는 것을 보여주기 위한 Paper Sprite Component가 포함되어 있다.<br>
> ![스크린샷 2023-10-15 202006](https://github.com/takndr/MonsterSlave/assets/126765215/40f0386e-318c-4797-b7dd-d577d41327ad)<br>
> <미니맵에서 보여지는 스프라이트 이미지><br>
> ![미니맵sprite](https://github.com/takndr/MonsterSlave/assets/126765215/50be5591-4f54-4307-bd63-0b01353cea96)<br>
>
> #### Equip Item
> * 플레이어가 실제가 착용하는 장비<br>
> * 착용하게 되면 플레이어에게 붙을 소켓을 지정해주거나, 공격을 할 때 어떤 몽타주를 사용할지 관리할 수 있다.<br>
> ![스크린샷 2023-10-15 203639](https://github.com/takndr/MonsterSlave/assets/126765215/4fa877c7-9091-43a8-87e6-714b2b71a481)<br>


### Sword vs Bow
아이템이 무기일 경우, 검의 형태인지, 활의 형태인지에 따라 큰 성능은 같아도 세부내용은 조금씩 차이가 있기에<br>
상위 Item을 상속 받아 다르게 함수들을 정의하였습니다.<br>
> #### Sword
> 플레이어가 근거리 공격을 진행할 때 많이 사용할 수 있는 무기
> #### Bow
> 플레이어가 원거리 공격을 진행하고자 할 때 사용할 수 있는 무기