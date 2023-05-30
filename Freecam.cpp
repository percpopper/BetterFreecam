// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Engine/ULocalPlayer/GetViewPoint/
void(*OGetViewPoint)(ULocalPlayer*, FMinimalViewInfo*, EStereoscopicPass) = nullptr;
void GetViewPoint(ULocalPlayer* thisLocalPlayer, FMinimalViewInfo* OutViewInfo, EStereoscopicPass StereoPass)
{
  // Call original function setting OutViewInfo (Before modifying it)
  OGetViewPoint(thisLocalPlayer, OutViewInfo, StereoPass);

	static FVector NewLocation;
	if (bFreecam)
	{
		if (PlayerController->IsInputKeyDown(FreecamHotkey))
		{

			PlayerController->SetIgnoreMoveInput(true);

			if (NewLocation == FVector(0, 0, 0))
			{
				NewLocation = OutViewInfo->Location;
			}

			FVector MoveDirection(0, 0, 0);
			if (PlayerController->IsInputKeyDown(WFKey)) MoveDirection.X += fcSpeed;
			if (PlayerController->IsInputKeyDown(SFKey)) MoveDirection.X -= fcSpeed;
			if (PlayerController->IsInputKeyDown(AFKey)) MoveDirection.Y -= fcSpeed;
			if (PlayerController->IsInputKeyDown(DFKey)) MoveDirection.Y += fcSpeed;
			if (PlayerController->IsInputKeyDown(SpaceFKey)) MoveDirection.Z += fcSpeed;
			if (PlayerController->IsInputKeyDown(ShiftFKey)) MoveDirection.Z -= fcSpeed;

			if (MoveDirection.SizeSquared() > 0)
			{
				MoveDirection.Normalize();
				NewLocation += CameraRotation.Quaternion().RotateVector(MoveDirection * fcSpeed);
			}

			OutViewInfo->Location = NewLocation;
			OutViewInfo->Rotation = CameraRotation;
		}
		else
		{
			PlayerController->SetIgnoreMoveInput(false);
			NewLocation = FVector(0, 0, 0);
		}
	}
}   
