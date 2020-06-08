// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Grabber.h"
#include "FirstPersonCharacter.generated.h"

UCLASS()
class BLUEPRINTSTOCPP_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent)
		UGrabber* GetGrabber() const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float Value) {
		FVector dir = GetActorForwardVector();
		dir = dir * Value;
		AddMovementInput(dir);
	}

	UFUNCTION()
	void MoveRight(float Value) {
		FVector dir = GetActorRightVector();
		dir = dir * Value;
		AddMovementInput(dir);
	}

	UFUNCTION()
	void LookUp(float Value) {
		/*
		AController* controller = GetController();
		FRotator rotator = controller->GetControlRotation();
		rotator.Yaw += Value;
		SetActorRotation(rotator);
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
		*/
		AddControllerPitchInput(Value);
	}

	UFUNCTION()
	void Turn(float Value) {
		AddControllerYawInput(Value);
	}

	UFUNCTION()
	void JumpPressed() {
		bPressedJump = true;
	}

	UFUNCTION()
	void JumpRealeased() {
		bPressedJump = false;
	}

	UFUNCTION()
	void Grab() {
		GetGrabber()->Grab();
	}

	UFUNCTION()
	void Release() {
		GetGrabber()->Release();
	}
};
