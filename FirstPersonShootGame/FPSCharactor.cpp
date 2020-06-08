// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharactor.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>
#include "Myproject2.h"
#include "FPSProjectile.h"

// Sets default values
AFPSCharactor::AFPSCharactor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FPSCameraConponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraConponent->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	FPSCameraConponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f + BaseEyeHeight));
	FPSCameraConponent->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCameraConponent);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AFPSCharactor::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Character is in Game now."));
	}
}

// Called every frame
void AFPSCharactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharactor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharactor::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharactor::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharactor::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharactor::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPSCharactor::JumpPressed);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AFPSCharactor::JumpReleased);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharactor::Fire);
}

void AFPSCharactor::MoveForward(float Value)
{
	//得到旋转矩阵，然后得到旋转后新的x轴方向，并在这个方向上进行移动
	//FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	FVector dir = GetActorForwardVector();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, dir.ToString());
	AddMovementInput(dir, Value);
}

void AFPSCharactor::MoveRight(float Value)
{
	//这两句话等价
	//FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	FVector dir = GetActorRightVector();
	AddMovementInput(dir, Value);
}

void AFPSCharactor::JumpPressed()
{
	bPressedJump = true;
}

void AFPSCharactor::JumpReleased()
{
	bPressedJump = false;
}

void AFPSCharactor::Fire()
{
	if (ProjectileClass) {
		FVector CameraLocation;      //相机的世界位置
		FRotator CameraRotation;      //相机的旋转
		GetActorEyesViewPoint(CameraLocation, CameraRotation);  //获得相机的世界位置以及旋转

		//我们想要子弹在镜头前面一点（offset）的位置被发射出去
		//子弹发射位置就等于镜头位置加上经过镜头旋转转换的offset
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		//子弹发射方向就等于镜头旋转的方向
		FRotator MuzzleRotation = CameraRotation;

		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World) {
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;   //暂时不知道是啥
			//用world的方法SpawnActor生成子弹，这个子弹必须是AFPSProjectile或者其子类，具体类别由ProjectileClass通知
			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile) {
				FVector LaunchDir = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDir);
			}
		}
	}
}



