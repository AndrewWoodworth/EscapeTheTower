// Copyright Andrew Woodworth 2019-2020 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "GameFramework/Character.h"
#include "PaperSpriteComponent.h"
#include "Templates/SubclassOf.h"
#include "UObject/Class.h"
#include "DefaultCharacter.generated.h"

USTRUCT(BlueprintType)
struct FObjectToRotate
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY()
	AActor* ActorToRotate;

	UPROPERTY()
	bool bIsRotating;

	UPROPERTY()
	float OriginalActorYaw;

	UPROPERTY()
	float TargetRotation;

	UPROPERTY()
	FRotator ActorRotation;

	UPROPERTY()
	UAudioComponent* AudioComp;

	// Default constructor.
	FObjectToRotate()
	{
		ActorRotation = FRotator(-1.0f);
		ActorToRotate = nullptr;
		AudioComp = nullptr;
		bIsRotating = false;
		OriginalActorYaw = -1.0f;
		TargetRotation = -1.0f;
	}
};

UCLASS()
class BUILDINGESCAPE_API ADefaultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Public Functions
	void Interact();

	// Public variables
	UPROPERTY(BlueprintReadOnly)
	AActor* ActorToGrab = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FRotator PlayerViewPointRotation;

	UPROPERTY(BlueprintReadOnly)
	FVector PlayerViewPointLocation;

	UPROPERTY(BlueprintReadWrite)
	FVector LineTraceEnd;

	UPROPERTY(BlueprintReadWrite)
	TArray<FObjectToRotate> ObjectsToRotate;

	// Return the ending point for line-tracing
	UFUNCTION(BlueprintCallable)
		FVector GetLineTraceEnd();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveBackward(float Value);
	void MoveLeft(float Value);

	void Grab();
	void ReleaseGrabbed();
	void CheckForObjectsToRotate();
	void RotateObjects(float DeltaTime);

private:
	// Member Variables
	bool bIsRotating = false;
	bool bCanBeGrabbing = false;
	float TurnSpeed = 45.f;
	float LookUpSpeed = 45.f;
	float TargetRotation;
	float OriginalActorYaw;
	FRotator ActorRotation;

	UPROPERTY()
	class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY(EditAnyWhere)
	float AmountToRotateActor = 90.f;

	UPROPERTY(EditAnyWhere)
	float PlayerMass = 60.f;

	UPROPERTY(EditAnyWhere)
	float Reach = 200.f;

	UPROPERTY(EditAnyWhere, meta = (category = "Rotatable Actors"))
	int32 NumberOfRotatableActors = 4;

	UPROPERTY()
	USceneComponent* GrabTransform = nullptr;

	UPROPERTY()
	UPaperSpriteComponent* EToInteractSprite = nullptr;

};
