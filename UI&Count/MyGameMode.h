// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Blueprint/UserWidget.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGCPP_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	//删除正在显示的widget，并将新的widget添加到视口
	UFUNCTION(Blueprintcallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:
	virtual void BeginPlay() override;

	//初始主菜单
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	//目前正在显示的widget
	UPROPERTY()
		UUserWidget* CurrentWidget;
	
};
