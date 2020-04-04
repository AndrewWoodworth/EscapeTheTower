// Copyright Andrew Woodworth 2019-2020 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "GameFramework/Character.h"
#include "PaperSpriteComponent.h"
#include "Templates/SubclassOf.h"
#include "DefaultCharacter.generated.h"

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
		AActor* ObjectToRotate = nullptr;

	UPROPERTY(BlueprintReadOnly)
		AActor* ActorToGrab = nullptr;

	UPROPERTY(BlueprintReadOnly)
		FRotator PlayerViewPointRotation;

	UPROPERTY(BlueprintReadOnly)
		FVector PlayerViewPointLocation;

	UPROPERTY(BlueprintReadWrite)
		FVector LineTraceEnd;

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
	void UpdateReticle();
	void LoadAssets();

private:
	// Member Variables
	bool bIsRotating = false;
	bool bCanBeGrabbing = false;
	FVector2D ViewportSize;
	float TargetRotation;
	float OriginalActorYaw;
	FRotator ActorRotation;

	float TurnSpeed = 45.f;
	float LookUpSpeed = 45.f;

	UPROPERTY(EditAnyWhere)
		float AmountToRotateObject = 90.f;

	UPROPERTY(EditAnyWhere)
		float PlayerMass = 60.f;

	UPROPERTY(EditAnyWhere)
		float Reach = 200.f;

	UPROPERTY()
		USceneComponent* GrabTransform = nullptr;

	UPROPERTY()
		class UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY()
		class UTexture2D* NotInteractableReticleTexture = nullptr;

	UPROPERTY()
		class UTexture2D* InteractableReticleTexture = nullptr;

	UPROPERTY()
		class UTexture2D* CurrentReticleTexture = nullptr;

	UPROPERTY()
		AHUD* PlayerHUD = nullptr;

	UPROPERTY()
		UPaperSpriteComponent* EToInteractSprite = nullptr;

};
