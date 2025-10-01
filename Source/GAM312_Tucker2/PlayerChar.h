// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Resource_M.h"
#include "Kismet/GameplayStatics.h"
#include "BuildingPart.h"
#include "PlayerWidget.h"
#include "ObjectiveWidget.h"
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

	   // Player Stats
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Player Stats")
	   float Health = 100.0f;
    
	   // Player Stats
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	   float Hunger = 100.0f;

	   // Player Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	   float Stamina = 100.0f;

	   // Resource Inventory
    UPROPERTY(EditAnywhere, Category = "Resources")
       int Wood;

	   // Resource Inventory
    UPROPERTY(EditAnywhere, Category = "Resources")
       int Stone;

	   // Resource Inventory
    UPROPERTY(EditAnywhere, Category = "Resources")
       int Berry;

	   // Resource Inventory Array
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
       TArray<int> ResourcesArray;

	   // Resource Inventory Names
    UPROPERTY(EditAnywhere, Category = "Resources")
       TArray<FString> ResourcesNameArray;

	   // Decal for hit marker
	UPROPERTY(EditAnywhere, Category = "HitMarker")
		UMaterialInterface* hitDecal;

	  // Array to store building IDs and their respective resources.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Supplies")
		TArray<int> BuildingArray;

		// Boolean to track if the player is currently in building mode.
	UPROPERTY()
		bool isBuilding;

		// Class reference for the building part to be spawned.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<ABuildingPart> BuildPartClass;

		// Pointer to the currently spawned building part.
	UPROPERTY()
		ABuildingPart* spawnedPart;

		// Reference to the player UI widget for updating health, hunger, and stamina bars.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPlayerWidget* playerUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UObjectiveWidget* objWidget;

	UPROPERTY()
		float objectsBuilt;

	UPROPERTY()
		float matsCollected;

		// Timer handle for managing the periodic decrease of player stats.
	UFUNCTION(BlueprintCallable)
	   void SetHealth(float amount);

	   // Timer handle for managing the periodic decrease of player stats.
    UFUNCTION(BlueprintCallable)
	   void SetHunger(float amount);

	   // Timer handle for managing the periodic decrease of player stats.
	UFUNCTION(BlueprintCallable)
	   void SetStamina(float amount);

	   // Function to decrease player stats over time.
	UFUNCTION()
	   void DecreasedStats();
	
	   // Timer handle for managing the periodic decrease of player stats.
	UFUNCTION()
		void GiveResource(float amount, FString resourceType);
	
	// Function to update resources when building structures.
	UFUNCTION(BlueprintCallable)
		void UpdateResources(float woodAmount, float stoneAmount, FString buildingObject);

	// Function to spawn a building part based on the provided building ID.
	UFUNCTION(BlueprintCallable)
		void SpawnBuilding(int buildingID, bool& isSuccess);

	// Function to rotate the building part being placed.
	UFUNCTION()
		void RotateBuilding();
};
