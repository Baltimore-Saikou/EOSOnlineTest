// Fill out your copyright notice in the Description page of Project Settings.


#include "EOSPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

AEOSPlayerController::AEOSPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AEOSPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AEOSPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEOSPlayerController, MainSingleTarget);
}


void AEOSPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	if(bInputPressed)
	{
		FollowTime += DeltaTime;
		
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		
		// Look for the touch location
		FVector const HitLocation = Hit.Location;

		// Direct the Pawn towards that location
		if(GetPawn())
		{
			// 没有这个判断会导致角色在平台跳下时出错, 原地打转
			if (UAIBlueprintHelperLibrary::GetNextNavLinkIndex(this) <= 0)
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
			}
		}
	}
	else
	{
		FollowTime = 0.f;
	}
}

void AEOSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 100);
	}

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AEOSPlayerController::OnMouseInputMovePressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AEOSPlayerController::OnMouseInputMoveReleased);
}

void AEOSPlayerController::OnMouseInputMovePressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
	// Just in case the character was moving because of a previous short press we stop it
	StopMovement();
}

void AEOSPlayerController::OnMouseInputMoveReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if(FollowTime <= ShortPressThreshold)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);
		// We look for the location in the world where the player has pressed the input
		FVector const HitLocation = Hit.Location;

		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, HitLocation);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, HitLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

APawn* AEOSPlayerController::GetMainSingleTarget()
{
	return MainSingleTarget;
}

void AEOSPlayerController::SetMainSingleTarget(APawn* Target)
{
	MainSingleTarget = Target;
	Server_SetMainSingleTarget(Target);
}

void AEOSPlayerController::Server_SetMainSingleTarget_Implementation(APawn* Target)
{
	MainSingleTarget = Target;
}
