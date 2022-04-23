// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Abilities/GameplayAbility.h"
#include "EOSInputComponent.generated.h"

USTRUCT(BlueprintType)
struct FEOSInputConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UInputAction* InputAction;
	
	UPROPERTY(EditAnywhere)
	FKey Key;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility> Ability;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ONLINETEST_API UEOSInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEOSInputComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const TArray<FEOSInputConfig> InputConfigs, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FEOSInputConfig> InputConfig;

	void InputPressed(const FKey Key, const TSubclassOf<UGameplayAbility> Ability);
	void InputReeased(const FKey Key, const TSubclassOf<UGameplayAbility> Ability);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UEOSInputComponent::BindAbilityActions(const TArray<FEOSInputConfig> InputConfigs, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	for (auto const Config : InputConfigs)
	{
		if (Config.Key.IsValid() && IsValid(Config.Ability))
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Config.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Config.Key, Config.Ability).GetHandle());
			}

			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(Config.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Config.Key, Config.Ability).GetHandle());
			}
		}
	}
}