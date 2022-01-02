// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineDoor"));
	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	//Check if curve asset reference is valid (RUNNING)
	if (FcurveDoor)
	{
		TimeLine->AddInterpFloat(FcurveDoor, InterpFunction, FName("Alpha"));
		//Setting timeline's settings before start
		TimeLine->SetLooping(false);
		TimeLine->SetIgnoreTimeDilation(true);
	}
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::AddKey()
{
	++CurrentKeys;
	if(CurrentKeys == NumKeys && IsClosed)
	{
		OpenDoor();
	}
}

void ADoor::OpenDoor()
{
	IsClosed = false;
	InitialPos = GetActorLocation();
	EndPos = InitialPos + EndOffset;

	if (DoorOpenSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorOpenSound, GetActorLocation(), 1.f, 1.f, 1.8f);

	TimeLine->PlayFromStart();
}

void ADoor::CloseDoor()
{
	IsClosed = true;
	InitialPos = GetActorLocation();
	EndPos = InitialPos - EndOffset;

	if (DoorOpenSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DoorOpenSound, GetActorLocation(), 1.f, 1.f, 1.8f);

	TimeLine->PlayFromStart();
}

void ADoor::TimelineFloatReturn(float const Value)
{
	SetActorLocation(FMath::Lerp(InitialPos, EndPos, Value));
}