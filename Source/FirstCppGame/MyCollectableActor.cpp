// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCollectableActor.h"

// Sets default values
AMyCollectableActor::AMyCollectableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// The root component of the thing
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	RootComponent = StaticMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	BoxCollision->SetupAttachment(StaticMesh);

}

void AMyCollectableActor::Jump(float velocity)
{
	if (!isLaunched) {
		StaticMesh->AddImpulse({ 0.f, 0.f, velocity * 500.f });

		// Start destruction
		SetActorTickEnabled(true);
		isLaunched = true;
	}
}

void AMyCollectableActor::OnComponentBeginOverlap(UBoxComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!isLaunched && OtherActor->IsA(TriggerClass)) {
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "HEY MAN, HEY 50K LIKES", true, { 3, 3 });

		onJumpTrigger.Broadcast(OtherActor, Component);
	}
}

// Called when the game starts or when spawned
void AMyCollectableActor::BeginPlay()
{
	Super::BeginPlay();

	// Setup overlap
	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnComponentBeginOverlap");
	BoxCollision->OnComponentBeginOverlap.Add(DelegateSubscriber);

	// Tick is only need after launched
	SetActorTickEnabled(false);

}

// Called every frame
void AMyCollectableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isLaunched) {
		liveTime -= DeltaTime;

		if (liveTime <= 0.f) {
			Destroy();
		}
	}

}

