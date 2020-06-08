// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "UObject/UObjectIterator.h"
#include "Kismet/GameplayStatics.h"
#include "RunTime/Engine/Public/EngineUtils.h"

// Sets default values
AMyActor::AMyActor():TotalDamage(200),
DamageTimeInSecond(1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::PostInitProperties()
{
	Super::PostInitProperties();
	DamagePerSecond = TotalDamage / DamageTimeInSecond;
}

void AMyActor::CalculateValues()
{
	DamagePerSecond = TotalDamage / DamageTimeInSecond;
}

#if WITH_EDITOR
void AMyActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	CalculateValues();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

