// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility_CharacterJump.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "OnlineTest/Component/EOSCameraComponent.h"
#include "OnlineTest/Interface/EOSCharacterInterface.h"
#include "EnhancedInputComponent.h"
#include "OnlineTest/Component/EOSInputComponent.h"

#include "EOSCharacter.generated.h"

USTRUCT(BlueprintType)
struct FEOSInputActor
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditAnywhere)
	FKey Key;
};

UCLASS()
class ONLINETEST_API AEOSCharacter : public ACharacter, public IAbilitySystemInterface, public IEOSCharacterInterface
{
	GENERATED_BODY()

public:
	AEOSCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USpringArmComponent* SpringArm = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCameraComponent* EOSCameraComponent = nullptr;
	

	// GAS
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EOS | GAS")
	TArray<FEOSInputActor> GameplayAbilities;

	
	// Input
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEOSInputComponent* EnhancedInputComponent = nullptr;

	void InputPressed(const FKey Key, const TSubclassOf<UGameplayAbility> Ability);
	
	void InputReleased(const FKey Key, const TSubclassOf<UGameplayAbility> Ability);


	// Interface
public:
	virtual USpringArmComponent* GetCharacterSpringArm() override;
};
