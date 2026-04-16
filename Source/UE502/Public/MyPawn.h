#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

struct FInputActionValue;

UCLASS()
class UE502_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	AMyPawn();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* BoxComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USkeletalMeshComponent* SkeletalMeshComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UCameraComponent* CameraComp;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void Move(const FInputActionValue& value);
    UFUNCTION()
    void Look(const FInputActionValue& value);
};
