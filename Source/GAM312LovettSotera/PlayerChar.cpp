// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChar.h"

// Sets default values
APlayerChar::APlayerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initial Setup of camera component.
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));

	//attaching camerea to character mesh and head bone
	PlayerCamComp->SetupAttachment(GetMesh(), "head");

	//share rotation with controller
	PlayerCamComp->bUsePawnControlRotation = true;


}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle StatsTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, & APlayerChar::DecreaseStats, 2.0f, true);


}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind player movement inputs to their corresponding functions

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerChar::MoveForward);
	// Moves the player character forward or backward depending on input value
	
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerChar::MoveRight);
	// Moves the player character left or right depending on input value
	
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerChar::AddControllerPitchInput);
	// Controls looking up and down by adjusting the controller's pitch
	
	PlayerInputComponent->BindAxis("Turn", this, &APlayerChar::AddControllerYawInput);
	// Controls turning left and right by adjusting the controller's yaw

	// Bind jump input events

	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &APlayerChar::StartJump);
	// Calls StartJump when the jump button is pressed
	
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &APlayerChar::StopJump);
	// Calls StopJump when the jump button is released

	// Bind interaction input
	
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &APlayerChar::FindObject);
	// Calls FindObject when the interact button is released (used to interact with objects)

}

// Function that moves the character forward or backward
void APlayerChar::MoveForward(float axisValue)
{
	// Get the forward direction based on the controller's current rotation
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	// Apply movement input in the forward direction with the strength of axisValue
	AddMovementInput(Direction, axisValue);
}

// Function that moves the character left or right
void APlayerChar::MoveRight(float axisValue)
{
	// Get the right direction based on the controller's current rotation
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

	// Apply movement input in the right direction with the strength of axisValue
	AddMovementInput(Direction, axisValue);
}

// Function called when the jump button is pressed
void APlayerChar::StartJump()
{
	// Sets the jump flag to true, telling the character to start jumping
	bPressedJump = true;
}

// Function called when the jump button is released
void APlayerChar::StopJump()
{
	// Sets the jump flag to false, telling the character to stop jumping
	bPressedJump = false;
}

void APlayerChar::FindObject()
{
}

void APlayerChar::SetHealth(float amount)
{
	if (Health + amount < 100)
		Health = Health + amount;
}

void APlayerChar::SetHunger(float amount)
{
	if (Hunger + amount < 100)
		Hunger = Hunger + amount;
}

void APlayerChar::SetStamina(float amount)
{
	if (Stamina + amount < 100)
		Stamina = Stamina + amount;
}

void APlayerChar::DecreaseStats()
{
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}

	SetStamina(10.0f);

	if (Hunger <= 0)
		SetHealth(-3.0f);
}

