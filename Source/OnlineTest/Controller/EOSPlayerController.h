// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "EOSPlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class ONLINETEST_API AEOSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEOSPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void OnMouseInputMovePressed();
	void OnMouseInputMoveReleased();

private:
	// Input is bring pressed
	bool bInputPressed;
	// For how long it has been pressed
	float FollowTime;
	
	// 单体目标
	UPROPERTY(Replicated)
	APawn* MainSingleTarget = nullptr;

public:
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EOSPC | Config")
	float ShortPressThreshold = 0.3;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EOSPC | Config")
	UNiagaraSystem* FXCursor;

	// 获取主要单体目标
	UFUNCTION(BlueprintCallable, BlueprintPure)
	APawn* GetMainSingleTarget();
	
	// 设置主要单体目标
	UFUNCTION(BlueprintCallable)
	void SetMainSingleTarget(APawn* Target);

	UFUNCTION(Reliable, Server)
	void Server_SetMainSingleTarget(APawn* Target);
	void Server_SetMainSingleTarget_Implementation(APawn* Target);


	// Input
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EOSPC | Input")
	UInputMappingContext* InputMappingContext;
};
