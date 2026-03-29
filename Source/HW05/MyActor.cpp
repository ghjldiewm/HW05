// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h" // Gengine 및 디버깅 메시지 관련 헤더
#include "Math/Color.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyActor::Move(const FVector& Delta) // X, Y, Z
{
	FVector Current = GetActorLocation();
	FVector NewLocation = Current + Delta;
	SetActorLocation(NewLocation);
}

void AMyActor::Turn(float YawDeltaDegree) // Pitch, Yaw, Roll
{
	FRotator Current = GetActorRotation();
	Current.Yaw += YawDeltaDegree;
	SetActorRotation(Current);
}

void AMyActor::RandomMoveAndTurn(/*float MaximumX, float MaximumY, float MaximumYaw*/)
{
	// 정수값으로만 이동, 소수점까지 안움직이게 int로 랜덤
	int32 RandomX = FMath::RandRange(-100, 100); // -100 ~ 100의 난수 생성
	int32 RandomY = FMath::RandRange(-100, 100); // -100 ~ 100의 난수 생성
	int32 RandomYaw = FMath::RandRange(-180, 180); // -180 ~ 180의 난수 생성
	
	FVector RandomMove((float)RandomX, (float)RandomY, 0.f); // 난수는int로 FVector로 받을 땐 float

	Move(RandomMove);
	Turn((float)RandomYaw);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Actor : %s"), *GetActorLocation().ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::Printf(TEXT("Actor : %s"), *GetActorRotation().ToString()));
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello, World!"));

	SetActorLocation(FVector(0.f, 50.f, 0.f));
	/*Move(FVector(0.f, 100.f, 0.f));
	Turn(80.f);*/

	/*FVector ActorLocation = GetActorLocation();
	FRotator ActorRotation = GetActorRotation();*/

	for (int i = 0; i < 10; ++i)
	{
		RandomMoveAndTurn();
	}

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hello UnrealS"));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Actor : %s"), *GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Actor : %s"), *ActorLocation.ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Actor : %s"), *ActorRotation.ToString()));
	}*/

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

