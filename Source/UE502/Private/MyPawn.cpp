#include "MyPawn.h"
#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


AMyPawn::AMyPawn()
{
	PrimaryActorTick.bCanEverTick = false;

    BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
    RootComponent = BoxComp;
    BoxComp->SetSimulatePhysics(false);

    SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
    SkeletalMeshComp->SetupAttachment(RootComponent); 
    SkeletalMeshComp->SetSimulatePhysics(false);

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->TargetArmLength = 300.0f;
    SpringArmComp->bUsePawnControlRotation = true;

    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
    CameraComp->bUsePawnControlRotation = false;
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController()))
        {
            if (PlayerController->MoveAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->MoveAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyPawn::Move
                );
            }

            if (PlayerController->LookAction)
            {
                EnhancedInput->BindAction(
                    PlayerController->LookAction,
                    ETriggerEvent::Triggered,
                    this,
                    &AMyPawn::Look
                );
            
            }
        }
    }
}


void AMyPawn::Move(const FInputActionValue& value)
{
    if (!Controller) return;

    FVector2D MovementVector = value.Get<FVector2D>();

    float DeltaTime = GetWorld()->GetDeltaSeconds();
    float MoveSpeed = 500.0f;

    FVector LocalOffset = FVector(MovementVector.Y * MoveSpeed * DeltaTime, MovementVector.X * MoveSpeed * DeltaTime, 0.0f);

    AddActorLocalOffset(LocalOffset, true);
}

void AMyPawn::Look(const FInputActionValue& value)
{
    if (!Controller) return;

    FVector2D LookAxisVector = value.Get<FVector2D>();

    float DeltaTime = GetWorld()->GetDeltaSeconds();

    float TurnSpeed = 100.0f;

    float PitchInput = LookAxisVector.Y * TurnSpeed * DeltaTime;
    float YawInput = LookAxisVector.X * TurnSpeed * DeltaTime;

    FRotator LocalRotation = FRotator(PitchInput, YawInput, 0.0f);

    AddActorLocalRotation(LocalRotation, true);
}
