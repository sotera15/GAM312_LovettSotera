// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "PlayerChar.generated.h"

UCLASS()
class GAM312LOVETTSOTERA_API APlayerChar : public ACharacter
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

	// Declares a function that handles forward and backward player movement
	UFUNCTION()
		void MoveForward(float axisValue);

	// Declares a function that handles left and right player movement
	UFUNCTION()
		void MoveRight(float axisValue);

	// Declares a function that is called when the player begins a jump action
	UFUNCTION()
		void StartJump();

	// Declares a function that is called when the player releases the jump button
	UFUNCTION()
		void StopJump();

	// Declares a function used to detect or interact with objects in the game world
	UFUNCTION()
		void FindObject();

	// Declares a camera component that represents the player's view in the game
	// VisibleAnywhere allows the camera to be seen in the Unreal Editor but not edited directly
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Hunger = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, Category = "Resources")
		int Wood;

	UPROPERTY(EditAnywhere, Category = "Resources")
		int Stone;

	UPROPERTY(EditAnywhere, Category = "Resources")
		int Berry;

	UPROPERTY(EditAnywhere, BluprintReadWrite, Category = "Resources")
		TAarray<int> ResourceArray;

	UPROPERTY(EditAnywhere, Category = "Resources")
		TArray<FString> ResourceNameArray;

	UFUNCTION(BlueprintCallable)
		void SetHealth(float amount);

	UFUNCTION(BlueprintCallable)
		void SetHunger(float amount);

	UFUNCTION(BlueprintCallable)
		void SetStamina(float amount);

	UFUNCTION()
		void DecreaseStats();

};