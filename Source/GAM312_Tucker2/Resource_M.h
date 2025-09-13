// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Resource_M.generated.h"

UCLASS()
class GAM312_TUCKER2_API AResource_M : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource_M();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Resource Properties
    UPROPERTY(EditAnywhere)
        FString resourceName = "Wood";

		// Amount of resource given to player per interaction
	UPROPERTY(EditAnywhere)
		int resourceAmount = 5;
		
		// Total amount of resource available
	UPROPERTY(EditAnywhere)
		int totalResource = 100;

		// Temporary variable to hold text value
	UPROPERTY()
		FText tempText;

		// Text Render Component to display resource name
	UPROPERTY(EditAnywhere)
		UTextRenderComponent* ResourceNameTxt;

		// Static Mesh Component to represent the resource visually
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Mesh;

	

};
