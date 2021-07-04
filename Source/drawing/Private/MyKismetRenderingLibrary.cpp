// Fill out your copyright notice in the Description page of Project Settings.


#include "MyKismetRenderingLibrary.h"

UMyKismetRenderingLibrary::UMyKismetRenderingLibrary()
{
	texture = UKismetRenderingLibrary::CreateRenderTarget2D(this, 512, 512, RTF_R8);
}
