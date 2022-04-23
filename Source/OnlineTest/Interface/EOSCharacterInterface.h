// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/Interface.h"
#include "EOSCharacterInterface.generated.h"

/** Interface for actors that expose access to an ability system component */
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UEOSCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ONLINETEST_API IEOSCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
	virtual USpringArmComponent* GetCharacterSpringArm() = 0;
};
