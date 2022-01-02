// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathDetector.h"
#include "Components/BoxComponent.h"
#include "SurvivalLandCharacter.h"
#include "SurvivalPlayerController.h"

// Sets default values
ADeathDetector::ADeathDetector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCollision;
}

// Called when the game starts or when spawned
void ADeathDetector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathDetector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
