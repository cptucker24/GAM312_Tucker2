// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initial setup of camera component.
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));

	// Attaching camera to the character mesh
	PlayerCamComp->SetupAttachment(GetMesh(), "head");

	// Share rotation with controller
	PlayerCamComp->bUsePawnControlRotation = true;

	ResourcesArray.SetNum(3);
	ResourcesNameArray.Add(TEXT("Wood"));
	ResourcesNameArray.Add(TEXT("Stone"));
	ResourcesNameArray.Add(TEXT("Berry"));
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APlayerChar::DecreasedStats, 2.0f, true);



}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)

// Bind axis inputs for movement and camera control.
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerChar::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput);

	// Bind action inputs for jumping.
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump);
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump);

	// Bind action input for a custom 'Interact' event.
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerChar::FindObject);

}

void APlayerChar::MoveForward(float axisValue)
{
	// Get the forward vector from the controller's rotation and apply movement.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::MoveRight(float axisValue)
{
	// Get the right vector from the controller's rotation and apply movement.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

void APlayerChar::StartJump()
{
	// Sets the 'bPressedJump' flag to true, which is handled by the character's built-in jump logic.
	bPressedJump = true;
}

void APlayerChar::StopJump()
{
	// Sets the 'bPressedJump' flag to false, which stops the jump.
	bPressedJump = false;
}

void APlayerChar::FindObject()
{   // Line trace (raycast) to find interactable objects in front of the player.
	FHitResult HitResult;
	FVector StartLocation = PlayerCamComp->GetComponentLocation();
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f;
	FVector EndLocation = StartLocation + Direction;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true;

	// Perform the line trace and check if it hits an actor of type AResource_M.
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))

	{   // Attempt to cast the hit actor to AResource_M.
		AResource_M* HitResource = Cast<AResource_M>(HitResult.GetActor());

		// If the cast is successful and the player has enough stamina, process resource collection.
		if (Stamina > 5.0f)
		{
			if (HitResource)
			{
				// Retrieve resource details from the hit resource actor.
				FString hitName = HitResource->resourceName;
				int resourceValue = HitResource->resourceAmount;

				// Deduct the resource amount from the total available in the resource actor.
				HitResource->totalResource = HitResource->totalResource - resourceValue;

				// If there are still resources left, give the player the resource and provide feedback.
				if (HitResource->totalResource > resourceValue)
				{
					GiveResource(resourceValue, hitName);

					// Debug message to indicate resource collection.
					check(GEngine != nullptr);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected"));

					// Spawn a decal at the hit location to provide visual feedback.
					UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitDecal, FVector(10.f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f);

					// Reduce player's stamina for the action.
					SetStamina(-5.0f);
				}

		}

		
			else
			{
				// If the resource is depleted, destroy the resource actor and notify the player.
				HitResource->Destroy();
				check(GEngine != nullptr);
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));
			}
		}
	}
}

// Functions to modify player stats, ensuring they do not exceed 100.
void APlayerChar::SetHealth(float amount)
{
	if (Health + amount < 100)
	{
		Health = Health + amount;
	}
}

// Functions to modify player stats, ensuring they do not exceed 100.
void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount < 100)
	{
		Hunger = Hunger + amount;
	}
}

// Functions to modify player stats, ensuring they do not exceed 100.
void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount < 100)
	{
		Stamina = Stamina + amount;
	}
}

// Function to decrease player stats over time.
void APlayerChar::DecreasedStats()
{
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}

	SetStamina(10.0f);

	if (Hunger <= 0)
	{
		SetHealth(-3.0f);
	}
}

// Function to add resources to the player's inventory based on resource type.
void APlayerChar::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood")
	{
		ResourcesArray[0] = ResourcesArray[0] + amount;
	}

	if (resourceType == "Stone")
	{
		ResourcesArray[1] = ResourcesArray[1] + amount;
	}

	if (resourceType == "Berry")
	{
		ResourcesArray[2] = ResourcesArray[2] + amount;
	}
}

