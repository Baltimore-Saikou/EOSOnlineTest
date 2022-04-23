// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSInputComponent.h"
#include "EnhancedInputComponent.h"


// Sets default values for this component's properties
UEOSInputComponent::UEOSInputComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEOSInputComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UEOSInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEOSInputComponent::InputPressed(const FKey Key, const TSubclassOf<UGameplayAbility> Ability)
{
	UE_LOG(LogTemp, Warning, TEXT("InputPressed, Key = %s, Ability = %s"), *Key.ToString(), *Ability->GetName())
}

void UEOSInputComponent::InputReeased(const FKey Key, const TSubclassOf<UGameplayAbility> Ability)
{
	UE_LOG(LogTemp, Error, TEXT("InputReeased, Key = %s, Ability = %s"), *Key.ToString(), *Ability->GetName())
}
