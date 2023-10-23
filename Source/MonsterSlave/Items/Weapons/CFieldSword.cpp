#include "Items/Weapons/CFieldSword.h"

#include "Engine/SkeletalMesh.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"

#include "Global.h"


ACFieldSword::ACFieldSword() {
	// Mesh Setting
	StaticMesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));

	// Sphere Collision Setting
	Sphere->SetRelativeLocation(FVector(0.0f, 30.0f, 0.0f));

	// Sprite Setting
	MinimapSprite->SetRelativeRotation(FRotator(90.0f, 0.0f, 90.0f));
	MinimapSprite->SetRelativeScale3D(FVector(0.15f, 0.1f, 0.2f));
}