// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MyProject2GameModeBase.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>

void AMyProject2GameModeBase::StartPlay()
{
	Super::StartPlay();
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World"));
	}
}
