// Copyright Epic Games, Inc. All Rights Reserved.

#include "RegistryOptWindowsBPLibrary.h"

#include "RegistryOptWindows.h"
#include "WinReg.hpp"

URegistryOptWindowsBPLibrary::URegistryOptWindowsBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString URegistryOptWindowsBPLibrary::GetDwordValue(ERegistryCategory Category, FString Path, FString Key)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring QueryKey = FStringToStdWString(Key);
        auto NewDw2 = RegisterKey.GetDwordValue(QueryKey);

        return FString::FromInt(NewDw2);
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }
    return *Key + FString(" not fond.");
}

void URegistryOptWindowsBPLibrary::TrySetDwordValue(ERegistryCategory Category, FString Path, FString Key, int Value)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring SetKey = FStringToStdWString(Key);

        if (RegisterKey.TrySetDwordValue(SetKey, Value).Failed())
        {
            UE_LOG(LogTemp,Warning,TEXT("RegKey::TrySetDwordValue failed"));
        }
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }
}

FString URegistryOptWindowsBPLibrary::GetQwordValue(ERegistryCategory Category, FString Path, FString Key)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring QueryKey = FStringToStdWString(Key);
        auto NewDw2 = RegisterKey.GetQwordValue(QueryKey);

        return FString::FromInt(NewDw2);
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }

    return *Key + FString(" not fond.");
}

void URegistryOptWindowsBPLibrary::TrySetStringValue(ERegistryCategory Category, FString Path, FString Key, FString Value)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring SetKey = FStringToStdWString(Key);
        const std::wstring SetValue = FStringToStdWString(Value);

        if (RegisterKey.TrySetStringValue(SetKey, SetValue).Failed())
        {
            UE_LOG(LogTemp,Warning,TEXT("RegKey::TrySetStringValue failed"));
        }
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }
}

FString URegistryOptWindowsBPLibrary::GetExpandStringValue(ERegistryCategory Category, FString Path, FString Key)
{
    TArray<FString> RetArray;
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring QueryKey = FStringToStdWString(Key);
        auto NewDw2 = RegisterKey.GetExpandStringValue(QueryKey);

        return FString(StdWStringToFString(NewDw2));
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }

    return *Key + FString(" not fond.");
}

void URegistryOptWindowsBPLibrary::TrySetExpandStringValue(ERegistryCategory Category, FString Path, FString Key, FString Value)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring SetKey = FStringToStdWString(Key);
        const std::wstring SetValue = FStringToStdWString(Value);

        if (RegisterKey.TrySetExpandStringValue(SetKey, SetValue).Failed())
        {
            UE_LOG(LogTemp,Warning,TEXT("RegKey::TrySetStringValue failed"));
        }
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }
}

TArray<FString> URegistryOptWindowsBPLibrary::TryGetMultiStringValue(ERegistryCategory Category, FString Path, FString Key)
{
    TArray<FString> RetArray;
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring QueryKey = FStringToStdWString(Key);
        std::vector<std::wstring> NewDw2 = RegisterKey.GetMultiStringValue(QueryKey);

        if (NewDw2.size() > 0)
        {
            for (auto v : NewDw2)
            {
                RetArray.Add(StdWStringToFString(v));
            }
        }
        else
        {
            UE_LOG(LogTemp,Warning,TEXT("GetMultiStringValue failed, not find the key: %s"),*Key);
        }
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }

    return RetArray;
}

void URegistryOptWindowsBPLibrary::TrySetMultiStringValue(ERegistryCategory Category, FString Path, FString Key, TArray<FString> Value)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring SetKey = FStringToStdWString(Key);

        std::vector<std::wstring> SetValue;

        for (auto v : Value)
        {
            SetValue.push_back(FStringToStdWString(v));
        }

        if (RegisterKey.TrySetMultiStringValue(SetKey, SetValue).Failed())
        {
            UE_LOG(LogTemp,Warning,TEXT("RegKey::TrySetMultiStringValue failed"));
        }
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }
}

void URegistryOptWindowsBPLibrary::DeleteRegistryValue(ERegistryCategory Category, FString Path, FString Key)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring SetKey = FStringToStdWString(Key);

        RegisterKey.DeleteValue(SetKey);
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }
}

void URegistryOptWindowsBPLibrary::TrySetQwordValue(ERegistryCategory Category, FString Path, FString Key, int Value)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring SetKey = FStringToStdWString(Key);

        if (RegisterKey.TrySetQwordValue(SetKey, Value).Failed())
        {
            UE_LOG(LogTemp,Warning,TEXT("RegKey::TrySetQwordValue failed"));
        }
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }
}

FString URegistryOptWindowsBPLibrary::GetStringValue(ERegistryCategory Category, FString Path, FString Key)
{
    try
    {
        const auto KeyRet = GetCategoryByEnum(Category);
        const std::wstring RegisterPath(FStringToStdWString(Path));
        winreg::RegKey RegisterKey{ KeyRet, RegisterPath };
        RegisterKey.Open(KeyRet, RegisterPath);

        const std::wstring QueryKey = FStringToStdWString(Key);
        auto NewDw2 = RegisterKey.GetStringValue(QueryKey);

        return FString(StdWStringToFString(NewDw2));
    }
    catch (const winreg::RegException& e)
    {
        PrintError(e,Key);
    }

    return *Key + FString(" not fond.");
}

Windows::HKEY URegistryOptWindowsBPLibrary::GetCategoryByEnum(ERegistryCategory Hkey)
{
    Windows::HKEY HKEY_Ret;
    switch (Hkey)
    {
    case Classes_Root:
        HKEY_Ret = HKEY_CLASSES_ROOT;
        break;
    case Current_User:
        HKEY_Ret = HKEY_CURRENT_USER;
        break;
    case Local_Machine:
        HKEY_Ret = HKEY_LOCAL_MACHINE;
        break;
    case Users:
        HKEY_Ret = HKEY_USERS;
        break;
    case Current_Config:
        HKEY_Ret = HKEY_CURRENT_CONFIG;
        break;
    default:
        HKEY_Ret = HKEY_CURRENT_USER;
    }
    return HKEY_Ret;
}

std::wstring URegistryOptWindowsBPLibrary::FStringToStdWString(const FString& InFString)
{
    // Get the underlying TCHAR array from the FString
    const TCHAR* CharArray = *InFString;

    // Create a new std::wstring using the TCHAR array
    std::wstring Result(CharArray);

    return Result;
}

FString URegistryOptWindowsBPLibrary::StdWStringToFString(const std::wstring& InString)
{
#if PLATFORM_WINDOWS
    return FString(InString.c_str());
#else
    return FString(UTF16_TO_TCHAR(WString.c_str()));
#endif
}

FString URegistryOptWindowsBPLibrary::StdStringToFString(const std::string& InString)
{
    return FString(InString.c_str());
}

std::string URegistryOptWindowsBPLibrary::GetEnglishErrorMessage(DWORD errorCode)
{
    LPVOID lpMsgBuf;
    DWORD languageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

    DWORD result = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        errorCode,
        languageId,
        (LPSTR)&lpMsgBuf,
        0, nullptr);

    if (result == 0) {
        return "Failed to retrieve error message.";
    }

    std::string message((LPCSTR)lpMsgBuf);
    LocalFree(lpMsgBuf);

    return message;
}

void URegistryOptWindowsBPLibrary::PrintError(const winreg::RegException& e, const FString& Key)
{
    std::string ErrorMessage = GetEnglishErrorMessage(e.code().value());

    UE_LOG(LogTemp,Warning,TEXT("[%s] Operate Registry failed: %s"),*Key,*StdStringToFString(ErrorMessage.c_str()));
}

