// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "MyKismetRenderingLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UMyKismetRenderingLibrary : public UKismetRenderingLibrary
{
	GENERATED_BODY()

	UMyKismetRenderingLibrary();

	UTextureRenderTarget2D* texture; //


	
};
