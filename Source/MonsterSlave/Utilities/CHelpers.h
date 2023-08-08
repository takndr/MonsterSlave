#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

// ---------------------- MACRO ---------------------- //

#define CheckNull(p) { if (p == nullptr) return; }
#define CheckNullResult(p, result) { if (p == nullptr) return result; }

#define CheckTrue(p) { if (p == true) return; }
#define CheckTrueResult(p, result) { if (p == true) return result; }

#define CheckFalse(p) { if (p == false) return; }
#define CheckFalseResult(p, result) { if (p == false) return result; }

// ---------------------- CLASS ---------------------- //

class MONSTERSLAVE_API CHelpers {
public:
	template<typename T>
	static void CreateSceneComponent(AActor* InActor, T** OutComp, FName InName, USceneComponent* InParent = nullptr) {
		*OutComp = InActor->CreateDefaultSubobject<T>(InName);

		if (!!InParent) {
			(*OutComp)->SetupAttachment(InParent);
			return;
		}

		InActor->SetRootComponent(*OutComp);
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComp, FName InName) {
		*OutComp = InActor->CreateDefaultSubobject<T>(InName);
	}

	template<typename T>
	static void GetAsset(T** meshObj, FString InPath) {
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), TEXT("Asset Not Found"));
		
		*meshObj = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** outAsset, FString InPath) {
		T* asset = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
		verifyf(!!asset, TEXT("Asset Not Found"));
		*outAsset = asset;
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* classObj, FString InPath) {
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		verifyf(asset.Succeeded(), TEXT("Class Not Found"));

		*classObj = asset.Class;
	}


};