// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RegistryOptWindowsBPLibrary.generated.h"

/*
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu.
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

namespace winreg
{
    class RegException;
}

UENUM()
enum ERegistryCategory
{
    Classes_Root,
    Current_User,
    Local_Machine,
    Users,
    Current_Config
};


UCLASS()
class URegistryOptWindowsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()


    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static FString GetDwordValue(ERegistryCategory Category, FString Path, FString Key);
    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static void TrySetDwordValue(ERegistryCategory Category, FString Path, FString Key,int Value);

    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static FString GetQwordValue(ERegistryCategory Category, FString Path, FString Key);
    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static void TrySetQwordValue(ERegistryCategory Category, FString Path, FString Key,int Value);

    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static FString GetStringValue(ERegistryCategory Category, FString Path, FString Key);
    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static void TrySetStringValue(ERegistryCategory Category, FString Path, FString Key,FString Value);

    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static FString GetExpandStringValue(ERegistryCategory Category, FString Path, FString Key);
    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static void TrySetExpandStringValue(ERegistryCategory Category, FString Path, FString Key,FString Value);

    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static TArray<FString> TryGetMultiStringValue(ERegistryCategory Category, FString Path, FString Key);
    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static void TrySetMultiStringValue(ERegistryCategory Category, FString Path, FString Key,TArray<FString> Value);

    UFUNCTION(BlueprintCallable, Category = "RegistryOptWindows")
    static void DeleteRegistryValue(ERegistryCategory Category, FString Path, FString Key);

private:
    static Windows::HKEY GetCategoryByEnum(ERegistryCategory Hkey);
    static std::wstring FStringToStdWString(const FString& InFString);
    static FString StdWStringToFString(const std::wstring& InString);
    static FString StdStringToFString(const std::string& InString);
    // 获取 win api 英文提示消息
    static std::string GetEnglishErrorMessage(DWORD errorCode);
    static void PrintError(const winreg::RegException& e, const FString& Key);
};
