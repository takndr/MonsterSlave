#include "Items/Weapons/CFieldBow.h"

#include "Engine/SkeletalMesh.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"

#include "Global.h"

ACFieldBow::ACFieldBow() {
	// Mesh Setting
	SkeletalMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	// Collision Setting
	Sphere->SetRelativeLocation(FVector(0.0f, -10.0f, 0.0f));

	// Sprite Setting
	MinimapSprite->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	MinimapSprite->SetRelativeScale3D(FVector(0.2f));

}