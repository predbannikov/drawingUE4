// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#include "MyPawn.generated.h"

UCLASS()
class AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowmapCapture")
	class UTextureRenderTarget2D* RenderTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlowmapCapture")
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlowmapCapture")
	class UStaticMeshComponent* BrushMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FlowmapCapture")
	float BrushSize;

	UFUNCTION(BlueprintCallable, Category = "FlowmapCapture")
	void BeginPaint();

	UFUNCTION(BlueprintCallable, Category = "FlowmapCapture")
	void EndPaint();

	UFUNCTION(BlueprintCallable, Category = "FlowmapCapture")
	void ChangeBrushSize(float Val);

	UFUNCTION(BlueprintCallable, Category = "FlowmapCapture")
	void Paint(const FVector2D& UVPos);

	UFUNCTION(BlueprintPure, Category = "FlowmapCapture")
	FORCEINLINE bool IsPainting() const { return bIsPainting; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bIsPainting;
	FVector2D LastUVPos;
	float LastTime;
};
