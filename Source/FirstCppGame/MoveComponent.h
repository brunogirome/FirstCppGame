// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MoveComponent.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveComponentReachEndPointSignature, bool, IsTopEndPoint);

UCLASS( ClassGroup=(FirstCppProject), meta=(BlueprintSpawnableComponent) )
class FIRSTCPPGAME_API UMoveComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveComponent();

	UFUNCTION(BlueprintCallable)
	void EnableMovement(bool ShouldMove);

	UFUNCTION(BlueprintCallable)
	void SwitchMovement();

	UFUNCTION(BlueprintCallable)
	void BackToOriginalPosition();

	UFUNCTION(BlueprintCallable)
	void SetMoveDirection(int direction);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	friend class FMoveComponentVisualizer;

	UPROPERTY(EditAnywhere)
	FVector MoveOffset;
	 
	UPROPERTY(EditAnywhere)
	float speed = 1.f;

	UPROPERTY(EditAnywhere)
	bool canItMove = true;

	UPROPERTY(BlueprintAssignable)
	FOnMoveComponentReachEndPointSignature OnEndpointReached;

	FVector StartRelativeLocation;
	FVector MoveOffsetNormalize;

	float maxDistance = 0.f;
	float currentDistance = 0.f;
	short movementDirection = 1;

};
