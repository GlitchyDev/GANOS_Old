// Fill out your copyright notice in the Description page of Project Settings.

#include "GANOS.h"
#include "TestBackgroundActor.h"


// Sets default values
ATestBackgroundActor::ATestBackgroundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Comp"));
    RootComponent = MeshComp;
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObj(TEXT("StaticMesh'/Engine/EngineSky/SM_SkySphere.SM_SkySphere'"));
    UStaticMesh* StaticMesh = (UStaticMesh*)StaticMeshObj.Object;
    
    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialObj(TEXT("Material'/Game/Background_Mat.Background_Mat'"));
    UMaterial* Material = (UMaterial*)MaterialObj.Object;
    
    MeshComp->SetMaterial(0,Material);
    MeshComp->SetStaticMesh(StaticMesh);

    //if(Material != NULL)
    //Mesh->SetMaterial(0,Material);


    // Material'/Game/Background_Mat.Background_Mat'

}

// Called when the game starts or when spawned
void ATestBackgroundActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestBackgroundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // GameState->GetServerWorldTimeSeconds();

    FRotator Rotator = GetActorRotation();
    SetActorRotation(FRotator(PitchAnglePerSecond * UGameplayStatics::GetRealTimeSeconds(GetWorld()),RollAnglePerSecond * UGameplayStatics::GetRealTimeSeconds(GetWorld()),YawAnglePerSecond * UGameplayStatics::GetRealTimeSeconds(GetWorld()) ));
    
    /*
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
     float YawAnglePerSecond;
     
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
     float PitchAnglePerSecond;
     
     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="C++")
     float RollAnglePerSecond;
     
     */
}

