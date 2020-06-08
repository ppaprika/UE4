// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "MyCountDOwn.generated.h"

UCLASS()
class LEARNINGCPP_API AMyCountDOwn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCountDOwn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 TimeToCount;

	UTextRenderComponent* TimeShower;

	void UpdateShower() {
		TimeShower->SetText(FString::FromInt(TimeToCount));
	}

	void MyTimer() {
		--TimeToCount;
		if (TimeToCount >= 0) {
			UpdateShower();
		}
		else {
			GetWorldTimerManager().ClearTimer(TimeHandle);
		}
	}

	FTimerHandle TimeHandle;
};
