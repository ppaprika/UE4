// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCountDOwn.h"

// Sets default values
AMyCountDOwn::AMyCountDOwn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeShower = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Shower"));
	TimeShower->SetHorizontalAlignment(EHTA_Center);
	RootComponent = TimeShower;


}

// Called when the game starts or when spawned
void AMyCountDOwn::BeginPlay()
{
	Super::BeginPlay();
	TimeToCount = 5;
	GetWorldTimerManager().SetTimer(TimeHandle, this, &AMyCountDOwn::MyTimer, 1.0f, true);
}

// Called every frame
void AMyCountDOwn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

