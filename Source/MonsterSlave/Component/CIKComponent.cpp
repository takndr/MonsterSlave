#include "Component/CIKComponent.h"

#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

#include "Global.h"

UCIKComponent::UCIKComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCIKComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void UCIKComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftFootDistance = 0.0f;
	float rightFootDistance = 0.0f;
	FRotator leftFootRotation = FRotator(0.0f);
	FRotator rightFootRotation = FRotator(0.0f);

	Trace(LeftFootSocket, leftFootDistance, leftFootRotation);
	Trace(RightFootSocket, rightFootDistance, rightFootRotation);

	float offset = FMath::Min<float>(leftFootDistance, rightFootDistance);

	CLog::Log("left Distance : " + FString::FromInt(leftFootDistance) + ", Right Distance : " + FString::FromInt(rightFootDistance));

	//CLog::Log("IK offset : " + FString::FromInt(offset));

	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterSpeed);
	Data.LeftFootDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftFootDistance.X, leftFootDistance - offset, DeltaTime, InterSpeed);
	Data.RightFootDistance.X = UKismetMathLibrary::FInterpTo(Data.RightFootDistance.X, rightFootDistance - offset, DeltaTime, InterSpeed);
	Data.LeftFootRotation = UKismetMathLibrary::RInterpTo(Data.LeftFootRotation, leftFootRotation, DeltaTime, InterSpeed);
	Data.RightFootRotation = UKismetMathLibrary::RInterpTo(Data.RightFootRotation, rightFootRotation, DeltaTime, InterSpeed);
}

void UCIKComponent::Trace(FName InSocketName, float& OutDistance, FRotator& OutRotation)
{
	FVector socketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(InSocketName);
	FVector start = FVector(socketLocation.X, socketLocation.Y, OwnerCharacter->GetActorLocation().Z);
	FVector end = FVector(socketLocation.X, socketLocation.Y, OwnerCharacter->GetActorLocation().Z - OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()- Extension);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingle
	(
		GetWorld(),
		start,
		end,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		ignoreActors,
		DebugTrace,
		hitResult,
		false,
		FLinearColor::Green,
		FLinearColor::Red
	);

	CheckFalse(hitResult.IsValidBlockingHit());

	// 지면에 얼마나 박혀있는지 체크 확인 
	float undergroundLength = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();

	// 발이 공중에 떠있는 길이(떠있으면 음수값, 지면에 붙어있으면 0)
	OutDistance = AdjustHeight + undergroundLength - Extension;

	FVector impactNormal = hitResult.ImpactNormal;
	impactNormal.Rotation();
	float pitch = -UKismetMathLibrary::DegAtan2(impactNormal.X, impactNormal.Z);
	float roll = UKismetMathLibrary::DegAtan2(impactNormal.Y, impactNormal.Z);

	// 경사면에 있을 때, 발목이 얼마나 휠지
	OutRotation = FRotator(pitch, 0.0f, roll);
}

