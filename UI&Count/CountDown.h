// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "CountDown.generated.h"

UCLASS()
class LEARNINGCPP_API ACountDown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountDown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 CountDownTime;

	UTextRenderComponent* CountDownText;

	void UpdateTimerDisplay();

	void AdvanceTimer();

	void CountDownHasFinished();


	//这个是干嘛的？
	FTimerHandle CountDownTimeHandle;


};
