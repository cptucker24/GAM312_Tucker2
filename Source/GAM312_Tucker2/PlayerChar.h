// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerChar.generated.h"

UCLASS()
class GAM312_TUCKER2_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	// Handles forward and backward movement based on input from an axis mapping, typically between -1.0 and 1.0.
	    void MoveForward(float axisValue);

	UFUNCTION()
	// Handles right and left movement based on input from an axis mapping, typically between -1.0 and 1.0.
	    void MoveRight(float axisValue);

    UFUNCTION()
	// Initiates a jump action when the jump input is pressed.
	    void StartJump();
   
    UFUNCTION()
	// Stops the jump action when the jump input is released.
	    void StopJump();

	UFUNCTION()
	// This function will called when the 'Interact' input action is triggered.
	    void FindObject();

    UPROPERTY(VisibleAnywhere)
	// Camera is attached to the player character, makes this component visible in UE5, but cannot be edited. First Person View only.
	UCameraComponent* PlayerCamComp;

};
