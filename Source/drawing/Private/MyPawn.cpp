// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#define ECC_FlowmapTraceable ECC_GameTraceChannel1

static const FName PaintActionName = FName(TEXT("Paint"));
static const FName BrushSizeActionName = FName(TEXT("BrushSize"));



// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsPainting = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetRootComponent());

	BrushMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrushMeshComponent"));
	BrushMeshComponent->SetupAttachment(GetRootComponent());

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(BrushSizeActionName, this, &AMyPawn::ChangeBrushSize);

	PlayerInputComponent->BindAction(PaintActionName, IE_Pressed, this, &AMyPawn::BeginPaint);
	PlayerInputComponent->BindAction(PaintActionName, IE_Released, this, &AMyPawn::EndPaint);
}

void AMyPawn::BeginPaint()
{
	bIsPainting = true;
	LastTime = GetWorld()->GetTimeSeconds();
}

void AMyPawn::Paint(const FVector2D& UVPos)
{
	if (!bIsPainting)
	{
		return;
	}

	const float NowTime = GetWorld()->GetTimeSeconds();
	const float DeltaTime = FMath::Max(NowTime - LastTime, 1.0f / 60.0f);

	FVector2D Velocity = ((UVPos - LastUVPos) / DeltaTime).ClampAxes(-1.0f, 1.0f);

	// Pintar la velocidad en el render target

	LastTime = NowTime;
	LastUVPos = UVPos;
}

void AMyPawn::EndPaint()
{
	bIsPainting = false;
}

void AMyPawn::ChangeBrushSize(float Val)
{
	BrushSize += 0.01f * Val;
	BrushSize = FMath::Clamp(BrushSize, 0.01f, 1.5f);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (RenderTarget == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Canvas is null"));
		return;
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	PC->bShowMouseCursor = true;

	// Inicializar el render target con un valor base
}

void AMyPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FHitResult Hit;

	APlayerController* PC = Cast<APlayerController>(GetController());

	FVector2D MouseScreenPos;
	PC->GetMousePosition(MouseScreenPos.X, MouseScreenPos.Y);

	FVector MouseWorldPos, MouseWorldDir;
	UGameplayStatics::DeprojectScreenToWorld(PC, MouseScreenPos, MouseWorldPos, MouseWorldDir);

	const FVector Start = MouseWorldPos;
	const FVector End = Start + 100000.0f * MouseWorldDir;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true; // required for UV

	BrushMeshComponent->SetWorldScale3D(6.5f * FVector(BrushSize, BrushSize, BrushSize));

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_FlowmapTraceable, QueryParams);
	if (bHit)
	{
		FVector2D UV;
		bool bFoundUV = UGameplayStatics::FindCollisionUV(Hit, 0, UV);

		Paint(UV);

		BrushMeshComponent->SetWorldLocationAndRotation(Hit.Location, Hit.Normal.Rotation());
	}
}