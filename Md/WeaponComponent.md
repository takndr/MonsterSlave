# WeaponComponent
캐릭터가 착용하고 있는 무기들을 관리하기 위한 Component
```
  UENUM(BlueprintType)
  enum class EWeaponType : uint8
  {
	  Unarmed, Sword, Bow
  };
```
* Unarmed : 캐릭터가 아무것도 착용하지 않았을 때
* Sword : 캐릭터가 칼을 착용하였을 때
* Bow : 캐릭터가 활을 착용하였을 때

---

캐릭터가 장비를 착용하거나 교체하는 것들을 전부 관리한다