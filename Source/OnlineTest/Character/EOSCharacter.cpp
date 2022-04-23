// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSCharacter.h"
#include "EnhancedInputSubsystems.h"


AEOSCharacter::AEOSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	EOSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("EOSCameraComponent"));
	EOSCameraComponent->SetupAttachment(SpringArm);

	EnhancedInputComponent = CreateDefaultSubobject<UEOSInputComponent>(TEXT("EOSInputComponent"));
}

void AEOSCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (auto const GameplayAbility : GameplayAbilities)
		GetAbilitySystemComponent()->GiveAbility(GameplayAbility.Ability);

	TArray<uint32> BindHandles;
	EnhancedInputComponent->BindAbilityActions(EnhancedInputComponent->InputConfig, this, &ThisClass::InputPressed, &ThisClass::InputReleased, BindHandles);
}

void AEOSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEOSCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	// ASC MixedMode replication requires that the ASC Owner's Owner be the Controller.
	SetOwner(NewController);
}

UAbilitySystemComponent* AEOSCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


// Input

void AEOSCharacter::InputPressed(const FKey Key, const TSubclassOf<UGameplayAbility> Ability)
{
	UE_LOG(LogTemp, Warning, TEXT("InputPressed"))
}

void AEOSCharacter::InputReleased(const FKey Key, const TSubclassOf<UGameplayAbility> Ability)
{
	UE_LOG(LogTemp, Warning, TEXT("InputReeased"))
}


// Interface

USpringArmComponent* AEOSCharacter::GetCharacterSpringArm()
{
	return SpringArm;
}

