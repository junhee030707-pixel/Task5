// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor1.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor1::AMyActor1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor1::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hello from MyActor1!"));
	}
	
	float TotalMoveDistance = 0.f;
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		int r = FMath::RandRange(0, 1);
		if (r == 0)
		{
			Move();
			FVector L = GetActorLocation();
			FString S = FString::Printf(TEXT("count : %d"), count);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, S);
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, L.ToString());
			count++;
		}
		else
		{
			Turn();
			FRotator R = GetActorRotation();
			FString S = FString::Printf(TEXT("Rotation Pitch: %f, Yaw: %f, Roll: %f"), R.Pitch, R.Yaw, R.Roll);

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, R.ToString());
		}

		bool B = FMath::RandBool();
		if (B == true)
		{
			EventFunction();
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("이벤트 발생!!"));
		}
	}
	//10회 이동후에는 총 이동거리와 총 이벤트 발생횟수를 출력 합니다

	TotalMoveDistance = 200.f * count;
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("총 이동거리 : %f"), TotalMoveDistance));
}

void AMyActor1::Move()
{
	float MoveDistance = 200.f;  // 이동 거리

	// 액터가 바라보는 방향
	FVector Forward = GetActorForwardVector();

	// 이동 벡터 = 방향 × 거리
	FVector MoveOffset = Forward * MoveDistance;

	AddActorWorldOffset(MoveOffset, true);

	UE_LOG(LogTemp, Warning, TEXT("Move"));
}

void AMyActor1::Turn()
{
	{
		// -90 ~ +90 도 중 랜덤 회전
		float YawValue = FMath::RandRange(-90.f, 90.f);

		FRotator NewRotation(0.f, YawValue, 0.f);

		AddActorWorldRotation(NewRotation);

		UE_LOG(LogTemp, Warning, TEXT("Turn : %f"), YawValue); //실행됐을 때 화면에 보이진않음(아웃풋로그에 보임)
	}
}
//10회 이동시 각 스텝마다, 50% 확률로 랜덤하게 이벤트가 발생합니다.(발생 시키는 부분도 구현하셔야 합니다.)  
//각  스텝마다 이벤트 발생(이벤트함수를 따로 생성해서 진행해주세요.)여부를 출력합니다.
void AMyActor1::EventFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("이벤트 발생!!"));
}
 
// Called every frame
void AMyActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}