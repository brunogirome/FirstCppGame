#include "FirstCppGameEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FFirstCppGameEditorModule, FirstCppGameEditor);

 void FFirstCppGameEditorModule::StartupModule()
 {
     // Check if editor is valid
     if (GUnrealEd)
     {
         // Registerin the move visualizer
         TSharedPtr<FMoveComponentVisualizer> MoveVisualizer = MakeShareable(new FMoveComponentVisualizer);
         if (MoveVisualizer.IsValid())
         {
             GUnrealEd->RegisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName(), MoveVisualizer);
             MoveVisualizer->OnRegister();
         }
     }
 }

 void FFirstCppGameEditorModule::ShutdownModule()
 {
     // Check if editor is valid
     if (GUnrealEd)
     {
         GUnrealEd->UnregisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName());
     }
 }