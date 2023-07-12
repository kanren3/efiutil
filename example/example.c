#include "efi.h"
#include "efilib.h"

VOID
EfiTestProcedure (
    IN OUT VOID *Buffer
)
{
    Print (L"CurrentNumber:%lld\n", GetCurrentProcessorNumber ());
}

EFI_STATUS
UefiMain (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
)
{
    InitializeLib (ImageHandle, SystemTable);

    Print (L"ProcessorNumber:%lld\n", GetActiveProcessNumber ());
    RunProcedureOnAllProcessors (EfiTestProcedure, NULL);
    return EFI_SUCCESS;
}