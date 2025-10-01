// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAM312_TUCKER2_API UObjectiveWidget : public UUserWidget
{
	GENERATED_BODY()

	// This class is responsible for updating the objective widget in the UI. (Week Five)
public:
	// Functions to be implemented in Blueprint to update the UI elements. (Week Five)
	UFUNCTION(BlueprintImplementableEvent)
	// 
		void UpdatematOBJ(float matsCollected);

	UFUNCTION(BlueprintImplementableEvent)
		void UpdatebuildObj(float objectsBuilt);
};
