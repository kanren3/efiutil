/*++

Copyright (c) 2023  kanren3

Module Name:

    mp.c

Abstract:




Revision History

--*/

#include "lib.h"

VOID
RunProcedureOnAllProcessors (
    IN EFI_GENERAL_PROCEDURE Procedure,
    IN VOID *Context
)
{
    EFI_STATUS Status;

    EFI_MP_SERVICES_PROTOCOL *MpService;

    Status = BS->LocateProtocol (&MultiProcessorProtocol, NULL, &MpService);

    if (EFI_SUCCESS == Status) {
        Procedure (Context);

        Status = MpService->StartupAllAPs (MpService,
                                           Procedure,
                                           TRUE,
                                           NULL,
                                           0,
                                           Context,
                                           NULL);
    }

    ASSERT (EFI_SUCCESS == Status);
}

UINTN EFIAPI
GetActiveProcessNumber (
    VOID
)
{
    EFI_STATUS Status;
    EFI_MP_SERVICES_PROTOCOL *MpService = NULL;
    UINTN NumberOfProcessors = 0;
    UINTN NumberOfEnabledProcessors = 0;

    Status = BS->LocateProtocol (&MultiProcessorProtocol, NULL, &MpService);

    if (EFI_SUCCESS == Status) {
        Status = MpService->GetNumberOfProcessors (MpService,
                                                   &NumberOfProcessors,
                                                   &NumberOfEnabledProcessors);
    }

    ASSERT (EFI_SUCCESS == Status);
    return NumberOfEnabledProcessors;
}

UINTN EFIAPI
GetCurrentProcessorNumber (
    VOID
)
{
    EFI_STATUS Status;
    EFI_MP_SERVICES_PROTOCOL *MpService = NULL;
    UINTN CurrentNumber = 0;

    Status = BS->LocateProtocol (&MultiProcessorProtocol, NULL, &MpService);

    if (EFI_SUCCESS == Status) {
        Status = MpService->WhoAmI (MpService, &CurrentNumber);
    }

    ASSERT (EFI_SUCCESS == Status);
    return CurrentNumber;
}